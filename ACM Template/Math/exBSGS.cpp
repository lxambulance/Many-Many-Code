#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;

const int Mo 131071;
ll top;
bool flag[Mo*2];
struct HashNode{ ll data,id,next; }hash[Mo*2];
void Insert(ll a,ll b){ 
	ll k=b&Mo;
	if (flag[k]==false) {
		flag[k]=true; hash[k].next=-1; hash[k].id=a; hash[k].data=b;
		return;
	}
	while (hash[k].next!=-1) {
		if (hash[k].data==b) return;
		k=hash[k].next;
	}
	if (hash[k].data==b) return;
	hash[k].next=++top; hash[top].next=-1; hash[top].id=a; hash[top].data=b;
}
ll Find(ll b){
	ll k=b&Mo;
	if(flag[k]==false) return -1;
	while (k!=-1) {
		if (hash[k].data==b) return hash[k].id;
		k=hash[k].next;
	}
	return -1;
}
ll gcd(ll a,ll b){ return b?gcd(b,a%b):a; }
ll ext_gcd(ll a,ll b,ll& x,ll& y ){
	ll t,ret;
	if (b==0) { x=1,y=0; return a; }
	ret=ext_gcd(b,a%b,x,y); t=x; x=y; y=t-a/b*y;
	return ret;
}
ll qpow(ll a,ll b,ll n){
	ll ret=1; a=a%n;
	while (b>=1) {
		if (b&1) ret=ret*a%n;
		a=a*a%n; b>>=1;
	}
	return ret;
}
ll BabyStep_GiantStep(ll A,ll B,ll C) {
	top=Mo; B%=C;
	ll i,tmp=1;
	for (i=0;i<=100;tmp=tmp*A%C,i++) if (tmp==B%C) return i;
	ll D=1,cnt=0;
	while ((tmp=gcd(A,C))!=1) {
		if (B%tmp) return -1;
		C/=tmp; B/=tmp; D=D*A/tmp%C; cnt++;
	}
	ll M=(ll)sqrt(C+0.0);
	for (tmp=1,i=0;i<=M;tmp=tmp*A%C,i++) Insert(i,tmp);
	ll x,y,K=qpow(A,M,C);
	for (i=0;i<=M;i++) {
		ext_gcd(D,C,x,y); //D*X=1(mod C)
		tmp=((B*x)%C+C)%C;
		if((y=Find(tmp))!=-1) return i*M+y+cnt;
		D=D*K%C;
	}
	return -1;
}

int main() {
	ll A,B,C;
	while (scanf("%lld%lld%lld",&A,&C,&B),!(A==0&&B==0&&C==0)) {
		memset(flag,0,sizeof(flag));
		ll tmp=BabyStep_GiantStep(A,B,C);
		if (tmp==-1) puts("No Solution\n"); else printf("%lld\n",tmp);
	}
	return 0;
}

/*
扩展BSGS
简单的来说，就是加了一个把不互质的数通过去除公因数变为互质的，再进行BSGS
具体的就是
考虑a与p不互质的情况： 1.对于a^x=b mod p，我们可以考虑从x个a中拿出c个a与b和p消去公因子，直到a和p’互质为止。
2.一旦互质了，那么方程就是v*a^(x-c)=b’ (mod p’)，v是拿出c个a消去公因子后剩下的东西，b’，p’是消去公因子的b，p。 
这个时候还要求v的逆元，方程变为a^(x-c)=b’*v^(-1) (mod p’)。 
此时就可以用baby-step-giant-step做了，答案为BSGS的答案+c。 
注意：有可能c会大于x，所以必须约去一次就特判一次方程两边（就是v和b’）是不是相等了。如果两边相等那么直接返回c。 
*/
