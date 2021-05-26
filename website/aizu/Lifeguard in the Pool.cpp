#include <bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for (int i=(a);i<=(b);++i)
#define ROF(i,a,b) for (int i=(a);i>=(b);--i)
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define pDI pair<double,int>
inline int read(){
	int x=0,f=1; char ch=getchar();
	while (ch<'0'||ch>'9') { if (ch=='-') f=-1; ch=getchar(); }
	while (ch>='0'&&ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	return x*f;
}

const int MAXN=300005;
const double PI=3.141592653589793238462,eps=1e-12,INF=1e20;
#define sqr(x) ((x)*(x))
inline int sgn(double x){ if (fabs(x)<eps) return 0; return x>0?1:-1; }
struct P{
	double x,y,k;
	P(double x=0,double y=0):x(x),y(y){}
	P operator +(const P& p)const{ return P(x+p.x,y+p.y); }
	P operator -(const P& p)const{ return P(x-p.x,y-p.y); }
	P operator *(const double& f)const{ return P(x*f,y*f); }
	P operator /(const double& f)const{ return P(x/f,y/f); }
	double len(){ return sqrt(x*x+y*y); }
	double operator ^(const P& p)const{ return x*p.y-y*p.x; }
	double operator *(const P& p)const{ return x*p.x+y*p.y; }
	bool operator <(const P& p)const{ return k<p.k; }
}A[MAXN],B,C,D,F[MAXN],U,s,t;
inline double dot(P a,P b,P o){ return (a-o)*(b-o); }
inline double cross(P a,P b,P o){ return (a-o)^(b-o); }
inline P ulen(P p){ return p/p.len(); }
inline P projection(P l1,P l2,P p){ return l2+(l1-l2)*dot(l1,p,l2)/sqr(l1-l2); }

struct list{
	int l,lt[MAXN],nt[MAXN],x[MAXN];
	double y[MAXN];
	void clear(){ l=0; memset(lt,0,sizeof(lt)); }
	void addedge(int a,int b,double c){
		//if (l&1) printf("%d-%d %.5f\n",a,b,c);
		nt[++l]=lt[a]; lt[a]=l; x[l]=b; y[l]=c;
	}
}E;

int n,m,l;
double tg,tw,tanalpha,dis[MAXN];
priority_queue<pDI >Q;
double dijkstra(int S,int T){
	FOR(i,1,T) dis[i]=INF;
	Q.push(mp(dis[S]=0,S));
	while (!Q.empty()) {
		pDI z=Q.top(); Q.pop();
		double x=-z.fi; int y=z.se;
		if (dis[y]<x-eps) continue;
		for (int i=E.lt[y];i;i=E.nt[i]) {
			int j=E.x[i];
			if (dis[j]>x+E.y[i]) Q.push(mp(-(dis[j]=x+E.y[i]),j));
		}
	}
	return dis[T];
}
int main(){
	while (n=read(),n!=0) {
		E.clear(),m=0;
		FOR(i,1,n) scanf("%lf%lf",&A[i].x,&A[i].y);
		A[n+1]=A[1]; F[0]=A[0]=A[n];
		scanf("%lf%lf",&tg,&tw);
		//printf("%.5f\n",acos(tg/tw)/PI*180.0);
		scanf("%lf%lf%lf%lf",&s.x,&s.y,&t.x,&t.y);
		if (tw-tg<eps) { printf("%.12f\n",(s-t).len()*tw); continue; }
		tanalpha=tg/sqrt(sqr(tw)-sqr(tg));
		FOR(i,1,n) {
			//printf("%d:\n",i);
			double l1;
			l=m+1;
			U=ulen(A[i+1]-A[i]);
			//printf("%.5f %.5f\n",U.x,U.y);
			B=projection(A[i],A[i+1],s);
			l1=(s-B).len()*tanalpha;
			C=B+U*l1;
			D=B-U*l1;
			//printf("%.5f\n",l1);
			//printf("S-B=(%.5f,%.5f)C=(%.5f,%.5f)D=(%.5f,%.5f)\n",B.x,B.y,C.x,C.y,D.x,D.y);
			if (sgn(dot(A[i],A[i+1],C))<0) F[++m]=C,F[m].k=(C-A[i]).len();
			if (sgn(dot(A[i],A[i+1],D))<0) F[++m]=D,F[m].k=(D-A[i]).len();
			B=projection(A[i],A[i+1],t);
			l1=(t-B).len()*tanalpha;
			C=B+U*l1;
			D=B-U*l1;
			//printf("%.5f\n",l1);
			//printf("T-B=(%.5f,%.5f)C=(%.5f,%.5f)D=(%.5f,%.5f)\n",B.x,B.y,C.x,C.y,D.x,D.y);
			if (sgn(dot(A[i],A[i+1],C))<0) F[++m]=C,F[m].k=(C-A[i]).len();
			if (sgn(dot(A[i],A[i+1],D))<0) F[++m]=D,F[m].k=(D-A[i]).len();
			F[++m]=A[i+1],F[m].k=(A[i+1]-A[i]).len();
			sort(F+l,F+m+1);
			FOR(j,l,m)
			if (j!=1) {
				E.addedge(j-1,j,(F[j]-F[j-1]).len()*tg);
				E.addedge(j,j-1,(F[j]-F[j-1]).len()*tg);
			}
		}
		E.addedge(1,m,(F[m]-F[1]).len()*tg);
		E.addedge(m,1,(F[m]-F[1]).len()*tg);
		F[++m]=s; F[++m]=t;
		FOR(i,1,m) {
			if (i!=m-1) E.addedge(i,m-1,(F[m-1]-F[i]).len()*tw);
			if (i!=m-1) E.addedge(m-1,i,(F[m-1]-F[i]).len()*tw);
			if (i!=m) E.addedge(i,m,(F[m]-F[i]).len()*tw);
			if (i!=m) E.addedge(m,i,(F[m]-F[i]).len()*tw);
		}
		//FOR(i,1,m) printf("ID:%d (%.5f,%.5f)\n",i,F[i].x,F[i].y);
		printf("%.12f\n",dijkstra(m-1,m));
	}
	
	return 0;
}

/*
4
0 0 10 0 10 10 0 10
10
12
0 5
9 5
4
0 0 10 0 10 10 0 10
10
12
0 0
9 1
4
0 0 10 0 10 10 0 10
10
12
0 1
9 1
8
2 0 4 0 6 2 6 4 4 6 2 6 0 4 0 2
10
12
3 0
3 5
0

*/