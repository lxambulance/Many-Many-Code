const int MAXN=10000005;
bool b[MAXN];
int tot,Mu[MAXN],mu[MAXN],prime[MAXN];
//O(n)
void get_prime_mu(int n) {
	memset(b,0,sizeof(b)); tot=0; mu[1]=1;
	for (int i=2;i<=n;++i) {
		if (!b[i]) {
			prime[++tot]=i;
			mu[i]=-1;
		}
		for (int j=1;j<=tot&&prime[j]*i<=n;++j) {
			b[prime[j]*i]=1;
			if (i%prime[j]==0) { mu[prime[j]*i]=0; break; }
			else mu[prime[j]*i]=-mu[i];
		}
	}
}
//O(n log n)
void get_Mu(int n) {
	memset(Mu,0,sizeof(Mu));
	int i,j,delta,target;
	for (i=1;i<=n;++i) { 
		Mu[i]=(i==1?1:0)-Mu[i];
		for (j=i+i;j<=n;j+=i) Mu[j]+=Mu[i];
	}
}

