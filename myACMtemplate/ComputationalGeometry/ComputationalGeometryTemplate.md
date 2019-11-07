# 几何模板

lxambulance

----

[TOC]

----

## 二维几何

### 二维点类（常用）
```C++
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
	int m=0;
	for (int i=1;i<=n;++i)
		{ for (;m>1&&Cross(q[m],p[i],q[m-1])<=eps;m--); q[++m]=p[i]; }
	int k=m;
	for (int i=n-1;i>0;--i)
		{ for (;m>k&&Cross(q[m],p[i],q[m-1])<=eps;m--); q[++m]=p[i]; }
	if (n>1) m--;
	return m;
}
```

### 半平面交
```C++
struct line{
	Point p;
	Vector v;
}l[MAXN];
Point lI(line l1,line l2){ return lineIntersect(l1.p,l1.v,l2.p,l2.v); }
bool onRight(Point p,line l){ return sgn(l.v*(p-l.p))<0; }
//相同极角保留最靠左的，排序中体现为相同极角的第一个
int cmp(line l1,line l2){
	int f1=(l1.v.x>=-eps),f2=(l2.v.x>=-eps);
	if (f1!=f2) return f1==1;
	int tmp=sgn(l1.v*l2.v);
	return (tmp==0&&sgn(l1.v*(l2.p-l1.p))<0)||tmp>0;
}
void checkCounterclockwise(Point p[],int n){
	double area=0;
	p[n+1]=p[1];
	FOR(i,1,n) area+=p[i+1]*p[i];
	if (sgn(area)==1)
		FOR(i,1,n/2) swap(p[i],p[n+1-i]);
}
int head,tail;
line que[MAXN];
bool HPI(Point p[],int n){
	p[n+1]=p[1];
	FOR(i,1,n) l[i].p=p[i],l[i].v=p[i+1]-p[i];
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
```

### 最小圆覆盖
```C++
//三点定圆心，保证不共线
Point threePointConfirmCentre(Point a,Point b,Point c){
	return lineIntersect((a+b)/2,Rot(b-a,PI/2),(a+c)/2,Rot(c-a,PI/2));
}
//最小圆覆盖
void minCircleCover(Point p[],int n){
	random_shuffle(p+1,p+1+n);
	Point o=p[1]; double r=0; int i,j,k;
	for (i=2;i<=n;++i)
	if (Dist(o,p[i])>r)
		for (o=p[i],r=0,j=1;j<i;++j)
		if (Dist(o,p[j])>r)
			for (o=(p[i]+p[j])/2,r=Dist(o,p[i]),k=1;k<j;++k)
			if (Dist(o,p[k])>r) o=threePointConfirmCentre(p[i],p[j],p[k]),r=Dist(o,p[j]);
	printf("%.2f %.2f %.2f\n",o.x,o.y,r);
}
```

### 圆的K次面积交
年久失修，凑合着看
```C++
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
	
	return 0;
}
```

