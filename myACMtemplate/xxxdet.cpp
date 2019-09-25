const int MAXN=505,Mo=1000000007;
int c[MAXN][MAXN];
int det(int n) {
	int i,j,k,tmp,ans=1;
	for (i=0;i<n;i++) {
		for (j=i+1;j<n;j++) {
			while (c[j][i]!=0) {
				tmp=c[i][i]/c[j][i];
				for (k=0;k<n;k++) { c[i][k]-=c[j][k]*tmp; c[i][k]%=Mo; }
				for (k=0;k<n;k++) swap(c[i][k],c[j][k]);
				ans=-ans; //important
			}
		}
		if (!c[i][i]) return 0;
		ans=ans*c[i][i]%Mo;
	}
	return (ans+Mo)%Mo;
}
//消成上三角矩阵即可