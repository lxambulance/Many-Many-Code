#include <bits/stdc++.h>
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

const int MAXN=300005;
void add_mod(LL &x,LL y,LL z){ if (x+y>=z) x=x+y-z; else x=x+y; }
LL qmul(LL x,LL y,LL z){
	LL ans=0; x%=z; y%=z;
	while (y) {
		if (y&1) add_mod(ans,x,z);
		y>>=1; add_mod(x,x,z);
	}
	return ans;
}
LL qpow(LL x,LL y,LL z){
	LL ans=1; x%=z;
	while (y) {
		if (y&1) ans=qmul(ans,x,z);
		y>>=1; x=qmul(x,x,z);
	}
	return ans;
}
LL test[7]={2,325,9375,28178,450775,9780504,1795265022};
bool miller_rabin(LL x,LL y){
	if (y%x==0) return true;
	LL z=x-1; while (!(z&1)) z>>=1;
	LL w=qpow(y,z,x);
	while (z!=x-1&&w!=1&&w!=x-1) w=qmul(w,w,x),z<<=1;
	//printf("%lld %lld %lld %lld\n",x,y,z,w);
	return (w==x-1)||(z&1);
}
bool is_prime(LL x){
	if (x==2) return true;
	if (x<2||!(x&1)) return false;
	//printf("%lld\n",x);
	FOR(i,0,6) {
		if (!miller_rabin(x,test[i])) return false;
		//printf("%lld OK!\n",test[i]);
	}
	return true;
}
LL gcd(LL a,LL b){ return b==0?a:gcd(b,a%b); }
LL pollard_rho(LL x0,int num){
	LL x=(rand()<<16|rand())%x0,y=x,z,i=0,j=1;
	while (1) {
		x=qmul(x,x,x0); x=(x+num)%x0;
		z=gcd(abs(x-y),x0);
		if (z!=1&&z!=x0) return z;
		if (x==y) return x0;
		if (j==++i) j<<=1,y=x;
	}
}
LL p,fac[MAXN];
void Divide(LL x,int num){
	if (x==1) return;
	if (is_prime(x)) { fac[++p]=x; return; }
	//printf("not pass prime test!\n");
	LL p0=x;
	while (p0==x) p0=pollard_rho(p0,num--);
	Divide(p0,num); Divide(x/p0,num);
}
int n,m,q,a[MAXN],b[MAXN];
int main(){
	int *lx=new int[5];
	srand((unsigned long long)lx);
	delete[] lx;
	
	LL x;
	while (scanf("%lld",&x)!=EOF) {
		p=0; Divide(x,233); sort(fac+1,fac+1+p);
		if (p==2&&fac[1]!=fac[2]) printf("%lld %lld %lld\n",fac[1],fac[2],fac[1]*fac[2]);
		else if(p==3&&fac[1]==fac[2]&&fac[2]==fac[3])
			printf("%lld %lld %lld\n",fac[1],fac[1]*fac[1],fac[1]*fac[1]*fac[1]);
		else printf("is not a D_num\n");
	}
	return 0;
}

/*
6
10
9

*/