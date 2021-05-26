#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int MAXN=100005;
const double INF=1e99,eps=1e-9;
struct P{
	double x,y;
	P(double v=0,double u=0){ x=v; y=u; }
	double len(){ return sqrt(x*x+y*y); }
	P operator +(const P &E)const{ return P(x+E.x,y+E.y); }
	P operator -(const P &E)const{ return P(x-E.x,y-E.y); }
	P operator *(const double &z)const{ return P(x*z,y*z); }
	double operator *(const P &E)const{ return x*E.x+y*E.y; }
	bool operator <(const P &E)const{ return (x<E.x)||((x==E.x)&&(y<E.y)); }
}A[MAXN],B[MAXN],C[MAXN];
inline double cross(P a,P b){ return a.x*b.y-a.y*b.x; }
inline double dist(P a,P b){ return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)); }
inline double work(P a,P b,P c){
	double ans=min(dist(a,c),dist(b,c));
	if (fabs(dist(a,b))<=eps) return ans;
	if ((b-a)*(c-a)>=-eps&&(a-b)*(c-b)>=-eps) ans=min(ans,fabs(cross(b-a,c-a)/dist(a,b)));
	return ans;
}
int ConvexHull(P p[],int n,P q[]){
	sort(p+1,p+n+1);
	int i,m=0;
	for (i=1;i<=n;i++) {
		while (m>1&&cross(q[m]-q[m-1],p[i]-q[m-1])<=eps) m--;
		q[++m]=p[i];
	}
	int k=m;
	for (i=n-1;i>0;i--) {
		while (m>k&&cross(q[m]-q[m-1],p[i]-q[m-1])<=eps) m--;
		q[++m]=p[i];
	}
	if (n>1) m--;
	return m;
}
double Rotating_calipers(P p[],int n,P q[],int m){
	int v,u,i;
	double ans=INF,tmp;
	for (i=u=1;i<=n;++i) if (p[u].y-eps>p[i].y) u=i;
	for (i=v=1;i<=m;++i) if (q[v].y+eps<q[i].y) v=i;
	for (i=1;i<=n;++i) {
		while ((tmp=cross(p[u+1]-p[u],q[v+1]-p[u])-cross(p[u+1]-p[u],q[v]-p[u]))>eps)
			{ v++; if (v==m+1) v=1; }
		ans=min(ans,work(p[u],p[u+1],q[v]));
		if (fabs(tmp)<=eps) {
			ans=min(ans,work(p[u],p[u+1],q[v+1]));
			ans=min(ans,work(q[v],q[v+1],p[u]));
			ans=min(ans,work(q[v],q[v+1],p[u+1]));
		}
		u++; if (u==n+1) u=1;
	}
	return ans;
}
int main(){
	int n,m,i;
	while (scanf("%d%d",&n,&m)) {
		if (n==0&&m==0) break;
		for (i=1;i<=n;++i) scanf("%lf%lf",&C[i].x,&C[i].y);
		n=ConvexHull(C,n,A); A[n+1]=A[1]; A[0]=A[n];
		for (i=1;i<=m;++i) scanf("%lf%lf",&C[i].x,&C[i].y);
		m=ConvexHull(C,m,B); B[m+1]=B[1]; B[0]=B[m];
		printf("%.5lf\n",min(Rotating_calipers(A,n,B,m),Rotating_calipers(B,m,A,n)));
	}
	return 0;
}

/*
5 3
109.00000 208.00000
100.00000 236.00000
111.00000 253.00000
122.00000 250.00000
161.00000 206.00000
72.00000 309.00000
157.00000 224.00000
167.00000 309.00000
0 0

6.36396
*/
