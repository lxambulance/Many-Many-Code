ll add(ll a,ll b,ll c) {
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
ll power(ll a,ll b,ll c) {
	ll ans=1;
	while (b) {
		if (b&1) ans=add(ans,a,c);
		a=add(a,a,c); b>>=1;
	}
	return ans;
}
bool Miller_Rabin_test(ll a,ll b,ll n) {
	if (n==2) return true;
	else if (n==a||!(n&1)) return false;
	while (!(b&1)) b>>=1;
	ll tmp=power(a,b,n);
	while (b!=n-1&&tmp!=n-1&&tmp!=1) { tmp=add(tmp,tmp,n); b<<=1; }
	return (tmp==n-1)||((b&1)&&(tmp==1));
}
//{2,7,61}4759123141
//{2,3,5,7,11,13,17}341550071728321
//{2,3,5,7,11,13,17,19,23,29,31,37}2^64
bool isprime(ll n){
    int a[]={2,3,5,7,11,13,17,19,23,29,31,37};
	for (int i=0;i<12;++i) {
		if (n==a[i]) return true;
		if (!Miller_Rabin_test(a[i],n-1,n)) return false;
	}
	return true;
}
