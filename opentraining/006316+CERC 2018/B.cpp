#include <bits/stdc++.h>
using namespace std;
#define PII pair<int,int>
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define FOR(i,a,b) for (int i=(a);i<=(b);++i)
#define ROF(i,b,a) for (int i=(b);i>=(a);--i)
typedef long long ll;
inline int read(){
	int x=0,f=1; char ch=getchar();
	while (!isdigit(ch)) { if (ch=='-') f=-1; ch=getchar(); }
	while (isdigit(ch)) { x=x*10+ch-'0'; ch=getchar(); }
	return x*f;
}

const int MAXN=100005;
struct DSU{
	int f[MAXN];
	void clear(){ FOR(i,0,MAXN-1) f[i]=i; }
	int ask(int x){ if (f[x]==x) return x; return f[x]=ask(f[x]); }
	void set(int x,int y){ f[x]=y; }
}dsu[20];
int A[MAXN],B[MAXN],X[MAXN],Y[MAXN],Z[MAXN];
int n,m,q,p,a[MAXN],b[MAXN],x[MAXN],y[MAXN],v[MAXN];
map<PII,int> S;
vector<int> t[MAXN<<2];
void build(int x,int l,int r){
	t[x].clear();
	if (l==r) return;
	int mid=(l+r)/2;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
}
void change(int x,int l,int r,int L,int R,int k){
	// printf("%d [%d %d][%d %d] %d\n",x,l,r,L,R,k);
	if (L<=l&&r<=R) { t[x].pb(k); return; }
	int mid=(l+r)/2;
	if (L<=mid) change(x<<1,l,mid,L,R,k);
	if (mid<R) change(x<<1|1,mid+1,r,L,R,k);
}
void work(int x,int l,int r,int dep){
	FOR(i,l,r) {
		int a=dsu[dep-1].ask(X[i]),b=dsu[dep-1].ask(Y[i]);
		dsu[dep].set(X[i],a),dsu[dep].set(a,a);
		dsu[dep].set(Y[i],b),dsu[dep].set(b,b);
	}
	int tot=t[x].size();
	FOR(I,0,tot-1) {
		int i=t[x][I];
		int a=dsu[dep-1].ask(X[i]),b=dsu[dep-1].ask(Y[i]);
		dsu[dep].set(X[i],a),dsu[dep].set(a,a);
		dsu[dep].set(Y[i],b),dsu[dep].set(b,b);
	}
	FOR(I,0,tot-1) {
		int i=t[x][I];
		int a=dsu[dep].ask(X[i]),b=dsu[dep].ask(Y[i]);
		dsu[dep].set(a,b);
	}
	// printf("work(%d %d %d %d)\n",x,l,r,dep);
	// FOR(i,0,n-1) printf("%d%c",dsu[dep].ask(i)," \n"[i==n-1]);
	if (l==r) {
		if (A[l]==2) B[Z[l]]=((dsu[dep].ask(X[l]))==(dsu[dep].ask(Y[l])));
		return;
	}
	int mid=(l+r)/2;
	work(x<<1,l,mid,dep+1);
	work(x<<1|1,mid+1,r,dep+1);
}
int main(){
	// freopen("bridge.in","r",stdin);
	// freopen("bridge.out","w",stdout);
	
	n=read(); q=read();
	FOR(i,1,q) {
		a[i]=read(),x[i]=read(),y[i]=read();
		if (x[i]>y[i]) swap(x[i],y[i]);
		if (a[i]==0) v[i]=read();
	}
	dsu[0].clear();
	memset(b,-1,sizeof(b));
	FOR(k,0,9) {
		m=p=0; S.clear();
		FOR(i,1,q) {
			if (a[i]==0&&v[i]<=k) {
				++m,A[m]=a[i],X[m]=x[i],Y[m]=y[i];
				Z[m]=q,S[mp(x[i],y[i])]=m;
			}
			else if (a[i]==1&&S.find(mp(x[i],y[i]))!=S.end()) {
				Z[S[mp(x[i],y[i])]]=m; S.erase(mp(x[i],y[i]));
				++m,A[m]=a[i],X[m]=x[i],Y[m]=y[i];
			}
			else if (a[i]==2) ++m,A[m]=a[i],X[m]=x[i],Y[m]=y[i],Z[m]=++p,B[p]=0;
		}
		build(1,1,m);
		FOR(i,1,m) if (A[i]==0) change(1,1,m,i,Z[i],i);
		// printf("%d\n",k);
		// FOR(i,1,m) printf("(%d)%d %d %d\n",A[i],X[i],Y[i],Z[i]);
		work(1,1,m,1);
		FOR(i,1,p) if (!~b[i]&&B[i]) b[i]=k;
		// FOR(i,1,p) printf("%d%c",B[i]," \n"[i==p]);
	}
	FOR(i,1,p) printf("%d\n",b[i]);
	
	// fclose(stdin);
	// fclose(stdout);
	return 0;
}

/*
6 15
0 1 2 1
2 1 4
2 1 5
0 2 3 2
2 1 4
2 1 5
0 3 4 3
2 1 4
2 1 5
0 4 5 4
2 1 4
2 1 5
1 4 5
2 1 4
2 1 5

6 6
0 2 0 4
0 3 4 3
0 0 4 1
0 2 5 4
2 3 2
2 4 2

5 6
0 4 2 0
0 4 2 4
0 2 0 2
2 0 4
2 3 1
2 3 1

6 10
0 1 2 0
2 4 2
2 5 4
0 1 1 6
0 1 4 2
2 2 4
0 4 4 4
1 4 1
2 1 4
1 2 1

*/
