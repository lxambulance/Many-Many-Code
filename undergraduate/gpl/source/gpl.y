%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* constant */
#define LAB_MIN 1
#define MODIFIED 1
#define UNMODIFIED 0

/* symbol */
#define SYM_UNDEF 0
#define SYM_VAR 1
#define SYM_FUNC 2
#define SYM_TEXT 3
#define SYM_INT 4
#define SYM_LABEL 5

/* tac */ 
#define TAC_UNDEF 0 /* undefine */
#define TAC_ADD 1 /* a=b+c */
#define TAC_SUB 2 /* a=b-c */
#define TAC_MUL 3 /* a=b*c */
#define TAC_DIV 4 /* a=b/c */
#define TAC_EQ 5 /* a=(b==c) */
#define TAC_NE 6 /* a=(b!=c) */
#define TAC_LT 7 /* a=(b<c) */
#define TAC_LE 8 /* a=(b<=c) */
#define TAC_GT 9 /* a=(b>c) */
#define TAC_GE 10 /* a=(b>=c) */
#define TAC_NEG 11 /* a=-b */
#define TAC_COPY 12 /* a=b */
#define TAC_GOTO 13 /* goto a */
#define TAC_IFZ 14 /* ifz b goto a */
#define TAC_BEGINFUNC 15 /* function begin */
#define TAC_ENDFUNC 16 /* function end */
#define TAC_LABEL 17 /* label a */
#define TAC_VAR 18 /* int a */
#define TAC_FORMAL 19 /* formal a */
#define TAC_ACTUAL 20 /* actual a */
#define TAC_CALL 21 /* a=call b */
#define TAC_RETURN 22 /* return a */

/* register */
#define R_UNDEF -1
#define R_FLAG 0
#define R_IP 1
#define R_BP 2
#define R_JP 3
#define R_TP 4
#define R_GEN 5
#define R_NUM 16

/* frame */
#define FORMAL_OFF -4 	/* first formal parameter */
#define OBP_OFF 0 		/* dynamic chain */
#define RET_OFF 4 		/* ret address */
#define LOCAL_OFF 8 		/* local var */

#define max(x,y) ((x)<(y)?(y):(x))
typedef struct GrammerTreeNode{
	char *name;
	int size;
	struct GrammerTreeNode *brother,*son;
}GTN;

typedef struct symb
{
	/*	
		type:SYM_VAR name:abc value:98 offset:-1
		type:SYM_VAR name:bcd value:99 offset:4
		type:SYM_LABEL name:L1/max			
		type:SYM_INT value:1			
		type:SYM_FUNC name:max address:1234		
		type:SYM_TEXT name:"hello" lable:10
	*/
	GTN *now;
	int type;
	int store; /* 0:global, 1:local */
	char *name;
	int offset;
	int value;
	int lable;
	struct tac *address; /* SYM_FUNC */	
	struct symb *next;
} SYMB;

typedef struct tac /* TAC instruction node */
{
	GTN *now;
	struct tac  *next; /* Next instruction */
	struct tac  *prev; /* Previous instruction */
	int op; /* TAC instruction */
	SYMB *a;
	SYMB *b;
	SYMB *c;
} TAC;

typedef struct enode /* Parser expression */
{
	GTN *now;
	struct enode *next; /* For argument lists */
	TAC *tac; /* The code */
	SYMB *ret; /* Where the result is */
} ENODE;

typedef struct keyw
{
	int id;
	char name[100];
} KEYW;

typedef struct regdesc /* Reg descriptor */
{
	struct symb *name; /* Thing in reg */
	int modified; /* If needs spilling */
} REGDESC;

%}

%union
{
	char character;
	char *string;
	SYMB *symb;
	TAC *tac;
	ENODE	*enode;
}

%token FUNC
%token PRINT
%token RETURN
%token CONTINUE
%token IF
%token THEN
%token ELSE
%token FI
%token WHILE
%token FOR
%token DO
%token DONE
%token INT
%token EQ
%token NE
%token LT
%token LE
%token GT
%token GE
%token UMINUS
%token <string> INTEGER
%token <string> IDENTIFIER
%token <string> TEXT

%type <tac> program
%type <tac> function_declaration_list
%type <tac> function_declaration
%type <tac> function
%type <symb> function_head
%type <tac> parameter_list
%type <tac> variable_list
%type <enode> argument_list
%type <enode> expression_list
%type <tac> statement
%type <tac> primary_statement
%type <tac> assignment_statement
%type <enode> expression
%type <tac> print_statement
%type <tac> print_list
%type <tac> print_item
%type <tac> return_statement
%type <tac> null_statement
%type <tac> if_statement
%type <tac> while_statement
%type <tac> for_statement
%type <tac> call_statement
%type <enode> call_expression
%type <tac> block
%type <tac> declaration_list
%type <tac> declaration
%type <tac> statement_list
%type <tac> error

%left EQ NE LT LE GT GE
%left '+' '-'
%left '*' '/'
%right UMINUS

%{
int yylex();
int yyerror(char *str);
int main(int argc, char *argv[]);
SYMB *mkconst(int n);
char *mklstr(int i);
SYMB *mklabel(char *name);
SYMB *get_symb(void);
void free_symb(SYMB *s);
ENODE *get_enode(void);
void free_enode(ENODE *e);
void *safe_malloc(int n);
TAC *mktac(int op, SYMB *a, SYMB *b, SYMB *c);
TAC *join_tac(TAC *c1, TAC *c2);
void insert(SYMB **symbtab, SYMB *sym);
SYMB *lookup(SYMB *symbtab, char *name);
SYMB *getvar(char *name); 
TAC *do_func(SYMB *name,    TAC *args, TAC *code);
TAC *declare_var(char *name);
TAC *declare_para(char *name);
SYMB *declare_func(char *name);
TAC *do_assign(SYMB *var, ENODE *expr);
ENODE *do_bin( int binop, ENODE *expr1, ENODE *expr2);
ENODE *do_cmp( int binop, ENODE *expr1, ENODE *expr2);
ENODE *do_un( int unop, ENODE *expr);
ENODE *do_call_ret(char *name, ENODE *arglist);
TAC *do_call(char *name, ENODE *arglist);
TAC *do_lib(char *name, SYMB *arg);
TAC *do_if(ENODE *expr, TAC *stmt);
TAC *do_test(ENODE *expr, TAC *stmt1, TAC *stmt2);
TAC *do_while(ENODE *expr, TAC *stmt);
TAC *do_for(TAC *pms1,ENODE *expr,TAC *pms2,TAC *stmt);
SYMB *mktext(char *text);
SYMB *mktmp(void);
SYMB *mkvar(char *name);
ENODE *mkenode(ENODE *next, SYMB *ret, TAC *code);
void tac_print(TAC *i);
char *ts(SYMB *s,  char *str);
void error(char *str);
void cg();
void cg_init();
void cg_code(TAC *c);
void cg_bin(char *op, SYMB *a, SYMB *b, SYMB *c);
void cg_cmp(int op, SYMB *a, SYMB *b, SYMB *c);
void cg_copy(SYMB *a, SYMB *b);
void cg_cond(char *op, SYMB *a,  char *l);
void cg_return(SYMB *a);
void cg_data(void);
void cg_str(SYMB *s);
void flush_all(void);
void spill_all(void);
void spill_one(int r);
void load_reg(int r, SYMB *n);
void clear_desc(int r);
void insert_desc(int r, SYMB *n, int mod);
int get_rreg(SYMB *c);
int get_areg(SYMB *b, int cr);
void cg_head();
void cg_lib();
void outputlocalsymboltable(SYMB *func);
GTN *gtn_newnode(const char *s);
GTN *gtn_copynode(GTN *root);
void gtn_calcsize(GTN *root);
void gtn_paint(int x,int y,GTN *root);

int mode;
TAC *tac_first, *tac_last;
int LocalScope, scope;
SYMB *GlobalSymbolTable, *LocalSymbolTable;
int next_tmp;
int next_label;
SYMB *symb_list;
ENODE *enode_list;
int line;
char character;
char token[1000];
REGDESC rdesc[R_NUM];
int tos; /* top of static */
int tof; /* top of frame */
int oof; /* offset of formal */
int oon; /* offset of next frame */
KEYW keywords[100]=
{
	{INT,"int"},
	{PRINT,"print"},
	{RETURN,"return"},
	{CONTINUE,"continue"},
	{IF,"if"},
	{THEN,"then"},
	{ELSE,"else"},
	{FI,"fi"},
	{WHILE,"while"},
	{FOR,"for"},
	{DO,"do"},
	{DONE,"done"},
	{0,""}
};
int hashMo=1000007,hasharg=13;
char *hash[1000007];
int hashkey[1000007];
char hashstr[1000007],top=0;
int hashtable[1000007],NUM=0;
int hash_add(char *s);
GTN *grammertreeroot;
char *sp[5]={"┬","├","└","─","│"};
char map[1000][1000];
int mapline[1000];

%}

%%
program : function_declaration_list
{
	tac_last=$1;
	grammertreeroot=gtn_newnode("program");
	grammertreeroot->son=($1)->now;
}
;

function_declaration_list : function_declaration
{
	GTN *s1=gtn_copynode(($1)->now);
	($$)->now=gtn_newnode("FDL");
	($$)->now->son=s1;
}
| function_declaration_list function_declaration
{
	GTN *s2=gtn_copynode(($2)->now);
	$$=join_tac($1, $2);
	($$)->now=gtn_newnode("FDL");
	($$)->now->son=($1)->now;
	($1)->now->brother=s2;
}
;

