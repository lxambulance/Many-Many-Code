#include<bits/stdc++.h>
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

const int MAXN=51;
int sgn(int x){ if (!x) return 0; else return x>0?1:-1; }
struct Point{
	int x,y;
	Point(int xx=0,int yy=0):x(xx),y(yy){}
	Point operator +(const Point &p)const{ return Point(x+p.x,y+p.y); }
	Point operator -(const Point &p)const{ return Point(x-p.x,y-p.y); }
	int operator *(const Point &p)const{ return x*p.y-y*p.x; }
	int operator ^(const Point &p)const{ return x*p.x+y*p.y; }
	bool operator <(const Point &p)const{ return x==p.x?y<p.y:x<p.x; }
};
int Dot(Point a,Point b,Point o){ return sgn((a-o)^(b-o)); }
int Cross(Point a,Point b,Point o){ return sgn((a-o)*(b-o)); }

Point A[MAXN],B[MAXN];
int n,m,q,a[MAXN],f[MAXN][MAXN];
int cmp(Point a,Point b){ return sgn(a*b)>0||sgn(a*b)==0&&(a^a)<(b^b); }
int main(){
	int T=read();
	while (T--) {
		n=read();
		FOR(i,1,n) A[i].x=read(),A[i].y=read();
		sort(A+1,A+1+n);
		// FOR(i,1,n) printf("A[%d]=(%d,%d)\n",i,A[i].x,A[i].y);
		int ans=0;
		FOR(left,1,n-2) {
			m=0;
			FOR(i,left+1,n) B[++m]=A[i]-A[left];
			sort(B+1,B+1+m,cmp);
			// printf("leftnode=(%d,%d)\n",A[left].x,A[left].y);
			// FOR(i,1,m) printf("B[%d]=(%d,%d)\n",i,B[i].x,B[i].y);
			memset(f,0,sizeof(f));
			FOR(i,2,m) {
				int j=i-1,k;
				while (j&&B[i]*B[j]==0) j--;
				q=0;
				for (;j;j=k) {
					for (k=j-1;k&&Cross(B[i],B[j],B[k])>0;--k);
					f[i][j]=max(f[i][j],f[j][k]+B[j]*B[i]);
					a[++q]=j;
				}
				ROF(j,q,2) f[i][a[j-1]]=max(f[i][a[j-1]],f[i][a[j]]);
				FOR(j,1,q) ans=max(ans,f[i][a[j]]);
			}
		}
		printf("%d",ans/2);
		if (ans&1) puts(".5"); else puts(".0");
	}
	return 0;
}

/*
3
0 0
1 0
0 1

5
0 0
1 0
2 0
0 1
1 1

5
0 0
3 0
4 1
3 5
-1 3

6
3 1
1 0
2 0
3 0
4 0
5 0

9
9 5
5 9
5 0
7 7
4 8
5 5
5 2
5 8
9 7

4
4 1
0 3
0 0
0 1

*/
