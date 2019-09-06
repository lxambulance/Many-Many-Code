#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <map>
#include <cmath>
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

#define sqr(x) ((x)*(x))
const double eps=1e-8,INF=1e20,PI=acos(-1.0);
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
//点o在直线上的投影，要求|v|不为0
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
	int m=0;
	for (int i=1;i<=n;++i)
		{ for (;m>1&&Cross(q[m],p[i],q[m-1])<=eps;m--); q[++m]=p[i]; }
	int k=m;
	for (int i=n-1;i>0;--i)
		{ for (;m>k&&Cross(q[m],p[i],q[m-1])<=eps;m--); q[++m]=p[i]; }
	if (n>1) m--;
	return m;
}

const int MAXN=10004;
#define mp(x,y) ((1ll*(x))<<32|(y))
map<ll,int> E;
Point p[MAXN],p1,p2;
int psize,Psize,lastp,lastP,f[MAXN];
struct Polygon{
	int pid[26],tot;
	Polygon(){ memset(pid,0,sizeof(pid)); tot=0; }
	void add(int id){ pid[++tot]=id; }
	void init(){ pid[0]=pid[tot],pid[tot+1]=pid[1]; }
	void print(){
		printf("{");
		FOR(i,1,tot) printf("%d ",pid[i]);
		printf("}\n");
	}
}P[MAXN];
void addPoint(Point p0){ p[++psize]=p0; }
int checkEdge(int id1,int id2){
	if (E.find(mp(id1,id2))!=E.end()) return E[mp(id1,id2)];
	addPoint(lineIntersect(p[id1],p[id2]-p[id1],p1,p2));
	return E[mp(id1,id2)]=E[mp(id2,id1)]=psize;
}
void init(){
	psize=0,Psize=1;
	addPoint(Point(0,0)),addPoint(Point(1,0));
	addPoint(Point(1,1)),addPoint(Point(0,1));
	P[1].tot=4;
	FOR(i,1,4) P[1].pid[i]=i;
	P[1].init();
}
int s[26];
void reflection(Polygon &P){
	FOR(i,1,P.tot) f[P.pid[i]]=1;
}
void fold(int x){
	int num1=0,num2=0;
	FOR(I,1,P[x].tot) {
		s[I]=sgn(Cross(p[P[x].pid[I]]-p1,p2));
		if (s[I]>0) num1++; else if (s[I]<0) num2++;
	}
	if (num1==0) {
		reflection(P[x]);
		FOR(i,1,P[x].tot/2) swap(P[x].pid[i],P[x].pid[P[x].tot+1-i]);
		P[x].init();
		return;
	}
	if (num2==0) return;
	Polygon P1,P2;
	FOR(I,1,P[x].tot) {
		int i=I,j=(I+1>P[x].tot?1:I+1);
		if (s[i]==0) P1.add(P[x].pid[I]),P2.add(P[x].pid[I]);
		else if (s[i]>0) {
			P1.add(P[x].pid[I]);
			if (s[j]<0) {
				int id=checkEdge(P[x].pid[I],P[x].pid[I+1]);
				P1.add(id),P2.add(id);
			}
		}
		else {
			P2.add(P[x].pid[I]);
			if (s[j]>0) {
				int id=checkEdge(P[x].pid[I],P[x].pid[I+1]);
				P1.add(id),P2.add(id);
			}
		}
	}
	reflection(P2);
	FOR(i,1,P2.tot/2) swap(P2.pid[i],P2.pid[P2.tot+1-i]);
	P1.init(),P2.init();
	P[x]=P1; P[++Psize]=P2;
}
void dfs(int x){
	f[x]=1;
	FOR(I,1,P[x].tot) {
		int i=I,j=I+1;
		if (sgn(Cross(p[P[x].pid[i]]-p1,p2))==0&&sgn(Cross(p[P[x].pid[j]]-p1,p2))==0) continue;
		FOR(y,1,Psize)
		if (!f[y]) {
			FOR(J,1,P[y].tot)
			if (P[x].pid[i]==P[y].pid[J]&&P[x].pid[j]==P[y].pid[J+1]) { dfs(y); break; }
		}
	}
}
int cut(){
	FOR(i,1,Psize) f[i]=0;
	int ans=0;
	FOR(i,1,Psize) if (!f[i]) dfs(i),ans++;
	return ans;
}
int main(){
	int T=read();
	while (T--) {
		init();
		int n=read()+1;
		while (n--) {
			scanf("%lf%lf%lf%lf",&p1.x,&p1.y,&p2.x,&p2.y);
			p2=p2-p1;
			lastP=Psize,lastp=psize;
			E.clear();
			FOR(i,1,lastp) f[i]=0;
			FOR(i,1,lastP) fold(i);
			FOR(i,1,lastp)
			if (f[i]&&sgn(Cross(p[i]-p1,p2))) {
				Point p0=Project(p[i],p1,p2);
				p[i]=p0*2-p[i];
			}
			// FOR(i,1,lastp) printf("%d%c",f[i]," \n"[i==lastp]);
			// FOR(i,1,psize) printf("p[%d]:(%.8f,%.8f)\n",i,p[i].x,p[i].y);
			// FOR(i,1,Psize) {
				// printf("Polygon[%d]:",i);
				// P[i].print();
			// }
		}
		printf("%d\n",cut());
	}
	return 0;
}

/*
4
1
0 0.5 1 1
0.5 0 0.5 1
1
0 0.5 1 1
0 0.4 1 0.4
0
0 0 1 0
1
0.30 0.10 0.00 0.90
0.70 0.70 0.50 0.40

*/