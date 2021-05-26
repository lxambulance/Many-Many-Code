/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "gpl.y" /* yacc.c:339  */

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


#line 187 "gpl.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    FUNC = 258,
    PRINT = 259,
    RETURN = 260,
    CONTINUE = 261,
    IF = 262,
    THEN = 263,
    ELSE = 264,
    FI = 265,
    WHILE = 266,
    FOR = 267,
    DO = 268,
    DONE = 269,
    INT = 270,
    EQ = 271,
    NE = 272,
    LT = 273,
    LE = 274,
    GT = 275,
    GE = 276,
    UMINUS = 277,
    INTEGER = 278,
    IDENTIFIER = 279,
    TEXT = 280
  };
#endif
/* Tokens.  */
#define FUNC 258
#define PRINT 259
#define RETURN 260
#define CONTINUE 261
#define IF 262
#define THEN 263
#define ELSE 264
#define FI 265
#define WHILE 266
#define FOR 267
#define DO 268
#define DONE 269
#define INT 270
#define EQ 271
#define NE 272
#define LT 273
#define LE 274
#define GT 275
#define GE 276
#define UMINUS 277
#define INTEGER 278
#define IDENTIFIER 279
#define TEXT 280

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 123 "gpl.y" /* yacc.c:355  */

	char character;
	char *string;
	SYMB *symb;
	TAC *tac;
	ENODE	*enode;

#line 282 "gpl.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);



/* Copy the second part of user declarations.  */
#line 189 "gpl.y" /* yacc.c:358  */

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


#line 406 "gpl.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  12
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   206

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  37
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  71
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  130

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   280

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      33,    34,    28,    26,    31,    27,     2,    29,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    30,
       2,    32,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    35,     2,    36,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   300,   300,   308,   314,   324,   330,   338,   351,   360,
     373,   387,   406,   422,   429,   442,   451,   466,   471,   479,
     487,   495,   503,   509,   515,   521,   527,   533,   540,   546,
     552,   558,   562,   569,   587,   590,   605,   611,   621,   636,
     646,   656,   666,   676,   685,   695,   705,   715,   725,   735,
     745,   756,   765,   774,   781,   789,   792,   800,   806,   819,
     834,   840,   852,   860,   871,   885,   891,   905,   924,   940,
     962,   980
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "FUNC", "PRINT", "RETURN", "CONTINUE",
  "IF", "THEN", "ELSE", "FI", "WHILE", "FOR", "DO", "DONE", "INT", "EQ",
  "NE", "LT", "LE", "GT", "GE", "UMINUS", "INTEGER", "IDENTIFIER", "TEXT",
  "'+'", "'-'", "'*'", "'/'", "';'", "','", "'='", "'('", "')'", "'{'",
  "'}'", "$accept", "program", "function_declaration_list",
  "function_declaration", "declaration", "variable_list", "function",
  "function_head", "parameter_list", "statement", "primary_statement",
  "block", "declaration_list", "statement_list", "assignment_statement",
  "expression", "argument_list", "expression_list", "print_statement",
  "print_list", "print_item", "return_statement", "null_statement",
  "if_statement", "while_statement", "for_statement", "call_statement",
  "call_expression", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,    43,    45,    42,    47,
      59,    44,    61,    40,    41,   123,   125
};
# endif

#define YYPACT_NINF -89

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-89)))

#define YYTABLE_NINF -56

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      96,   -89,     7,   -89,    46,    83,   -89,   -89,   -89,    14,
      19,   -25,   -89,   -89,    30,    54,   -89,    33,   -89,   -17,
     -89,   -89,    25,    54,    54,   177,   -89,    31,    48,    40,
      68,   -89,   105,    54,    54,    54,    54,    54,    54,    54,
      54,    54,    54,    54,   -89,   -89,   -89,   177,    51,    49,
     -89,   -16,   -16,   -16,   -16,   -16,   -16,   -13,   -13,   -89,
     -89,   177,    55,   -89,    54,   -89,    53,    54,   -89,    60,
      61,    76,    11,   -89,   -89,   -89,    29,    80,    82,    85,
      86,   -89,   -89,   -89,    87,   177,    81,   177,    54,    54,
      44,    54,    68,   -89,   -89,   -89,   -89,   -89,   -89,   -89,
     -89,   177,    -2,   -89,   124,   143,   -89,    88,   -89,   -89,
     -89,   -89,   177,    79,    81,   -89,    40,    40,    54,   -89,
     -89,   110,   -89,   162,    40,    44,   -89,    93,    40,   -89
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    13,     0,    14,     0,     0,     3,     6,     5,     0,
       8,     0,     1,     4,    17,     0,     7,     0,    15,     0,
      54,    51,    52,     0,     0,    10,    53,     9,     0,     0,
       0,    43,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    16,    34,    12,    57,     0,    56,
      50,    44,    45,    46,    47,    48,    49,    39,    40,    41,
      42,    11,     0,    71,     0,    27,     0,     0,    65,     0,
       0,     0,     0,    35,    36,    26,     0,     0,     0,     0,
       0,    23,    24,    25,     0,    58,     0,    64,     0,     0,
       0,     0,     0,    33,    37,    18,    21,    20,    22,    19,
      63,    62,     0,    60,     0,     0,    32,     0,    28,    30,
      31,    29,    38,     0,     0,    59,     0,     0,     0,    70,
      61,    66,    68,     0,     0,     0,    67,     0,     0,    69
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -89,   -89,   -89,   123,    67,   -89,   -89,   -89,   -89,    59,
       5,   -28,   -89,   -89,   -88,   -15,    45,   -89,   -87,   -89,
      22,   -89,   -86,   -89,   -89,   -89,   -83,   -89
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     4,     5,     6,     7,    11,     8,     9,    19,    74,
     107,    75,    62,    76,    77,    47,    48,    49,    78,   102,
     103,    79,    80,    81,    82,    83,    84,    26
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      25,    46,   108,   109,   110,    16,    17,   111,    31,    32,
      39,    40,    41,    42,    28,    41,    42,    29,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,   114,
      65,    10,   115,    66,    67,    68,    69,   108,   109,   110,
      70,    71,   111,    91,    92,   106,    12,    14,    66,    85,
      68,    15,    87,    72,    18,    20,    65,    27,    30,    66,
      67,    68,    69,    43,    45,    93,    70,    71,    72,    20,
       2,   101,    44,   104,   105,    45,   112,    21,    22,    72,
      64,    23,    20,    -2,     1,    63,    86,    24,   121,   122,
      45,    21,    22,    88,    89,    23,   126,     1,     2,   101,
     129,    24,   -55,   123,    21,    22,   100,     3,    23,    90,
      95,     2,    96,   119,    24,    97,    98,    99,   118,   124,
       3,    33,    34,    35,    36,    37,    38,   128,    13,    73,
     127,    39,    40,    41,    42,    94,   120,   113,     0,    50,
      33,    34,    35,    36,    37,    38,     0,     0,     0,     0,
      39,    40,    41,    42,     0,     0,     0,     0,   116,    33,
      34,    35,    36,    37,    38,     0,     0,     0,     0,    39,
      40,    41,    42,     0,     0,     0,     0,   117,    33,    34,
      35,    36,    37,    38,     0,     0,     0,     0,    39,    40,
      41,    42,   125,    33,    34,    35,    36,    37,    38,     0,
       0,     0,     0,    39,    40,    41,    42
};

