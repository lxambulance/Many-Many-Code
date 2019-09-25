int minstring(char s[],int n) {
	int p1,p2,k,t;
	for (p1=1,p2=2,k=0;p1<=n&&p2<=n&&k<=n;) {
		t=s[p1+k]-s[p2+k];
		if (!t) k++;
		else {
			if (t<0) p2=p2+k+1; else p1=p1+k+1;
			if (p1==p2) p2++; 
			k=0;
		}
	}
	return min(p1,p2);
}
