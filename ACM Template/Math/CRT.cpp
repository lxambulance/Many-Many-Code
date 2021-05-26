int CRT(int a[],int m[],int n) {
	int i,M=1,ans=0;
	for (i=1;i<=n;i++) M*=m[i];
	for (i=1;i<=n;i++) {
		int x,y,Mi=M/m[i];
		extend_gcd(Mi,m[i],x,y);
		ans=(ans+Mi*x*a[i])%M;
	}
	if (ans<0) ans+=M;
	return ans;  
}

/*
Problem:
x=ai(%mi)[0<=i<n]
m0,m1,m2,...,mn-1两两互质
已知mi,ai,求x
Solution:
Mi=pi(mj) [i!=j]

gcd(Mi,mi)=1 --> Mipi+miqi=1
Let ei=Mipi ,then ei={0(%mj)[i!=j],1(%mj)[i==j]}
ans0=(e0a0+e1a1+e2a2+...+en-1an-1)%pi(mi)
*/