static const yytype_int16 yycheck[] =
{
      15,    29,    90,    90,    90,    30,    31,    90,    23,    24,
      26,    27,    28,    29,    31,    28,    29,    34,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    31,
       1,    24,    34,     4,     5,     6,     7,   125,   125,   125,
      11,    12,   125,    32,    33,     1,     0,    33,     4,    64,
       6,    32,    67,    24,    24,     1,     1,    24,    33,     4,
       5,     6,     7,    32,    35,    36,    11,    12,    24,     1,
      15,    86,    24,    88,    89,    35,    91,    23,    24,    24,
      31,    27,     1,     0,     1,    34,    33,    33,   116,   117,
      35,    23,    24,    33,    33,    27,   124,     1,    15,   114,
     128,    33,    34,   118,    23,    24,    25,    24,    27,    33,
      30,    15,    30,    34,    33,    30,    30,    30,    30,     9,
      24,    16,    17,    18,    19,    20,    21,    34,     5,    62,
     125,    26,    27,    28,    29,    76,   114,    92,    -1,    34,
      16,    17,    18,    19,    20,    21,    -1,    -1,    -1,    -1,
      26,    27,    28,    29,    -1,    -1,    -1,    -1,    34,    16,
      17,    18,    19,    20,    21,    -1,    -1,    -1,    -1,    26,
      27,    28,    29,    -1,    -1,    -1,    -1,    34,    16,    17,
      18,    19,    20,    21,    -1,    -1,    -1,    -1,    26,    27,
      28,    29,    30,    16,    17,    18,    19,    20,    21,    -1,
      -1,    -1,    -1,    26,    27,    28,    29
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,    15,    24,    38,    39,    40,    41,    43,    44,
      24,    42,     0,    40,    33,    32,    30,    31,    24,    45,
       1,    23,    24,    27,    33,    52,    64,    24,    31,    34,
      33,    52,    52,    16,    17,    18,    19,    20,    21,    26,
      27,    28,    29,    32,    24,    35,    48,    52,    53,    54,
      34,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    49,    34,    31,     1,     4,     5,     6,     7,
      11,    12,    24,    41,    46,    48,    50,    51,    55,    58,
      59,    60,    61,    62,    63,    52,    33,    52,    33,    33,
      33,    32,    33,    36,    46,    30,    30,    30,    30,    30,
      25,    52,    56,    57,    52,    52,     1,    47,    51,    55,
      59,    63,    52,    53,    31,    34,    34,    34,    30,    34,
      57,    48,    48,    52,     9,    30,    48,    47,    34,    48
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    37,    38,    39,    39,    40,    40,    41,    42,    42,
      42,    42,    43,    43,    44,    45,    45,    45,    46,    46,
      46,    46,    46,    46,    46,    46,    46,    46,    47,    47,
      47,    47,    47,    48,    49,    49,    50,    50,    51,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    53,    53,    54,    54,    55,
      56,    56,    57,    57,    58,    59,    60,    60,    61,    62,
      63,    64
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     3,     1,     3,
       3,     5,     5,     1,     1,     1,     3,     0,     2,     2,
       2,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     4,     0,     2,     1,     2,     3,     3,
       3,     3,     3,     2,     3,     3,     3,     3,     3,     3,
       3,     1,     1,     1,     1,     0,     1,     1,     3,     4,
       1,     3,     1,     1,     2,     1,     5,     7,     5,     9,
       4,     4
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 301 "gpl.y" /* yacc.c:1646  */
    {
	tac_last=(yyvsp[0].tac);
	grammertreeroot=gtn_newnode("program");
	grammertreeroot->son=((yyvsp[0].tac))->now;
}
#line 1592 "gpl.c" /* yacc.c:1646  */
    break;

  case 3:
#line 309 "gpl.y" /* yacc.c:1646  */
    {
	GTN *s1=gtn_copynode(((yyvsp[0].tac))->now);
	((yyval.tac))->now=gtn_newnode("FDL");
	((yyval.tac))->now->son=s1;
}
#line 1602 "gpl.c" /* yacc.c:1646  */
    break;

  case 4:
#line 315 "gpl.y" /* yacc.c:1646  */
    {
	GTN *s2=gtn_copynode(((yyvsp[0].tac))->now);
	(yyval.tac)=join_tac((yyvsp[-1].tac), (yyvsp[0].tac));
	((yyval.tac))->now=gtn_newnode("FDL");
	((yyval.tac))->now->son=((yyvsp[-1].tac))->now;
	((yyvsp[-1].tac))->now->brother=s2;
}
#line 1614 "gpl.c" /* yacc.c:1646  */
    break;

  case 5:
#line 325 "gpl.y" /* yacc.c:1646  */
    {
	GTN *s1=gtn_copynode(((yyvsp[0].tac))->now);
	((yyval.tac))->now=gtn_newnode("FD");
	((yyval.tac))->now->son=s1;
}
#line 1624 "gpl.c" /* yacc.c:1646  */
    break;

  case 6:
#line 331 "gpl.y" /* yacc.c:1646  */
    {
	GTN *s1=gtn_copynode(((yyvsp[0].tac))->now);
	((yyval.tac))->now=gtn_newnode("FD");
	((yyval.tac))->now->son=s1;
}
#line 1634 "gpl.c" /* yacc.c:1646  */
    break;

  case 7:
#line 339 "gpl.y" /* yacc.c:1646  */
    {
	GTN *s2=gtn_copynode(((yyvsp[-1].tac))->now);
	(yyval.tac)=(yyvsp[-1].tac);
	((yyval.tac))->now=gtn_newnode("declaration");
	GTN *s1=gtn_newnode("INT");
	((yyval.tac))->now->son=s1;
	s1->brother=s2;
	GTN *s3=gtn_newnode(";");
	s2->brother=s3;
}
#line 1649 "gpl.c" /* yacc.c:1646  */
    break;

  case 8:
#line 352 "gpl.y" /* yacc.c:1646  */
    {
	(yyval.tac)=declare_var((yyvsp[0].string));
	((yyval.tac))->now=gtn_newnode("VL");
	GTN *s1=gtn_newnode("IDENTIFIER");
	((yyval.tac))->now->son=s1;	
	GTN *s11=gtn_newnode((yyvsp[0].string));
	s1->son=s11;
}
#line 1662 "gpl.c" /* yacc.c:1646  */
    break;

  case 9:
#line 361 "gpl.y" /* yacc.c:1646  */
    {
	GTN *s1=gtn_copynode(((yyvsp[-2].tac))->now);
	(yyval.tac)=join_tac((yyvsp[-2].tac), declare_var((yyvsp[0].string)));
	((yyval.tac))->now=gtn_newnode("VL");
	((yyval.tac))->now->son=s1;
	GTN *s2=gtn_newnode(",");
	s1->brother=s2;
	GTN *s3=gtn_newnode("IDENTIFIER");
	s2->brother=s3;
	GTN *s33=gtn_newnode((yyvsp[0].string));
	s3->son=s33;
}
#line 1679 "gpl.c" /* yacc.c:1646  */
    break;

  case 10:
#line 374 "gpl.y" /* yacc.c:1646  */
    {
	GTN *s3=gtn_copynode(((yyvsp[0].enode))->now);
	(yyval.tac)=declare_var((yyvsp[-2].string));
	(yyval.tac)=join_tac((yyval.tac),do_assign(getvar((yyvsp[-2].string)),(yyvsp[0].enode)));
	((yyval.tac))->now=gtn_newnode("VL");
	GTN *s1=gtn_newnode("IDENTIFIER");
	((yyval.tac))->now->son=s1;
	GTN *s11=gtn_newnode((yyvsp[-2].string));
	s1->son=s11;
	GTN *s2=gtn_newnode("=");
	s1->brother=s2;
	s2->brother=s3;
}
#line 1697 "gpl.c" /* yacc.c:1646  */
    break;

  case 11:
#line 388 "gpl.y" /* yacc.c:1646  */
    {
	GTN *s5=gtn_copynode(((yyvsp[0].enode))->now);
	(yyval.tac)=join_tac((yyvsp[-4].tac),declare_var((yyvsp[-2].string)));
	(yyval.tac)=join_tac((yyval.tac),do_assign(getvar((yyvsp[-2].string)),(yyvsp[0].enode)));
	((yyval.tac))->now=gtn_newnode("VL");
	((yyval.tac))->now->son=((yyvsp[-4].tac))->now;
	GTN *s2=gtn_newnode(",");
	((yyvsp[-4].tac))->now->brother=s2;
	GTN *s3=gtn_newnode("IDENTIFIER");
	s2->brother=s3;
	GTN *s33=gtn_newnode((yyvsp[-2].string));
	s3->son=s33;
	GTN *s4=gtn_newnode("=");
	s3->brother=s4;
	s4->brother=s5;
}
#line 1718 "gpl.c" /* yacc.c:1646  */
    break;

  case 12:
#line 407 "gpl.y" /* yacc.c:1646  */
    {
	(yyval.tac)=do_func((yyvsp[-4].symb), (yyvsp[-2].tac), (yyvsp[0].tac));
	outputlocalsymboltable((yyvsp[-4].symb));
	LocalScope=0; /* Leave local scope. */
	LocalSymbolTable=NULL; /* Clear local symbol table. */
	((yyval.tac))->now=gtn_newnode("function");
	((yyval.tac))->now->son=((yyvsp[-4].symb))->now;
	GTN *s2=gtn_newnode("(");
	((yyvsp[-4].symb))->now->brother=s2;
	if ((yyvsp[-2].tac)!=NULL) s2->brother=((yyvsp[-2].tac))->now;
	GTN *s4=gtn_newnode(")");
	if ((yyvsp[-2].tac)!=NULL) ((yyvsp[-2].tac))->now->brother=s4;
	else s2->brother=s4;
	s4->brother=((yyvsp[0].tac))->now;
}
#line 1738 "gpl.c" /* yacc.c:1646  */
    break;

  case 13:
#line 423 "gpl.y" /* yacc.c:1646  */
    {
	error("Bad function syntax");
	(yyval.tac)=NULL;
}
#line 1747 "gpl.c" /* yacc.c:1646  */
    break;

  case 14:
#line 430 "gpl.y" /* yacc.c:1646  */
    {
	(yyval.symb)=declare_func((yyvsp[0].string));
	LocalScope=1; /* Enter local scope. */
	LocalSymbolTable=NULL; /* Init local symbol table. */
	((yyval.symb))->now=gtn_newnode("FH");
	GTN *s1=gtn_newnode("IDENTIFIER");
	((yyval.symb))->now->son=s1;
	GTN *s11=gtn_newnode((yyvsp[0].string));
	s1->son=s11;
}
#line 1762 "gpl.c" /* yacc.c:1646  */
    break;

  case 15:
#line 443 "gpl.y" /* yacc.c:1646  */
    {
	(yyval.tac)=declare_para((yyvsp[0].string));
	((yyval.tac))->now=gtn_newnode("PL");
	GTN *s1=gtn_newnode("IDENTIFIER");
	((yyval.tac))->now->son=s1;
	GTN *s11=gtn_newnode((yyvsp[0].string));
	s1->son=s11;
}
#line 1775 "gpl.c" /* yacc.c:1646  */
    break;

  case 16:
#line 452 "gpl.y" /* yacc.c:1646  */
    {
	if ((yyvsp[-2].tac)==NULL) error("Bad statement syntax");
	GTN *s1=gtn_copynode(((yyvsp[-2].tac))->now);
	(yyval.tac)=join_tac((yyvsp[-2].tac), declare_para((yyvsp[0].string)));
	((yyval.tac))->now=gtn_newnode("PL");
	((yyval.tac))->now->son=s1;
	GTN *s2=gtn_newnode(",");
	s1->brother=s2;
	GTN *s3=gtn_newnode("IDENTIFIER");
	s2->brother=s3;
	GTN *s33=gtn_newnode((yyvsp[0].string));
	s3->son=s33;
}
#line 1793 "gpl.c" /* yacc.c:1646  */
    break;

  case 17:
#line 466 "gpl.y" /* yacc.c:1646  */
    {
	(yyval.tac)=NULL;
}
#line 1801 "gpl.c" /* yacc.c:1646  */
    break;

  case 18:
#line 472 "gpl.y" /* yacc.c:1646  */
    {
	GTN *s1=gtn_copynode(((yyvsp[-1].tac))->now);
	((yyval.tac))->now=gtn_newnode("statement");
	((yyval.tac))->now->son=s1;
	GTN *s2=gtn_newnode(";");
	s1->brother=s2;
}
#line 1813 "gpl.c" /* yacc.c:1646  */
    break;

  case 19:
#line 480 "gpl.y" /* yacc.c:1646  */
    {
	GTN *s1=gtn_copynode(((yyvsp[-1].tac))->now);
	((yyval.tac))->now=gtn_newnode("statement");
	((yyval.tac))->now->son=s1;
	GTN *s2=gtn_newnode(";");
	s1->brother=s2;
}
#line 1825 "gpl.c" /* yacc.c:1646  */
    break;

  case 20:
#line 488 "gpl.y" /* yacc.c:1646  */
    {
	GTN *s1=gtn_copynode(((yyvsp[-1].tac))->now);
	((yyval.tac))->now=gtn_newnode("statement");
	((yyval.tac))->now->son=s1;
	GTN *s2=gtn_newnode(";");
	s1->brother=s2;
}
#line 1837 "gpl.c" /* yacc.c:1646  */
    break;

  case 21:
#line 496 "gpl.y" /* yacc.c:1646  */
    {
	GTN *s1=gtn_copynode(((yyvsp[-1].tac))->now);
	((yyval.tac))->now=gtn_newnode("statement");
	((yyval.tac))->now->son=s1;
	GTN *s2=gtn_newnode(";");
	s1->brother=s2;
}
#line 1849 "gpl.c" /* yacc.c:1646  */
    break;

  case 22:
#line 504 "gpl.y" /* yacc.c:1646  */
    {
	((yyval.tac))->now=gtn_newnode("statement");
	GTN *s2=gtn_newnode(";");
	((yyval.tac))->now->son=s2;
}
#line 1859 "gpl.c" /* yacc.c:1646  */
    break;

  case 23:
#line 510 "gpl.y" /* yacc.c:1646  */
    {
	GTN *s1=gtn_copynode(((yyvsp[0].tac))->now);
	((yyval.tac))->now=gtn_newnode("statement");
	((yyval.tac))->now->son=s1;
}
#line 1869 "gpl.c" /* yacc.c:1646  */
    break;

  case 24:
#line 516 "gpl.y" /* yacc.c:1646  */
    {
	GTN *s1=gtn_copynode(((yyvsp[0].tac))->now);
	((yyval.tac))->now=gtn_newnode("statement");
	((yyval.tac))->now->son=s1;
}
#line 1879 "gpl.c" /* yacc.c:1646  */
    break;

  case 25:
#line 522 "gpl.y" /* yacc.c:1646  */
    {
	GTN *s1=gtn_copynode(((yyvsp[0].tac))->now);
	((yyval.tac))->now=gtn_newnode("statement");
	((yyval.tac))->now->son=s1;
}
#line 1889 "gpl.c" /* yacc.c:1646  */
    break;

  case 26:
#line 528 "gpl.y" /* yacc.c:1646  */
    {
	GTN *s1=gtn_copynode(((yyvsp[0].tac))->now);
	((yyval.tac))->now=gtn_newnode("statement");
	((yyval.tac))->now->son=s1;
}
#line 1899 "gpl.c" /* yacc.c:1646  */
    break;

  case 27:
#line 534 "gpl.y" /* yacc.c:1646  */
    {
	error("Bad statement syntax");
	(yyval.tac)=NULL;
}
#line 1908 "gpl.c" /* yacc.c:1646  */
    break;

  case 28:
#line 541 "gpl.y" /* yacc.c:1646  */
    {
	GTN *s1=gtn_copynode(((yyvsp[0].tac))->now);
	((yyval.tac))->now=gtn_newnode("PMS");
	((yyval.tac))->now->son=s1;
}
#line 1918 "gpl.c" /* yacc.c:1646  */
    break;

  case 29:
#line 547 "gpl.y" /* yacc.c:1646  */
    {
	GTN *s1=gtn_copynode(((yyvsp[0].tac))->now);
	((yyval.tac))->now=gtn_newnode("PMS");
	((yyval.tac))->now->son=s1;
}
#line 1928 "gpl.c" /* yacc.c:1646  */
    break;

  case 30:
#line 553 "gpl.y" /* yacc.c:1646  */
    {
	GTN *s1=gtn_copynode(((yyvsp[0].tac))->now);
	((yyval.tac))->now=gtn_newnode("PMS");
	((yyval.tac))->now->son=s1;
}
#line 1938 "gpl.c" /* yacc.c:1646  */
    break;

  case 31:
#line 559 "gpl.y" /* yacc.c:1646  */
    {
	((yyval.tac))->now=gtn_newnode("PMS");
}
#line 1946 "gpl.c" /* yacc.c:1646  */
    break;

  case 32:
#line 563 "gpl.y" /* yacc.c:1646  */
    {
	error("bad semanteme:expected primary-statement");
	(yyval.tac)=NULL;
}
#line 1955 "gpl.c" /* yacc.c:1646  */
    break;

  case 33:
#line 570 "gpl.y" /* yacc.c:1646  */
    {
	GTN *s3=gtn_copynode(((yyvsp[-1].tac))->now);
	(yyval.tac)=join_tac((yyvsp[-2].tac), (yyvsp[-1].tac));
	((yyval.tac))->now=gtn_newnode("block");
	GTN *s1=gtn_newnode("{");
	((yyval.tac))->now->son=s1;
	if ((yyvsp[-2].tac)!=NULL) {
		s1->brother=((yyvsp[-2].tac))->now;
		((yyvsp[-2].tac))->now->brother=s3;
	}
	else s1->brother=s3;
	GTN *s4=gtn_newnode("}");
	s3->brother=s4;
}
#line 1974 "gpl.c" /* yacc.c:1646  */
    break;

  case 34:
#line 587 "gpl.y" /* yacc.c:1646  */
    {
	(yyval.tac)=NULL;
}
#line 1982 "gpl.c" /* yacc.c:1646  */
    break;

  case 35:
#line 591 "gpl.y" /* yacc.c:1646  */
    {
	GTN *s2=gtn_copynode(((yyvsp[0].tac))->now);
	(yyval.tac)=join_tac((yyvsp[-1].tac), (yyvsp[0].tac));
	((yyval.tac))->now=gtn_newnode("DL");
	if ((yyvsp[-1].tac)==NULL) {
		((yyval.tac))->now->son=s2;
	}
	else {
		((yyval.tac))->now->son=((yyvsp[-1].tac))->now;
		((yyvsp[-1].tac))->now->brother=s2;
	}
}
#line 1999 "gpl.c" /* yacc.c:1646  */
    break;

  case 36:
#line 606 "gpl.y" /* yacc.c:1646  */
    {
	GTN *s1=gtn_copynode(((yyvsp[0].tac))->now);
	((yyval.tac))->now=gtn_newnode("SL");
	((yyval.tac))->now->son=s1;
}
#line 2009 "gpl.c" /* yacc.c:1646  */
    break;

  case 37:
#line 612 "gpl.y" /* yacc.c:1646  */
    {
	GTN *s2=gtn_copynode(((yyvsp[0].tac))->now);
	(yyval.tac)=join_tac((yyvsp[-1].tac), (yyvsp[0].tac));
	((yyval.tac))->now=gtn_newnode("SL");
	((yyval.tac))->now->son=((yyvsp[-1].tac))->now;
	((yyvsp[-1].tac))->now->brother=s2;
}
#line 2021 "gpl.c" /* yacc.c:1646  */
    break;

  case 38:
#line 622 "gpl.y" /* yacc.c:1646  */
    {
	GTN *s3=gtn_copynode(((yyvsp[0].enode))->now);
	(yyval.tac)=do_assign(getvar((yyvsp[-2].string)), (yyvsp[0].enode));
	((yyval.tac))->now=gtn_newnode("AS");
	GTN *s1=gtn_newnode("IDENTIFIER");
	((yyval.tac))->now->son=s1;
	GTN *s11=gtn_newnode((yyvsp[-2].string));
	s1->son=s11;
	GTN *s2=gtn_newnode("=");
	s1->brother=s2;
	s2->brother=s3;
}
#line 2038 "gpl.c" /* yacc.c:1646  */
    break;

  case 39:
#line 637 "gpl.y" /* yacc.c:1646  */
    {
	GTN *s1=gtn_copynode(((yyvsp[-2].enode))->now);
	(yyval.enode)=do_bin(TAC_ADD, (yyvsp[-2].enode), (yyvsp[0].enode));
	((yyval.enode))->now=gtn_newnode("expression");
	((yyval.enode))->now->son=s1;
	GTN *s2=gtn_newnode("+");
	s1->brother=s2;
	s2->brother=((yyvsp[0].enode))->now;
}
#line 2052 "gpl.c" /* yacc.c:1646  */
    break;

  case 40:
#line 647 "gpl.y" /* yacc.c:1646  */
    {
	GTN *s1=gtn_copynode(((yyvsp[-2].enode))->now);
	(yyval.enode)=do_bin(TAC_SUB, (yyvsp[-2].enode), (yyvsp[0].enode));
	((yyval.enode))->now=gtn_newnode("expression");
	((yyval.enode))->now->son=s1;
	GTN *s2=gtn_newnode("-");
	s1->brother=s2;
	s2->brother=((yyvsp[0].enode))->now;
}
#line 2066 "gpl.c" /* yacc.c:1646  */
    break;

  case 41:
#line 657 "gpl.y" /* yacc.c:1646  */
    {
	GTN *s1=gtn_copynode(((yyvsp[-2].enode))->now);
	(yyval.enode)=do_bin(TAC_MUL, (yyvsp[-2].enode), (yyvsp[0].enode));
	((yyval.enode))->now=gtn_newnode("expression");
	((yyval.enode))->now->son=s1;
	GTN *s2=gtn_newnode("*");
	s1->brother=s2;
	s2->brother=((yyvsp[0].enode))->now;
}
#line 2080 "gpl.c" /* yacc.c:1646  */
    break;

  case 42:
#line 667 "gpl.y" /* yacc.c:1646  */
    {
	GTN *s1=gtn_copynode(((yyvsp[-2].enode))->now);
	(yyval.enode)=do_bin(TAC_DIV, (yyvsp[-2].enode), (yyvsp[0].enode));
	((yyval.enode))->now=gtn_newnode("expression");
	((yyval.enode))->now->son=s1;
	GTN *s2=gtn_newnode("/");
	s1->brother=s2;
	s2->brother=((yyvsp[0].enode))->now;
}
#line 2094 "gpl.c" /* yacc.c:1646  */
    break;

  case 43:
#line 677 "gpl.y" /* yacc.c:1646  */
    {
	GTN *s2=gtn_copynode(((yyvsp[0].enode))->now);
	(yyval.enode)=do_un(TAC_NEG, (yyvsp[0].enode));
	((yyval.enode))->now=gtn_newnode("expression");
	GTN *s1=gtn_newnode("-");
	((yyval.enode))->now->son=s1;
	s1->brother=s2;
}
#line 2107 "gpl.c" /* yacc.c:1646  */
    break;

  case 44:
#line 686 "gpl.y" /* yacc.c:1646  */
    {
	GTN *s1=gtn_copynode(((yyvsp[-2].enode))->now);
	(yyval.enode)=do_cmp(TAC_EQ, (yyvsp[-2].enode), (yyvsp[0].enode));
	((yyval.enode))->now=gtn_newnode("expression");
	((yyval.enode))->now->son=s1;
	GTN *s2=gtn_newnode("==");
	s1->brother=s2;
	s2->brother=((yyvsp[0].enode))->now;
}
#line 2121 "gpl.c" /* yacc.c:1646  */
    break;

  case 45:
#line 696 "gpl.y" /* yacc.c:1646  */
    {
	GTN *s1=gtn_copynode(((yyvsp[-2].enode))->now);
	(yyval.enode)=do_cmp(TAC_NE, (yyvsp[-2].enode), (yyvsp[0].enode));
	((yyval.enode))->now=gtn_newnode("expression");
	((yyval.enode))->now->son=s1;
	GTN *s2=gtn_newnode("!=");
	s1->brother=s2;
	s2->brother=((yyvsp[0].enode))->now;
}
#line 2135 "gpl.c" /* yacc.c:1646  */
    break;

  case 46:
#line 706 "gpl.y" /* yacc.c:1646  */
    {
	GTN *s1=gtn_copynode(((yyvsp[-2].enode))->now);
	(yyval.enode)=do_cmp(TAC_LT, (yyvsp[-2].enode), (yyvsp[0].enode));
	((yyval.enode))->now=gtn_newnode("expression");
	((yyval.enode))->now->son=s1;
	GTN *s2=gtn_newnode("<");
	s1->brother=s2;
	s2->brother=((yyvsp[0].enode))->now;
}
#line 2149 "gpl.c" /* yacc.c:1646  */
    break;

  case 47:
#line 716 "gpl.y" /* yacc.c:1646  */
    {
	GTN *s1=gtn_copynode(((yyvsp[-2].enode))->now);
	(yyval.enode)=do_cmp(TAC_LE, (yyvsp[-2].enode), (yyvsp[0].enode));
	((yyval.enode))->now=gtn_newnode("expression");
	((yyval.enode))->now->son=s1;
	GTN *s2=gtn_newnode("<=");
	s1->brother=s2;
	s2->brother=((yyvsp[0].enode))->now;
}
#line 2163 "gpl.c" /* yacc.c:1646  */
    break;

  case 48:
#line 726 "gpl.y" /* yacc.c:1646  */
    {
	GTN *s1=gtn_copynode(((yyvsp[-2].enode))->now);
	(yyval.enode)=do_cmp(TAC_GT, (yyvsp[-2].enode), (yyvsp[0].enode));
	((yyval.enode))->now=gtn_newnode("expression");
	((yyval.enode))->now->son=s1;
	GTN *s2=gtn_newnode(">");
	s1->brother=s2;
	s2->brother=((yyvsp[0].enode))->now;
}
#line 2177 "gpl.c" /* yacc.c:1646  */
    break;

  case 49:
#line 736 "gpl.y" /* yacc.c:1646  */
    {
	GTN *s1=gtn_copynode(((yyvsp[-2].enode))->now);
	(yyval.enode)=do_cmp(TAC_GE, (yyvsp[-2].enode), (yyvsp[0].enode));
	((yyval.enode))->now=gtn_newnode("expression");
	((yyval.enode))->now->son=s1;
	GTN *s2=gtn_newnode(">=");
	s1->brother=s2;
	s2->brother=((yyvsp[0].enode))->now;
}
#line 2191 "gpl.c" /* yacc.c:1646  */
    break;

  case 50:
#line 746 "gpl.y" /* yacc.c:1646  */
    {
	GTN *s2=gtn_copynode(((yyvsp[-1].enode))->now);
	(yyval.enode)=(yyvsp[-1].enode);
	((yyval.enode))->now=gtn_newnode("expression");
	GTN *s1=gtn_newnode("(");
	((yyval.enode))->now->son=s1;
	s1->brother=s2;
	GTN *s3=gtn_newnode(")");
	s2->brother=s3;
}
#line 2206 "gpl.c" /* yacc.c:1646  */
    break;

  case 51:
#line 757 "gpl.y" /* yacc.c:1646  */
    {
	(yyval.enode)=mkenode(NULL, mkconst(atoi((yyvsp[0].string))), NULL);
	((yyval.enode))->now=gtn_newnode("expression");
	GTN *s1=gtn_newnode("INTEGER");
	((yyval.enode))->now->son=s1;
	GTN *s11=gtn_newnode((yyvsp[0].string));
	s1->son=s11;
}
#line 2219 "gpl.c" /* yacc.c:1646  */
    break;

  case 52:
#line 766 "gpl.y" /* yacc.c:1646  */
    {
	(yyval.enode)=mkenode(NULL, getvar((yyvsp[0].string)), NULL);
	((yyval.enode))->now=gtn_newnode("expression");
	GTN *s1=gtn_newnode("IDENTIFIER");
	((yyval.enode))->now->son=s1;
	GTN *s11=gtn_newnode((yyvsp[0].string));
	s1->son=s11;
}
#line 2232 "gpl.c" /* yacc.c:1646  */
    break;

  case 53:
#line 775 "gpl.y" /* yacc.c:1646  */
    {
	GTN *s1=gtn_copynode(((yyvsp[0].enode))->now);
	(yyval.enode)=(yyvsp[0].enode);
	((yyval.enode))->now=gtn_newnode("expression");
	((yyval.enode))->now->son=s1;
}
#line 2243 "gpl.c" /* yacc.c:1646  */
    break;

  case 54:
#line 782 "gpl.y" /* yacc.c:1646  */
    {
	error("Bad expression syntax");
	(yyval.enode)=mkenode(NULL, NULL, NULL);
}
#line 2252 "gpl.c" /* yacc.c:1646  */
    break;

  case 55:
#line 789 "gpl.y" /* yacc.c:1646  */
    {
	(yyval.enode)=NULL;
}
#line 2260 "gpl.c" /* yacc.c:1646  */
    break;

  case 56:
#line 793 "gpl.y" /* yacc.c:1646  */
    {
	GTN *s1=gtn_copynode(((yyvsp[0].enode))->now);
	((yyval.enode))->now=gtn_newnode("AL");
	((yyval.enode))->now->son=s1;
}
#line 2270 "gpl.c" /* yacc.c:1646  */
    break;

  case 57:
#line 801 "gpl.y" /* yacc.c:1646  */
    {
	GTN *s1=gtn_copynode(((yyvsp[0].enode))->now);
	((yyval.enode))->now=gtn_newnode("EL");
	((yyval.enode))->now->son=s1;
}
#line 2280 "gpl.c" /* yacc.c:1646  */
    break;

  case 58:
#line 807 "gpl.y" /* yacc.c:1646  */
    {
	GTN *s3=gtn_copynode(((yyvsp[0].enode))->now);
	(yyvsp[0].enode)->next=(yyvsp[-2].enode);
	(yyval.enode)=(yyvsp[0].enode);
	((yyval.enode))->now=gtn_newnode("EL");
	((yyval.enode))->now->son=((yyvsp[-2].enode))->now;
	GTN *s2=gtn_newnode(",");
	((yyvsp[-2].enode))->now->brother=s2;
	s2->brother=s3;
}
#line 2295 "gpl.c" /* yacc.c:1646  */
    break;

  case 59:
#line 820 "gpl.y" /* yacc.c:1646  */
    {
	GTN *s3=gtn_copynode(((yyvsp[-1].tac))->now);
	(yyval.tac)=(yyvsp[-1].tac);
	((yyval.tac))->now=gtn_newnode("PTS");
	GTN *s1=gtn_newnode("PRINT");
	((yyval.tac))->now->son=s1;
	GTN *s2=gtn_newnode("(");
	s1->brother=s2;
	s2->brother=s3;
	GTN *s4=gtn_newnode(")");
	s3->brother=s4;
}
#line 2312 "gpl.c" /* yacc.c:1646  */
    break;

  case 60:
#line 835 "gpl.y" /* yacc.c:1646  */
    {
	GTN *s1=gtn_copynode(((yyvsp[0].tac))->now);
	((yyval.tac))->now=gtn_newnode("print_list");
	((yyval.tac))->now->son=s1;
}
#line 2322 "gpl.c" /* yacc.c:1646  */
    break;

  case 61:
#line 841 "gpl.y" /* yacc.c:1646  */
    {
	GTN *s3=gtn_copynode(((yyvsp[0].tac))->now);
	(yyval.tac)=join_tac((yyvsp[-2].tac), (yyvsp[0].tac));
	((yyval.tac))->now=gtn_newnode("print_list");
	((yyval.tac))->now->son=((yyvsp[-2].tac))->now;
	GTN *s2=gtn_newnode(",");
	((yyvsp[-2].tac))->now->brother=s2;
	s2->brother=s3;
}
#line 2336 "gpl.c" /* yacc.c:1646  */
    break;

  case 62:
#line 853 "gpl.y" /* yacc.c:1646  */
    {
	GTN *s1=gtn_copynode(((yyvsp[0].enode))->now);
	(yyval.tac)=join_tac((yyvsp[0].enode)->tac,
	do_lib("PRINTN", (yyvsp[0].enode)->ret));
	((yyval.tac))->now=gtn_newnode("print_item");
	((yyval.tac))->now->son=s1;
}
#line 2348 "gpl.c" /* yacc.c:1646  */
    break;

  case 63:
#line 861 "gpl.y" /* yacc.c:1646  */
    {
	(yyval.tac)=do_lib("PRINTS", mktext((yyvsp[0].string)));
	((yyval.tac))->now=gtn_newnode("print_item");
	GTN *s1=gtn_newnode("TEXT");
	((yyval.tac))->now->son=s1;
	GTN *s11=gtn_newnode((yyvsp[0].string));
	s1->son=s11;
}
#line 2361 "gpl.c" /* yacc.c:1646  */
    break;

  case 64:
#line 872 "gpl.y" /* yacc.c:1646  */
    {
	GTN *s2=gtn_copynode(((yyvsp[0].enode))->now);
	TAC *t=mktac(TAC_RETURN, (yyvsp[0].enode)->ret, NULL, NULL);
	t->prev=(yyvsp[0].enode)->tac;
	free_enode((yyvsp[0].enode));
	(yyval.tac)=t;
	((yyval.tac))->now=gtn_newnode("return_statement");
	GTN *s1=gtn_newnode("RETURN");
	((yyval.tac))->now->son=s1;
	s1->brother=s2;
}
#line 2377 "gpl.c" /* yacc.c:1646  */
    break;

  case 65:
#line 886 "gpl.y" /* yacc.c:1646  */
    {
	(yyval.tac)=NULL;
}
#line 2385 "gpl.c" /* yacc.c:1646  */
    break;

  case 66:
#line 892 "gpl.y" /* yacc.c:1646  */
    {
	GTN *s3=gtn_copynode(((yyvsp[-2].enode))->now);
	(yyval.tac)=do_if((yyvsp[-2].enode), (yyvsp[0].tac));
	((yyval.tac))->now=gtn_newnode("if_statement");
	GTN *s1=gtn_newnode("IF");
	((yyval.tac))->now->son=s1;
	GTN *s2=gtn_newnode("(");
	s1->brother=s2;
	s2->brother=s3;
	GTN *s4=gtn_newnode(")");
	s3->brother=s4;
	s4->brother=((yyvsp[0].tac))->now;
}
#line 2403 "gpl.c" /* yacc.c:1646  */
    break;

  case 67:
#line 906 "gpl.y" /* yacc.c:1646  */
    {
	GTN *s3=gtn_copynode(((yyvsp[-4].enode))->now);
	(yyval.tac)=do_test((yyvsp[-4].enode), (yyvsp[-2].tac), (yyvsp[0].tac));
	((yyval.tac))->now=gtn_newnode("if_statement");
	GTN *s1=gtn_newnode("IF");
	((yyval.tac))->now->son=s1;
	GTN *s2=gtn_newnode("(");
	s1->brother=s2;
	s2->brother=s3;
	GTN *s4=gtn_newnode(")");
	s3->brother=s4;
	s4->brother=((yyvsp[-2].tac))->now;
	GTN *s6=gtn_newnode("ELSE");
	((yyvsp[-2].tac))->now->brother=s6;
	s6->brother=((yyvsp[0].tac))->now;
}
#line 2424 "gpl.c" /* yacc.c:1646  */
    break;

  case 68:
#line 925 "gpl.y" /* yacc.c:1646  */
    {
	GTN *s3=gtn_copynode(((yyvsp[-2].enode))->now);
	(yyval.tac)=do_while((yyvsp[-2].enode), (yyvsp[0].tac));
	((yyval.tac))->now=gtn_newnode("while_statement");
	GTN *s1=gtn_newnode("WHILE");
	((yyval.tac))->now->son=s1;
	GTN *s2=gtn_newnode("(");
	s1->brother=s2;
	s2->brother=s3;
	GTN *s4=gtn_newnode(")");
	s3->brother=s4;
	s4->brother=((yyvsp[0].tac))->now;
}
#line 2442 "gpl.c" /* yacc.c:1646  */
    break;

  case 69:
#line 941 "gpl.y" /* yacc.c:1646  */
    {
	GTN *s5=gtn_copynode(((yyvsp[-4].enode))->now);
	(yyval.tac)=do_for((yyvsp[-6].tac),(yyvsp[-4].enode),(yyvsp[-2].tac),(yyvsp[0].tac));
	((yyval.tac))->now=gtn_newnode("for_statement");
	GTN *s1=gtn_newnode("FOR");
	((yyval.tac))->now->son=s1;
	GTN *s2=gtn_newnode("(");
	s1->brother=s2;
	s2->brother=((yyvsp[-6].tac))->now;
	GTN *s4=gtn_newnode(";");
	((yyvsp[-6].tac))->now->brother=s4;
	s4->brother=s5;
	GTN *s6=gtn_newnode(";");
	s5->brother=s6;
	s6->brother=((yyvsp[-2].tac))->now;
	GTN *s8=gtn_newnode(")");
	((yyvsp[-2].tac))->now->brother=s8;
	s8->brother=((yyvsp[0].tac))->now;
}
#line 2466 "gpl.c" /* yacc.c:1646  */
    break;

  case 70:
#line 963 "gpl.y" /* yacc.c:1646  */
    {
	
	GTN *s3=gtn_copynode(((yyvsp[-1].enode))->now);
	(yyval.tac)=do_call((yyvsp[-3].string), (yyvsp[-1].enode));
	((yyval.tac))->now=gtn_newnode("call_statement");
	GTN *s1=gtn_newnode("IDENTIFIER");
	((yyval.tac))->now->son=s1;
	GTN *s11=gtn_newnode((yyvsp[-3].string));
	s1->son=s11;
	GTN *s2=gtn_newnode("(");
	s1->brother=s2;
	s2->brother=s3;
	GTN *s4=gtn_newnode(")");
	s3->brother=s4;
}
#line 2486 "gpl.c" /* yacc.c:1646  */
    break;

  case 71:
#line 981 "gpl.y" /* yacc.c:1646  */
    {
	GTN *s3=gtn_copynode(((yyvsp[-1].enode))->now);
	(yyval.enode)=do_call_ret((yyvsp[-3].string), (yyvsp[-1].enode));
	((yyval.enode))->now=gtn_newnode("call_expression");
	GTN *s1=gtn_newnode("IDENTIFIER");
	((yyval.enode))->now->son=s1;
	GTN *s11=gtn_newnode((yyvsp[-3].string));
	s1->son=s11;
	GTN *s2=gtn_newnode("(");
	s1->brother=s2;
	s2->brother=s3;
	GTN *s4=gtn_newnode(")");
	s3->brother=s4;
}
#line 2505 "gpl.c" /* yacc.c:1646  */
    break;


#line 2509 "gpl.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 998 "gpl.y" /* yacc.c:1906  */


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
