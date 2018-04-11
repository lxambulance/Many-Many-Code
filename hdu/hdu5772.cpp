#include <queue>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define FOR(i,a,b) for (int i=(a);i<=(b);++i)
#define ROF(i,b,a) for (int i=(b);i>=(a);--i)
typedef long long LL;
inline int read() {
	int x=0,f=1; char ch=getchar();
	while (ch<'0'||ch>'9') { if (ch=='-') f=-1; ch=getchar(); }
	while (ch>='0'&&ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	return x*f;
}

const int MAXN=300005,MAXM=1000006,INF=2147483647;
int en,u[MAXN],cur[MAXN];//cur为当前弧优化
struct edge{ int v,nt,c; }e[MAXM];
void clear(){ en=0; memset(u,-1,sizeof(u)); }
void addEdge(int x,int y,int z){//反向边为i^1
	e[en]=(edge){y,u[x],z}; u[x]=en++;
	e[en]=(edge){x,u[y],0}; u[y]=en++;
}
int S,T,nn,rear,head,Q[MAXN],dis[MAXN];
int BFS(){
	FOR(i,1,nn) dis[i]=INF;
	rear=head=0; dis[Q[++rear]=S]=0;
	while (head<rear) {
		int x=Q[++head];
		for (int i=u[x];~i;i=e[i].nt) {
			int j=e[i].v;
			if (e[i].c>0&&dis[j]>dis[x]+1) dis[Q[++rear]=j]=dis[x]+1;
		}
	}
	return dis[T]!=INF;
}
int DFS(int now,int flow) {
	if (now==T) return flow;
	int ans=0;
	for (int i=cur[now];~i;i=e[i].nt) {
		int j=e[i].v;
		if (e[i].c>0&&dis[j]==dis[now]+1) {
			int k=min(e[i].c,flow); k=DFS(j,k);
			e[i].c-=k; e[i^1].c+=k; ans+=k; flow-=k;
		}
		if (!flow) break;
	}
	return ans;
}
int Dinic() {
	int ans=0;
	while (BFS()) {
		FOR(i,1,nn) cur[i]=u[i];
		ans+=DFS(S,INF);
	}
	return ans;
}
char s[MAXN];
int n,m,q,a[MAXN],b[MAXN],c[105][105];
int main() {
	q=read();
	FOR(cas,1,q) {
		clear(); m=0;
		n=read(); scanf("%s",s+1);
		FOR(i,0,9) a[i]=read(),b[i]=read();
		FOR(i,1,n)
			FOR(j,1,n) c[i][j]=read();
		S=n*n+n+10+1,T=n*n+n+10+2,nn=T;
		FOR(i,1,n)
			FOR(j,1,n)
			if (i!=j&&c[i][j]) {
				int k=(i-1)*n+j;
				addEdge(k,n*n+i,INF);
				addEdge(k,n*n+j,INF);
				addEdge(S,k,c[i][j]);
				m+=c[i][j];
			}
		FOR(i,1,n) {
			int k=s[i]-'0';
			addEdge(n*n+i,n*n+n+k+1,INF);
			if (a[k]) addEdge(n*n+i,T,a[k]);
		}
		FOR(i,0,9) {
			if (b[i]>a[i]) addEdge(n*n+n+1+i,T,b[i]-a[i]);
		}
		printf("Case #%d: %d\n",cas,m-Dinic());
	}
	
	return 0;
}

/*
2
3
135
1 2
1 2
1 2
1 2
1 2
1 2
1 2
1 2 
1 2
1 2
0 0 3
1 0 0
4 0 0
3
135
1 2
1 2
1 2
1 2
1 2
1 2
1 2
1 2 
1 2
1 2
0 0 3
1 0 0
4 0 0

*/
