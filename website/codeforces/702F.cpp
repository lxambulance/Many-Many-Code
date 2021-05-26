#include <bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for (int i=(a);i<=(b);++i)
#define ROF(i,b,a) for (int i=(b);i>=(a);--i)
typedef long long LL;
inline int read(){
	int x=0,f=1; char ch=getchar();
	while (ch<'0'||ch>'9') { if (ch=='-') f=-1; ch=getchar(); }
	while (ch>='0'&&ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	return x*f;
}

const int MAXN=300005;
int rd(){ return rand()<<16|rand(); }
struct TreapNode{
	int key,val,ads,l,r,f1,f2;
	TreapNode(int v=0,int a=0):key(rd()),val(v),ads(a){ l=r=f1=f2=0; }
}tr[MAXN];
typedef TreapNode TN;
int rt,sz,p,q[MAXN],ans[MAXN],tot,pool[MAXN];
void pushdown(int x){
	if (!tr[x].f1&&!tr[x].f2) return;
	int l=tr[x].l,r=tr[x].r;
	if (l) {
		tr[l].val-=tr[x].f1,tr[l].f1+=tr[x].f1;
		ans[tr[l].ads]+=tr[x].f2,tr[l].f2+=tr[x].f2;
	}
	if (r) {
		tr[r].val-=tr[x].f1,tr[r].f1+=tr[x].f1;
		ans[tr[r].ads]+=tr[x].f2,tr[r].f2+=tr[x].f2;
	}
	tr[x].f1=tr[x].f2=0;
}
void build(int &rt,int a[],int b[],int n){
	int now,last; p=rt=0;
	FOR(i,1,n) {
		tr[now=++sz]=TN(a[b[i]],b[i]); last=0;
		while (p&&tr[now].key>tr[q[p]].key) last=q[p--];
		if (p) tr[q[p]].r=now;
		tr[q[++p]=now].l=last;
	}
	last=now;
	while (p) last=q[p--];
	rt=last;
}
void split(int now,int &A,int &B,int k){
	if (!now) { A=B=0; return; }
	pushdown(now); //printf("lxsb--------%d %d %d %d\n",now,A,B,k);
	if (tr[now].val<k) A=now,split(tr[now].r,tr[A].r,B,k);
	else B=now,split(tr[now].l,A,tr[B].l,k);
}
void merge(int &now,int A,int B){
	if (!A||!B) { now=A+B; return; }
	if (tr[A].key>tr[B].key) pushdown(now=A),merge(tr[now].r,tr[A].r,B);
	else pushdown(now=B),merge(tr[now].l,A,tr[B].l);
}
int findR(int now){
	while (tr[now].r) pushdown(now),now=tr[now].r;
	return now;
}
int n,m,l,a[MAXN],b[MAXN],c[MAXN],f[MAXN],g[MAXN];
int cmp(int i,int j){ return b[i]>b[j]||b[i]==b[j]&&a[i]<a[j]; }
int mmp(int i,int j){ return f[i]<f[j]; }
void dfs(int now){
	if (!now) return;
	++l,f[l]=tr[now].val,g[l]=tr[now].ads;
	pool[++tot]=now; pushdown(now);
	dfs(tr[now].l); dfs(tr[now].r);
}
int main(){
	int *lx=new int[5];
	srand((unsigned long long)lx);
	delete[] lx;
	
	n=read();
	FOR(i,1,n) a[i]=read(),b[i]=read(),c[i]=i;
	sort(c+1,c+1+n,cmp);
	m=read();
	FOR(i,1,m) f[i]=read(),g[i]=i;
	rt=sz=tot=tr[0].l=tr[0].r=0;
	sort(g+1,g+1+m,mmp); build(rt,f,g,m);
	//FOR(i,1,sz) printf("ID:%d (l:%d r:%d) val:%d ads:%d\n",i,tr[i].l,tr[i].r,tr[i].val,tr[i].ads);
	FOR(i,1,m) ans[i]=0;
	FOR(k,1,n) {
		int i=c[k],r1,r2,r3,Max;
		split(rt,r1,r2,a[i]);
		tr[r2].val-=a[i],tr[r2].f1+=a[i];
		ans[tr[r2].ads]++,tr[r2].f2++;
		Max=findR(r1);
		if (Max) Max=tr[Max].val;
		split(r2,r2,r3,Max);
		//printf("%d %d %d a[i]=%d Max=%d\n",r1,r2,r3,a[i],Max);
		l=0,dfs(r2);
		FOR(j,1,l) {
			int r4,r5,now=pool[tot--];
			tr[now]=TN(f[j],g[j]); split(r1,r4,r5,f[j]);
			merge(r1,r4,now); merge(r1,r1,r5);
		}
		merge(rt,r1,r3);
	}
	l=0,dfs(rt);
	FOR(i,1,m) printf("%d%c",ans[i]," \n"[i==m]);
	
	return 0;
}

/*
*/