function_declaration : function
{
	GTN *s1=gtn_copynode(($1)->now);
	($$)->now=gtn_newnode("FD");
	($$)->now->son=s1;
}
| declaration
{
	GTN *s1=gtn_copynode(($1)->now);
	($$)->now=gtn_newnode("FD");
	($$)->now->son=s1;
}
;

declaration : INT variable_list ';'
{
	GTN *s2=gtn_copynode(($2)->now);
	$$=$2;
	($$)->now=gtn_newnode("declaration");
	GTN *s1=gtn_newnode("INT");
	($$)->now->son=s1;
	s1->brother=s2;
	GTN *s3=gtn_newnode(";");
	s2->brother=s3;
}
;

variable_list : IDENTIFIER
{
	$$=declare_var($1);
	($$)->now=gtn_newnode("VL");
	GTN *s1=gtn_newnode("IDENTIFIER");
	($$)->now->son=s1;	
	GTN *s11=gtn_newnode($1);
	s1->son=s11;
}               
| variable_list ',' IDENTIFIER
{
	GTN *s1=gtn_copynode(($1)->now);
	$$=join_tac($1, declare_var($3));
	($$)->now=gtn_newnode("VL");
	($$)->now->son=s1;
	GTN *s2=gtn_newnode(",");
	s1->brother=s2;
	GTN *s3=gtn_newnode("IDENTIFIER");
	s2->brother=s3;
	GTN *s33=gtn_newnode($3);
	s3->son=s33;
}               
| IDENTIFIER '=' expression
{
	GTN *s3=gtn_copynode(($3)->now);
	$$=declare_var($1);
	$$=join_tac($$,do_assign(getvar($1),$3));
	($$)->now=gtn_newnode("VL");
	GTN *s1=gtn_newnode("IDENTIFIER");
	($$)->now->son=s1;
	GTN *s11=gtn_newnode($1);
	s1->son=s11;
	GTN *s2=gtn_newnode("=");
	s1->brother=s2;
	s2->brother=s3;
}
| variable_list ',' IDENTIFIER '=' expression
{
	GTN *s5=gtn_copynode(($5)->now);
	$$=join_tac($1,declare_var($3));
	$$=join_tac($$,do_assign(getvar($3),$5));
	($$)->now=gtn_newnode("VL");
	($$)->now->son=($1)->now;
	GTN *s2=gtn_newnode(",");
	($1)->now->brother=s2;
	GTN *s3=gtn_newnode("IDENTIFIER");
	s2->brother=s3;
	GTN *s33=gtn_newnode($3);
	s3->son=s33;
	GTN *s4=gtn_newnode("=");
	s3->brother=s4;
	s4->brother=s5;
}
;

function : function_head '(' parameter_list ')' block
{
	$$=do_func($1, $3, $5);
	outputlocalsymboltable($1);
	LocalScope=0; /* Leave local scope. */
	LocalSymbolTable=NULL; /* Clear local symbol table. */
	($$)->now=gtn_newnode("function");
	($$)->now->son=($1)->now;
	GTN *s2=gtn_newnode("(");
	($1)->now->brother=s2;
	if ($3!=NULL) s2->brother=($3)->now;
	GTN *s4=gtn_newnode(")");
	if ($3!=NULL) ($3)->now->brother=s4;
	else s2->brother=s4;
	s4->brother=($5)->now;
}
| error
{
	error("Bad function syntax");
	$$=NULL;
}
;

function_head : IDENTIFIER
{
	$$=declare_func($1);
	LocalScope=1; /* Enter local scope. */
	LocalSymbolTable=NULL; /* Init local symbol table. */
	($$)->now=gtn_newnode("FH");
	GTN *s1=gtn_newnode("IDENTIFIER");
	($$)->now->son=s1;
	GTN *s11=gtn_newnode($1);
	s1->son=s11;
}
;

parameter_list : IDENTIFIER
{
	$$=declare_para($1);
	($$)->now=gtn_newnode("PL");
	GTN *s1=gtn_newnode("IDENTIFIER");
	($$)->now->son=s1;
	GTN *s11=gtn_newnode($1);
	s1->son=s11;
}               
| parameter_list ',' IDENTIFIER
{
	if ($1==NULL) error("Bad statement syntax");
	GTN *s1=gtn_copynode(($1)->now);
	$$=join_tac($1, declare_para($3));
	($$)->now=gtn_newnode("PL");
	($$)->now->son=s1;
	GTN *s2=gtn_newnode(",");
	s1->brother=s2;
	GTN *s3=gtn_newnode("IDENTIFIER");
	s2->brother=s3;
	GTN *s33=gtn_newnode($3);
	s3->son=s33;
}
|
{
	$$=NULL;
}
;

statement : assignment_statement ';'
{
	GTN *s1=gtn_copynode(($1)->now);
	($$)->now=gtn_newnode("statement");
	($$)->now->son=s1;
	GTN *s2=gtn_newnode(";");
	s1->brother=s2;
}
| call_statement ';'
{
	GTN *s1=gtn_copynode(($1)->now);
	($$)->now=gtn_newnode("statement");
	($$)->now->son=s1;
	GTN *s2=gtn_newnode(";");
	s1->brother=s2;
}
| return_statement ';'
{
	GTN *s1=gtn_copynode(($1)->now);
	($$)->now=gtn_newnode("statement");
	($$)->now->son=s1;
	GTN *s2=gtn_newnode(";");
	s1->brother=s2;
}
| print_statement ';'
{
	GTN *s1=gtn_copynode(($1)->now);
	($$)->now=gtn_newnode("statement");
	($$)->now->son=s1;
	GTN *s2=gtn_newnode(";");
	s1->brother=s2;
}
| null_statement ';'
{
	($$)->now=gtn_newnode("statement");
	GTN *s2=gtn_newnode(";");
	($$)->now->son=s2;
}
| if_statement
{
	GTN *s1=gtn_copynode(($1)->now);
	($$)->now=gtn_newnode("statement");
	($$)->now->son=s1;
}
| while_statement
{
	GTN *s1=gtn_copynode(($1)->now);
	($$)->now=gtn_newnode("statement");
	($$)->now->son=s1;
}
| for_statement
{
	GTN *s1=gtn_copynode(($1)->now);
	($$)->now=gtn_newnode("statement");
	($$)->now->son=s1;
}
| block
{
	GTN *s1=gtn_copynode(($1)->now);
	($$)->now=gtn_newnode("statement");
	($$)->now->son=s1;
}
| error
{
	error("Bad statement syntax");
	$$=NULL;
}
;

primary_statement : assignment_statement
{
	GTN *s1=gtn_copynode(($1)->now);
	($$)->now=gtn_newnode("PMS");
	($$)->now->son=s1;
}
| call_statement
{
	GTN *s1=gtn_copynode(($1)->now);
	($$)->now=gtn_newnode("PMS");
	($$)->now->son=s1;
}
| print_statement
{
	GTN *s1=gtn_copynode(($1)->now);
	($$)->now=gtn_newnode("PMS");
	($$)->now->son=s1;
}
| null_statement
{
	($$)->now=gtn_newnode("PMS");
}
| error
{
	error("bad semanteme:expected primary-statement");
	$$=NULL;
}
;

block : '{' declaration_list statement_list '}'
{
	GTN *s3=gtn_copynode(($3)->now);
	$$=join_tac($2, $3);
	($$)->now=gtn_newnode("block");
	GTN *s1=gtn_newnode("{");
	($$)->now->son=s1;
	if ($2!=NULL) {
		s1->brother=($2)->now;
		($2)->now->brother=s3;
	}
	else s1->brother=s3;
	GTN *s4=gtn_newnode("}");
	s3->brother=s4;
}               
;

declaration_list:
{
	$$=NULL;
}
| declaration_list declaration
{
	GTN *s2=gtn_copynode(($2)->now);
	$$=join_tac($1, $2);
	($$)->now=gtn_newnode("DL");
	if ($1==NULL) {
		($$)->now->son=s2;
	}
	else {
		($$)->now->son=($1)->now;
		($1)->now->brother=s2;
	}
}
;

statement_list : statement
{
	GTN *s1=gtn_copynode(($1)->now);
	($$)->now=gtn_newnode("SL");
	($$)->now->son=s1;
}
| statement_list statement
{
	GTN *s2=gtn_copynode(($2)->now);
	$$=join_tac($1, $2);
	($$)->now=gtn_newnode("SL");
	($$)->now->son=($1)->now;
	($1)->now->brother=s2;
}               
;

assignment_statement : IDENTIFIER '=' expression
{
	GTN *s3=gtn_copynode(($3)->now);
	$$=do_assign(getvar($1), $3);
	($$)->now=gtn_newnode("AS");
	GTN *s1=gtn_newnode("IDENTIFIER");
	($$)->now->son=s1;
	GTN *s11=gtn_newnode($1);
	s1->son=s11;
	GTN *s2=gtn_newnode("=");
	s1->brother=s2;
	s2->brother=s3;
}
;

