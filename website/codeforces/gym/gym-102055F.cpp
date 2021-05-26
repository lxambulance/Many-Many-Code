#include <bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for (int i=(a);i<=(b);++i)
#define ROF(i,a,b) for (int i=(a);i>=(b);--i)
typedef long long ll;
inline int read() {
	int x=0,s=1; char ch=getchar();
	while (ch<'0'||ch>'9') { if (ch=='-') s=-1; ch=getchar(); }
	while (ch>='0'&&ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	return s*x;
}

#define sqr(x) ((x)*(x))
const double eps=1e-12,INF=1e20,PI=3.141592653589793238462;
inline int sgn(double x){ if (fabs(x)<=eps) return 0; return x>0?1:-1; }
struct Point{
	double x,y;
	Point(double xx=0,double yy=0):x(xx),y(yy){}
	double len(){ return sqrt(x*x+y*y); }
	//向量的加减乘除
	Point operator +(const Point &p)const{ return Point(x+p.x,y+p.y); }
	Point operator -(const Point &p)const{ return Point(x-p.x,y-p.y); }
	Point operator *(const double &f)const{ return Point(x*f,y*f); }
	//要求f不为0
	Point operator /(const double &f)const{ return Point(x/f,y/f); }
	//向量的叉积与点积
	double operator *(const Point &p)const{ return x*p.y-p.x*y; }
	double operator ^(const Point &p)const{ return x*p.x+y*p.y; }
	//凸包的排序
	bool operator <(const Point &p)const{ return x<p.x||(x==p.x&&y<p.y); }
};
typedef Point Vector;
//函数形式的距离、叉积与点积
double Dist(Point a,Point b){ return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)); }
double Cross(Point a,Point b,Point o){ return (a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x); }
double Cross(Vector v1,Vector v2){ return v1.x*v2.y-v1.y*v2.x; }
double Dot(Point a,Point b,Point o){ return (a.x-o.x)*(b.x-o.x)+(a.y-o.y)*(b.y-o.y); }
double Dot(Vector v1,Vector v2){ return v1.x*v2.x+v1.y*v2.y; }
//向量旋转（逆时针，弧度）
inline Vector Rot(Vector p,double a){ return Vector(cos(a)*p.x-sin(a)*p.y,sin(a)*p.x+cos(a)*p.y); }
//向量极角（弧度）
double Deg(Point p){ double tmp=atan2(p.y,p.x); return tmp<0?tmp+PI*2:tmp; }
//点p在直线上的投影，要求|v|不为0
Point Project(Point o,Point p,Vector v){ double tmp=((o-p)^v)/(v^v); return p+v*tmp; }
//两直线（点向式）交点，要求直线不平行
Point lineIntersect(Point p1,Vector v1,Point p2,Vector v2){ double tmp=(v1*(p2-p1))/(v2*v1); return p2+v2*tmp; }
//点到线段的距离，要求s1!=s2
double pointToSeg(Point s1,Point s2, Point p){
	if (Dot(p,s1,s2)<eps) return Dist(s2,p); else if (Dot(p,s2,s1)<eps) return Dist(s1,p);
	return fabs(Cross(p,s2,s1))/Dist(s1,s2);
}
//点到直线的距离
double pointToLine(Point p,Point o,Vector v){ return fabs(Cross(p-o,v))/v.len(); }
//线段是否相交，0为不相交，1为严格相交且交点不在线段端点上，2表示交点为某线段端点，3为线段平行且部分重合
inline int segIntersect(Point a,Point b,Point c,Point d){
	if (max(a.x,b.x)<min(c.x,d.x)||min(a.x,b.x)>max(c.x,d.x)) return 0;
	if (max(a.y,b.y)<min(c.y,d.y)||min(a.y,b.y)>max(c.y,d.y)) return 0;
	double x=Cross(a-b,c-b),y=Cross(a-b,d-b),z=Cross(c-d,a-d),w=Cross(c-d,b-d);
	if (sgn(x)==0&&sgn(y)==0) return 3;
	if (sgn(x)*sgn(y)<0&&sgn(z)*sgn(w)<0) return 1;
	if (sgn(x)*sgn(y)<=0&&sgn(z)*sgn(w)<=0) return 2;
	return 0;
}
//凸包，相邻边不平行
int ConvexHull(Point p[],int n,Point q[]){
	sort(p+1,p+n+1);
	int i,m=0;
	for (i=1;i<=n;++i) {
		while (m>1&&Cross(q[m],p[i],q[m-1])<=eps) m--;
		q[++m]=p[i];
	}
	int k=m;
	for (i=n-1;i>0;--i) {
		while (m>k&&Cross(q[m],p[i],q[m-1])<=eps) m--;
		q[++m]=p[i];
	}
	if (n>1) m--;
	return m;
}
struct line{
	Point p;
	Vector v;
};
Point lI(line l1,line l2){ return lineIntersect(l1.p,l1.v,l2.p,l2.v); }
bool onRight(Point p,line l){ return sgn(l.v*(p-l.p))<0; }
//相同极角保留最靠左的，排序中体现为相同极角的第一个
int cmp(line l1,line l2){
	int f1=(l1.v.x>=-eps),f2=(l2.v.x>=-eps);
	if (f1!=f2) return f1==1;
	int tmp=sgn(l1.v*l2.v);
	return (tmp==0&&sgn(l1.v*(l2.p-l1.p))<0)||tmp>0;
}
int head,tail;
line que[1000006];
bool HPI(line l[],int &n){
	sort(l+1,l+1+n,cmp);
	int N=n; n=0;
	FOR(i,1,N) {
		if (i>1&&sgn(l[i].v*l[i-1].v)==0) continue;
		l[++n]=l[i];
	}
	head=1,tail=0;
	//FOR(i,1,n) printf("(%.8f,%.8f) vector(%.8f,%.8f)\n",l[i].p.x,l[i].p.y,l[i].v.x,l[i].v.y);
	FOR(i,1,n) {
		while (tail>head&&onRight(lI(que[tail],que[tail-1]),l[i])) tail--;
		while (tail>head&&onRight(lI(que[head],que[head+1]),l[i])) head++;
		que[++tail]=l[i];
	}
	while (tail>head&&onRight(lI(que[tail],que[tail-1]),que[head])) tail--;
	while (tail>head&&onRight(lI(que[head],que[head+1]),que[tail])) head++;
	if (tail-head+1>=3) return true;
	return false;
}

