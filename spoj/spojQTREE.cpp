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
int dep[MAXN],sum[MAXN],fa[MAXN],st[MAXN],belong[MAXN],len,arr[2][MAXN];
void dfs1(int x,int f,int d){
	dep[x]=d; sum[x]=1; fa[x]=f;
	for (int i=u[x];~i;i=e[i].nt) {
		int j=e[i].v;
		if (j!=f) {
			dfs1(j,x,d+1);
			sum[x]+=sum[j];
		}
	}
}
void dfs2(int x,int f,int b){
	belong[x]=b; arr[0][++len]=x; st[x]=len;
	int y=0,z=0,w=0;
	for (int i=u[x];~i;i=e[i].nt) {
		int j=e[i].v;
		if (j!=f&&sum[j]>y) { y=sum[j]; z=j; w=e[i].w; } 
	}
	//printf("now=%d maxsonsize=%d maxson=%d\n",x,y,z);
	if (z) arr[1][len]=w,dfs2(z,x,b);
	for (int i=u[x];~i;i=e[i].nt) {
		int j=e[i].v;
		if (j!=f&&j!=z) arr[1][len]=e[i].w,dfs2(j,x,j);
	}
}

int n,m,a[MAXN],b[MAXN],maxV[MAXN];
void build(int x,int l,int r){
	if (l==r) {
		maxV[x]=a[arr[1][l]];
		return;
	}
	int mid=(l+r)/2;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	maxV[x]=max(maxV[x<<1],maxV[x<<1|1]);
}
void change(int x,int l,int r,int pos,int val){
	if (l==pos&&pos==r) {
		maxV[x]=val;
		return;
	}
	int mid=(l+r)/2;
	if (pos<=mid) change(x<<1,l,mid,pos,val);
	else change(x<<1|1,mid+1,r,pos,val);
	maxV[x]=max(maxV[x<<1],maxV[x<<1|1]);
}
int getMax(int x,int l,int r,int L,int R){
	// printf("getMax(%d,%d,%d,%d,%d)\n",x,l,r,L,R);
	if (L<=l&&r<=R) return maxV[x];
	int mid=(l+r)/2,ret=-2147483648;
	if (L<=mid) ret=max(ret,getMax(x<<1,l,mid,L,R));
	if (mid<R) ret=max(ret,getMax(x<<1|1,mid+1,r,L,R));
	return ret;
}
int main(){
	int T=read();
	while (T--) {
		memset(u,-1,sizeof(u)); esize=0;
		n=read();
		FOR(i,1,n-1) {
			int x=read(),y=read(),z=read();
			addEdge(x,y,i),addEdge(y,x,i); a[i]=z;
		}
		dfs1(1,0,1);
		// FOR(i,1,n) printf("%d ",dep[i]); puts("dep");
		// FOR(i,1,n) printf("%d ",sum[i]); puts("sum");
		// FOR(i,1,n) printf("%d ",fa[i]); puts("fa");
		len=0; dfs2(1,0,1);
		// FOR(i,1,n) printf("%d ",arr[0][i]); puts("arr[0]");
		// FOR(i,1,n) printf("%d ",arr[1][i]); puts("arr[1]");
		// FOR(i,1,n) printf("%d ",st[i]); puts("st");
		FOR(i,1,n-1) b[arr[1][i]]=i;
		build(1,1,n-1);
		char ch[10];
		while (scanf("%s",ch),ch[0]!='D') {
			if (ch[0]=='C') {
				int i=read(),ti=read();
				a[i]=ti,change(1,1,n-1,b[i],a[i]);
			}
			else {
				int x=read(),y=read(),ans=-2147483648;
				while (belong[x]!=belong[y]) {
					// printf("%d %d\n",x,y);
					if (dep[belong[x]]>dep[belong[y]]) swap(x,y);
					ans=max(ans,getMax(1,1,n-1,st[belong[y]]-1,st[y]-1)); y=fa[belong[y]];
				}
				if (dep[x]>dep[y]) swap(x,y);
				if (x!=y) ans=max(ans,getMax(1,1,n-1,st[x],st[y]-1));
				printf("%d\n",ans);
			}
		}
	}
	
	return 0;
}

/*
1
3
1 2 1
2 3 2
QUERY 1 2
CHANGE 1 3
QUERY 1 2
DONE

1
8
2 1 29
3 2 9
4 3 14
5 1 29
6 5 25
7 3 58
8 6 16
Query 6 3
Query 8 8
Query 1 4
Query 1 1
Query 5 1
Done

*/
