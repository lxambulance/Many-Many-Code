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

const int MAXN=1003;
const double PI=3.1415926535897932384626433832795028841971693993,eps=1e-8;
int n,m;
double ans[MAXN][2],b[MAXN],R[MAXN];
struct P{
	double x,y;
	P(double v=0,double u=0){ x=v; y=u; }
	double len(){ return sqrt(x*x+y*y); }
	P operator +(const P &E)const{ return P(x+E.x,y+E.y); }
	P operator -(const P &E)const{ return P(x-E.x,y-E.y); }
	P operator *(const double &z)const{ return P(x*z,y*z); }
	P operator /(const double &z)const{ return P(x/z,y/z); }
	double operator *(const P &E)const{ return x*E.x+y*E.y; }
}a[MAXN];
inline double cross(P p,P q){ return p.x*q.y-p.y*q.x; }
inline double dist(P p,P q){ return sqrt((p.x-q.x)*(p.x-q.x)+(p.y-q.y)*(p.y-q.y)); }
struct Data{
	P ax; double x; int y;
	bool operator <(const Data &E)const{ return x<E.x; }
}c[MAXN*10];
inline P rot(P p,double a){ return P(cos(a)*p.x-sin(a)*p.y,sin(a)*p.x+cos(a)*p.y); }
inline double deg(P p){
	double tmp=atan2(p.y,p.x);
	return tmp<0?tmp+PI*2:tmp;
}
inline void work(P o1,P o2,double r1,double r2){
	double s,p,h,alpha,tmp=dist(o1,o2);
	p=(r1+r2+tmp)/2; s=sqrt(p*(p-r1)*(p-r2)*(p-tmp));
	h=s*2/tmp; alpha=asin(h/r1);
	if (r1*r1+tmp*tmp<r2*r2) alpha=PI-alpha;
	c[++m].ax=rot(o2-o1,PI*2-alpha)/tmp*r1+o1; c[m].x=deg(c[m].ax-o1); c[m].y=1;
	c[++m].ax=rot(o2-o1,alpha)/tmp*r1+o1; c[m].x=deg(c[m].ax-o1); c[m].y=-1;
	if (c[m-1].x>c[m].x) {
		c[++m].ax=o1+P(r1,0); c[m].x=0; c[m].y=1;
		c[++m].ax=o1+P(r1,0); c[m].x=PI*2; c[m].y=-1;
	}
}
int main() {
	//freopen("1.in","r",stdin);
	//freopen("2.out","w",stdout);
	
	int i,j,k,l;
	n=read();
	for (i=1;i<=n;++i) { a[i].x=read(); a[i].y=read(); R[i]=read(); }
	memset(b,0,sizeof(b));
	for (i=1;i<=n;++i)
		for (j=1;j<=n;++j)
		if (i!=j&&dist(a[i],a[j])<=R[j]-R[i]) b[i]++;
	memset(ans,0,sizeof(ans));
	for (i=1;i<=n;++i) {
		for (j=1,m=0;j<=n;++j)
		if (i!=j&&dist(a[i],a[j])<R[i]+R[j]&&dist(a[i],a[j])>fabs(R[j]-R[i]))
			work(a[i],a[j],R[i],R[j]);
		c[++m].ax=a[i]+P(R[i],0); c[m].x=0; c[m].y=b[i]+1;
		c[++m].ax=a[i]+P(R[i],0); c[m].x=PI*2; c[m].y=-b[i]-1;
		sort(c+1,c+1+m);
		/*printf("%d\n",i);
		for (j=1;j<=m;++j) {
			printf("%d %.3lf %d\n",j,c[j].x,c[j].y);
			printf("(%.3lf,%.3lf)\n",c[j].ax.x,c[j].ax.y);
		}*/
		int sa=1,sb=0,sc;
		for (j=1;j<=m;j=k+1) {
			for (k=j;k<m&&fabs(c[k+1].x-c[j].x)<eps;++k);
			for (l=j,sc=sb;l<=k;++l) sc+=c[l].y;
			if (sc==sb&&k!=m) continue;
			if (fabs(c[sa].x-c[j].x)>eps) {
				ans[sb][0]+=cross(c[sa].ax,c[j].ax);
				double tmp=c[j].x-c[sa].x;
				ans[sb][1]+=R[i]*R[i]*(tmp-sin(tmp))/2;
			}
			sb=sc; sa=j;
		}
	}
	//for (i=1;i<=n;++i) printf("%.3lf %.3lf %.3lf\n",ans[i][0],ans[i][1],fabs(ans[i][0])/2+ans[i][1]);
	for (i=1;i<=n;++i) ans[i][0]=fabs(ans[i][0])/2+ans[i][1];
	for (i=1;i<=n;++i) printf("[%d] = %.3lf\n",i,ans[i][0]-ans[i+1][0]);
	
	//fclose(stdin);
	//fclose(stdout);
	return 0;
}

/*
5
3 0 3
4 3 5
1 2 4
4 3 5
1 4 4

*/
