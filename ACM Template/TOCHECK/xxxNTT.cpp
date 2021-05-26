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

//const LL p0=50000000001507329LL; //190734863287*2^18+1 g=2
//const LL p1=1005060097; //1917*2^19 g=5;
const LL p2=1004535809; //479*2^21+1 g=3
//const LL p3=998244353; //119*2^23+1 g=3
//const LL p4=950009857; //453*2^21 g=7;
const int g=3,num=20;
#define MAXN (1<<(num-2))

LL wn[MAXN];
LL pow_mod(LL a,LL b,LL c) {
	LL ans=1;
	while (b) {
		if (b&1) ans=ans*a%c;
		a=a*a%c; b>>=1;
	}
	return ans;
}
void NTT(LL a[],int n,int f) {
	int i,j,k,l;
	for (i=1,j=(n>>1);i<n-1;++i,j^=k) {
		if (i<j) swap(a[i],a[j]);
		for (k=(n>>1);j>=k;k>>=1) j^=k;
	}
	for (i=2,l=0;i<=n;i<<=1) {
		for (j=0,l++;j<n;j+=i) {
			LL w=1;
			for (k=j;k<j+i/2;++k) {
				LL b=a[k],c=a[k+i/2]*w%p2;
				a[k]=(b+c); a[k+i/2]=(b-c+p2);
				if (a[k]>=p2) a[k]-=p2;
				if (a[k+i/2]>=p2) a[k+i/2]-=p2;
				w=w*wn[l]%p2;
			}
		}
	}
	if (f==-1) {
		for (i=1;i<n/2;++i) swap(a[i],a[n-i]);
		LL tmp=pow_mod(n,p2-2,p2);
		for (i=0;i<n;++i) a[i]=a[i]*tmp%p2;
	}
}

int n,m;
LL a[MAXN],b[MAXN];
int main() {
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	
	int i,j,k; 
	m=read(); for (n=1;n<=(m<<1);n<<=1);
	for (i=0;i<m;++i) a[i]=read();
	for (i=0;i<m;++i) b[i]=read();
	for (i=0;i<num;++i) { int tmp=1<<i; wn[i]=pow_mod(g,(p2-1)/tmp,p2); }
	NTT(a,n,1); NTT(b,n,1);
	for (i=0;i<n;++i) a[i]=a[i]*b[i]%p2;
	NTT(a,n,-1);
	for (i=0;i<m*2-1;++i) cout<<a[i]<<' '; cout<<endl;
	
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