expression : expression '+' expression
{
	GTN *s1=gtn_copynode(($1)->now);
	$$=do_bin(TAC_ADD, $1, $3);
	($$)->now=gtn_newnode("expression");
	($$)->now->son=s1;
	GTN *s2=gtn_newnode("+");
	s1->brother=s2;
	s2->brother=($3)->now;
}
| expression '-' expression
{
	GTN *s1=gtn_copynode(($1)->now);
	$$=do_bin(TAC_SUB, $1, $3);
	($$)->now=gtn_newnode("expression");
	($$)->now->son=s1;
	GTN *s2=gtn_newnode("-");
	s1->brother=s2;
	s2->brother=($3)->now;
}
| expression '*' expression
{
	GTN *s1=gtn_copynode(($1)->now);
	$$=do_bin(TAC_MUL, $1, $3);
	($$)->now=gtn_newnode("expression");
	($$)->now->son=s1;
	GTN *s2=gtn_newnode("*");
	s1->brother=s2;
	s2->brother=($3)->now;
}
| expression '/' expression
{
	GTN *s1=gtn_copynode(($1)->now);
	$$=do_bin(TAC_DIV, $1, $3);
	($$)->now=gtn_newnode("expression");
	($$)->now->son=s1;
	GTN *s2=gtn_newnode("/");
	s1->brother=s2;
	s2->brother=($3)->now;
}
| '-' expression  %prec UMINUS
{
	GTN *s2=gtn_copynode(($2)->now);
	$$=do_un(TAC_NEG, $2);
	($$)->now=gtn_newnode("expression");
	GTN *s1=gtn_newnode("-");
	($$)->now->son=s1;
	s1->brother=s2;
}
| expression EQ expression
{
	GTN *s1=gtn_copynode(($1)->now);
	$$=do_cmp(TAC_EQ, $1, $3);
	($$)->now=gtn_newnode("expression");
	($$)->now->son=s1;
	GTN *s2=gtn_newnode("==");
	s1->brother=s2;
	s2->brother=($3)->now;
}
| expression NE expression
{
	GTN *s1=gtn_copynode(($1)->now);
	$$=do_cmp(TAC_NE, $1, $3);
	($$)->now=gtn_newnode("expression");
	($$)->now->son=s1;
	GTN *s2=gtn_newnode("!=");
	s1->brother=s2;
	s2->brother=($3)->now;
}
| expression LT expression
{
	GTN *s1=gtn_copynode(($1)->now);
	$$=do_cmp(TAC_LT, $1, $3);
	($$)->now=gtn_newnode("expression");
	($$)->now->son=s1;
	GTN *s2=gtn_newnode("<");
	s1->brother=s2;
	s2->brother=($3)->now;
}
| expression LE expression
{
	GTN *s1=gtn_copynode(($1)->now);
	$$=do_cmp(TAC_LE, $1, $3);
	($$)->now=gtn_newnode("expression");
	($$)->now->son=s1;
	GTN *s2=gtn_newnode("<=");
	s1->brother=s2;
	s2->brother=($3)->now;
}
| expression GT expression
{
	GTN *s1=gtn_copynode(($1)->now);
	$$=do_cmp(TAC_GT, $1, $3);
	($$)->now=gtn_newnode("expression");
	($$)->now->son=s1;
	GTN *s2=gtn_newnode(">");
	s1->brother=s2;
	s2->brother=($3)->now;
}
| expression GE expression
{
	GTN *s1=gtn_copynode(($1)->now);
	$$=do_cmp(TAC_GE, $1, $3);
	($$)->now=gtn_newnode("expression");
	($$)->now->son=s1;
	GTN *s2=gtn_newnode(">=");
	s1->brother=s2;
	s2->brother=($3)->now;
}
| '(' expression ')'
{
	GTN *s2=gtn_copynode(($2)->now);
	$$=$2;
	($$)->now=gtn_newnode("expression");
	GTN *s1=gtn_newnode("(");
	($$)->now->son=s1;
	s1->brother=s2;
	GTN *s3=gtn_newnode(")");
	s2->brother=s3;
}               
| INTEGER
{
	$$=mkenode(NULL, mkconst(atoi($1)), NULL);
	($$)->now=gtn_newnode("expression");
	GTN *s1=gtn_newnode("INTEGER");
	($$)->now->son=s1;
	GTN *s11=gtn_newnode($1);
	s1->son=s11;
}
| IDENTIFIER
{
	$$=mkenode(NULL, getvar($1), NULL);
	($$)->now=gtn_newnode("expression");
	GTN *s1=gtn_newnode("IDENTIFIER");
	($$)->now->son=s1;
	GTN *s11=gtn_newnode($1);
	s1->son=s11;
}
| call_expression
{
	GTN *s1=gtn_copynode(($1)->now);
	$$=$1;
	($$)->now=gtn_newnode("expression");
	($$)->now->son=s1;
}               
| error
{
	error("Bad expression syntax");
	$$=mkenode(NULL, NULL, NULL);
}
;

argument_list:
{
	$$=NULL;
}
| expression_list
{
	GTN *s1=gtn_copynode(($1)->now);
	($$)->now=gtn_newnode("AL");
	($$)->now->son=s1;
}
;

expression_list : expression
{
	GTN *s1=gtn_copynode(($1)->now);
	($$)->now=gtn_newnode("EL");
	($$)->now->son=s1;
}
|  expression_list ',' expression
{
	GTN *s3=gtn_copynode(($3)->now);
	$3->next=$1;
	$$=$3;
	($$)->now=gtn_newnode("EL");
	($$)->now->son=($1)->now;
	GTN *s2=gtn_newnode(",");
	($1)->now->brother=s2;
	s2->brother=s3;
}
;

print_statement : PRINT '(' print_list ')'
{
	GTN *s3=gtn_copynode(($3)->now);
	$$=$3;
	($$)->now=gtn_newnode("PTS");
	GTN *s1=gtn_newnode("PRINT");
	($$)->now->son=s1;
	GTN *s2=gtn_newnode("(");
	s1->brother=s2;
	s2->brother=s3;
	GTN *s4=gtn_newnode(")");
	s3->brother=s4;
}
;

print_list : print_item
{
	GTN *s1=gtn_copynode(($1)->now);
	($$)->now=gtn_newnode("print_list");
	($$)->now->son=s1;
}
| print_list ',' print_item
{
	GTN *s3=gtn_copynode(($3)->now);
	$$=join_tac($1, $3);
	($$)->now=gtn_newnode("print_list");
	($$)->now->son=($1)->now;
	GTN *s2=gtn_newnode(",");
	($1)->now->brother=s2;
	s2->brother=s3;
}               
;

print_item : expression
{
	GTN *s1=gtn_copynode(($1)->now);
	$$=join_tac($1->tac,
	do_lib("PRINTN", $1->ret));
	($$)->now=gtn_newnode("print_item");
	($$)->now->son=s1;
}
| TEXT
{
	$$=do_lib("PRINTS", mktext($1));
	($$)->now=gtn_newnode("print_item");
	GTN *s1=gtn_newnode("TEXT");
	($$)->now->son=s1;
	GTN *s11=gtn_newnode($1);
	s1->son=s11;
}
;

return_statement : RETURN expression
{
	GTN *s2=gtn_copynode(($2)->now);
	TAC *t=mktac(TAC_RETURN, $2->ret, NULL, NULL);
	t->prev=$2->tac;
	free_enode($2);
	$$=t;
	($$)->now=gtn_newnode("return_statement");
	GTN *s1=gtn_newnode("RETURN");
	($$)->now->son=s1;
	s1->brother=s2;
}               
;

null_statement : CONTINUE
{
	$$=NULL;
}               
;

if_statement : IF '(' expression ')' block
{
	GTN *s3=gtn_copynode(($3)->now);
	$$=do_if($3, $5);
	($$)->now=gtn_newnode("if_statement");
	GTN *s1=gtn_newnode("IF");
	($$)->now->son=s1;
	GTN *s2=gtn_newnode("(");
	s1->brother=s2;
	s2->brother=s3;
	GTN *s4=gtn_newnode(")");
	s3->brother=s4;
	s4->brother=($5)->now;
}
| IF '(' expression ')' block ELSE block
{
	GTN *s3=gtn_copynode(($3)->now);
	$$=do_test($3, $5, $7);
	($$)->now=gtn_newnode("if_statement");
	GTN *s1=gtn_newnode("IF");
	($$)->now->son=s1;
	GTN *s2=gtn_newnode("(");
	s1->brother=s2;
	s2->brother=s3;
	GTN *s4=gtn_newnode(")");
	s3->brother=s4;
	s4->brother=($5)->now;
	GTN *s6=gtn_newnode("ELSE");
	($5)->now->brother=s6;
	s6->brother=($7)->now;
}
;

while_statement : WHILE '(' expression ')' block
{
	GTN *s3=gtn_copynode(($3)->now);
	$$=do_while($3, $5);
	($$)->now=gtn_newnode("while_statement");
	GTN *s1=gtn_newnode("WHILE");
	($$)->now->son=s1;
	GTN *s2=gtn_newnode("(");
	s1->brother=s2;
	s2->brother=s3;
	GTN *s4=gtn_newnode(")");
	s3->brother=s4;
	s4->brother=($5)->now;
}
;

