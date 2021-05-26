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
const double eps=1e-8,INF=1e20,PI=3.141592653589793238462;
#define sqr(x) ((x)*(x))
inline int sgn(double x){ if (fabs(x)<=eps) return 0; return x>0?1:-1; }
struct P{
	double x,y;
	P(double x=0,double y=0):x(x),y(y){}
	P operator +(const P& p)const{ return P(x+p.x,y+p.y); }
	P operator -(const P& p)const{ return P(x-p.x,y-p.y); }
	P operator *(const double& f)const{ return P(x*f,y*f); }
	P operator /(const double& f)const{ return P(x/f,y/f); }
	double operator *(const P& p)const{ return x*p.y-y*p.x; }
	double len(){ return sqrt(sqr(x)+sqr(y)); }
	bool operator <(const P& p)const{ return x<p.x||(x==p.x&&y<p.y); }
}A[MAXN],B[MAXN],C,D;
typedef P V;
inline double cross(P a,P b,P o){
	return (a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x);
}
inline P intersection(P a,V va,P b,V vb){
	double tmp=((b-a)*va)/(va*vb);
	return b+vb*tmp;
}
int n,m,p,a[MAXN],b[MAXN];
int main(){
	n=read();
	double ans=0,x,y;
	x=read(); y=read(); D=P(x,y);
	FOR(i,1,n) {
		double a,b,c;
		a=read(); b=read(); c=read();
		A[i].x=a/c; A[i].y=b/c;
		ans=max(ans,min(x/A[i].x,y/A[i].y));
	}
	sort(A+1,A+1+n);
	m=0;
	FOR(i,1,n) {
		while (m>1&&cross(A[i],B[m],B[m-1])>=-eps) m--;
		B[++m]=A[i];
	}
	m--; p=m;
	ROF(i,n,1) {
		while (m>p+1&&cross(A[i],B[m],B[m-1])>=-eps) m--;
		B[++m]=A[i];
	}
	if (n>1) m--;
	
	B[m+1]=B[1];
	FOR(i,1,m)
	if (sgn(B[i]*D)*sgn(B[i+1]*D)<=0) {
		C=intersection(B[i],B[i+1]-B[i],D,D);
		ans=max(ans,D.len()/C.len());
	}
	printf("%.6f\n",ans);
	
	return 0;
}

/*
*/