### delaunay三角剖分（分治算法）
```C++
namespace delaunay{
    const int MAXN=1003;
    Point p[MAXN];
    int n,esize,u[MAXN],q[MAXN];
    struct edge{ int v,nt,pr; }e[MAXN*10];
    void clear(){
        sort(p+1,p+1+n);
        esize=0; memset(u,-1,sizeof(u));
    }
    void addEdge(int x,int y){
        e[esize]=(edge){y,u[x],-1}; e[u[x]].pr=esize; u[x]=esize++;
        e[esize]=(edge){x,u[y],-1}; e[u[y]].pr=esize; u[y]=esize++;
    }
    void delEdge(int w){
        if (~e[w].pr) e[e[w].pr].nt=e[w].nt;
        if (~e[w].nt) e[e[w].nt].pr=e[w].pr;
        if (u[e[w^1].v]==w) u[e[w^1].v]=e[w].nt;
    }
    bool inCir(Point p,Point a,Point b,Point c){
        Point o=lineIntersect((a+b)/2,Rot(b-a,PI/2),(a+c)/2,Rot(c-a,PI/2));
        return Dist(o,p)<=Dist(o,a)+eps;
    }
    void triangulation(int l,int r){
        if (r-l<=2) {
            if (l!=r)
                FOR(i,l,r-1) addEdge(i,i+1);
            if (r-l==2) addEdge(l,r);
            return;
        }
        int mid=(l+r)/2;
        triangulation(l,mid),triangulation(mid+1,r);
        int h=0;
        FOR(i,l,r) {
            while (h>1&&Cross(p[q[h]],p[i],p[q[h-1]])<=eps) h--;
            q[++h]=i;
        }
        int ld=0,rd=0;
        FOR(i,1,h) {
            if (q[i]<=mid) ld=q[i];
            if (!rd&&q[i]>mid) rd=q[i];
        }
        addEdge(ld,rd);
        while (1) {
            int d=0;
            for (int i=u[ld];~i;i=e[i].nt)
            if ((Cross(p[rd],p[e[i].v],p[ld])>eps)&&(!d||inCir(p[e[i].v],p[d],p[ld],p[rd]))) d=e[i].v;
            for (int i=u[rd];~i;i=e[i].nt)
            if ((Cross(p[ld],p[e[i].v],p[rd])<-eps)&&(!d||inCir(p[e[i].v],p[d],p[ld],p[rd]))) d=e[i].v;
            if (!d) break;//return;
            if (d<=mid) {
                addEdge(d,rd);
                for (int i=u[ld];~i;i=e[i].nt)
                if (segIntersect(p[ld],p[e[i].v],p[d],p[rd])==1) delEdge(i),delEdge(i^1);
                ld=d;
            }
            else {
                addEdge(ld,d);
                for (int i=u[rd];~i;i=e[i].nt)
                if (segIntersect(p[rd],p[e[i].v],p[ld],p[d])==1) delEdge(i),delEdge(i^1);
                rd=d;
            }
        }
        // printf("working(%d,%d)\n",l,r);
        // FOR(i,l,r) {
            // printf("%d:",i);
            // for (int j=u[i];~j;j=e[j].nt) printf("%d,",e[j].v);
            // printf("\n");
        // }
    }
}
```

### 三角形各心
```C++
//三角形重心
Point MassCenter(Point A,Point B,Point C)
{
    return (A + B + C) * (1.0 / 3.0);
}
//三角形内心
Point InnerCenter(Point A,Point B,Point C)
{
    double a = dist(B,C),b = dist(A,C),c = dist(A,B);
    return (A * a + B * b + C * c) * (1.0 / (a + b + c));
}
//三角形外心
Point CircumCenter(Point A,Point B,Point C)
{
    Point t1 = B - A,t2 = C - A,t3((t1 * t1) * 0.5,(t2 * t2) * 0.5);
    swap(t1.y,t2.x);
    return A + Point(t3 ^ t2,t1 ^ t3) * (1.0 / (t1 ^ t2));
}
//三角形垂心
Point OrthoCenter(Point A,Point B,Point C)
{
    return MassCenter(A,B,C) * 3.0 - CircumCenter(A,B,C) * 2.0;
}
```

### 折纸问题（普通）

```C++
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

```

### 折纸问题（进阶）

```C++
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

```


## 三维几何

