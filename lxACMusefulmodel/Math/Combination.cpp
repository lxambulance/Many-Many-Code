int Cf[MAXN],Ci[MAXN];
void prepareC(){
	Cf[0]=1;
	FOR(i,1,MAXN-1) Cf[i]=1ll*Cf[i-1]*i%Mo;
	Ci[MAXN-1]=qpow(Cf[MAXN-1],Mo-2);
	ROF(i,MAXN-1,1) Ci[i-1]=1ll*Ci[i]*i%Mo;
	//FOR(i,0,5) printf("%d %d\n",Cf[i],Ci[i]);
}
int C(int x,int y){
	if (y<0||y>x) return 0;
	return 1ll*Cf[x]*Ci[y]%Mo*Ci[x-y]%Mo;
}
