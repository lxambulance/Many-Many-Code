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
const double PI=3.141592653589793238462,eps=1e-8;
int n,m;
double ans1,ans2,b[MAXN],R[MAXN];
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
	P ax,ay;
	double x,y;
	bool operator <(const Data &E)const{ return (x<E.x)||((x==E.x)&&(y<E.y)); }
}c[MAXN*2];
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
	m++;
	c[m].ax=rot(o2-o1,PI*2-alpha)/tmp*r1+o1;
	c[m].ay=rot(o2-o1,alpha)/tmp*r1+o1;
	c[m].x=deg(c[m].ax-o1);
	c[m].y=deg(c[m].ay-o1);
	if (c[m].x>c[m].y) {
		m++; c[m].y=c[m-1].y; c[m].ay=c[m-1].ay;
		c[m-1].y=PI*2; c[m].x=0;
		c[m-1].ay=c[m].ax=o1+P(r1,0);
	}
}
int main() {
	//freopen("1.in","r",stdin);
	//freopen("2.out","w",stdout);
	int i,j,k,l;
	m=read();
	for (i=1,n=0;i<=m;++i) {
		n++; a[n].x=read(); a[n].y=read(); R[n]=read();
		if (fabs(R[n])<=eps) n--;
	}
	memset(b,0,sizeof(b));
	for (i=1;i<=n;++i)
	if (!b[i])
		for (j=1;j<=n;++j)
		if (!b[j]&&i!=j&&dist(a[i],a[j])<=R[j]-R[i]) { b[i]=1; break; }
	//for (i=1;i<=n;++i) if (!b[i]) printf("%d\n",i);
	for (i=1,ans1=ans2=0;i<=n;++i)
	if (!b[i]) {
		for (j=1,m=0;j<=n;++j)
		if (!b[j]&&i!=j&&dist(a[i],a[j])<R[i]+R[j]) work(a[i],a[j],R[i],R[j]);
		if (m==0) {
			ans2+=PI*R[i]*R[i];
			continue;
		}
		sort(c+1,c+1+m); c[0].y=0; c[m+1].x=PI*2; c[0].ay=c[m+1].ax=a[i]+P(R[i],0);
		/*for (j=1;j<=m;++j) {
			printf("%.8lf %.8lf\n",c[j].x,c[j].y);
			printf("%.8lf %.8lf||%.8lf %.8lf\n",c[j].ax.x,c[j].ax.y,c[j].ay.x,c[j].ay.y);
		}*/
		double tmp=0;
		for (j=0;j<=m;j=k+1) {
			for (k=l=j;k<m&&c[k+1].x<=c[l].y;++k) if (c[k+1].y>c[l].y) l=k+1;
			ans1+=cross(c[l].ay,c[k+1].ax);
			tmp=c[k+1].x-c[l].y;
			ans2+=R[i]*R[i]*(tmp-sin(tmp))/2;
		}
		//printf("%d %d %.8lf %.8lf\n",i,m,ans1,ans2);
	}
	printf("%.5lf\n",fabs(ans1)/2+ans2);
	
	//fclose(stdin);
	//fclose(stdout);
	return 0;
}

/*
2
4 2 5
3 3 4

*/
