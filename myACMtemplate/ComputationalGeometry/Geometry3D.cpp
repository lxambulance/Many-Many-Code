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
//点p在平面上的投影
P3 project(P3 p,V3 f,P3 o){ double tmp=((o-p)^f)/(f^f); return p+f*tmp; }
//两直线交点，0表示异面，-1表示平行，-2表示共线，1表示有交点
int lineIntersect(P3 s,V3 u,P3 t,V3 v,P3 &c){
	if (sgn(mixP(u,v,s-t))) return 0;
	if (!sgn((u*v).len())) {
		if (sgn((u*(s-t)).len())) return -1;
		c=s; return -2;
	}
	V3 f=u*v;
	double tmp=-mixP(f,t-s,u)/mixP(f,v,u);
	c=t+v*tmp;
	return 1;
}