for_statement : FOR '(' primary_statement ';' expression ';' primary_statement ')' block
{
	GTN *s5=gtn_copynode(($5)->now);
	$$=do_for($3,$5,$7,$9);
	($$)->now=gtn_newnode("for_statement");
	GTN *s1=gtn_newnode("FOR");
	($$)->now->son=s1;
	GTN *s2=gtn_newnode("(");
	s1->brother=s2;
	s2->brother=($3)->now;
	GTN *s4=gtn_newnode(";");
	($3)->now->brother=s4;
	s4->brother=s5;
	GTN *s6=gtn_newnode(";");
	s5->brother=s6;
	s6->brother=($7)->now;
	GTN *s8=gtn_newnode(")");
	($7)->now->brother=s8;
	s8->brother=($9)->now;
}
;

call_statement : IDENTIFIER '(' argument_list ')'
{
	
	GTN *s3=gtn_copynode(($3)->now);
	$$=do_call($1, $3);
	($$)->now=gtn_newnode("call_statement");
	GTN *s1=gtn_newnode("IDENTIFIER");
	($$)->now->son=s1;
	GTN *s11=gtn_newnode($1);
	s1->son=s11;
	GTN *s2=gtn_newnode("(");
	s1->brother=s2;
	s2->brother=s3;
	GTN *s4=gtn_newnode(")");
	s3->brother=s4;
}
;

call_expression : IDENTIFIER '(' argument_list ')'
{
	GTN *s3=gtn_copynode(($3)->now);
	$$=do_call_ret($1, $3);
	($$)->now=gtn_newnode("call_expression");
	GTN *s1=gtn_newnode("IDENTIFIER");
	($$)->now->son=s1;
	GTN *s11=gtn_newnode($1);
	s1->son=s11;
	GTN *s2=gtn_newnode("(");
	s1->brother=s2;
	s2->brother=s3;
	GTN *s4=gtn_newnode(")");
	s3->brother=s4;
}
;


%%

GTN *gtn_newnode(const char *s){
	GTN *ret=(GTN *)malloc(sizeof(GTN));
	ret->name=malloc(strlen(s)+1);
	memcpy(ret->name,s,strlen(s)+1);
	ret->brother=ret->son=NULL;
	return ret;
}
GTN *gtn_copynode(GTN *root){
	GTN *ret=(GTN *)malloc(sizeof(GTN));
	*ret=*root;
	return ret;
}

TAC *reverse_tac(TAC *code){
	TAC *p=NULL,*q=code;
	while (q!=NULL) {
		TAC *tmp=q->prev;
		q->prev=p;
		if (p!=NULL) p->next=q;
		p=q;
		q=tmp;
	}
	if (p!=NULL) p->next=NULL;
	return p;
}

TAC *do_func(SYMB *func, TAC *args, TAC *code)
{
	TAC *tlist; /* The backpatch list */

	TAC *tlab; /* Label at start of function */
	TAC *tbegin; /* BEGINFUNC marker */
	TAC *tend; /* ENDFUNC marker */

	tlab=mktac(TAC_LABEL, mklabel(func->name), NULL, NULL);
	tbegin=mktac(TAC_BEGINFUNC, NULL, NULL, NULL);
	tend=mktac(TAC_ENDFUNC,   NULL, NULL, NULL);

	tbegin->prev=tlab;
	args=reverse_tac(args);
	code=join_tac(args, code);
	tend->prev=join_tac(tbegin, code);

	return tend;
}

SYMB *mktmp(void)
{
	SYMB *sym;
	char *name;

	name=safe_malloc(12);
	sprintf(name, "t%d", next_tmp++); /* Set up text */
	return mkvar(name);
}

SYMB *mkvar(char *name)
{
	SYMB *sym=NULL;

	if(LocalScope)  
		sym=lookup(LocalSymbolTable,name);
	else
		sym=lookup(GlobalSymbolTable,name);

	/* var already declared */
	if(sym!=NULL)
	{
		error("variable already declared");
		return NULL;
	}

	/* var unseen before, set up a new symbol table node, insert it into the symbol table. */
	sym=get_symb();
	sym->type=SYM_VAR;
	sym->name=name; /* ysj */
	sym->offset=-1; /* Unset address */

	if(LocalScope)  
		insert(&LocalSymbolTable,sym);
	else
		insert(&GlobalSymbolTable,sym);

	return sym;
}

TAC *declare_var(char *name)
{
	return mktac(TAC_VAR,mkvar(name),NULL,NULL);
}

TAC *declare_para(char *name)
{
	return mktac(TAC_FORMAL,mkvar(name),NULL,NULL);
}

SYMB *declare_func(char *name)
{
	SYMB *sym=NULL;

	sym=lookup(GlobalSymbolTable,name);

	/* name used before declared */
	if(sym!=NULL)
	{
		if(sym->type==SYM_FUNC)
		{
			error("func already declared");
			return NULL;
		}

		if(sym->type !=SYM_UNDEF)
		{
			error("func name already used");
			return NULL;
		}

		return sym;
	}
	
	
	sym=get_symb();
	sym->type=SYM_FUNC;
	sym->name=name;
	sym->address=NULL;

	insert(&GlobalSymbolTable,sym);
	return sym;
}

TAC *do_assign(SYMB *var, ENODE *expr)
{
	TAC *code;

	if(var->type !=SYM_VAR) error("assignment to non-variable");

	code=mktac(TAC_COPY, var, expr->ret, NULL);
	code->prev=expr->tac;
	if (expr->tac!=NULL) expr->tac->next=code;

	free_enode(expr); /* Expression now finished with */

	return code;
}

ENODE *do_bin( int binop, ENODE *expr1, ENODE *expr2)
{
	TAC *temp; /* TAC code for temp symbol */
	TAC *ret; /* TAC code for result */

	if((expr1->ret->type==SYM_INT) && (expr2->ret->type==SYM_INT))
	{
		int newval; /* The result of constant folding */

		switch(binop) /* Chose the operator */
		{
			case TAC_ADD:
			newval=expr1->ret->value + expr2->ret->value;
			break;

			case TAC_SUB:
			newval=expr1->ret->value - expr2->ret->value;
			break;

			case TAC_MUL:
			newval=expr1->ret->value * expr2->ret->value;
			break;

			case TAC_DIV:
			newval=expr1->ret->value / expr2->ret->value;
			break;
		}

		expr1->ret=mkconst(newval); /* New space for result */
		free_enode(expr2); /* Release space in expr2 */

		return expr1; /* The new expression */
	}

	temp=mktac(TAC_VAR, mktmp(), NULL, NULL);
	temp->prev=join_tac(expr1->tac, expr2->tac);
	ret=mktac(binop, temp->a, expr1->ret, expr2->ret);
	ret->prev=temp;

	expr1->ret=temp->a;
	expr1->tac=ret;
	free_enode(expr2);

	return expr1;  
}   

ENODE *do_cmp( int binop, ENODE *expr1, ENODE *expr2)
{
	TAC *temp; /* TAC code for temp symbol */
	TAC *ret; /* TAC code for result */

	if((expr1->ret->type==SYM_INT) && (expr2->ret->type==SYM_INT))
	{
		int newval; /* The result of constant folding */

		switch(binop) /* Chose the operator */
		{
			case TAC_EQ:
			newval=(expr1->ret->value==expr2->ret->value);
			break;
			
			case TAC_NE:
			newval=(expr1->ret->value !=expr2->ret->value);
			break;
			
			case TAC_LT:
			newval=(expr1->ret->value < expr2->ret->value);
			break;
			
			case TAC_LE:
			newval=(expr1->ret->value <=expr2->ret->value);
			break;
			
			case TAC_GT:
			newval=(expr1->ret->value > expr2->ret->value);
			break;
			
			case TAC_GE:
			newval=(expr1->ret->value >=expr2->ret->value);
			break;
		}

		expr1->ret=mkconst(newval); /* New space for result */
		free_enode(expr2); /* Release space in expr2 */
		return expr1; /* The new expression */
	}

	temp=mktac(TAC_VAR, mktmp(), NULL, NULL);
	temp->prev=join_tac(expr1->tac, expr2->tac);
	ret=mktac(binop, temp->a, expr1->ret, expr2->ret);
	ret->prev=temp;

	expr1->ret=temp->a;
	expr1->tac=ret;
	free_enode(expr2);

	return expr1;  
}   

ENODE *do_un( int unop, ENODE *expr) 
{
	TAC *temp; /* TAC code for temp symbol */
	TAC *ret; /* TAC code for result */

	/* Do constant folding if possible. Calculate the constant into expr */
	if(expr->ret->type==SYM_INT)
	{
		switch(unop) /* Chose the operator */
		{
			case TAC_NEG:
			expr->ret->value=- expr->ret->value;
			break;
		}

		return expr; /* The new expression */
	}

	temp=mktac(TAC_VAR, mktmp(), NULL, NULL);
	temp->prev=expr->tac;
	ret=mktac(unop, temp->a, expr->ret, NULL);
	ret->prev=temp;

	expr->ret=temp->a;
	expr->tac=ret;

	return expr;   
}

TAC *do_call(char *name, ENODE *arglist)
{
	ENODE  *alt; /* For counting args */
	TAC *code; /* Resulting code */
	TAC *temp; /* Temporary for building code */

	code=NULL;
	for(alt=arglist; alt !=NULL; alt=alt->next) code=join_tac(alt->tac,code);

	TAC *last=NULL;
	while(arglist !=NULL) /* Generate ARG instructions */
	{
		temp=mktac(TAC_ACTUAL, arglist->ret, NULL, NULL);
		temp->next=last;
		if (last!=NULL) last->prev=temp;
		last=temp;

		alt=arglist->next;
		free_enode(arglist); /* Free the space */
		arglist=alt;
	};
	if (last!=NULL) {
		last->prev=code;
		code->next=last;
	}
	while (code->next!=NULL) code=code->next;

	temp=mktac(TAC_CALL, NULL, (SYMB *)strdup(name), NULL);
	temp->prev=code;
	code=temp;

	return code;
}

