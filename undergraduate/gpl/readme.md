## 文件（夹）说明

根目录为gpl，包含三个文件夹。source里包含源文件以及makefile共5个文件，debug文件夹包含3个编译好的可执行文件以及两个\*.y文件的中间\*.c输出文件，可以直接运行在实验机上。sample文件夹是原本clone时就存在的测试文件，sample-new文件夹包含本人设计的5组新测试用例文件，error文件夹下包含了一系列编译错误文件，错误原因各不相同，在各自的输出文件中写出了。

编译环境使用bison-3.0+gcc (Debian 4.9.2-10) 4.9.2，与实验机一致，安装方法请自行google。



## 实验说明书一

本作品在老师半成品基础上修改得来，支持了词法分析，将逐个输出遇到的关键字、标识符、整形常量、字符串常量、运算符和界符。各个字符输出格式如下：

| 类型       | 输出格式                  |
| ---------- | ------------------------- |
| 关键字     | keyword    %+5s (%3d,-)   |
| 标识符     | identifier %+5s (%3d,%X)  |
| 整形常量   | number     %+5s (%3d,%X)  |
| 字符串常量 | string     %+5s (%3d,%X)  |
| 运算符     | operator       %c (%3d,-) |
| 界符       | delimiter      %c (%3d,-) |

本程序会对非法字符报错lex error: undefined character!；会对不在同一行的字符串常量报错lex error: \" expected；会对！后接非=报错lex error: = expected。由于语法分析的同步进行，实测大部分错误会报语法错误而不是词法错误。

修改了老师的代码，将报错用yyerror统一输出。其次发现yyerror的行号输出有误，原因在于getnbc里滤除特殊字符时，换行没有line++。

本程序会输出一个全局变量表和多个局部变量表。

符号表管理由于与语法和语义分析共用同一个符号表，与后续步骤杂糅较多，本程序没有对此做过多区分，因此会出现一些中间临时变量也形成了局部变量。其次局部变量在函数结束时清空，所以在语法分析该函数结束前输出，故输出位置可能不在文件最后。

