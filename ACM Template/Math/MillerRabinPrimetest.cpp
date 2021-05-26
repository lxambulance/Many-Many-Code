ll qmul(ll a,ll b,ll c) {
	ll ans=0;
	while (b) {
		if (b&1) {
			ans+=a;
			if (ans>=c) ans-=c;
		}
		a<<=1; b>>=1;
		if (a>=c) a-=c;
	}
	return ans;
}
ll qpow(ll a,ll b,ll c) {
	ll ans=1; a%=c;
	while (b) {
		if (b&1) ans=qmul(ans,a,c);
		a=qmul(a,a,c); b>>=1;
	}
	return ans;
}
//{2,7,61};//4759123141=4e9
//{2,2570940,880937,610386380,4130785767};//341550071728321=3e15
//{2,325,9375,28178,450755,9780504,1795265022};//2^64
int pri[]={2,7,61};//4759123141=4e9
bool Miller_Rabin_test(ll n) {
	if (n==2) return true;
	if (n<2||!(n&1)) return false;
	ll k=0,m=n-1;
	while (!(m&1)) m>>=1,k++;
	FOR(i,0,2) {
		if (pri[i]>=n) return true;
		ll x=qpow(pri[i],m,n);
		if (x==1) continue;
		bool flag=false;
		FOR(j,1,k) {
			if (x==n-1) { flag=true; break; }
			x=qmul(x,x,n);
		}
		if (!flag) return false;
	}
	return true;
}
