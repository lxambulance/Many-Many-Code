#include <bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for (int i=(a);i<=(b);++i)
#define ROF(i,a,b) for (int i=(a);i>=(b);--i)
typedef long long ll;
inline int read(){
	int x=0,f=1; char ch=getchar();
	while (!isdigit(ch)) { if (ch=='-') f=-1; ch=getchar(); }
	while (isdigit(ch)) { x=x*10+ch-'0'; ch=getchar(); }
	return x*f;
}

const int MAXN=400005;
const double PI=acos(-1.0),INF=1e10;
#define sqr(x) ((x)*(x))
struct P{
	int x,y;
	P(int xx=0,int yy=0):x(xx),y(yy){}
	P operator +(const P &p)const{ return P(x+p.x,y+p.y); }
	P operator -(const P &p)const{ return P(x-p.x,y-p.y); }
	int operator *(const P &p)const{ return x*p.y-p.x*y; }
	int operator ^(const P &p)const{ return x*p.x+y*p.y; }
	bool operator <(const P &p)const{ return x<p.x||(x==p.x&&y<p.y); }
};
typedef P V;
int Cross(P a,P b,P o){ return (a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x); }
int Cross(V v1,V v2){ return v1.x*v2.y-v1.y*v2.x; }
int Dot(P a,P b,P o){ return (a.x-o.x)*(b.x-o.x)+(a.y-o.y)*(b.y-o.y); }
int Dot(V v1,V v2){ return v1.x*v2.x+v1.y*v2.y; }
//凸包，相邻边不平行
int ConvexHull(P p[],int n,P q[]){
	sort(p+1,p+n+1);
	int i,m=0;
	for (i=1;i<=n;++i) {
		while (m>1&&Cross(q[m],p[i],q[m-1])<=0) m--;
		q[++m]=p[i];
	}
	int k=m;
	for (i=n-1;i>0;--i) {
		while (m>k&&Cross(q[m],p[i],q[m-1])<=0) m--;
		q[++m]=p[i];
	}
	if (n>1) m--;
	return m;
}

int n,m,l,ans;
P A[MAXN],B[MAXN],C[MAXN];
void checkIn(P p1,P p2,double &d1,double &d2){
	d1=-INF,d2=INF;
	FOR(i,1,n) {
		int x=Dot(p1,p2,A[i]),y=Cross(p1,p2,A[i]);
		// printf("checkIn(%d:%d %d)\n",i,x,y);
		if (y==0) continue;
		double tmp=-((double)x)/((double)abs(y));
		if (y>0) {
			tmp=-tmp;
			if (tmp>d1) d1=tmp;
		}
		else {
			if (tmp<d2) d2=tmp;
		}
		if (d1>=d2) return;
	}
}
void checkOut(P p1,P p2,double &d1,double &d2){
	d1=-INF,d2=INF;
	FOR(i,1,m) {
		int x=Dot(p1,p2,B[i]),y=Cross(p1,p2,B[i]);
		// printf("checkOut(%d:%d %d)\n",i,x,y);
		if (y==0) {
			if (x<=0) { d1=INF,d2=-INF; return; }
			continue;
		}
		double tmp=-((double)x)/((double)abs(y));
		if (y>0) {
			tmp=-tmp;
			if (tmp<d2) d2=tmp;
		}
		else {
			if (tmp>d1) d1=tmp;
		}
		if (d1>=d2) return;
	}
}
vector<pair<int,int> >Q;
void dfs(int l,int r){
	Q.push_back(make_pair(l,r));
	if (l+1>=r) return;
	int k=0; double mx=-INF;
	FOR(i,l+1,r-1) {
		double tmp=(double)Dot(C[l],C[r],C[i])/(double)abs(Cross(C[l],C[r],C[i]));
		if (tmp>mx) mx=tmp,k=i;
	}
	dfs(l,k),dfs(k,r);
}
void solve(){
	l=ConvexHull(A,n,C);
	Q.resize(0); dfs(1,l);
	// printf("%d %d\n",l,Q.size());
	for (int i=0;i<(int)Q.size();++i) {
		int a=Q[i].first,b=Q[i].second;
		// printf("%d:(%d,%d)(%d,%d)\n",i+1,C[a].x,C[a].y,C[b].x,C[b].y);
		double d1,d2,d3,d4;
		checkIn(C[a],C[b],d1,d2);
		// printf("[%.8f %.8f]\n",d1,d2);
		if (d1>=d2) continue;
		checkOut(C[a],C[b],d3,d4);
		// printf("[%.8f %.8f]\n",d3,d4);
		if (d3>=d4) continue;
		if ((d1<=d3&&d3<d2)||(d1>=d3&&d1<d4)) { ans=1; return; }
	}
}
int main(){
	n=read(); m=read();
	FOR(i,1,n) A[i].x=read(),A[i].y=read();
	FOR(i,1,m) B[i].x=read(),B[i].y=read();
	ans=0;
	if (n==1||m==1) ans=1;
	if (!ans) solve();
	if (!ans) {
		FOR(i,1,max(n,m)) swap(A[i],B[i]);
		swap(n,m);
		solve();
	}
	puts(ans?"YES":"NO");
	
	return 0;
}

/*
5 5
19 14
16 19
18 4
3 17
18 6
13 2
5 6
13 17
14 3
7 4

*/
