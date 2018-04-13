#include <bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for (int i=(a);i<=(b);++i)
#define ROF(i,b,a) for (int i=(b);i>=(a);--i)
typedef long long LL;
int read() {
	int x=0,f=1; char ch=getchar();
	while (ch<'0'||ch>'9') { if (ch=='-') f=-1; ch=getchar(); }
	while (ch>='0'&&ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	return x*f;
}

const int MAXN=500005;
vector<int> b[MAXN],c[MAXN],d[MAXN];
int n,m,q,a[MAXN],ans[MAXN],f[2][30],g[2][30];
int main() {
	n=read();
	FOR(i,1,n) a[i]=read();
	m=read();
	FOR(i,1,m) {
		int x=read();
		b[x].push_back(read());
		c[x].push_back(read());
		d[x].push_back(i);
	}
	int o=0;
	memset(f[o],0,sizeof(f[o]));
	FOR(i,0,29) g[o][i]=n+1;
	ROF(x,n,1) {
		o^=1;
		FOR(i,0,29) f[o][i]=f[o^1][i],g[o][i]=g[o^1][i];
		int y=a[x],z=x;
		ROF(i,29,0)
		if ((y>>i)&1) {
			if (f[o][i]==0) { f[o][i]=y; g[o][i]=z; break; }
			else {
				if (z<g[o][i]) swap(f[o][i],y),swap(g[o][i],z);
				y^=f[o][i];
			}
		}
		for (int i=0;i<d[x].size();++i) {
			int y=b[x][i],z=c[x][i],I=d[x][i],flag=1;
			ROF(j,29,0)
			if ((z>>j)&1) {
				if (f[o][j]==0||g[o][j]>y) { flag=0; break; }
				else z^=f[o][j];
			}
			ans[I]=flag;
		}
	}
	FOR(i,1,m) if (ans[i]) puts("YES"); else puts("NO");
	return 0;
}

/*
5
1 1 2 4 6
3
1 2 1
2 4 8
3 5 7

*/