ENODE *do_call_ret(char *name, ENODE *arglist)
{
	ENODE  *alt; /* For counting args */
	SYMB *ret; /* Where function result will go */
	TAC *code; /* Resulting code */
	TAC *temp; /* Temporary for building code */

	ret=mktmp(); /* For the result */
	code=mktac(TAC_VAR, ret, NULL, NULL);

	for(alt=arglist; alt !=NULL; alt=alt->next) code=join_tac(alt->tac,code);

	TAC *last=NULL;
	while(arglist !=NULL) /* Generate ARG instructions */
	{
		temp=mktac(TAC_ACTUAL, arglist->ret, NULL, NULL);
		temp->next=last;
		if (last!=NULL) last->prev=temp;
		last=temp;

		alt=arglist->next;
		free_enode(arglist); /* Free the space */
		arglist=alt;
	};
	if (last!=NULL) {
		last->prev=code;
		code->next=last;
	}
	while (code->next!=NULL) code=code->next;

	temp=mktac(TAC_CALL, ret, (SYMB *)strdup(name), NULL);
	temp->prev=code;
	code=temp;

	return mkenode(NULL, ret, code);
}

TAC *do_lib(char *name, SYMB *arg)
{
        TAC *a=mktac(TAC_ACTUAL, arg, NULL, NULL);
        TAC *c=mktac(TAC_CALL, NULL, (SYMB *)strdup(name), NULL);
        c->prev=a;
        return c;
}

TAC *do_if(ENODE *expr, TAC *stmt)
{
	TAC *label=mktac(TAC_LABEL, mklabel(mklstr(next_label++)), NULL, NULL);
	TAC *code=mktac(TAC_IFZ, label->a, expr->ret, NULL);

	code->prev=expr->tac;
	expr->tac->next=code;
	code=join_tac(code, stmt);
	label->prev=code;
	code->next=label;

	free_enode(expr); /* Expression finished with */

	return label;
}

TAC *do_test(ENODE *expr, TAC *stmt1, TAC *stmt2)
{
	TAC *label1=mktac(TAC_LABEL, mklabel(mklstr(next_label++)), NULL, NULL);
	TAC *label2=mktac(TAC_LABEL, mklabel(mklstr(next_label++)), NULL, NULL);
	TAC *code1=mktac(TAC_IFZ, label1->a, expr->ret, NULL);
	TAC *code2=mktac(TAC_GOTO, label2->a, NULL, NULL);

	code1->prev=expr->tac; /* Join the code */
	code1=join_tac(code1, stmt1);
	code2->prev=code1;
	label1->prev=code2;
	label1=join_tac(label1, stmt2);
	label2->prev=label1;

	free_enode(expr); /* Free the expression */

	return label2;
}

TAC *do_while(ENODE *expr, TAC *stmt) 
{
	TAC *label=mktac(TAC_LABEL, mklabel(mklstr(next_label++)), NULL, NULL);
	TAC *code=mktac(TAC_GOTO, label->a, NULL, NULL);

	code->prev=stmt; /* Bolt on the goto */
	stmt->next=code;

	return join_tac(label, do_if(expr, code));
}

TAC *do_for(TAC *pms1,ENODE *expr,TAC *pms2,TAC *stmt){
	TAC *label=mktac(TAC_LABEL,mklabel(mklstr(next_label++)),NULL,NULL);
	TAC *code=mktac(TAC_GOTO,label->a,NULL,NULL);

	label->prev=pms1;
	if (pms1!=NULL) pms1->next=label;
	TAC *tmp=pms2;
	while (tmp->prev!=NULL) tmp=tmp->prev;
	if (pms2!=NULL) {
		tmp->prev=stmt;
		stmt->next=tmp;
		stmt=pms2;
	}
	code->prev=stmt;
	stmt->next=code;

	return join_tac(label,do_if(expr,code));
}

SYMB *getvar(char *name)
{
	SYMB *sym=NULL; /* Pointer to looked up symbol */

	if(LocalScope) sym=lookup(LocalSymbolTable,name);

	if(sym==NULL) sym=lookup(GlobalSymbolTable,name);

	if(sym==NULL)
	{
		error("name not declared as local/global variable");
		return NULL;
	}

	if(sym->type!=SYM_VAR)
	{
		error("not a variable");
		return NULL;
	}

	return sym;
} 

ENODE *mkenode(ENODE *next, SYMB *ret, TAC *code)
{
	ENODE *expr=get_enode();

	expr->next=next;
	expr->ret=ret;
	expr->tac=code;

	return expr;
}

SYMB *mktext(char *text)
{
	SYMB *sym=NULL; /* Pointer to looked up symbol */

	sym=lookup(GlobalSymbolTable,text);

	/* text already used */
	if(sym!=NULL)
	{
		return sym;
	}

	/* text unseen before, set up a new symbol table node, insert it into the symbol table. */
	sym=get_symb();
	sym->type=SYM_TEXT;
	sym->name=text; /* ysj */
	sym->lable=next_label++; /* ysj */

	insert(&GlobalSymbolTable,sym);
	return sym;
}

SYMB *mkconst(int n)
{
	SYMB *c=get_symb(); /* Create a new node */

	c->type=SYM_INT;
	c->value=n; /* ysj */
	return c;
}     

char *mklstr(int i)
{
	char lstr[100]="L";
	sprintf(lstr,"L%d",i);
	return(strdup(lstr));	
}

SYMB *mklabel(char *name)
{
	SYMB *t=get_symb();

	t->type=SYM_LABEL;
	t->name=strdup(name);

	return t;
}  

SYMB *get_symb(void)
{
	SYMB *t;

	if(symb_list !=NULL)
	{
		t=symb_list;
		symb_list=symb_list->next;
	}
	else t=(SYMB *)safe_malloc(sizeof(SYMB));

	return t;
}     


void free_symb(SYMB *s)
{
	s->next=symb_list;
	symb_list=s;
} 


ENODE *get_enode(void)
{
	if(enode_list !=NULL)
	{
		ENODE *expr;
		expr=enode_list;
		enode_list=expr->next;
		return expr;
	}
	else return (ENODE *)safe_malloc(sizeof(ENODE));
}  

void free_enode(ENODE *expr)
{
	expr->next=enode_list;
	enode_list=expr;
} 

void *safe_malloc(int n)
{
	void *t=(void *)malloc(n);

	if(t==NULL)
	{
		/* We can't use printf to put the message out here, since it calls malloc, which will fail because that's why we're here... */
		error("malloc() failed");
		exit(0);
	}

	return t;
}      

TAC *mktac(int op, SYMB *a, SYMB *b, SYMB *c)
{
	TAC *t=(TAC *)safe_malloc(sizeof(TAC));

	t->next=NULL; /* Set these for safety */
	t->prev=NULL;
	t->op=op;
	t->a=a;
	t->b=b;
	t->c=c;

	return t;
}  

TAC *join_tac(TAC *c1, TAC *c2)
{
	TAC *t;

	/* If either list is NULL return the other */
	if(c1==NULL) return c2;
	if(c2==NULL) return c1;

	/* Run down c2, until we get to the beginning and then add c1 */
	t=c2;
	while(t->prev !=NULL) 
		t=t->prev;

	t->prev=c1;
	c1->next=t;

	return c2;
}   
			   
void insert(SYMB **symbtab, SYMB *sym)
{
	sym->next=*symbtab; /* Insert at head */
	*symbtab=sym;
}


SYMB *lookup(SYMB *symbtab, char *name)
{
	SYMB *t=symbtab;

	while(t !=NULL)
	{
		if(strcmp(t->name, name)==0) break; 
		else t=t->next;
	}
	
	return t; /* NULL if not found */
}

