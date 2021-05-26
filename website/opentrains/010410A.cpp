#include <bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for (LL i=(a);i<=(b);++i)
#define ROF(i,b,a) for (LL i=(b);i>=(a);--i)
typedef long long LL;
LL read(){
	LL x=0,f=1; char ch=getchar();
	while (ch<'0'||ch>'9') { if (ch=='-') f=-1; ch=getchar(); }
	while (ch>='0'&&ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	return x*f;
}

const LL MAXN=400005;
LL sz,rt,mx[MAXN*50],f[MAXN*50],l[MAXN*50],r[MAXN*50];
void write(LL x){
	printf("node %lld:(%lld,%lld) (l=%lld,r=%lld)\n",x,mx[x],f[x],l[x],r[x]);
	if (l[x]) write(l[x]);
	if (r[x]) write(r[x]);
}
void update(LL &x,LL ll,LL rr,LL L,LL R,LL v){
	if (x==0) { x=++sz; f[x]=l[x]=r[x]=mx[x]=0; }
	if (L<=ll&&rr<=R) { f[x]+=v; mx[x]+=v; return; }
	LL mid=(ll+rr)/2;
	if (f[x]!=0) {
		update(l[x],ll,   mid,ll,   mid,f[x]);
		update(r[x],mid+1,rr, mid+1,rr, f[x]);
		f[x]=0;
	}
	if (L<=mid) update(l[x],ll,   mid,L,R,v);
	if (R>mid)  update(r[x],mid+1,rr, L,R,v);
	mx[x]=max(mx[l[x]],mx[r[x]]);
	//printf("add %lld %lld %lld; id=%lld[%lld,%lld]:delta=%lld,max=%lld (l=%lld,r=%lld)\n",L,R,v,x,ll,rr,f[x],mx[x],l[x],r[x]);
}
LL n,m,q,L,R,a[MAXN],b[MAXN],c[MAXN],d[MAXN],x[MAXN];
LL cmp(LL i,LL j){ return b[i]<b[j]; }
int main() {
	sz=rt=0; mx[0]=l[0]=r[0]=f[0]=0;
	n=read(); L=read(); R=read();
	LL lx=3000000000ll;
	FOR(i,1,n) a[i]=read()+lx,b[i]=read()+lx,c[i]=read(),d[i]=i;
	sort(d+1,d+1+n,cmp);
	FOR(i,1,n) x[i]=b[i],x[i+n]=b[i]-(R-L),x[i+n*2]=b[i]-(L+R),x[i+n*3]=b[i]-(R+R);
	sort(x+1,x+1+n*4);
	LL l1=1,l2=0,l3=1,l4=0;
	LL ans=0;
	lx=4000000000ll;
	FOR(i,1,n*4) {
		while (l4<n&&b[d[l4+1]]<=x[i]+R+R)
			l4++,update(rt,0,lx,a[d[l4]]-R-R,a[d[l4]],c[d[l4]]);
		while (l3<=l4&&b[d[l3]]<x[i]+R+L)
			update(rt,0,lx,a[d[l3]]-R-L+1,a[d[l3]]-R+L-1,-c[d[l3]]),l3++;
		while (l2<l3-1&&b[d[l2+1]]<=x[i]+R-L)
			l2++,update(rt,0,lx,a[d[l2]]-R-L+1,a[d[l2]]-R+L-1,c[d[l2]]);
		while (l1<=l2&&b[d[l1]]<x[i])
			update(rt,0,lx,a[d[l1]]-R-R,a[d[l1]],-c[d[l1]]),l1++;
		ans=max(ans,mx[rt]);
		//FOR(k,1,40) printf("-");
		//printf("\ni=%lld,l1=%lld,l2=%lld,l3=%lld,l4=%lld;ans=%lld\n",i,l1,l2,l3,l4,ans);
		//if (rt) write(rt); else printf("empty\n");
	}
	printf("%lld\n",ans);
	
	return 0;
}

/*
9 5 8
0 -4 3
-6 -10 -7
1 8 -6
-10 -4 8
5 -2 -7
5 3 -8
-1 -4 -1
3 -5 5
-8 1 -2

*/

