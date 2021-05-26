const int MAXM=10000007;
bool b[MAXM];
int tot,prime[MAXM];
void get_prime(int n) {
	memset(b,0,sizeof(b)); tot=0;
	for (int i=2;i<=n;++i) {
		if (!b[i]) prime[++tot]=i;
		for (int j=1;j<=tot&&prime[j]*i<=n;++j) {
			b[prime[j]*i]=1;
			if (i%prime[j]==0) break;
		}
	}
}
LL next_prime(LL x) {
	int i,j;
	while (1) {
		for (i=2,j=1;i*i<=x;++i) if (x%i==0) { j=0; break; }
		if (j==1) { return x; break; }
		x++;
	}
}
