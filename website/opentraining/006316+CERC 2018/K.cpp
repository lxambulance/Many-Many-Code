#include <bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for (int i=(a);i<=(b);++i)
#define ROF(i,b,a) for (int i=(b);i>=(a);--i)
typedef long long ll;
inline int readint(){
	int x=0,f=1; char ch=getchar();
	while (!isdigit(ch)) { if (ch=='-') f=-1; ch=getchar(); }
	while (isdigit(ch)) { x=x*10+ch-'0'; ch=getchar(); }
	return x*f;
}

const int MAXN=103;
#define sqr(x) ((x)*(x))
const double eps=1e-8,INF=1e20,PI=acos(-1.0);
inline int sgn(double x){ if (fabs(x)<=eps) return 0; return x>0?1:-1; }
struct Point{
	double x,y;
	Point(double xx=0,double yy=0):x(xx),y(yy){}
	double len(){ return sqrt(x*x+y*y); }
	//向量的加减乘�?
	Point operator +(const Point &p)const{ return Point(x+p.x,y+p.y); }
	Point operator -(const Point &p)const{ return Point(x-p.x,y-p.y); }
	Point operator *(const double &f)const{ return Point(x*f,y*f); }
	//要求f不为0
	Point operator /(const double &f)const{ return Point(x/f,y/f); }
	//向量的叉积与点积
	double operator *(const Point &p)const{ return x*p.y-p.x*y; }
	double operator ^(const Point &p)const{ return x*p.x+y*p.y; }
	//凸包的排�?
	bool operator <(const Point &p)const{ return x<p.x||(x==p.x&&y<p.y); }
};
typedef Point Vector;
//函数形式的距离、叉积与点积
double Dist(Point a,Point b){ return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)); }
double Cross(Point a,Point b,Point o){ return (a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x); }
double Cross(Vector v1,Vector v2){ return v1.x*v2.y-v1.y*v2.x; }
double Dot(Point a,Point b,Point o){ return (a.x-o.x)*(b.x-o.x)+(a.y-o.y)*(b.y-o.y); }
double Dot(Vector v1,Vector v2){ return v1.x*v2.x+v1.y*v2.y; }
//向量旋转（逆时针，弧度�?
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
//点到直线的距�?
double pointToLine(Point p,Point o,Vector v){ return fabs(Cross(p-o,v))/v.len(); }
//线段是否相交�?0为不相交�?1为严格相交且交点不在线段端点上，2表示交点为某线段端点�?3为线段平行且部分重合
inline int segIntersect(Point a,Point b,Point c,Point d){
	if (max(a.x,b.x)<min(c.x,d.x)||min(a.x,b.x)>max(c.x,d.x)) return 0;
	if (max(a.y,b.y)<min(c.y,d.y)||min(a.y,b.y)>max(c.y,d.y)) return 0;
	double x=Cross(a-b,c-b),y=Cross(a-b,d-b),z=Cross(c-d,a-d),w=Cross(c-d,b-d);
	if (sgn(x)==0&&sgn(y)==0) return 3;
	if (sgn(x)*sgn(y)<0&&sgn(z)*sgn(w)<0) return 1;
	if (sgn(x)*sgn(y)<=0&&sgn(z)*sgn(w)<=0) return 2;
	return 0;
}
//凸包，相邻边不平�?
int ConvexHull(Point p[],int n,Point q[]){
	sort(p+1,p+n+1);
	int m=0;
	for (int i=1;i<=n;++i)
		{ for (;m>1&&Cross(q[m],p[i],q[m-1])<=eps;m--); q[++m]=p[i]; }
	int k=m;
	for (int i=n-1;i>0;--i)
		{ for (;m>k&&Cross(q[m],p[i],q[m-1])<=eps;m--); q[++m]=p[i]; }
	if (n>1) m--;
	return m;
}

Point A[MAXN],B[MAXN],C[MAXN],D[MAXN],S,E;
int n,m,q,ans,a[MAXN],b[MAXN],c[MAXN];
void work(int len){
	// printf("len=%d\n",len);
	// FOR(i,1,len) printf("%d%c",a[i]," \n"[i==len]);
	C[0]=S; C[len+1]=D[len+1]=E;
	ROF(i,len,1) {
		Point tmp=Project(D[i+1],A[a[i]],B[a[i]]-A[a[i]]);
		D[i]=tmp*2-D[i+1];
	}
	FOR(i,1,len) {
		Vector v=D[i]-C[i-1];
		if (sgn(Cross(v,B[a[i]]-A[a[i]]))==0) return;
		C[i]=lineIntersect(A[a[i]],B[a[i]]-A[a[i]],C[i-1],v);
		if (sgn(Dot(C[i-1],D[i],C[i]))>=0) return;
	}
	// FOR(i,0,len+1) printf("%d:(%.8f,%.8f)\n",i,C[i].x,C[i].y);
	FOR(i,1,n) c[i]=0;
	FOR(i,1,len+1) {
		FOR(j,1,n)
		if (!c[j]) {
			// printf("check(j=%d,i=%d)\n",j,i);
			if (sgn(Cross(C[i-1],B[j],A[j]))*sgn(Cross(C[i],B[j],A[j]))<0) return;
		}
		c[a[i]]=1;
	}
	// printf("len=%d ok\n",len);
	ans++;
}
void dfs(int x){
	work(x-1);
	if (x==n+1) return;
	FOR(i,1,n)
	if (!b[i]) {
		b[i]=1; a[x]=i;
		dfs(x+1);
		b[i]=0;
	}
}
int main(){
	n=readint();
	S.x=readint(),S.y=readint();
	E.x=readint(),E.y=readint();
	FOR(i,1,n) {
		A[i].x=readint(),A[i].y=readint();
		B[i].x=readint(),B[i].y=readint();
	}
	dfs(1);
	printf("%d\n",ans);
	
	return 0;
}

/*
2
2 3 4 2
2 2 3 3
1 4 3 4
1
0 0 4 0
0 4 4 4
3
2 3 5 2
1 3 1 1
2 4 4 2
5 4 6 5

*/