#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
#define FOR(i,a,b) for (int i=(a);i<=(b);++i)
#define ROF(i,a,b) for (int i=(a);i>=(b);--i)
inline int read(){
	int x=0,h=1; char ch=getchar();
	while (ch<'0'||ch>'9') { if (ch=='-') h=-1; ch=getchar(); }
	while (ch>='0'&&ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	return x*h;
}

const int MAXN=400005,Mo=1e9+7;
int u[MAXN],esize;
struct edge{ int v,w,nt; }e[MAXN];
void addEdge(int a,int b,int c){ e[esize]=(edge){b,c,u[a]}; u[a]=esize++; }
int dep[MAXN],dis[MAXN],fa[MAXN][20];
void dfs(int x,int f,int d,int w){
	fa[x][0]=f;
	FOR(k,1,19) fa[x][k]=fa[fa[x][k-1]][k-1];
	dep[x]=d; dis[x]=w;
	for (int i=u[x];~i;i=e[i].nt) {
		int j=e[i].v;
		if (j!=f) dfs(j,x,d+1,w+e[i].w);
	}
}
void walk(int &x,int k){ FOR(i,0,19) if ((k>>i)&1) x=fa[x][i]; }
int lca(int x,int y){
	if (dep[x]>dep[y]) swap(x,y);
	walk(y,dep[y]-dep[x]);
	if (x==y) return x;
	ROF(i,19,0) if (fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}

int n,m,a[MAXN],b[MAXN];
int main(){
	int T=read();
	while (T--) {
		memset(u,-1,sizeof(u)); esize=0;
		n=read();
		FOR(i,1,n-1) {
			int x=read(),y=read(),z=read();
			addEdge(x,y,z),addEdge(y,x,z);
		}
		dfs(1,0,1,0);
		// FOR(i,1,n) printf("%d%c",dep[i]," \n"[i==n]);
		// FOR(i,1,n) printf("%d%c",dis[i]," \n"[i==n]);
		// FOR(k,0,3)
			// FOR(i,1,n) printf("%d%c",fa[i][k]," \n"[i==n]);
		char ch[10];
		while (scanf("%s",ch),ch[1]!='O') {
			if (ch[1]=='I') {
				int x=read(),y=read(),z=lca(x,y);
				printf("%d\n",(dis[x]-dis[z])+(dis[y]-dis[z]));
			}
			else {
				int x=read(),y=read(),z=lca(x,y),k=read();
				if (dep[x]-dep[z]+1>=k) {
					walk(x,k-1);
					printf("%d\n",x);
				}
				else {
					int tmp=dep[x]+dep[y]-dep[z]*2;
					walk(y,tmp-k+1);
					printf("%d\n",y);
				}
			}
		}
	}
	
	return 0;
}

/*
1
6
1 2 1
2 4 1
2 5 2
1 3 1
3 6 2
DIST 4 6
KTH 4 6 4
DONE

*/
