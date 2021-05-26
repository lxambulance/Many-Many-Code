#include <bits/stdc++.h>
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

const int MAXN=400005;
#define sqr(x) ((x)*(x))
const double eps=1e-10,INF=1e20,PI=3.141592653589793238462;
inline int sgn(double x){ if (fabs(x)<=eps) return 0; return x>0?1:-1; }
struct P{
	double x,y;
	P(double xx=0,double yy=0):x(xx),y(yy){}
	double len(){ return sqrt(x*x+y*y); }
	//向量的加减乘除
	P operator +(const P &p)const{ return P(x+p.x,y+p.y); }
	P operator -(const P &p)const{ return P(x-p.x,y-p.y); }
	P operator *(const double &f)const{ return P(x*f,y*f); }
	//要求f不为0
	P operator /(const double &f)const{ return P(x/f,y/f); }
	//向量的叉积与点积
	double operator *(const P &p)const{ return x*p.y-p.x*y; }
	double operator ^(const P &p)const{ return x*p.x+y*p.y; }
	//凸包的排序
	bool operator <(const P &p)const{ return x<p.x||(x==p.x&&y<p.y); }
};
typedef P V;
//函数形式的距离、叉积与点积
double Dist(P a,P b){ return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)); }
double Cross(P a,P b,P o){ return (a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x); }
double Cross(V v1,V v2){ return v1.x*v2.y-v1.y*v2.x; }
double Dot(P a,P b,P o){ return (a.x-o.x)*(b.x-o.x)+(a.y-o.y)*(b.y-o.y); }
double Dot(V v1,V v2){ return v1.x*v2.x+v1.y*v2.y; }
//向量旋转（逆时针，弧度）
inline V Rot(V p,double a){ return V(cos(a)*p.x-sin(a)*p.y,sin(a)*p.x+cos(a)*p.y); }
//向量极角（弧度）
double Deg(P p){ double tmp=atan2(p.y,p.x); return tmp<0?tmp+PI*2:tmp; }
//点o在直线上的投影，要求|v|不为0
P Project(P o,P p,V v){ double tmp=((o-p)^v)/(v^v); return p+v*tmp; }
//两直线（点向式）交点，要求直线不平行
P lineIntersect(P p1,V v1,P p2,V v2){ double tmp=(v1*(p2-p1))/(v2*v1); return p2+v2*tmp; }
//点到线段的距离，要求s1!=s2
double pointToSeg(P s1,P s2, P p){
	if (Dot(p,s1,s2)<eps) return Dist(s2,p); else if (Dot(p,s2,s1)<eps) return Dist(s1,p);
	return fabs(Cross(p,s2,s1))/Dist(s1,s2);
}
//点到直线的距离
double pointToLine(P p,P o,V v){ return fabs(Cross(p-o,v))/v.len(); }
//线段是否相交，0为不相交，1为严格相交且交点不在线段端点上，2表示交点为某线段端点，3为线段平行且部分重合
inline int segIntersect(P a,P b,P c,P d){
	if (max(a.x,b.x)<min(c.x,d.x)||min(a.x,b.x)>max(c.x,d.x)) return 0;
	if (max(a.y,b.y)<min(c.y,d.y)||min(a.y,b.y)>max(c.y,d.y)) return 0;
	double x=Cross(a-b,c-b),y=Cross(a-b,d-b),z=Cross(c-d,a-d),w=Cross(c-d,b-d);
	if (sgn(x)==0&&sgn(y)==0) return 3;
	if (sgn(x)*sgn(y)<0&&sgn(z)*sgn(w)<0) return 1;
	if (sgn(x)*sgn(y)<=0&&sgn(z)*sgn(w)<=0) return 2;
	return 0;
}
//凸包，相邻边不平行
int ConvexHull(P p[],int n,P q[]){
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

P Xa,Xb,Oa,Ob,Oc,p,A,B,C,v,ans1[10];
double ra,rb,Ra,Rb,Rc,lOa,lOb,ans2[10];
int n;
P Inv(P p){ double tmp=(p^p); return P(p.x/tmp,p.y/tmp); }
int main(){
	int T=read();
	while (T--) {
		n=0;
		Oa.x=read(),Oa.y=read(),ra=Ra=read();
		Ob.x=read(),Ob.y=read(),rb=Rb=read();
		p.x=read(),p.y=read();
		Xa=Oa=Oa-p,Xb=Ob=Ob-p;
		lOa=Oa.len(),A=Inv(Oa/lOa*(lOa-Ra)),B=Inv(Oa/lOa*(lOa+Ra));
		Oa=(A+B)/2; Ra=Dist(A,B)/2;
		lOb=Ob.len(),A=Inv(Ob/lOb*(lOb-Rb)),B=Inv(Ob/lOb*(lOb+Rb));
		Ob=(A+B)/2; Rb=Dist(A,B)/2;
		if (Ra>Rb) swap(Oa,Ob),swap(Ra,Rb);
		double lab=Dist(Oa,Ob);
		double alpha=acos((Rb-Ra)/lab);
		// printf("%.8f\n",alpha);
		v=Rot(Oa-Ob,alpha)/lab;
		// printf("(%.8f,%.8f)\n",v.x,v.y);
		C=Project(P(0,0),Oa+v*Ra,Ob-Oa+v*(Rb-Ra));
		// printf("(%.8f,%.8f)\n",C.x,C.y);
		if (sgn(C.len())!=0) {
			C=Inv(C)/2; Rc=C.len();
			// printf("(%.8f,%.8f) %.8f\n",C.x,C.y,Rc);
			if (sgn(Rc+ra-Dist(C,Xa))<=0&&sgn(Rc+rb-Dist(C,Xb))<=0) ++n,ans2[n]=Rc,ans1[n]=C;
		}
		v=Rot(Oa-Ob,-alpha)/lab;
		// printf("(%.8f,%.8f)\n",v.x,v.y);
		C=Project(P(0,0),Oa+v*Ra,Ob-Oa+v*(Rb-Ra));
		// printf("(%.8f,%.8f)\n",C.x,C.y);
		if (sgn(C.len())!=0) {
			C=Inv(C)/2; Rc=C.len();
			// printf("(%.8f,%.8f) %.8f\n",C.x,C.y,Rc);
			if (sgn(Rc+ra-Dist(C,Xa))<=0&&sgn(Rc+rb-Dist(C,Xb))<=0) ++n,ans2[n]=Rc,ans1[n]=C;
		}
		printf("%d\n",n);
		FOR(i,1,n) printf("%.8f %.8f %.8f\n",ans1[i].x+p.x,ans1[i].y+p.y,ans2[i]);
	}
	return 0;
}

/*
2
12 10 1 8 10 1 10 10
12 10 1 8 10 1 10 10

*/