const int MAXN=400005;
line l[MAXN];
Point p[MAXN],q[4],tmp[MAXN];
int n,m,f[MAXN];
double calc_arg(Point a,Point b){
	double A=atan2(a.y,a.x);
	double B=atan2(b.y,b.x);
	if (A-B<eps) return (A-B+PI*2)/6;
	return (A-B)/6;
}
double calc_tri(Vector v){
	v.x=fabs(v.x);
	double theta=PI/2-Deg(v);
	double tanTh=tan(theta),secTh=1.0/cos(theta),v2=v.y*v.y,v3=v2*v.y;
	return v2*tanTh/2-v3*tanTh*secTh/6-v3*log(tanTh+secTh)/6;
}
double calc(Vector a,Vector b){
	if (pointToLine(Point(0,0),a,b-a)>1-eps) return calc_arg(b,a);
	double tmp=PI-Deg(b-a);
	a=Rot(a,tmp); b=Rot(b,tmp);
	Point c=Project(Point(0,0),a,b-a);
	double Dabc=Dot(a,b,c),al=a.len(),bl=b.len();
	if (sgn(Dabc)>=0&&al>1+eps&&bl>1+eps) return calc_arg(b,a);
	double ret=0,d=sqrt(1.0-sqr(c.len()));
	if (al>1+eps) {
		Point A=c+(a-c)/(a-c).len()*d;
		ret+=calc_arg(A,a);
		a=A;
	}
	if (bl>1+eps) {
		Point B=c+(b-c)/(b-c).len()*d;
		ret+=calc_arg(b,B);
		b=B;
	}
	if (sgn(Dabc)<0) ret+=calc_tri(a)+calc_tri(b);
	else ret+=fabs(calc_tri(a)-calc_tri(b));
	return ret;
}

int main(){
	int T=read();
	q[0]=(Point){25,25};
	q[1]=(Point){-25,25};
	q[2]=(Point){-25,-25};
	q[3]=(Point){25,-25};
	FOR(cas,1,T) {
		n=read();
		FOR(i,1,n) scanf("%lf%lf",&p[i].x,&p[i].y);
		double ans=0;
		FOR(i,1,n) {
			m=0;
			FOR(j,0,3) l[++m]=(line){q[j],q[(j+1)%4]-q[j]};
			FOR(j,1,n)
			if (i^j) l[++m]=(line){(p[i]+p[j])/2,Rot(p[j]-p[i],PI/2)};
			HPI(l,m);
			que[tail+1]=que[head];
			FOR(j,head,tail) tmp[j]=lI(que[j],que[j+1]);
			//FOR(j,head,tail) printf("(%.8f,%.8f)%c",tmp[j].x,tmp[j].y," \n"[j==tail]);
			tmp[tail+1]=tmp[head];
			FOR(j,head,tail) {
				ans+=calc(tmp[j]-p[i],tmp[j+1]-p[i]);
				//printf("calc[%d]=%.8f\n",j,calc(tmp[j]-p[i],tmp[j+1]-p[i]));
			}
			//printf("ans=%.15f\n",ans);
		}
		printf("Case %d: %.15f\n",cas,ans);
	}
	return 0;
}

/*
4
1
0.0000 0.0000
2
0.0000 0.0000
1.0000 0.0000
3
-4.1850 0.8550
3.8150 4.0400
2.1300 -2.6700
5
5.6422 7.8467
-5.7704 9.1233
-1.2843 5.2843
3.8242 -2.2140
-4.6870 1.8571

*/