该程序已经上传我的 [github](https://github.com/lxambulance/gpl)

使用方法很简单，下载所有文件，在老师的服务器上相应下载文件的目录里输入make命令，即可自动编译（**注意makefile文件略有修改，实测实验机器可以运行**），编译完成后得到gpl的可执行文件，在可执行目录下输入./gpl name -lex（name需要带上./sample-new/的路径）即可对目标文件name.gpl做词法分析，结果全部输出到name.lex文件里。**其余三个实验测试操作步骤基本相同，将后缀改成-syn或-tac或不加即可，最后需要跑汇编代码可以先输入./gal name编译汇编代码，再输入./gvm name运行汇编。**

出错处理见error文件夹。

现场问题：

新修改的代码仍旧保存在gpl.y中，前面原来的代码已经删除。新代码不破坏老代码的输出，只是在最后加了一部分新的输出。

1、借用老师代码，具体见line 68结构体symb

2、现在使用gpl.y将在最后首先打印一个hashstr字符串（一整个**地址连续的**串，定义在line286-291），然后将输出hash表中存入项目条数，每一条项目打印一行信息，包含这个符号在哈希表中的地址，该地址字符串指针所指的内容以及在hashstr中的偏移量。

3、哈希表定义在line 286-291，hash_add函数实现在line2358-2371，采用了线性探测避免冲突，每一项存储了该字面量在hashstr的首地址指针和一个判断重复的hashkey，为了输出的方便，又用一个hashtable存储了hash表被占用的那几项。

对文件夹中sample/while.gpl的输出示例如下：

```
identifier  main (279,0x8fe0038)
delimiter      ( ( 40,-)
delimiter      ) ( 41,-)
delimiter      { (123,-)
keyword      int (270,-)
identifier     i (279,0x8fe00e8)
delimiter      ; ( 59,-)
identifier     i (279,0x8fe0288)
operator       = ( 61,-)
number         1 (278,0x8fe02a8)
delimiter      ; ( 59,-)
keyword    while (266,-)
delimiter      ( ( 40,-)
identifier     i (279,0x8fe04f0)
operator       < (273,-)
number        10 (278,0x8fe0588)
delimiter      ) ( 41,-)
delimiter      { (123,-)
keyword    print (259,-)
delimiter      ( ( 40,-)
identifier     i (279,0x8fe0730)
delimiter      , ( 44,-)
string      "\n" (280,0x8fe0888)
delimiter      ) ( 41,-)
delimiter      ; ( 59,-)
identifier     i (279,0x8fe0b50)
operator       = ( 61,-)
identifier     i (279,0x8fe0b60)
operator       + ( 43,-)
number         1 (278,0x8fe0c10)
delimiter      ; ( 59,-)
delimiter      } (125,-)
delimiter      } (125,-)
main       LocalSymbolTable
VAR        (0x8fe0d00,t1)
VAR        (0x8fe0678,t0)
VAR        (0x8fe00f8,i)
=====GlobalSymbolTable=====
STRING     (0x8fe0898,"\n")
===========================
hashstring:
0: m
1: a
2: i
3: n
5: i
7: 1
9: 1
10: 0
12: "
13: \
14: n
15: "

5
hashtable(address:3ed3d,name:main,offset:0)
hashtable(address:69,name:i,offset:5)
hashtable(address:31,name:1,offset:7)
hashtable(address:2ad,name:10,offset:9)
hashtable(address:1663e,name:"\n",offset:12)
```



## 实验说明书二

本作品为老师作品的加强版，在所有的tac节点、enode节点和symb节点上加入了自定义的GrammerTreeNode节点，表示语法树上的一个点。该类型采用左儿子、右兄弟的方式将多叉树转二叉树存储，其定义如下：
```
typedef struct GrammerTreeNode{
	char *name;
	int size;
	struct GrammerTreeNode *brother,*son;
}GTN;
```
name表示该节点的名称，size是输出行数，用于后续输出统计。

本程序用制表符输出语法树，涉及到5个特殊字符{"┬","├","└","─","│"}，大致输出效果（该输出不是程序实际输出，是演示输出，实际输出情况请查看[github](https://github.com/lxambulance/gpl)（**由于输出宽度过宽，这里贴文本内容较丑，请翻阅对应文件查看，查看时注意去掉在状态栏里txt方式打开的自动换行**），项目内还提供有测试文件）如下：
```
folder1┬─name0
       ├─name1
       ├─name2
       ├─folder2┬─name5
       │        ├─name6
       │        └─name7
       ├─name3
       └─name4
```
由于宽度过长，本程序对长命名称做了压缩，具体压缩项有

```
function_declaration_list:FDL
function_declaration:FD
function_head:FH
declaration_list:DL
variable_list:VL
statement_list:SL
parameter_list:PL
assignment_statement:AS
print_statement:PTS
primary_statement:PMS
argument_list:AL
expression_list:EL
```

前面为长名称，冒号后面为对应的压缩名称。

出错处理采用了老师的error函数，加上了输出行数的功能，现在出错会显示："错误信息at line行数。"

由于符号表具有local和global之分，全局和局部显而易见（具体见实验一的输出，那时候偷懒直接就用了老师的符号表输出，虽然现场问题又自己实现了一遍...）。

出错处理见error文件夹。

现场问题：

1、line 1056-1084 每次mkvar添加新变量的时候localScope记录当前处理行在函数内还是全局变量。localScope变量会随着匹配到函数开始的时候置为1，退出时置为0（**同一个函数内的不能有同名变量重复定义，函数中没有定义的变量会查找全局变量表**）。

2、具体见github测试文件夹sample-new下5个文件，如果想直接看输出结果，可是查看对应后缀的文件，文件内容为本机测试结果。

3、个性化功能详见line2384-2410 gtn_paint功能，它将输出当做一个画布，递归处理语法树输出，代码比较精简。




## 实验说明书三

使用了老师的三地址码输出，支持了for语句和变量直接赋值，且顺序传递了形参。修改了部分func.gpl代码如下：
```
	int l=1,m=2,n;
	n=func(2*2,1*3,n);
	for (l=0;l<5;l=l+1){
		print(l);
	}
```
测试三地址码输出如下（空行为书写报告时人工添加，方便查看，一行代码对应一块代码）：
```
	var l
	l = 1
	var m
	m = 2
	var n
	n = 3
	var t2
	
	actual 4
	actual 3
	actual n
	t2 = call func
	n = t2
	
	l = 0
	label L4
	var t3
	t3 = (l < 5)
	ifz t3 goto L5
	actual l
	call PRINTN
	var t4
	t4 = l + 1
	l = t4
	goto L4
	label L5
```
出错处理见error文件夹。

现场提问：

1、全局变量初始化分了两条语句，先一个var m的定义语句，再一个m=2的赋值语句，见上面示例段最开始

2、具体见测试文件夹sample-new

3、for语句着重考虑语义出错。for语句括号内的前后两部分语句，需要是一些基本语句段（基本语句段是本人测试c++部分语句试出来的部分结果，额外定义的一个lex类型），否则会报错，具体见error文件夹。可以请大家踊跃尝试，在for语句分号里写一些奇怪的语句，出错结果不同于语法和词法。




## 实验说明书四

采用老师的代码改进而来，修改了活动记录表，现在活动记录表按返回值、动态链接、参数和变量的顺序存放，除了当前函数变量在当前函数基址正偏移（包含0）外，其余全部在基址负偏移，**不用新定义位置标号，在源代码基础上加一些偏移量以及修改原偏移边界指针即可**。
函数传参顺序按照实验三改了，同时为了不出错，函数开始时的参数也做了对应调换处理。
由于在实验三改进而来，所以支持函数赋初值。

对文件夹中sample/func.gpl的部分输出示例如下：

```
func.gpl源文件部分：
...
	n=func(l,m,n);
...
func(o,p,q)
{
	print(o,p,q);
	i=o;
	j=p;
	k=q;
...
函数调用部分：
...
	# actual l
	LOD R5,(R2+0)
	STO (R2+24),R5

	# actual m
	LOD R6,(R2+4)
	STO (R2+28),R6

	# actual n
	LOD R7,(R2+8)
	STO (R2+32),R7

	# t0 = call func
	STO (R2+20),R2
	LOD R4,R1+32
	STO (R2+16),R4
	LOD R2,R2+36
	JMP func
...
函数实现部分：
...
	# i = o
	LOD R5,(R2-12)

	# j = p
	LOD R6,(R2-8)

	# k = q
	LOD R7,(R2-4)
...
```

现场提问：

1、参数在基址负偏移处，代码中tac里symb中offset存储偏移值。局部变量在基址正偏移处，同时tac里对应位置也存储了偏移，全局变量在最初定义，存在对应tac里。

2、具体见测试文件夹sample-new

3、对源文件改动极小，只是修改了几个偏移量以及两个边界变量的初始化值。同时修改了print函数，现在print函数活动记录表也按照我们新定义的顺序存放。整个测试程序代码可以完美地在老师的模拟器上运行，print函数输出如下（主要功能已经注释说明）：

```
	"\nPRINTN:\n" //对10取摸得到最低位
	"	LOD R7,(R2-4) # 789\n"
	"	LOD R15,R7 # 789 \n"
	"	DIV R7,10 # 78\n"
	"	TST R7\n"
	"	JEZ PRINTDIGIT\n"
	"	LOD R8,R7 # 78\n"
	"	MUL R8,10 # 780\n"
	"	SUB R15,R8 # 9\n"
	"	STO (R2),R15 # local 9 store\n"
	"\n	# out 78\n" //递归处理高位
	"	STO (R2+12),R7 # actual 78 push\n"
	"\n	# call PRINTN\n" //递归调用PRINTN
	"	STO (R2+8),R2\n"
	"	LOD R4,R1+32\n"
	"	STO (R2+4),R4\n"
	"	LOD R2,R2+16\n"
	"	JMP PRINTN\n"
	"\n	# out 9\n" //输出当前的最低位
	"	LOD R15,(R2) # local 9 \n"
	"\nPRINTDIGIT:\n" //输出数字0~9对应acsII码，原数加48
	"	ADD  R15,48\n"
	"	OUT\n"
	"\n	# ret\n" //PRINTN正常结束
	"	LOD R3,(R2-12)\n"
	"	LOD R2,(R2-8)\n"
	"	JMP R3\n"
	"\nPRINTS:\n" //输出字符串
	"	LOD R7,(R2-4)\n"
	"\nPRINTC:\n" //输出一个字符
	"	LOD R15,(R7)\n"
	"	DIV R15,16777216\n"
	"	TST R15\n" //测试字符串是否结束
	"	JEZ PRINTSEND\n"
	"	OUT\n"
	"	ADD R7,1\n"
	"	JMP PRINTC\n"
	"\nPRINTSEND:\n" //PRINTS正常结束
	"	# ret\n"
	"	LOD R3,(R2-12)\n"
	"	LOD R2,(R2-8)\n"
	"	JMP R3\n"
	
```

