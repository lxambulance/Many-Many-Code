# 训练笔记

| A   | B   | C   | D   | E   | F   | G   | H   | I   | J   | K   | L   | M   |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| O   | Q   |     | O   | O   | Q   | O   |     |     | O   |     | O   | O   |

> 其中O表示训练时通过，Q表示补题通过，X表示尝试过但未通过，为空表示至今未提交过。

### 难度分类

简单题：JDGA；中档题：MLEBFIK；难题：CH

### 通过题注意点

J题签到题，没看。

D题转化为直线下方整点个数。即：
$$
\sum_{i=1}^{n}\quad[\ (p*i)\mod q] = \frac{p*(n+1)*n}{2} - q*\sum_{i=1}^{n}\quad\lfloor\frac{p*i}{q}\rfloor
$$
G题扫描线左右端点丢入set，验证每次插入、删除的端点是否连续。

A题将多边形面积转化为每条边的贡献分开计算。

M题暂时不会。

L题最小路径覆盖裸题，最后统计合法点。

E题$2^m$枚举列的状态，边枚举边计算每一行是否递增或递减，同时还要维护任意两行的转移状态，即每列的增减状态，用一个$2^m$的数表示，枚举完列状态后DP。$DP_{i,j}$表示以第i行结尾的子矩阵，在当前枚举状态下每一列的增减状态为j的方案数，再用一个特殊状态$DP_{i,-1}$表示以第i行开始的子矩阵方案数，这样就可以得到一个$O(n^2)$的简单DP。总共转移是两维的，所以状态也只用了$n^2$个，用几个清理几个并不会有内存危机。枚举和预处理复杂度可以做到$O(n^2*2^n)​$，加上DP总复杂度不变，不过常数还是有点大，10s勉勉强强。

B题我们发现如果目标状态一行（或一列）包含两个X，则这行（或这列）没有元素被锤过。进一步推断我们发现一个X所处的行（或列）没被锤过，那么它的行列都不应该被锤过（“锤”的传递性）。我们将所有没被锤的行列标记，那么这些行列的交点应该和原状态保持一致。在考察所有没被锤的行列，这些行列交点的目标状态一定每个X不在同一行同一列，我们只要原状态这些位置能下第一锤，就一定能完成任务。最后还要考虑全O或者没变的两个特殊情况。

F题概率题，我不会。

### 文件夹包含

我们队所有过了题的标程，以及出题人所有题目的标程压缩包。