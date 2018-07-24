const int MAXN=300005,Mo=1000000007;
const double eps=1e-10,INF=1e20,PI=3.141592653589793238462;
inline int sgn(double x){ if (fabs(x)<=eps) return 0; return x>0?1:-1; }
struct P{
	double x,y;
	P(double xx=0,double yy=0):x(xx),y(yy){}
	double len(){ return sqrt(x*x+y*y); }
	P operator +(const P &E)const{ return P(x+E.x,y+E.y); }
	P operator -(const P &E)const{ return P(x-E.x,y-E.y); }
	P operator *(const double &f)const{ return P(x*f,y*f); }
	P operator /(const double &f)const{ return P(x/f,y/f); }
	double operator *(const P &E)const{ return x*E.y-E.x*y; }
	double operator ^(const P &E)const{ return x*E.x+y*E.y; }
}A,B,C,O;
inline double dist(P a,P b){ return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)); }
inline double cross(P a,P b,P o){ return (a-o)*(b-o); }
inline double dot(P a,P b,P o){ return (a-o)^(b-o); }
inline double deg(P p){ double tmp=atan2(p.y,p.x); return tmp<0?tmp+PI*2:tmp; }
inline P rot(P p,double a){ return P(cos(a)*p.x-sin(a)*p.y,sin(a)*p.x+cos(a)*p.y); }
struct L{
	double a,b,c;
	L(P A,P B){ a=B.y-A.y; b=A.x-B.x; c=-(A*B); }
}l1,l2;
inline P clammer(L l,L r){
	P ans(-l.c*r.b+l.b*r.c,-l.a*r.c+l.c*r.a);
	return ans/(l.a*r.b-r.a*l.b);
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
