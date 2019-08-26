int nt[MAXN],ex[MAXN];
void exKMP(char s[],int f[]){
	int len=strlen(s+1);
	f[1]=len,f[2]=0;
	while (f[2]+2<=len&&s[f[2]+1]==s[f[2]+2]) f[2]++;
	for (int i=3,p0=2;i<=len;++i) {
		if (f[i-p0+1]+i-1<f[p0]+p0-1) f[i]=f[i-p0+1];
		else {
			int j=max(0,p0+f[p0]-i);
			while (i+j<=len&&s[i+j]==s[j+1]) j++;
			f[p0=i]=j;
		}
	}
}
void getExtend(char s[],char t[],int f[]){
	int n=strlen(s+1),m=strlen(t+1);
	f[1]=0;
	while (f[1]+1<=n&&f[1]+1<=m&&s[f[1]+1]==t[f[1]+1]) f[1]++;
	for (int i=2,p0=1;i<=m;++i) {
		if (nt[i-p0+1]+i-1<f[p0]+p0-1) f[i]=nt[i-p0+1];
		else {
			int j=max(0,p0+f[p0]-i);
			while (i+j<=m&&j+1<=n&&s[j+1]==t[i+j]) j++;
			f[p0=i]=j;
		}
	}
}
