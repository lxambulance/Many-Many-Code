#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <map>
#include <cmath>
#include <vector>
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
#define mix(x,y) ((1ll*(x))<<32|(y))
map<ll,int> E;
Point p[MAXN],p1,p2;
int psize,Psize,lastp,lastP,f[MAXN],g[MAXN],h[MAXN];
struct Polygon{
	int pid[26],tot,depth;
	Polygon(){ memset(pid,0,sizeof(pid)); depth=tot=0; }
	bool operator <(const Polygon &Q)const{ return depth<Q.depth; }
	void print(){
		printf("{");
		FOR(i,1,tot) printf("%d ",pid[i]);
		printf("}\n");
	}
	void add(int id){ pid[++tot]=id; }
	void init(){ pid[0]=pid[tot],pid[tot+1]=pid[1]; }
	int checkIn(Point O){
		FOR(i,1,tot) if (sgn(Cross(p[pid[i]],p[pid[i+1]],O))==0) return -1;
		Point OO=O+Point(INF,0);
		int num=0;
		FOR(i,1,tot) {
			int si=segIntersect(O,OO,p[pid[i]],p[pid[i+1]]);
			if (si==1) num++;
			else if (si==2) {
				if (sgn(Cross(p[pid[i]],O,OO))<0) num++;
				else if (sgn(Cross(p[pid[i+1]],O,OO))<0) num++;
			}
		}
		return (num&1);
	}
}P[MAXN];
//map<ll,int> cover;
int s[26];
int checkIntersect(int x,int y){
	//if (cover.find(mix(x,y))!=cover.end()) return cover[mix(x,y)];
	// printf("%d<--->%d\n",x,y);
	// FOR(i,1,P[x].tot) printf("%d%c",P[x].pid[i]," \n"[i==P[x].tot]);
	// FOR(i,1,P[y].tot) printf("%d%c",P[y].pid[i]," \n"[i==P[y].tot]);
	FOR(i,1,P[x].tot) {
		int num=0;
		FOR(j,1,P[y].tot)
		if (sgn(Cross(p[P[y].pid[j]],p[P[x].pid[i+1]],p[P[x].pid[i]]))>=0) num++;
		if (num==P[y].tot) return 0;//cover[mix(x,y)]=cover[mix(y,x)]=0;
	}
	swap(x,y);
	FOR(i,1,P[x].tot) {
		int num=0;
		FOR(j,1,P[y].tot)
		if (sgn(Cross(p[P[y].pid[j]],p[P[x].pid[i+1]],p[P[x].pid[i]]))>=0) num++;
		if (num==P[y].tot) return 0;//cover[mix(x,y)]=cover[mix(y,x)]=0;
	}
	return 1;//cover[mix(x,y)]=cover[mix(y,x)]=1;
}
void addPoint(Point p0){ p[++psize]=p0; }
void init(){
	psize=0,Psize=1;
	addPoint(Point(0,0)),addPoint(Point(100,0));
	addPoint(Point(100,100)),addPoint(Point(0,100));
	P[1].tot=4,P[1].depth=1;
	FOR(i,1,4) P[1].pid[i]=i;
	P[1].init();
	memset(f,0,sizeof(f));
}
int checkEdge(int id1,int id2){
	if (E.find(mix(id1,id2))!=E.end()) return E[mix(id1,id2)];
	addPoint(lineIntersect(p[id1],p[id2]-p[id1],p1,p2));
	return E[mix(id1,id2)]=E[mix(id2,id1)]=psize;
}
void cut(int x){
	int num1=0,num2=0;
	FOR(I,1,P[x].tot) {
		s[I]=sgn(Cross(p[P[x].pid[I]]-p1,p2));
		if (s[I]>0) num1++; else if (s[I]<0) num2++;
	}
	if (num1==0||num2==0) return;
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
	P1.init(),P2.init();
	P[x]=P1; P[++Psize]=P2;
	P[x].depth=P[Psize].depth=1;
	FOR(y,1,Psize) {
		if (y==Psize||y>=x&&y<=lastP) continue;
		if (checkIntersect(x,y)) P[x].depth=max(P[x].depth,P[y].depth+1);
		if (checkIntersect(Psize,y)) P[Psize].depth=max(P[Psize].depth,P[y].depth+1);
	}
}
void dfs(int x){
	// printf("%d st\n",x);
	FOR(i,1,P[x].tot) g[P[x].pid[i]]=1;
	f[x]=1;
	FOR(y,1,Psize)
	if (!f[y]&&P[y].depth>P[x].depth&&checkIntersect(y,x)) dfs(y);
	FOR(i,1,P[x].tot) {
		if (sgn(Cross(p[P[x].pid[i]]-p1,p2))==0&&sgn(Cross(p[P[x].pid[i+1]]-p1,p2))==0) continue;
		FOR(y,1,Psize)
		if (!f[y]) {
			FOR(j,1,P[y].tot)
			if ((P[x].pid[i]==P[y].pid[j]&&P[x].pid[i+1]==P[y].pid[j+1])
			  ||(P[x].pid[i]==P[y].pid[j+1]&&P[x].pid[i+1]==P[y].pid[j])) { dfs(y); break; }
		}
	}
	// printf("%d ed\n",x);
}
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define PII pair<int,int>
vector<PII > l;
int main(){
	int n;
	while (n=read()) {
		init();
		while (n--) {
			Point A,B;
			A.x=read(),A.y=read(),B.x=read(),B.y=read();
			p1=(A+B)/2;
			p2=Rot(B-A,PI/2);
			lastP=Psize,lastp=psize;
			E.clear(); //cover.clear();
			FOR(i,1,lastP) cut(i);
			int root=0,tmp=0;
			FOR(i,1,Psize)
			if (P[i].checkIn(A)&&tmp<P[i].depth) tmp=P[i].depth,root=i;
			FOR(i,1,Psize) f[i]=0;
			FOR(i,1,psize) g[i]=0;
			dfs(root);
			// puts("prepare");
			// printf("nowroot=%d\n",root);
			// FOR(i,1,psize) printf("%d%c",g[i]," \n"[i==psize]);
			// FOR(i,1,Psize) printf("%d%c",f[i]," \n"[i==Psize]);
			// FOR(i,1,psize) printf("p[%d]:(%.8f,%.8f)\n",i,p[i].x,p[i].y);
			// FOR(i,1,Psize) {
				// printf("Polygon[%d] depth=%d:",i,P[i].depth);
				// P[i].print();
			// }
			// puts("main");
			FOR(i,1,psize)
			if (g[i]&&sgn(Cross(p[i]-p1,p2))) {
				Point tmp=Project(p[i],p1,p2);
				p[i]=tmp*2-p[i];
			}
			// FOR(i,1,psize) printf("p[%d]:(%.8f,%.8f)\n",i,p[i].x,p[i].y);
			l.resize(0);
			FOR(i,1,Psize)
			if (f[i]) {
				l.pb(mp(P[i].depth,i));
				FOR(j,1,P[i].tot/2) swap(P[i].pid[j],P[i].pid[P[i].tot+1-j]);
				P[i].init();
			}
			sort(l.begin(),l.end());
			int top=l.size();
			//cover.clear();
			while (top--) {
				int x=l[top].se;
				// printf("%d\n",x);
				P[x].depth=1;
				FOR(i,1,Psize)
				if (!f[i]&&checkIntersect(x,i)) P[x].depth=max(P[x].depth,P[i].depth+1);
				f[x]=0;
			}
			// FOR(i,1,Psize) {
				// printf("Polygon[%d] depth=%d:",i,P[i].depth);
				// P[i].print();
			// }
			sort(P+1,P+1+Psize);
		}
		Point H; H.x=read(),H.y=read();
		int ans=0;
		FOR(i,1,Psize) if (P[i].checkIn(H)) ans++;
		printf("%d\n",ans);
	}
	return 0;
}

/*
2
90 90 80 20
80 20 75 50
50 35
2
90 90 80 20
75 50 80 20
55 20
3
5 90 15 70
95 90 85 75
20 67 20 73
20 75
3
5 90 15 70
5 10 15 55
20 67 20 73
75 80
8
1 48 1 50
10 73 10 75
31 87 31 89
91 94 91 96
63 97 62 96
63 80 61 82
39 97 41 95
62 89 62 90
41 93
5
2 1 1 1
-95 1 -96 1
-190 1 -191 1
-283 1 -284 1
-373 1 -374 1
-450 1
2
77 17 89 8
103 13 85 10
53 36
0

*/
