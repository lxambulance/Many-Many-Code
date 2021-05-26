#include <bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for (int i=(a);i<=(b);++i)
#define ROF(i,a,b) for (int i=(a);i>=(b);--i)
typedef long long LL;
inline int read(){
	int x=0,f=1; char ch=getchar();
	while (ch<'0'||ch>'9') { if (ch=='-') f=-1; ch=getchar(); }
	while (ch>='0'&&ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	return x*f;
}

const int MAXN=300005,Mo=1000000007;
int n,q,a[72],b[72];
int tt[9]={4,6,5,1,8,7,3,2,0};
int t[8][18]={
{14,15,11,12,10,19,28,30,31,35,36,68,45,44,43,42,41,54},
{01,03,04,8,9,41,54,53,52,51,50,63,23,24,20,21,19,28},
{01,10,12,13,17,18,50,63,62,61,60,59,72,32,33,29,30,28},
{05,06,02,03,01,10,19,21,22,26,27,59,72,71,70,69,68,45},
{9,8,07,06,05,36,68,69,65,66,64,55,46,48,49,53,54,14},
{9,41,42,38,39,37,64,55,57,58,62,63,23,18,17,16,15,14},
{18,50,51,47,48,46,37,64,66,67,71,72,32,27,26,25,24,23},
{05,36,35,34,33,32,27,59,60,56,57,55,46,37,39,40,44,45}
};
void T(int y,int x){//y=0 1 2 3 4 5 6 7;x=0 1;
	if (x) { T(y,0); T(y,0); return; }
	FOR(i,0,71) b[i]=a[i];
	FOR(i,0,11) b[t[y][i]-1]=a[t[y][i+6]-1];
	FOR(i,12,17) b[t[y][i]-1]=a[t[y][i-12]-1];
	FOR(i,0,8) b[y*9+i]=a[y*9+tt[i]];
	FOR(i,0,71) a[i]=b[i];
}
int m[4][18]={
{02,06,07,43,42,38,49,48,47,58,62,61,25,26,22,29,30,31},
{16,17,13,20,21,22,29,33,34,70,69,65,40,39,38,49,53,52},
{04,03,02,31,35,34,70,71,67,56,57,58,47,51,52,16,15,11},
{07,8,04,11,12,13,20,24,25,61,60,56,67,66,65,40,44,43},
};
void M(int y,int x){//y=0 1 2 3;x=0 1
	if (x) { M(y,0); M(y,0); return; }
	FOR(i,0,71) b[i]=a[i];
	FOR(i,0,11) b[m[y][i]-1]=a[m[y][i+6]-1];
	FOR(i,12,17) b[m[y][i]-1]=a[m[y][i-12]-1];
	FOR(i,0,71) a[i]=b[i];
}
void dfs(int x){
	if (x<=3) {
		q=1;
		FOR(i,0,71) if (i%9!=0&&a[i]!=a[i-1]) { q=0; break; }
		if (x==3||q==1) return;
	}
	FOR(i,0,7)
		FOR(j,0,1) {
			T(i,j); dfs(x+1);
			if (q) return; else T(i,j^1);
		}
	FOR(i,0,3)
		FOR(j,0,1) {
			M(i,j); dfs(x+1);
			if (q) return; else M(i,j^1);
		}
}
int main(){
	int T=read();
	while (T--) {
		int k=0;
		FOR(i,1,8)
			FOR(j,1,9) a[k++]=read();
		q=0; dfs(0);
		if (q) puts("YES"); else puts("NO");
	}
	return 0;
}

/*
1
1 1 1 1 1 1 1 1 1
2 2 2 2 2 2 2 2 2
3 3 3 3 3 3 3 3 3
4 4 4 4 4 4 4 4 4
5 5 5 5 5 5 5 5 5
6 6 6 6 6 6 6 6 6
7 7 7 7 7 7 7 7 7
8 8 8 8 8 8 8 8 8

*/