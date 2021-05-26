#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;

class hash{
private:
	static const ll MOD=100007,lx1=19260817,lx2=997244353;
	ll a[MOD+100],v[MOD+100];
public:
	hash() { memset(a,0xff,sizeof(a)); }
	int locate(ll x) {
		ll l=((x*lx1)^lx2)%MOD;
		while(a[l]!=x&&a[l]!=-1) l=(l+1)%MOD;
		return l;
	}
	void insert(ll x,ll va) {
		ll l=locate(x);
		if (a[l]==-1) { a[l]=x; v[l]=va; }
	}
	ll get(ll x) { ll l=locate(x); return a[l]==x?v[l]:-1; }
	void clear() { memset(a,0xff,sizeof(a)); }
}S;
ll exgcd(ll a,ll b,ll &x,ll &y) {
	ll t,ret;
	if (!b) { x=1,y=0; return a; }
	ret=exgcd(b,a%b,x,y); t=x; x=y; y=t-a/b*y;
	return ret;
}

int main() {
	ll C,A,B,m,i,t,D,ans,x,y;
	while (scanf("%lld%lld%lld",&C,&A,&B)!=EOF) {
		S.clear();
		m=ceil(sqrt((double)C)); t=1;
		for (i=0;i<m;i++) { S.insert(t,i); t=t*A%C; }
		D=1; ans=-1;
		for (i=0;i<m;i++) {
			exgcd(D,C,x,y); //exgcd求逆元，得到x=D^(-i*m)
			x=((x*B)%C+C)%C;
			y=S.get(x);
			if(y!=-1) { ans=i*m+y; break; }
			D=(D*t)%C; //D=t^i,(t=A^m)
		}
		if (ans==-1) printf("no solution\n"); else printf("%lld\n",ans);
	}
	return 0;
}

/*
B^L=N (mod P) 知 B N P，求L
A^x=B(modC) A^j=B*A^(-m*i)(mod C)
*/
