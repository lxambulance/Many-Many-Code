#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
inline int read() {
	int x=0,s=1; char ch=getchar();
	while (ch<'0'||ch>'9') { if (ch=='-') s=-1; ch=getchar(); }
	while (ch>='0'&&ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	return s*x;
}

const double PI=3.141592653589793238462;
struct cpxnb{
	double x,y;
	cpxnb() {}
	cpxnb(double xx,double yy) { x=xx; y=yy; }
	inline cpxnb operator +(const cpxnb &C) const { return cpxnb(x+C.x,y+C.y); }
	inline cpxnb operator -(const cpxnb &C) const { return cpxnb(x-C.x,y-C.y); }
	inline cpxnb operator *(const cpxnb &C) const { return cpxnb(x*C.x-y*C.y,x*C.y+y*C.x); }
}A,B;
typedef cpxnb CN;
inline void swap(CN &A,CN &B) { CN tmp=A; A=B; B=tmp; }
//n必须为2^k,f=1为正变换,f=-1为逆变换,数组[0..n-1]
void FFT(CN a[],int n,int f) {
	int i,j,k;
	for (i=1,j=n>>1;i<n-1;++i,j^=k) {
		if (i<j) swap(a[i],a[j]);
		for (k=n>>1;k<=j;k>>=1) j^=k; //模拟反序进位
	}
	for (i=0;i<n;++i) printf("%.0lf ",a[i].x); printf("\n");
	for (i=2;i<=n;i<<=1) {
		CN wn(cos(PI*2.0/i),sin(PI*2.0/i)*f);
		for (k=0;k<n;k+=i) {
			CN w(1,0);
			for (j=0;j<=(i/2-1);++j) {
				CN x=a[j+k],y=a[j+k+i/2]*w;
				a[j+k]=x+y; a[j+k+i/2]=x-y; w=w*wn;
			}
		}
	}
	if (f==-1) for (i=0;i<n;++i) a[i].x/=n;
}

int n,m;
CN a[100005],b[100005];
int main() {
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	
	int i,j,k; 
	m=read(); for (n=1;n<(m<<1);n<<=1);
	for (i=0;i<m;++i) a[i].x=read(),a[i].y=0;
	for (i=0;i<m;++i) b[i].x=read(),b[i].y=0;
	FFT(a,n,1); FFT(b,n,1);
	for (i=0;i<n;++i) a[i]=a[i]*b[i];
	FFT(a,n,-1);
	for (i=0;i<n;++i) printf("%.0lf ",a[i].x); cout<<endl;
	
	//fclose(stdin);
	//fclose(stdout);
	return 0;
}

/*
8
1 2 3 4 5 6 7 8
1 2 3 4 5 6 7 8

1 5 3 7 2 6 4 8
1 4 10 20 35 56 84 120 147 164 170 164 145 112 64 0 0

*/

