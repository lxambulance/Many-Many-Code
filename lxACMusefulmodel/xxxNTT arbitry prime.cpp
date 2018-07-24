//常数爆炸
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
#define K 3
#define G 3
#define inline __attribute__((optimize("O2")))
inline LL read() {
	LL x=0,f=1; char ch=getchar();
	while (ch<'0'||ch>'9') { if (ch=='-') f=-1; ch=getchar(); }
	while (ch>='0'&&ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	return x*f;
}

const LL MAXN=2005,Mo=1000000007,m[K]={1004535809LL,998244353LL,104857601LL};
LL n,lx,ans,a[MAXN<<2],b[MAXN<<2],c[MAXN<<2],ll[MAXN<<2],rr[MAXN<<2],g[MAXN][MAXN];
inline void add(LL &x,LL y) { x+=y; if (x>=Mo) x-=Mo; }
inline LL lowbit(LL x) { return x&(-x); }
inline LL sum(LL x,LL y) { LL z=0; while (y>0) { add(z,g[x][y]); y-=lowbit(y); } return z; }
inline void update(LL x,LL y,LL z) { while (y<=n) { add(g[x][y],z); y+=lowbit(y); } }
inline LL pow(LL x,LL k,LL P) {
	LL ans=1;
	while(k) {
		if(k&1) ans=ans*x%P;
		k>>=1; x=x*x%P;
	}
	return ans;
}
struct _NTT {
	LL wn[25],P;
	inline void init(LL _P) {
		P=_P;
		for(LL i=1;i<=21;++i) {	  
			LL t=1<<i;	  
			wn[i]=pow(G,(P-1)/t,P);	  
		}
	}
	inline void change(LL *y,LL len) {
		for(LL i=1,j=len/2;i<len-1;++i) {	  
			if(i<j) swap(y[i],y[j]);	  
			LL k=len/2;	  
			while(j >= k) {	  
				j -= k;	  
				k /= 2;	  
			}	  
			j += k;	  
		} 
	}
	inline void NTT(LL *y,LL len,LL on) {
		change(y,len);	  
		LL id=0;
		for(LL h=2;h<=len;h<<=1) {	  
			++id;
			for(LL j=0;j<len;j+=h) {	  
				LL w=1;
				for(LL k=j;k<j+h/2;++k) {
					LL u=y[k];
					LL t=1LL*y[k+h/2]*w%P;	 
					y[k]=u+t;
					if(y[k]>=P) y[k]-=P;
					y[k+h/2]=u-t+P;
					if(y[k+h/2]>=P) y[k+h/2]-=P; 
					w=1LL*w*wn[id]%P;
				}
			}
		}
		if(on==-1) {
			for(LL i=1;i<len/2;++i) swap(y[i],y[len-i]);
			LL inv=pow(len,P-2,P);
			for(LL i=0;i<len;++i) y[i]=1LL*y[i]*inv%P;
		}
	}
	inline void mul(LL A[],LL B[],LL len) {
		NTT(A,len,1);
		NTT(B,len,1);
		for(LL i=0;i<len;++i) A[i]=1LL*A[i]*B[i]%P;
		NTT(A,len,-1);
	}
}ntt[K];
LL tmp[MAXN<<2][K],t1[MAXN<<2],t2[MAXN<<2];
LL r[K][K];
inline LL CRT(LL a[]) {
	LL x[K];
	for(LL i=0;i<K;++i) {
		x[i]=a[i];
		for(LL j=0;j<i;++j) {
			LL t=(x[i]-x[j])%m[i];
			if(t<0) t+=m[i];
			x[i]=1LL*t*r[j][i]%m[i];
		}
	}
	LL mul=1,ans=x[0]%Mo;
	for(LL i=1;i<K;++i) {
		mul=1LL*mul*m[i-1]%Mo;
		ans+=1LL*x[i]*mul%Mo;
		if(ans>=Mo) ans-=Mo;
	}
	return ans;
}
inline void mul(LL A[],LL B[],LL len) {
	for(LL id=0;id<K;++id) {
		for(LL i=0;i<len;++i) {
			t1[i]=A[i];
			t2[i]=B[i];
		}
		ntt[id].mul(t1,t2,len);
		for(LL i=0;i<len;++i) tmp[i][id]=t1[i];
	}
	for(LL i=0;i<len;++i) A[i]=CRT(tmp[i]);
}
inline void init() {
	for(LL i=0;i<K;++i)
		for(LL j=0;j<i;++j) r[j][i]=pow(m[j],m[i]-2,m[i]);
	for(LL i=0;i<K;++i) ntt[i].init(m[i]);
}
inline int main() {
	LL i,j,k;
	n=read(); init();
	for (i=1;i<=n;++i) a[i]=i;//a[i]=read();
	memset(g,0,sizeof(g));
	for (lx=1;lx<n*2;lx<<=1); //printf("lx:%d\n",lx);
	for (i=1,ll[0]=1;i<=n;++i) ll[i]=1LL*ll[i-1]*i%Mo;
	for (i=n,rr[n]=pow(ll[n],Mo-2,Mo);i;--i) rr[i-1]=1LL*rr[i]*i%Mo;
	//for (i=1;i<=n;++i) cout<<ll[i]<<' '<<rr[i]<<endl;
	update(0,1,1);
	for (i=1,ans=0;i<=n;++i) {
		//for (k=0;k<=n;++k) printf("%lld ",sum(k,a[i])); printf("sum\n");
		for (k=0;k<=lx;++k) b[k]=c[k]=0;
		for (k=0;k<=n;++k) b[k]=sum(k,a[i]);
		for (k=1,c[0]=0;k<=n;++k) c[k]=rr[k];
		//printf("sb: %lld\n",i);
		//for (k=0;k<lx;++k) printf("%lld ",b[k]); printf("B\n");
		//for (k=0;k<lx;++k) printf("%lld ",c[k]); printf("C\n");
		mul(b,c,lx);
		//for (k=0;k<lx*2;++k) printf("%lld ",b[k]); printf("ans\n");
		for (k=1;k<=n;++k) update(k,a[i]+1,b[k]);
		add(ans,1LL*b[n]*ll[n]%Mo);
	}
	ans=(ans%Mo+Mo)%Mo;
	cout<<ans<<endl;
	//for (i=1;i<=n;++i) {
	//	for (j=1;j<=n;++j) printf("%lld ",f[i][j]);
	//	printf("\n");
	//}
	cout<<pow(n,n,Mo)<<endl;
}

/*
7
1 2 3 4 5 6 7

*/