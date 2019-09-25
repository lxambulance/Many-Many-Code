#include <queue>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
inline int read() {
	int x=0,s=1; char ch=getchar();
	while (ch<'0'||ch>'9') { if (ch=='-') s=-1; ch=getchar(); }
	while (ch>='0'&&ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	return s*x;
}

const int MAXN=50005,INF=2147483647;
int n,m,S,T,b[MAXN],dis[MAXN],pre[MAXN];
struct list{
	int l,lt[MAXN],nt[MAXN*2],v0[MAXN*2],v1[MAXN*2],v2[MAXN*2];
	inline void clear() { l=1; memset(lt,0,sizeof(lt)); }
	inline void addedge(int x,int y,int z,int w) {
		nt[++l]=lt[x]; lt[x]=l; v0[l]=y; v1[l]=z; v2[l]=w;
		nt[++l]=lt[y]; lt[y]=l; v0[l]=x; v1[l]=0; v2[l]=-w;
	}
}E;
int SPFA() {
	memset(b,0,sizeof(b));
	memset(pre,0,sizeof(pre));
	for (int i=1;i<=T;++i) dis[i]=INF;
	queue<int> Q; Q.push(S); dis[S]=0; b[S]=1;
	while (!Q.empty()) {
		int x=Q.front(),i,j;
		for (i=E.lt[x];i;i=E.nt[i]) {
			j=E.v0[i];
			if (E.v1[i]>0&&dis[j]>dis[x]+E.v2[i]) {
				dis[j]=dis[x]+E.v2[i]; pre[j]=i;
				if (!b[j]) { Q.push(j); b[j]=1; }
			}
		}
		b[x]=0; Q.pop();
	}
	return pre[T];
}
int mincostflow() {
	int i,j,k,flow=0,cost=0;
	while (SPFA()) {
		for (i=T,k=INF;i!=S;i=E.v0[pre[i]^1]) k=min(k,E.v1[pre[i]]);
		flow+=k; cost+=dis[T]*k;
		for (i=T;i!=S;i=E.v0[j^1]) { j=pre[i]; E.v1[j]-=k; E.v1[j^1]+=k; }
	}
	return cost;
}
int main() {
	int i,j,k;
	n=read(); m=read(); E.clear();
	while (m--) {
		i=read(); j=read(); k=read();
		E.addedge(i,j,1,k); E.addedge(j,i,1,k);
	}
	S=n+1; T=S+1;
	E.addedge(S,1,2,0); E.addedge(n,T,2,0);
	printf("%d\n",mincostflow());
	
	return 0;
}

/*
4 5
1 2 1
2 3 1
3 4 1
1 3 2
2 4 2

*/
