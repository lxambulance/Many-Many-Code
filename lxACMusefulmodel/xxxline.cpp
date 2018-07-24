const int MAXN=50,eps=1e-10;
struct P{
	double x,y;
	P(double xx=0,double yy=0){ x=xx; y=yy; }
	P operator +(const P &E)const{ return P(x+E.x,y+E.y); }
	P operator -(const P &E)const{ return P(x-E.x,y-E.y); }
	P operator *(const double z)const{ return P(x*z,y*z); }
	double operator *(const P &E)const{ return x*E.x+y*E.y; }
	inline void init(){ x=read(); y=read(); }
}A[MAXN],B,C,D[MAXN];
int n,m;
inline int sgn(double x){
	if (fabs(x)<=eps) return 0;
	else if (x>eps) return 1; else return -1;
}
inline double dist(P a,P b){ return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)); }
inline double cross(P a,P b){ return a.x*b.y-a.y*b.x; }
inline bool intersect(P a,P b,P c,P d){
	if (max(a.x,b.x)<min(c.x,d.x)||min(a.x,b.x)>max(c.x,d.x)) return false;
	if (max(a.y,b.y)<min(c.y,d.y)||min(a.y,b.y)>max(c.y,d.y)) return false;
	double x=cross(a-b,c-b),y=cross(a-b,d-b),z=cross(c-d,a-d),w=cross(c-d,b-d);
	if (sgn(x)==0&&sgn(y)==0) return false;
	if (sgn(z)==0) return true; else if (sgn(w)==0) return false;
	if (sgn(x)*sgn(y)<=0&&sgn(z)*sgn(w)<=0) return true; else return false;
}
inline P work(P a,P b,P c,P d){
	P ans;
	double a1=b.y-a.y,b1=-(b.x-a.x),c1=a.x*b.y-a.y*b.x;
	double a2=d.y-c.y,b2=-(d.x-c.x),c2=c.x*d.y-c.y*d.x;
	ans.x=(c1*b2-c2*b1)/(a1*b2-a2*b1); ans.y=(a1*c2-a2*c1)/(a1*b2-a2*b1);
	return ans;
}