void tac_print(TAC *i)
{
	char sa[12]; /* For text of TAC args */
	char sb[12];
	char sc[12];

	switch(i->op)
	{
		case TAC_UNDEF:
		printf("undef");
		break;

		case TAC_ADD:
		printf("%s = %s + %s", ts(i->a, sa), ts(i->b, sb),
		ts(i->c, sc));
		break;

		case TAC_SUB:
		printf("%s = %s - %s", ts(i->a, sa), ts(i->b, sb),
		ts(i->c, sc));
		break;

		case TAC_MUL:
		printf("%s = %s * %s", ts(i->a, sa), ts(i->b, sb),
		ts(i->c, sc));
		break;

		case TAC_DIV:
		printf("%s = %s / %s", ts(i->a, sa), ts(i->b, sb),
		ts(i->c, sc));
		break;

		case TAC_EQ:
		printf("%s = (%s == %s)", ts(i->a, sa), ts(i->b, sb), ts(i->c, sc));
		break;

		case TAC_NE:
		printf("%s = (%s != %s)", ts(i->a, sa), ts(i->b, sb), ts(i->c, sc));
		break;

		case TAC_LT:
		printf("%s = (%s < %s)", ts(i->a, sa), ts(i->b, sb), ts(i->c, sc));
		break;

		case TAC_LE:
		printf("%s = (%s <= %s)", ts(i->a, sa), ts(i->b, sb), ts(i->c, sc));
		break;

		case TAC_GT:
		printf("%s = (%s > %s)", ts(i->a, sa), ts(i->b, sb), ts(i->c, sc));
		break;

		case TAC_GE:
		printf("%s = (%s >= %s)", ts(i->a, sa), ts(i->b, sb), ts(i->c, sc));
		break;

		case TAC_NEG:
		printf("%s = - %s", ts(i->a, sa), ts(i->b, sb));
		break;

		case TAC_COPY:
		printf("%s = %s", ts(i->a, sa), ts(i->b, sb));
		break;

		case TAC_GOTO:
		printf("goto %s", i->a->name);
		break;

		case TAC_IFZ:
		printf("ifz %s goto %s", ts(i->b, sb), i->a->name);
		break;

		case TAC_ACTUAL:
		printf("actual %s", ts(i->a, sa));
		break;

		case TAC_FORMAL:
		printf("formal %s", ts(i->a, sa));
		break;

		case TAC_CALL:
		if(i->a==NULL) printf("call %s", (char *)i->b);
		else printf("%s = call %s", ts(i->a, sa), (char *)i->b);
		break;

		case TAC_RETURN:
		printf("return %s", ts(i->a, sa));
		break;

		case TAC_LABEL:
		printf("label %s", i->a->name);
		break;

		case TAC_VAR:
		printf("var %s", ts(i->a, sa));
		break;

		case TAC_BEGINFUNC:
		printf("begin");
		break;

		case TAC_ENDFUNC:
		printf("end");
		break;

		default:
		error("unknown TAC opcode");
		break;
	}

	fflush(stdout);

}


char *ts(SYMB *s, char *str) 
{
	/* Check we haven't been given NULL */
	if(s==NULL)	return "NULL";

	/* Identify the type */
	switch(s->type)
	{
		case SYM_FUNC:
		case SYM_VAR:
		/* Just return the name */
		return s->name; /* ysj */

		case SYM_TEXT:
		/* Put the address of the text */
		sprintf(str, "L%d", s->lable);
		return str;

		case SYM_INT:
		/* Convert the number to string */
		sprintf(str, "%d", s->value);
		return str;

		default:
		/* Unknown arg type */
		error("unknown TAC arg type");
		return "?";
	}
} 

void error(char *str)
{
	printf("%s at line%d\n", str,line);
	exit(0);
} 

void cg()
{
	tof=0; /* TOS allows space for link info */
	oof=-4;
	oon=0;

	int r;
	for(r=0; r < R_NUM; r++) 
		rdesc[r].name=NULL;
	insert_desc(0, mkconst(0), UNMODIFIED); /* R0 holds 0 */

	cg_head();

	TAC * cur;
	for(cur=tac_first; cur!=NULL; cur=cur->next)
	{
		printf("\n	# ");
		tac_print(cur);
		printf("\n");
		cg_code(cur);
	}
	cg_lib();
	cg_data();
} 

void tac_tidy()
{
	TAC *c=NULL; 		/* Current TAC */
	TAC *p=tac_last; 	/* Previous TAC */

	while(p !=NULL)
	{
		p->next=c;
		c=p;
		p=p->prev;
	}

	tac_first = c;
} 

void cg_code(TAC *c)
{
	int r;

	switch(c->op)
	{
		case TAC_UNDEF:
		error("cannot translate TAC_UNDEF");
		return;

		case TAC_ADD:
		cg_bin("ADD", c->a, c->b, c->c);
		return;

		case TAC_SUB:
		cg_bin("SUB", c->a, c->b, c->c);
		return;

		case TAC_MUL:
		cg_bin("MUL", c->a, c->b, c->c);
		return;

		case TAC_DIV:
		cg_bin("DIV", c->a, c->b, c->c);
		return;

		case TAC_NEG:
		cg_bin("SUB", c->a, mkconst(0), c->b);
		return;

		case TAC_EQ:
		case TAC_NE:
		case TAC_LT:
		case TAC_LE:
		case TAC_GT:
		case TAC_GE:
		cg_cmp(c->op, c->a, c->b, c->c);
		return;

		case TAC_COPY:
		cg_copy(c->a, c->b);
		return;

		case TAC_GOTO:
		cg_cond("JMP", NULL, c->a->name);
		return;

		case TAC_IFZ:
		cg_cond("JEZ", c->b, c->a->name);
		return;

		case TAC_LABEL:
		flush_all();
		printf("%s:\n", c->a->name);
		return;

		case TAC_ACTUAL:
		r=get_rreg(c->a);
		printf("	STO (R2+%d),R%u\n", tof+oon+8, r);
		oon += 4;
		return;

		case TAC_CALL:
		flush_all();
		printf("	STO (R2+%d),R2\n", tof+4);	/* store old bp */
		oon += 4;
		printf("	LOD R4,R1+32\n"); 				/* return addr: 4*8=32 */
		printf("	STO (R2+%d),R4\n", tof);	/* store return addr */
		oon += 4;
		printf("	LOD R2,R2+%d\n", tof+oon);	/* load new bp */
		printf("	JMP %s\n", (char *)c->b);	/* jump to new func */
		if(c->a !=NULL) insert_desc(R_TP, c->a, MODIFIED);
		oon=0;
		return;

		case TAC_BEGINFUNC:
		/* We reset the top of stack, since it is currently empty apart from the link information. */
		LocalScope=1;
		tof=0;
		oof=-4;
		oon=0;
		return;

		case TAC_FORMAL:
		c->a->store=1; /* parameter is special local var */
		c->a->offset=oof;
		oof -=4;
		return;

		case TAC_VAR:
		if(LocalScope)
		{
			c->a->store=1; /* local var */
			c->a->offset=tof;
			tof +=4;
		}
		else
		{
			c->a->store=0; /* global var */
			c->a->offset=tos;
			tos +=4;
		}
		return;

		case TAC_RETURN:
		cg_return(c->a);
		return;

		case TAC_ENDFUNC:
		cg_return(NULL);
		LocalScope=0;
		return;

		default:
		/* Don't know what this one is */
		error("unknown TAC opcode to translate");
		return;
	}
}

void cg_bin(char *op, SYMB *a, SYMB *b, SYMB *c)
{
	int rreg=get_rreg(b); /* Result register */
	int areg=get_areg(c, rreg); /* One more register */

	printf("	%s R%u,R%u\n", op, rreg, areg);

	/* Delete c from the descriptors and insert a */
	clear_desc(rreg);
	insert_desc(rreg, a, MODIFIED);
}   

void cg_cmp(int op, SYMB *a, SYMB *b, SYMB *c)
{
	int rreg=get_rreg(b); /* Result register */
	int areg=get_areg(c, rreg); /* One more register */

	printf("	SUB R%u,R%u\n", rreg, areg);
	printf("	TST R%u\n", rreg);

	switch(op)
	{		
		case TAC_EQ:
		printf("	LOD R3,R1+40\n");
		printf("	JEZ R3\n");
		printf("	LOD R%u,0\n", rreg);
		printf("	LOD R3,R1+24\n");
		printf("	JMP R3\n");
		printf("	LOD R%u,1\n", rreg);
		break;
		
		case TAC_NE:
		printf("	LOD R3,R1+40\n");
		printf("	JEZ R3\n");
		printf("	LOD R%u,1\n", rreg);
		printf("	LOD R3,R1+24\n");
		printf("	JMP R3\n");
		printf("	LOD R%u,0\n", rreg);
		break;
		
		case TAC_LT:
		printf("	LOD R3,R1+40\n");
		printf("	JLZ R3\n");
		printf("	LOD R%u,0\n", rreg);
		printf("	LOD R3,R1+24\n");
		printf("	JMP R3\n");
		printf("	LOD R%u,1\n", rreg);
		break;
		
		case TAC_LE:
		printf("	LOD R3,R1+40\n");
		printf("	JGZ R3\n");
		printf("	LOD R%u,1\n", rreg);
		printf("	LOD R3,R1+24\n");
		printf("	JMP R3\n");
		printf("	LOD R%u,0\n", rreg);
		break;
		
		case TAC_GT:
		printf("	LOD R3,R1+40\n");
		printf("	JGZ R3\n");
		printf("	LOD R%u,0\n", rreg);
		printf("	LOD R3,R1+24\n");
		printf("	JMP R3\n");
		printf("	LOD R%u,1\n", rreg);
		break;
		
		case TAC_GE:
		printf("	LOD R3,R1+40\n");
		printf("	JLZ R3\n");
		printf("	LOD R%u,1\n", rreg);
		printf("	LOD R3,R1+24\n");
		printf("	JMP R3\n");
		printf("	LOD R%u,0\n", rreg);
		break;
	}

	/* Delete c from the descriptors and insert a */
	clear_desc(rreg);
	insert_desc(rreg, a, MODIFIED);
}   

void cg_copy(SYMB *a, SYMB *b)
{
	int rreg=get_rreg(b); /* Load b into a register */
	insert_desc(rreg, a, MODIFIED); /* Indicate a is there */
}    

void cg_cond(char *op, SYMB *a,  char *l)
{
	spill_all();

	if(a !=NULL)
	{
		int r;

		for(r=R_GEN; r < R_NUM; r++) /* Is it in reg? */
		{
			if(rdesc[r].name==a) break;
		}

		if(r < R_NUM) printf("	TST R%u\n", r);
		else printf("	TST R%u\n", get_rreg(a)); /* Load into new register */
	}

	printf("	%s %s\n", op, l); 
} 
			   
