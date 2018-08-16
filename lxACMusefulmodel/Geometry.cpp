const double eps=1e-8,INF=1e20,PI=3.141592653589793238462;
inline int sgn(double x){ if (fabs(x)<=eps) return 0; return x>0?1:-1; }
struct Point{
	double x,y;
	Point(double xx=0,double yy=0):x(xx),y(yy){}
	double len(){ return sqrt(x*x+y*y); }
	Point operator +(const Point &p)const{ return Point(x+p.x,y+p.y); }
	Point operator -(const Point &p)const{ return Point(x-p.x,y-p.y); }
	Point operator *(const double &f)const{ return Point(x*f,y*f); }
	Point operator /(const double &f)const{ return Point(x/f,y/f); }
	double operator *(const Point &p)const{ return x*p.y-p.x*y; }
	double operator ^(const Point &p)const{ return x*p.x+y*p.y; }
	bool operator <(const Point &p)const{ return x<p.x||(x==p.x&&y<p.y); }
}A,B,C,O;
typedef Point Vector;
inline double dist(Point a,Point b){ return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)); }
inline double cross(Point a,Point b,Point o){ return (a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x); }
inline double cross(Vector v1,Vector v2){ return v1.x*v2.y-v1.y*v2.x; }
inline double dot(Point a,Point b,Point o){ return (a.x-o.x)*(b.x-o.x)+(a.y-o.y)*(b.y-o.y); }
inline double dot(Vector v1,Vector v2){ return v1.x*v2.x+v1.y*v2.y; }
inline Point rot(Point p,double a){ return Point(cos(a)*p.x-sin(a)*p.y,sin(a)*p.x+cos(a)*p.y); }
double deg(Point p){ double tmp=atan2(p.y,p.x); return tmp<0?tmp+PI*2:tmp; }
Point project(Point o,Point p,Vector v){ double tmp=((o-p)^v)/(v^v); return p+v*tmp; }
Point lineIntersect(Point p1,Vector v1,Point p2,Vector v2){ double tmp=(v1*(p2-p1))/(v2*v1); return p2+v2*tmp; }
double point2seg(Point p1,Point p2, Point o){
	if (dot(o,p1,p2)<eps) return dist(p2,o);
	else if (dot(o,p2,p1)<eps) return dist(p1,o);
	else return fabs(cross(o,p2,p1))/dist(p1,p2);
}
int ConvexHull(Point p[],int n,Point q[]){
	sort(p+1,p+n+1);
	int i,m=0;
	for (i=1;i<=n;i++) {
		while (m>1&&cross(q[m],p[i],q[m-1])<=eps) m--;
		q[++m]=p[i];
	}
	int k=m;
	for (i=n-1;i>0;i--) {
		while (m>k&&cross(q[m],p[i],q[m-1])<=eps) m--;
		q[++m]=p[i];
	}
	if (n>1) m--;
	return m;
}

struct L{
	double a,b,c;
	L(Point A=Point(),Point B=Point()){ a=B.y-A.y; b=A.x-B.x; c=-(A*B); }
}l1,l2;
inline Point clammer(L l,L r){ //(l.a*r.b-r.a*l.b)!=0
	Point ans(-l.c*r.b+l.b*r.c,-l.a*r.c+l.c*r.a);
	return ans/(l.a*r.b-r.a*l.b);
}
