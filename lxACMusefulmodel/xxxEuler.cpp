const int MAXN=10000005;
bool b[MAXN];
int tot,phi[MAXN],prime[MAXN];
void get_prime_phi(int n) {
	memset(b,0,sizeof(b)); tot=0; phi[1]=1;
	for (int i=2;i<=n;++i) {
		if (!b[i]) {
			prime[++tot]=i;
			phi[i]=i-1;
		}
		for (int j=1;j<=tot&&prime[j]*i<=n;++j) {
			b[prime[j]*i]=1;
			if (i%prime[j]==0) {
				phi[prime[j]*i]=prime[j]*phi[i];
				break;
			}
			else phi[prime[j]*i]=phi[prime[j]]*phi[i];
		}
	}
}
int get_phi(int n) {
	int i,j=n,k=n;
	for (i=2;i<=trunc(sqrt(n))&&i<=k;++i) 
	if (!(k%i)) {
		j=j/i*(i-1);
		while (!(k%i)) k/=i;
	}
	if (k>1) { j=j/k*(k-1); k=1; }
	//printf("%d %d %d\n",n,j,k);
	return j;
}
