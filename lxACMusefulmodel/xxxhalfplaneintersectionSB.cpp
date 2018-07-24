#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN=100005;
struct point{
	double x,y;
	point(double xx=0,double yy=0):x(xx),y(yy){}
}p[MAXN],q[MAXN],tmp[MAXN];
inline double cross(point A,point B){ return A.x*B.y-A.y*B.x; }
double a,b,c;
inline void get_line(point p1,point p2){ a=p2.y-p1.y; b=p1.x-p2.x; c=p2.x*p1.y-p2.y*p1.x; }
inline point intersect(point p1,point p2){
	double u=fabs(a*p1.x+b*p1.y+c),v=fabs(a*p2.x+b*p2.y+c);
	return point((v*p1.x+u*p2.x)/(u+v),(v*p1.y+u*p2.y)/(u+v));
}
int n,m;
void cut(){
	int i,h=0;
	for (i=1;i<=m;i++) {
		if (a*q[i].x+b*q[i].y+c>=0) tmp[++h]=q[i];
		else {
			if (a*q[i-1].x+b*q[i-1].y+c>0) tmp[++h]=intersect(q[i-1],q[i]);
			if (a*q[i+1].x+b*q[i+1].y+c>0) tmp[++h]=intersect(q[i],q[i+1]);
		}
	}
	for (i=1;i<=h;i++) q[i]=tmp[i];
	q[0]=q[h]; q[h+1]=q[1]; m=h;
}
int main(){
	int i;
	scanf("%d",&n);
	q[1].x=0; q[1].y=0;
	q[2].x=10000; q[2].y=0;
	q[3].x=10000; q[3].y=10000;
	q[4].x=0; q[4].y=10000;
	q[0]=q[4]; q[5]=q[1]; m=4;
	for (i=1;i<=n;i++) {
		point A,B;
		scanf("%lf%lf%lf%lf",&A.x,&A.y,&B.x,&B.y);
		get_line(B,A); cut();
		//cout<<i<<endl;
		//for (int j=1;j<=m;++j) printf("%.8lf %.8lf\n",q[j].x,q[j].y);
	}
	double ans=0;
	for (i=1;i<=m;++i) ans+=cross(q[i],q[i+1]);
	ans=fabs(ans)/2;
	printf("%.1lf\n",ans);
	
	return 0;
}

/*
3
10000 10000 0 5000
10000 5000 5000 10000
0 5000 5000 0

*/
