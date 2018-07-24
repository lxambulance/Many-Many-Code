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
inline void clear(){ en=0; memset(u,-1,sizeof(u)); }
inline void addEdge(int x,int y,int z){//反向边为i^1
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
	for (int& i=cur[now];~i;i=e[i].nt) {
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
int n,m,q,a[MAXN],b[MAXN];
int main() {
	clear();
	nn=read(),m=read(),S=read(),T=read();
	while (m--) {
		int x=read(),y=read(),z=read();
		addEdge(x,y,z);
	}
	printf("%d\n",Dinic());
	
	return 0;
}

/*
*/