### 三维点类（常用）
```C++
#define sqr(x) ((x)*(x))
const double eps=1e-8,INF=1e20,PI=3.141592653589793238462;
double sgn(double x){ if (fabs(x)<=eps) return 0; return x>0?1:-1; }
struct P3{
	double x,y,z;
	P3(double xx=0,double yy=0,double zz=0):x(xx),y(yy),z(zz){}
	double len(){ return sqrt(x*x+y*y+z*z); }
	//三维向量加减乘除
	P3 operator +(const P3 &p)const{ return P3(x+p.x,y+p.y,z+p.z); }
	P3 operator -(const P3 &p)const{ return P3(x-p.x,y-p.y,z-p.z); }
	P3 operator *(const double &f)const{ return P3(x*f,y*f,z*f); }
	P3 operator /(const double &f)const{ return P3(x/f,y/f,z/f); }
	//三维叉积和点积
	P3 operator *(const P3 &p)const{ return P3(y*p.z-z*p.y,-x*p.z+z*p.x,x*p.y-y*p.x); }
	double operator ^(const P3 &p)const{ return x*p.x+y*p.y+z*p.z; }
	bool operator ==(const P3 &p)const{ return sgn(x-p.x)==0&&sgn(y-p.y)==0&&sgn(z-p.z)==0; }
	bool operator <(const P3 &p)const{ return !sgn(x-p.x)?(!sgn(y-p.y)?(!sgn(z-p.z)?0:z<p.z):y<p.y):x<p.x; }
	//读入与输出
	void input(){ scanf("%lf%lf%lf",&x,&y,&z); }
	void output(){ printf("(%.8f,%.8f,%.8f)\n",x,y,z); }
};
typedef P3 V3;
//三维距离
double Dist(P3 p1,P3 p2){ return sqrt(sqr(p1.x-p2.x)+sqr(p1.y-p2.y)+sqr(p1.z-p2.z)); }
//三维叉积和点积
P3 Cross(P3 p1,P3 p2,P3 o){ return (p1-o)*(p2-o); }
double Dot(P3 p1,P3 p2,P3 o){ return (p1-o)^(p2-o); }
//三维混合积
double mixP(V3 p1,V3 p2,V3 p3){ return p1^(p2*p3); }
double mixP(P3 p1,P3 p2,P3 p3,P3 o){ return (p1-o)^((p2-o)*(p3-o)); }
//向量夹角
double rad(P3 p,P3 q){ return acos((p^q)/p.len()/q.len()); }
struct L3{
	P3 s; V3 v;
	L3(){}
	L3(P3 s,P3 e):s(s),v(e-s){}
	bool operator ==(const L3 &l)const{ return sgn((v*l.v).len())==0&&sgn((v*(l.s-s)).len())==0; }
};
//判断点在直线上
bool pointOnLine(P3 p,L3 l){ return sgn((l.v*(p-l.s)).len())==0; }
//点到直线的距离
double pointToLine(P3 p,L3 l){ return (l.v*(p-l.s)).len()/l.v.len(); }
//点到线段的距离
double pointToSeg(P3 p,P3 s,P3 e){
	if (sgn(Dot(p,s,e))<0||sgn(Dot(p,e,s))<0) return min(Dist(s,p),Dist(e,p));
	return ((p-s)*(e-s)).len()/Dist(s,e);
}
//点p在直线上的投影
P3 lineProj(P3 p,L3 l){ return l.s+l.v*(l.v^(p-l.s))/(l.v^l.v); }
//两直线交点，0表示异面，-1表示平行，-2表示共线，1表示有交点
int lineIntersect(L3 l1,L3 l2,P3 &c){
	if (sgn(mixP(l1.v,l2.v,l1.s-l2.s))) return 0;
	if (!sgn((l1.v*l2.v).len())) {
		if (sgn((l1.v*(l1.s-l2.s)).len())) return -1;
		c=l1.s; return -2;
	}
	V3 f=l1.v*l2.v;
	double tmp=-mixP(f,l1.s-l2.s,l2.v)/mixP(f,l1.v,l2.v);
	c=l1.s+l1.v*tmp; return 1;
}
//点p饶向量v逆时针旋转arg角度
P3 rotate(P3 p,V3 v,double arg){
	v=v/v.len(); P3 tmp=v*(v^p);
	return tmp+(p-tmp)*cos(arg)+(v*p)*sin(arg);
}
struct Plane{
	P3 o; V3 f;
	Plane(){}
	Plane(P3 O,V3 F):o(O),f(F){}
};
//判断点p在平面上
bool pointOnPlane(P3 p,Plane c){ return sgn(c.f^(p-c.o))==0; }
//点p在平面上的投影
P3 planeProj(P3 p,Plane c){ double tmp=((c.o-p)^c.f)/(c.f^c.f); return p+c.f*tmp; }
//两平面夹角（法向量）
double planeAngle(Plane c1,Plane c2){ return acos((c1.f^c2.f)/c1.f.len()/c2.f.len()); }
//平面与直线交点，平面与平面交线用得不多，请现场推，此处省略
const int MAXP=2003;
namespace CH3D{
	struct face{
		int a,b,c;
		bool ok;
	}f[MAXP*8];
	P3 p[MAXP];
	int pn,fn,g[MAXP][MAXP];
	int cmp(face f,P3 o){ return sgn(mixP(o,p[f.b],p[f.c],p[f.a])); }
	void dfs(int p0,int f0);
	void deal(int p0,int a,int b){
		int f0=g[a][b];
		if (f[f0].ok) {
			if (cmp(f[f0],p[p0])>0) dfs(p0,f0);
			else {
				g[b][a]=g[a][p0]=g[p0][b]=fn;
				f[fn++]=(face){b,a,p0,true};
			}
		}
	}
	void dfs(int p0,int f0){
		f[f0].ok=false;
		deal(p0,f[f0].b,f[f0].a);
		deal(p0,f[f0].c,f[f0].b);
		deal(p0,f[f0].a,f[f0].c);
	}
	int create(){
		fn=0;
		//先找一个四面体
		bool flag=true;
		FOR(i,1,pn-1)
		if (!(p[0]==p[i])) {
			swap(p[1],p[i]);
			flag=false; break;
		}
		if (flag) return 1;
		flag=true;
		FOR(i,2,pn-1)
		if (sgn(Cross(p[0],p[1],p[i]).len())) {
			swap(p[2],p[i]);
			flag=false; break;
		}
		if (flag) return 1;
		flag=true;
		FOR(i,3,pn-1)
		if (sgn(mixP(p[0],p[1],p[2],p[i]))) {
			swap(p[3],p[i]);
			flag=false; break;
		}
		if (flag) return 1;
		//构建初始四面体
		FOR(i,0,3) {
			face tmp=(face){(i+1)%4,(i+2)%4,(i+3)%4,true};
			if (cmp(tmp,p[i])>0) swap(tmp.b,tmp.c);
			g[tmp.a][tmp.b]=g[tmp.b][tmp.c]=g[tmp.c][tmp.a]=fn;
			f[fn++]=tmp;
		}
		//不断加点
		FOR(i,4,pn-1)
			FOR(j,0,fn-1)
			if (f[j].ok&&cmp(f[j],p[i])>0) { dfs(i,j); break; }
		int tmp=fn;
		fn=0;
		FOR(i,0,tmp-1) if (f[i].ok) f[fn++]=f[i];
		return 0;
	}
	P3 massCenter(){
		double volume=0;
		P3 ans(0,0,0),o(0,0,0);
		FOR(i,0,fn-1) {
			double tmp=mixP(o,p[f[i].a],p[f[i].b],p[f[i].c]);
			ans=ans+(o+p[f[i].a]+p[f[i].b]+p[f[i].c])/4*tmp;
			volume+=tmp;
		}
		ans=ans/volume;
		return ans;
	}
	double pointToFace(P3 o,face f)
	{ return fabs(mixP(o,p[f.a],p[f.b],p[f.c]))/Cross(p[f.a],p[f.b],p[f.c]).len(); }
	double area(int x){
		return Cross(p[f[x].a],p[f[x].b],p[f[x].c]).len();
	}
	int faceNum(){
		int ans=0;
		FOR(i,0,fn-1) {
			ans++;
			FOR(j,0,i-1) {
				if (sgn(mixP(p[f[i].a],p[f[i].b],p[f[i].c],p[f[j].a]))==0
				  &&sgn(mixP(p[f[i].a],p[f[i].b],p[f[i].c],p[f[j].b]))==0
				  &&sgn(mixP(p[f[i].a],p[f[i].b],p[f[i].c],p[f[j].c]))==0) { ans--; break; }
			}
		}
		return ans;
	}
}
```

