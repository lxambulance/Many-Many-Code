int extend_gcd(int a,int b,int &x,int &y) {
	if (b==0) { x=1; y=0; return a; }
	else {
		int tmp=extend_gcd(b,a%b,y,x);
		y-=x*(a/b); return tmp;
	}
}
/*
AX+BY=GCD(A,B)
B(Y+A/B*X)+A%B*X=GCD(B,A%B)
*/