void cg_return(SYMB *a)
{
	if(a !=NULL)					/* return value */
	{
		spill_one(R_TP);
		load_reg(R_TP, a);
	}

	printf("	LOD R3,(R2%d)\n",oof-4);	/* return address */
	printf("	LOD R2,(R2%d)\n",oof);	/* restore bp */
	printf("	JMP R3\n");		/* return */
}   

void cg_head()
{
	char head[]=
	"	# head\n"
	"	LOD R2,STACK\n"
	"	LOD R4,0\n"
	"	STO (R2+4),R4\n"
	"	STO (R2),EXIT\n"
	"	LOD R2,R2+8";

	puts(head);
}

void cg_lib()
{
	char lib[]=
	"\nPRINTN:\n"
	"	LOD R7,(R2-4) # 789\n"
	"	LOD R15,R7 # 789 \n"
	"	DIV R7,10 # 78\n"
	"	TST R7\n"
	"	JEZ PRINTDIGIT\n"
	"	LOD R8,R7 # 78\n"
	"	MUL R8,10 # 780\n"
	"	SUB R15,R8 # 9\n"
	"	STO (R2),R15 # local 9 store\n"
	"\n	# out 78\n"
	"	STO (R2+12),R7 # actual 78 push\n"
	"\n	# call PRINTN\n"
	"	STO (R2+8),R2\n"
	"	LOD R4,R1+32\n"
	"	STO (R2+4),R4\n"
	"	LOD R2,R2+16\n"
	"	JMP PRINTN\n"
	"\n	# out 9\n"
	"	LOD R15,(R2) # local 9 \n"
	"\nPRINTDIGIT:\n"
	"	ADD  R15,48\n"
	"	OUT\n"
	"\n	# ret\n"
	"	LOD R3,(R2-12)\n"
	"	LOD R2,(R2-8)\n"
	"	JMP R3\n"
	"\nPRINTS:\n"
	"	LOD R7,(R2-4)\n"
	"\nPRINTC:\n"
	"	LOD R15,(R7)\n"
	"	DIV R15,16777216\n"
	"	TST R15\n"
	"	JEZ PRINTSEND\n"
	"	OUT\n"
	"	ADD R7,1\n"
	"	JMP PRINTC\n"	
	"\nPRINTSEND:\n"
	"	# ret\n"
	"	LOD R3,(R2-12)\n"
	"	LOD R2,(R2-8)\n"
	"	JMP R3\n"

	"\n"
	"EXIT:\n"
	"	END\n";

	puts(lib);
}

void cg_data(void)
{
	int i;

	SYMB *sl;

	for(sl=GlobalSymbolTable; sl !=NULL; sl=sl->next)
	{
		if(sl->type==SYM_TEXT) cg_str(sl);
	}

	printf("STATIC:\n");
	printf("	DBN 0,%u\n", tos);				
	printf("STACK:\n");
}

void cg_str(SYMB *s)
{
	char *t=s->name; /* The text */
	int i;

	printf("L%u:\n", s->lable); /* Label for the string */
	printf("	DBS "); /* Label for the string */

	for(i=1; t[i + 1] !=0; i++)
	{
		if(t[i]=='\\')
		{
			switch(t[++i])
			{
				case 'n':
				printf("%u,", '\n');
				break;

				case '\"':
				printf("%u,", '\"');
				break;
			}
		}
		else printf("%u,", t[i]);
	}

	printf("0\n"); /* End of string */
}

void flush_all(void)
{
	int r;

	spill_all();

	for(r=R_GEN; r < R_NUM; r++) clear_desc(r);

	clear_desc(R_TP); /* Clear result register */
}

void spill_all(void)
{
	int r;
	for(r=R_GEN; r < R_NUM; r++) spill_one(r);
} 

void spill_one(int r)
{
	if((rdesc[r].name !=NULL) && rdesc[r].modified)
	{
		if(rdesc[r].name->store==1) /* local var */
		{
			printf("	STO (R%u+%u),R%u\n", R_BP, rdesc[r].name->offset, r);
		}
		else /* global var */
		{
			printf("	LOD R%u,STATIC\n", R_TP);
			printf("	STO (R%u+%u),R%u\n", R_TP, rdesc[r].name->offset, r);
		}
		rdesc[r].modified=UNMODIFIED;
	}
}


void load_reg(int r, SYMB *n) 
{
	int s;

	/* Look for a register */
	for(s=0; s < R_NUM; s++)  
	{
		if(rdesc[s].name==n)
		{
			printf("	LOD R%u,R%u\n", r, s);
			insert_desc(r, n, rdesc[s].modified);
			return;
		}
	}
	
	/* Not in a reg. Load appropriately */
	switch(n->type)
	{
		case SYM_INT:
		printf("	LOD R%u,%u\n", r, n->value);
		break;

		case SYM_VAR:
		if(n->store==1) /* local var */
		{
			if((n->offset)>=0) printf("	LOD R%u,(R%u+%d)\n", r, R_BP, n->offset);
			else printf("	LOD R%u,(R%u-%d)\n", r, R_BP, -(n->offset));
		}
		else /* global var */
		{
			printf("	LOD R%u,STATIC\n", R_TP);
			printf("	LOD R%u,(R%u+%d)\n", r, R_TP, n->offset);
		}
		break;

		case SYM_TEXT:
		printf("	LOD R%u,L%u\n", r, n->lable);
		break;
	}

	insert_desc(r, n, UNMODIFIED);
}   
	
void clear_desc(int r)    
{
        rdesc[r].name=NULL;
}    

void insert_desc(int r, SYMB *n, int mod)
{
	int or; /* Old register counter */

	/* Search through each register in turn looking for "n". There should be at most one of these. */
	for(or=R_GEN; or < R_NUM; or++)
	{
	if(rdesc[or].name==n)
	{
	/* Found it, clear it and break out of the loop. */

	clear_desc(or);
	break;
	}
	}

	/* We should not find any duplicates, but check, just in case. */

	for(or++; or < R_NUM; or++)

	if(rdesc[or].name==n)
	{
	error("Duplicate slave found");
	clear_desc(or);
	}

	/* Finally insert the name in the new descriptor */

	rdesc[r].name=n;
	rdesc[r].modified=mod;
}     

int get_rreg(SYMB *c)
{
	int r; /* Register for counting */

	for(r=R_GEN; r < R_NUM; r++) /* Already in a register */
	{
		if(rdesc[r].name==c)
		{
			spill_one(r);
			return r;
		}
	}

	for(r=R_GEN; r < R_NUM; r++)
	{
		if(rdesc[r].name==NULL) /* Empty register */
		{
			load_reg(r, c);
			return r;
		}

	}
	
	for(r=R_GEN; r < R_NUM; r++)
	{
		if(!rdesc[r].modified) /* Unmodifed register */
		{
			clear_desc(r);
			load_reg(r, c);
			return r;
		}
	}

	spill_one(R_GEN); /* Modified register */
	clear_desc(R_GEN);
	load_reg(R_GEN, c);
	return R_GEN;
} 

int get_areg(SYMB *b, int cr)             
{
	int r; /* Register for counting */

	for(r=R_GEN; r < R_NUM; r++)
	{
		if(rdesc[r].name==b) /* Already in register */
		return r;
	}

	for(r=R_GEN; r < R_NUM; r++)
	{
		if(rdesc[r].name==NULL) /* Empty register */
		{
			load_reg(r, b);
			return r;
		}
	}

	for(r=R_GEN; r < R_NUM; r++)
	{
		if(!rdesc[r].modified && (r !=cr)) /* Unmodifed register */
		{
			clear_desc(r);
			load_reg(r, b);
			return r;
		}
	}

	for(r=R_GEN; r < R_NUM; r++)
	{
		if(r !=cr) /* Modified register */
		{
			spill_one(r);
			clear_desc(r);
			load_reg(r, b);
			return r;
		}
	}
}      

void outputlocalsymboltable(SYMB *func){
	if (mode!=1) return;
	printf("%-11s",func->name);
	puts("LocalSymbolTable");
	SYMB *now=LocalSymbolTable;
	while (now!=NULL) {
		if (now->type==SYM_VAR) printf("%-10s (%p,%s)\n","VAR",now,now->name);
		if (now->type==SYM_INT) printf("%-10s (%p,%d)\n","INT",now,now->value);
		if (now->type==SYM_TEXT) printf("%-10s (%p,%s)\n","STRING",now,now->name);
		now=now->next;
	}
}


int hash_add(char *s){
	int i,len=strlen(s),key=0;
	for (i=0;i<len;++i) key=key*hasharg+s[i];
	int now=(key%hashMo+hashMo)%hashMo;
	while (hashkey[now]!=key&&hash[now]!=NULL) now=(now+1)%hashMo;
	if (hashkey[now]==key) return 1;
	hashkey[now]=key;
	for (i=0;i<len;++i) hashstr[top+i]=s[i];
	hashstr[top+len]=0;
	hash[now]=&hashstr[top];
	top+=len+1;
	hashtable[++NUM]=now;
	return 0;
}

void gtn_calcsize(GTN *root){
	GTN *now=root->son;
	root->size=0;
	while (now!=NULL) {
		gtn_calcsize(now);
		root->size+=now->size;
		now=now->brother;
	}
	if (root->size==0) root->size=1;
}

