const int MAXN=505;
const double eps=1e-8;
bool l[MAXN];
double ans[MAXN],a[MAXN][MAXN];
inline int Gaussian_elimination(const int &n) {
	int i,j,k,res=0;
	for (i=0;i<n;++i) l[i]=false;
	for (i=0;i<n;++i) {
		for (j=i;j<n;++j)
		if (fabs(a[j][i])>eps) {
			for (k=i;k<=n;++k) swap(a[j][k],a[i][k]);
			break;
		}
		if (fabs(a[i][i])<eps) { ++res; continue; }
		for (j=0;j<n;++j)
		if (j!=i&&fabs(a[j][i])>eps) {
			double tmp=a[j][i]/a[i][i];
			for (k=i;k<=n;++k) a[j][k]-=tmp*a[i][k];
		}
		l[i]=true;
	}
	for (i=0;i<n;++i)
	if (l[i])
		for (j=0;j<n;++j)
		if (fabs(a[j][i])>0) ans[i]=a[j][n]/a[j][i];
	return res;
}
