LL add(LL a,LL b,LL c) {
	LL ans=0;
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
LL power(LL a,LL b,LL c) {
	LL ans=1;
	while (b) {
		if (b&1) ans=add(ans,a,c);
		a=add(a,a,c); b>>=1;
	}
	return ans;
}
bool Miller_Rabin_test(LL a,LL b,LL n) {
	if (n==2) return true;
	else if (n==a||!(n&1)) return false;
	while (!(b&1)) b>>=1;
	LL tmp=power(a,b,n);
	while (b!=n-1&&tmp!=n-1&&tmp!=1) { tmp=add(tmp,tmp,n); b<<=1; }
	return (tmp==n-1)||((b&1)&&(tmp==1));
}
bool isprime(LL n) {
	int a[]={2,3,7,61,24251}; //10^16
	if (n==46856248255981LL) return false;
	for (int i=0;i<5;++i) {
		if (n==a[i]) return true;
		if (!Miller_Rabin_test(a[i],n-1,n)) return false;
	}
	return true;
}