### 最小球覆盖
```C++
//三点定球心，保证不共线
P3 threeP3ConfirmSphere(P3 a,P3 b,P3 c){
	V3 f=Cross(b,c,a);
	P3 abm=(a+b)/2,acm=(a+c)/2,ret;
	lineIntersect(abm,f*(b-a),acm,f*(c-a),ret);
	return ret;
}
//四点定球心
P3 fourP3ConfirmSphere(P3 a,P3 b,P3 c,P3 d){
	if (!sgn(mixP(a,b,c,d))) return threeP3ConfirmSphere(a,b,c);
	P3 o=threeP3ConfirmSphere(a,b,c),f=Cross(b,c,a),adm=(a+d)/2;
	double tmp=-((o-adm)^(d-a))/(f^(d-a));
	return o+f*tmp;
}
//最小球覆盖
void minSphere(P3 p[],int n){
	random_shuffle(p+1,p+1+n);
	P3 o=p[1]; double r=0; int i,j,k,l;
	for (i=2;i<=n;++i)
	if (Dist(o,p[i])>r+eps)
		for (o=p[i],r=0,j=1;j<i;++j)
		if (Dist(o,p[j])>r+eps)
			for (o=(p[i]+p[j])/2,r=Dist(o,p[i]),k=1;k<j;++k)
			if (Dist(o,p[k])>r+eps)
				for (o=threeP3ConfirmSphere(p[i],p[j],p[k]),r=Dist(o,p[j]),l=1;l<k;++l)
				if (Dist(o,p[l])>r+eps) o=fourP3ConfirmSphere(p[i],p[j],p[k],p[l]),r=Dist(o,p[k]);
	printf("%.5f\n",r);
}
```
