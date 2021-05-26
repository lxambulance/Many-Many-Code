#include <bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for (int i=(a);i<=(b);++i)
#define ROF(i,b,a) for (int i=(b);i>=(a);--i)
typedef long long LL;
inline int read(){
	int x=0,f=1; char ch=getchar();
	while (ch<'0'||ch>'9') { if (ch=='-') f=-1; ch=getchar(); }
	while (ch>='0'&&ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	return x*f;
}

const int MAXN=300005;
vector<int> e[MAXN];
int n,m,p,a[MAXN],b[MAXN],f[MAXN][2];
void dfs_prepare(int x,int y){
	b[x]=0;
	for (int i=0;i<(int)e[x].size();++i) {
		int j=e[x][i];
		if (j!=y) dfs_prepare(j,x),b[x]+=b[j];
	}
	if (!b[x]) b[x]=1;
}
int dfs(int x,int y,int z){
	if (~f[x][y]) return f[x][y];
	int tot=0;
	for (int i=0;i<(int)e[x].size();++i) {
		int j=e[x][i];
		if (j!=z) tot+=dfs(j,0,x)+2-(b[j]&1);
	}
	f[x][y]=tot;
	if (y) {
		for (int i=0;i<(int)e[x].size();++i) {
			int j=e[x][i];
			if (j!=z) {
				if (b[j]&1) f[x][y]=min(f[x][y],tot-dfs(j,0,x)+dfs(j,1,x)+1);
				else f[x][y]=min(f[x][y],tot-dfs(j,0,x)+dfs(j,1,x)-1);
			}
		}
	}
	return f[x][y];
}
int main(){
	int T=read();
	while (T--) {
		n=read();
		FOR(i,1,n) e[i].clear(),a[i]=0;
		FOR(i,2,n) {
			int x=read(),y=read();
			e[x].push_back(y),e[y].push_back(x);
			a[x]++,a[y]++;
		}
		if (n<=2) printf("%d\n",n-1);
		else {
			FOR(i,1,n) f[i][0]=f[i][1]=-1;
			int k=0,tot=0;
			FOR(i,1,n) if (a[i]==1) tot++,f[i][0]=f[i][1]=0; else k=i;
			dfs_prepare(k,0);
			//FOR(i,1,n) printf("%d:%d\n",i,b[i]);
			printf("%d\n",dfs(k,tot&1,0));
		}
	}
	return 0;
}

/*
3
6
2 1
3 1
4 3
5 2
6 2
3
1 2
2 3
7
1 2
1 3
2 4
2 5
3 6
3 7

*/
