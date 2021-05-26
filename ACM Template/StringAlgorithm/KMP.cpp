inline void KMP(char s[],int f[]) {
	int i,j;
	for (i=2,j=0,f[1]=0;i<=n;++i) {
		while (j>0&&s[i]!=s[j+1]) j=f[j];
		if (s[i]==s[j+1]) j++;
		f[i]=j;
	}
}