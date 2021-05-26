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
