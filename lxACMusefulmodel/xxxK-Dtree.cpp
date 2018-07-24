#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
inline int read() {
	int x=0,f=1; char ch=getchar();
	while (ch<'0'||ch>'9') { if (ch=='-') f=-1; ch=getchar(); }
	while (ch>='0'&&ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	return x*f;
}

const int MAXN=200005,MAXD=2;
const double INF=1e10;
int n,m,D;
struct P{
	int d[MAXD],M[MAXD],m[MAXD],l,r;
	P(int x=0,int y=0) { l=r=0; d[0]=x; d[1]=y; }
	int& operator [](int x){ return d[x]; }
	friend bool operator <(P a,P b){ return a[D]<b[D]; }
	friend bool operator ==(P a,P b){ return a.d[0]==b.d[0]&&a.d[1]==b.d[1]; }
}p[MAXN];
inline double dis(P a,P b)
{ return sqrt(1.0*(a[0]-b[0])*(a[0]-b[0])+1.0*(a[1]-b[1])*(a[1]-b[1])); }
inline bool in(int x1,int y1,int x2,int y2,int X1,int Y1,int X2,int Y2) 
{ return x1<=X1&&X2<=x2&&y1<=Y1&&Y2<=y2; }
inline bool out(int x1,int y1,int x2,int y2,int X1,int Y1,int X2,int Y2)
{ return x1>X2||x2<X1||y1>Y2||y2<Y1; }
struct KDtree{
	P t[MAXN],T;
	int root,n;
	double ans;
	inline void update(int k){
		int i,l=t[k].l,r=t[k].r;
		for (i=0;i<MAXD;++i) {
			if (l) {
				t[k].M[i]=max(t[k].M[i],t[l].M[i]);
				t[k].m[i]=min(t[k].m[i],t[l].m[i]);
			}
			if (r) {
				t[k].M[i]=max(t[k].M[i],t[r].M[i]);
				t[k].m[i]=min(t[k].m[i],t[r].m[i]);
			}
		}
	}
	int build(int l,int r,int now){
		D=now;
		int i,mid=(l+r)>>1;
		nth_element(p+l,p+mid,p+r+1); t[mid]=p[mid];
		for (i=0;i<MAXD;++i) t[mid].M[i]=t[mid].m[i]=t[mid][i];
		if (l<mid) t[mid].l=build(l,mid-1,now^1);
		if (mid<r) t[mid].r=build(mid+1,r,now^1);
		update(mid); return mid;
	}
	inline void build(int nn){ n=nn; root=build(1,nn,0); }
	void insert(int &k,int now){
		if (k==0) {
			t[k].r=++n; t[n]=T;
			for (int i=0;i<MAXD;++i) t[n].M[i]=t[n].m[i]=t[n][i];
			return;
		}
		if (T[now]>=t[k][now]) insert(t[k].r,now^1);
		else insert(t[k].l,now^1);
		update(k);
	}
	inline void insert(P p){ T=p; T.l=T.r=0; insert(root,0); }
	inline double get(int k,P p){
		double tmp[2]={0.0,0.0};
		for (int i=0;i<MAXD;++i) {
			if (tmp[i]<t[k].m[i]-p[i]) tmp[i]=t[k].m[i]-p[i];
			if (tmp[i]<p[i]-t[k].M[i]) tmp[i]=p[i]-t[k].M[i];
		}
		return sqrt(tmp[0]*tmp[0]+tmp[1]*tmp[1]);
	}
	void query(int k,int now){
		double d,dl=INF,dr=INF;
		d=dis(t[k],T); ans=min(ans,d);
		if (t[k].l) dl=get(t[k].l,T);
		if (t[k].r) dr=get(t[k].r,T);
		if (dl<dr) {
			if (dl<ans) query(t[k].l,now^1);
			if (dr<ans) query(t[k].r,now^1);
		}
		else {
			if (dr<ans) query(t[k].r,now^1);
			if (dl<ans) query(t[k].l,now^1);
		}
	}
	inline double query(P p){ ans=INF; T=p; query(root,0); return ans; }
}kd;
int main() {
	int i; n=read();
	for (i=1;i<=n*2;++i) p[i][0]=read(),p[i][1]=read();
	kd.build(n);
	double ans=INF,tmp;
	for (i=n+1;i<=n*2;++i) {
		tmp=kd.query(p[i]);
		if (ans>tmp) ans=tmp;
	}
	printf("%.3lf\n",ans);
	return 0;
}

/*
4 
0 0 
0 1 
1 0 
1 1 
2 2 
2 3 
3 2 
3 3

*/
