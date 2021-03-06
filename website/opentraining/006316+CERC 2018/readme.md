# 训练笔记

A|B|C|D|E|F|G|H|I|J|K|L
---|---|---|---|---|---|---|---|---|---|---|---
O|Q|O| |O| |O| |O|O|Q|O

> 其中O表示训练时通过，Q表示补题通过，X表示尝试过但未通过，为空表示至今未提交过。

### 难度分类

简单题：ACIJ；中档题：BEGKL；难题：DFH

### 简易题意和题解

#### 简单题
A题：给一个文本串和一些单词串，问文本串最少由几个单词串拼接而来，单词串可以重叠。
简易题解：直接对单词串建立AC自动机，然后文本串在上面跑，对于每个单词的结尾位置需要找到最长的匹配单词串，AC自动机需要预处理每个节点跳fail链最近的终止节点，剩下就是一个简单DP用线段树维护一下就可以了。

C题：给一个01串S，每次操作可以S&(S>>i) i任意，两次操作i可以不同，问最少几次操作变成全1，无解输出-1。（串长度只有40）
简易题解：由于串长度的限制，可以大力搜索，但是直接莽（40^6）会T，需要一定的剪枝，比如每次操作 i 非降（因为操作满足交换律，可以人为规定非降），同时每次操作第一个0一定转变为1（否则在满足前一条剪枝的条件下无法填成全1）。

I题：体积小于n的长方体三边长为整数且互不相同的方案数。（大概？队友做的。。。）
简易题解：（不是我写的，纯口胡）枚举每种体积的因子作为一边长，剩下部分是个O(1)，可以直接计算。由于n只有1e6，用一个调和级数的算法就可以了，时间有点卡，两个1e6的调和级数就挂了，只能跑一遍。

J题：给一个字符矩阵，问同字符的等腰直角三角形的个数（直角边水平或竖直）。
简易题解：处理一种方向的三角形即可，其余方向的三角形旋转矩阵即可。求一种方向（比如直角在右下）的可以用DP来做，注意到如果一行一行处理，枚举到直角点(i,j)，该次的答案取决于(i-1,j)与(i,j-1)。

#### 中档题
E题：给一颗树以及一些平面上的点。求一种对应方式使得所有树边在平面上不相交。
简易题解：由于点数不多1000级别，可以每次极角排序，然后按根的子树大小分组，递归处理子树，复杂度$n^2 log\ n$。

G题：给两种操作，一种操作是给一个矩形涂黑，第二种操作是询问两个格子是否通过黑格子四联通（注意给的询问格子不一定是黑格子，不是输出0）。坐标x轴只有1~50，y轴坐标只有1~100000。
简易题解：暴力处理出每个格子最早是在什么时候被涂黑的，之后按时间顺序并查集模拟即可。

L题：非均等博弈，在经典的两人取石子博弈中加一个条件，第一个人最多取A个石子，第二个人最多取B个石子。
简易题解：（不是我做的，我也不知道为啥的结论就对了？）具体来说好像是一个局面如果先手可取的石子数大于后手，先手必胜。另外如果局面中最多石子数小于min(A,B)，那么退化为一个均等博弈，直接求异或和即可。针对这两条结论，对于先手石子数小于后手的情况，可以枚举第一步取啥，转化为结论的两条情况。

B题：N个点的图，有Q次操作，操作分三种：0 X Y V，在X与Y之间连一条危险度为V的边（V为1到10）；1 X Y，毁掉X与Y之间的连边（保证此时X---Y该边一定存在）；2 X Y，询问X到Y的所有路径中危险度最大的最小可能值。
简易题解：队友做的，可退并查集。

K题：给一些镜子（镜子数小于等于8），只可以反射一次，问起点到终点合法的路径有几条。
简易题解：暴力枚举经过的镜子顺序，暴力判断是否合法即可，傻逼几何题没时间写。

#### 难题
DFH


### 文件夹包含

题目和题解
B题数据和std
赛后过的B、K