void gtn_paint(int x,int y,GTN *root){
	int len=strlen(root->name);
	for (int i=0;i<len;++i) map[x][y+i]=root->name[i];
	y+=len;
	mapline[x]=max(mapline[x],y);
	if (root->size==1&&root->son==NULL) return;
	for (int i=0;i<root->size;++i) map[x+i][y]=4;
	int pos=0;
	GTN *now=root->son,*last=NULL;
	while (now!=NULL) {
		map[x+pos][y]=1;
		map[x+pos][y+1]=3;
		gtn_paint(x+pos,y+2,now);
		last=now;
		pos+=now->size;
		now=now->brother;
	}
	if (last==root->son) {
		map[x][y]=3;
		for (int i=1;i<root->size;++i) map[x+i][y]=' ';
	}
	else {
		map[x][y]=0;
		for (int i=root->size-last->size;i<root->size;++i) map[x+i][y]=' ';
		map[x+root->size-last->size][y]=2;
	}
}

int main(int argc,char *argv[])
{
	int i; /* General counter */
	char *ifile;
	char *ofile;

	if(argc==2)
	{
		mode=0;
	}
	else if(argc==3)
	{
		if(!strcmp(argv[2],"-lex"))
			mode=1;
		else if(!strcmp(argv[2],"-syn"))
			mode=2;
		else if(!strcmp(argv[2],"-tac"))
			mode=3;
		else
		{
			printf("error: argument %s\n", argv[2]);
			exit(0);
		}			
	}
	else
	{
		printf("usage: %s name [-lex/-syn/-tac]\n", argv[0]);
		exit(0);
	}

	ifile=(char *)malloc(strlen(argv[1]) + 10);
	strcpy(ifile,argv[1]);
	strcat(ifile,".gpl");
	
	if(freopen(ifile, "r", stdin)==NULL)
	{
		printf("error: open %s failed\n", ifile);
		exit(0);
	}
	
	ofile=(char *)malloc(strlen(argv[1]) + 10);
	strcpy(ofile,argv[1]);
	
	if(mode==1)
		strcat(ofile,".lex");
	else if(mode==2)
		strcat(ofile,".syn");
	else if(mode==3)
		strcat(ofile,".tac");
	else
		strcat(ofile,".gal");
										   
	if(freopen(ofile, "w", stdout)==NULL)
	{
		printf("error: open %s failed\n", ofile);
		exit(0);
	}

	/* Give values to global variables */
	line=1;
	character=0;
	token[0]=0;
	LocalScope=0;
	GlobalSymbolTable=NULL;
	LocalSymbolTable=NULL;	
	tos=0;
	symb_list=NULL; /* Freelists */
	enode_list=NULL;
	next_tmp=0; /* No temporaries used */
	next_label=LAB_MIN;
	memset(hashkey,-1,sizeof(hashkey));

	/* parse */
	yyparse();
	
	if (mode==1) {
		puts("=====GlobalSymbolTable=====");
		SYMB *now=GlobalSymbolTable;
		while (now!=NULL) {
			if (now->type==SYM_VAR) printf("%-10s (%p,%s)\n","VAR",now,now->name);
			if (now->type==SYM_INT) printf("%-10s (%p,%d)\n","INT",now,now->value);
			if (now->type==SYM_TEXT) printf("%-10s (%p,%s)\n","STRING",now,now->name);
			now=now->next;
		}
		puts("===========================");
		puts("hashstring:");
		for (i=0;i<top;++i)
		if (hashstr[i]) printf("%d: %c\n",i,hashstr[i]);
		puts("");
		printf("%d\n",NUM);
		for (i=1;i<=NUM;++i) {
			printf("hashtable(address:%x,name:%s,offset:%d)\n",hashtable[i],hash[hashtable[i]],(int)(hash[hashtable[i]]-hashstr));
		}
	}
	
	if (mode==2) {
		//printf("%slx\n",sp[0]);
		//printf("%d\n",(int)sizeof(sp[0]));
		for (int i=0;i<1000;++i)
			for (int j=0;j<1000;++j) map[i][j]=' ';
		gtn_calcsize(grammertreeroot);
		gtn_paint(0,0,grammertreeroot);
		for (int i=0;i<grammertreeroot->size;++i) {
			for (int j=0;j<mapline[i];++j) {
				if (map[i][j]<5) printf("%s",sp[map[i][j]]);
				else printf("%c",map[i][j]);
			}
			puts("");
		}
	}
	
	/* tac */
	tac_tidy();
	if(mode==3)
	{
		TAC * cur;
		for(cur = tac_first; cur !=NULL; cur=cur->next)
		{
			tac_print(cur);
			printf("\n");
		}
		exit (0);
	}

	/* code generate */
	if (mode==0) cg();
	return 0;
}

int yyerror(char *str)
{
	fprintf(stderr, "yyerror: %s at line %d\n", str, line);
	return 0;
}

void getch()
{
	character=getchar();
	if(character=='#') 
	{
		while(1)
		{
			character=getchar();
			if(character=='\n' || character==EOF) break;
		}
	}
	if(character=='\n') line++;
}

void getnbc()
{
	while((character==' ') || (character=='\t') || (character=='\r') || (character=='\n')) {
		character=getchar();	
		if (character=='\n') line++;
	}
}

void concat()
{
	int len=strlen(token);
	token[len]=character;
	token[len+1]='\0';	
}

int letter()
{
	if(((character>='a') && (character<='z')) || ((character>='A') && (character<='Z')))
		return 1;
	else 
		return 0;
}

int digit()
{
	if((character>='0') && (character<='9'))
		return 1;
	else 
		return 0;
}

void retract()
{
	ungetc(character,stdin);
	character='\0';
}

int keyword()
{
	int i=0;
	while(strcmp(keywords[i].name,""))
	{
		if(!strcmp(keywords[i].name,token)) 
			return keywords[i].id;
		i++;
	}
	return 0;
}

int yylex()
{
	int num;
	char *lexeme;
	
	strcpy(token,"");
	getch();
	getnbc();

	if(letter())
	{
		while(letter() || digit())
		{
			concat();
			getch();
		}
		retract();
		num=keyword();
		if(num!=0) {
			if (mode==1) printf("keyword    %5s (%3d,-)\n",token,num);
			return num; // return keyword
		}
		else
		{
			lexeme=malloc(strlen(token)+1);
			strcpy(lexeme,token);
			yylval.string=lexeme;
			hash_add(lexeme);
			if (mode==1) printf("identifier %5s (%3d,%p)\n",lexeme,IDENTIFIER,lexeme);
			return IDENTIFIER;
		}
	}

	if(digit())
	{
		while(digit())
		{
			concat();
			getch();
		}
		retract();
		lexeme=malloc(strlen(token)+1);
		strcpy(lexeme,token);
		yylval.string=lexeme;
		int *x=malloc(4);
		*x=atoi(lexeme);
		hash_add(lexeme);
		if (mode==1) printf("number     %5s (%3d,%p)\n",lexeme,INTEGER,x);
		return INTEGER;
	}

	if(character=='"')
	{
		concat();
		getch();
		while(character!='"' && character!=EOF)
		{
			concat();
			getch();
		}
		if(character==EOF)
		{
			yyerror("lex error: \" expected\n");
			exit(1);
		}
		concat();
		lexeme=malloc(strlen(token)+1);
		strcpy(lexeme,token);
		hash_add(lexeme);
		yylval.string=lexeme;
		if (mode==1) printf("string     %5s (%3d,%p)\n",lexeme,TEXT,lexeme);
		return TEXT;			
	}

	if(character=='=')
	{
		concat();
		getch();
		if(character=='=') 
		{
			concat();
			if (mode==1) printf("operator      == (%3d,-)\n",EQ);
			return EQ;
		}
		else
		{
			retract();
			if (mode==1) printf("operator       = (%3d,-)\n",((int)'='));
			return '=';
		}
	}

	if(character=='!')
	{
		concat();
		getch();
		if(character=='=') 
		{
			concat();
			if (mode==1) printf("operator      != (%3d,-)\n",NE);
			return NE;
		}
		else
		{
			yyerror("lex error: = expected\n");
			exit(1);
		}		
	}

	if(character=='<')
	{
		concat();
		getch();
		if(character=='=') 
		{
			concat();
			if (mode==1) printf("operator      <= (%3d,-)\n",LE);
			return LE;
		}
		else
		{
			retract();
			if (mode==1) printf("operator       < (%3d,-)\n",LT);
			return LT;
		}		
	}

	if(character=='>')
	{
		concat();
		getch();
		if(character=='=') 
		{
			concat();
			if (mode==1) printf("operator      >= (%3d,-)\n",GE);
			return GE;
		}
		else
		{
			retract();
			if (mode==1) printf("operator       > (%3d,-)\n",GT);
			return GT;
		}
	}
	
	if (character!=EOF) {
		if (character=='+'||character=='-'||character=='*'||character=='/') {
			if (mode==1) printf("operator       %c (%3d,-)\n",character,((int)character));
        }
		else if (character=='{'||character=='}'||character=='('||character==')'||character==','||character==';'||character=='#') {
			if (mode==1) printf("delimiter      %c (%3d,-)\n",character,((int)character));
        }
		else {
			yyerror("lex error: undefined character!\n");
			exit(1);
		}
	}
	return character;
}
