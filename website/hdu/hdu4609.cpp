//program hdu4609
//Author LxAmbulance
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;
#define FOR(i,a,b) for (int i=(a);i<=(b);++i)
#define ROF(i,b,a) for (int i=(b);i>=(a);--i)
typedef long long LL;
inline int read(){
	int x=0,f=1; char ch=getchar();
	while (ch<'0'||ch>'9') { if (ch=='-') f=-1; ch=getchar(); }
	while (ch>='0'&&ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	return x*f;
}

const int MAXN=800005;
const double eps=1e-8,PI=3.141592653589793238462;
struct P{
	double x,y;
	P(double x=0,double y=0):x(x),y(y){}
	P operator +(const P &E)const{ return P(x+E.x,y+E.y); }
	P operator -(const P &E)const{ return P(x-E.x,y-E.y); }
	P operator *(const P &E)const{ return P(x*E.x-y*E.y,x*E.y+y*E.x); }
}A[MAXN];
int n,m,len,a[MAXN];
LL b[MAXN],c[MAXN];
void FFT(P A[],int f){
	int i,j,k;
	for (i=j=0;i<len;++i) {
		if (i<j) swap(A[i],A[j]);
		for (k=len>>1;(j^=k)<k;k>>=1);
	}
	for (i=1;i<len;i<<=1) {
		P wi=P(cos(PI/i),sin(PI/i)*f);
		for (j=0;j<len;j+=i<<1) {
			P w=P(1,0);
			for (k=0;k<i;++k,w=w*wi) {
				P x=A[j+k],y=w*A[j+k+i];
				A[j+k]=x+y; A[j+k+i]=x-y;
			}
		}
	}
	if (f==-1) FOR(i,0,len-1) A[i].x/=len;
}
int main(){
	int T=read();
	while (T--) {
		n=read(); m=0;
		FOR(i,1,n) a[i]=read(),m=max(a[i],m);
		for (len=2;len<=m*2;len<<=1);
		//printf("maxsize=%d\n",len);
		FOR(i,0,len) A[i]=P(0,0),b[i]=c[i]=0;
		FOR(i,1,n) A[a[i]].x+=1;
		//printf("before\n");
		//FOR(i,0,len-1) printf("%.0f%c",A[i].x," \n"[i==len-1]);
		FFT(A,1);
		FOR(i,0,len-1) A[i]=A[i]*A[i];
		FFT(A,-1);
		FOR(i,0,len-1) b[i]=LL(A[i].x+0.5);
		FOR(i,1,n) b[a[i]*2]--;
		FOR(i,0,len) b[i]/=2;
		//printf("after\n");
		//FOR(i,0,len-1) printf("%lld%c",b[i]," \n"[i==len-1]);
		c[0]=b[0];
		FOR(i,1,len) c[i]=c[i-1]+b[i];
		LL ans=0,tot=1LL*n*(n-1)*(n-2)/6;
		sort(a+1,a+1+n);
		FOR(i,1,n) {
			ans+=c[len]-c[a[i]];
			ans-=1LL*(n-i)*(n-i-1)/2;
			ans-=1LL*(n-i)*(i-1);
			ans-=1LL*(n-1);
		}
		printf("%.7f\n",double(ans)/double(tot));
	}
	return 0;
}

/*
2
4
1 3 3 4
4
2 3 3 4

*/
