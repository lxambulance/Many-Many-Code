# 其他模板

lxambulance

---

[TOC]

### random

```C++
#include <chrono>//计时头文件
#include <random>
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
mt19937 rng((uint64_t) new char);
mt19937_64 rng64((uint64_t) new char);
shuffle(permutation.begin(), permutation.end(), rng);
int R=uniform_int_distribution<int>(0, i)(rng); //闭区间
```

### MillerRabinPrimeTest

```C++
ll qmul(ll a,ll b,ll c) {
	ll ans=0;
	while (b) {
		if (b&1) {
			ans+=a;
			if (ans>=c) ans-=c;
		}
		a<<=1; b>>=1;
		if (a>=c) a-=c;
	}
	return ans;
}
ll qpow(ll a,ll b,ll c) {
	ll ans=1; a%=c;
	while (b) {
		if (b&1) ans=qmul(ans,a,c);
		a=qmul(a,a,c); b>>=1;
	}
	return ans;
}
//{2,7,61};//4759123141=4e9
//{2,2570940,880937,610386380,4130785767};//341550071728321=3e15
//{2,325,9375,28178,450755,9780504,1795265022};//2^64
int pri[]={2,7,61};//4759123141=4e9
bool Miller_Rabin_test(ll n) {
	if (n==2) return true;
	if (n<2||!(n&1)) return false;
	ll k=0,m=n-1;
	while (!(m&1)) m>>=1,k++;
	FOR(i,0,2) {
		if (pri[i]>=n) return true;
		ll x=qpow(pri[i],m,n);
		if (x==1) continue;
		bool flag=false;
		FOR(j,1,k) {
			if (x==n-1) { flag=true; break; }
			x=qmul(x,x,n);
		}
		if (!flag) return false;
	}
	return true;
}
```

### PollardRho

```C++
ll gcd(ll a,ll b){ return b==0?a:gcd(b,a%b); }
ll pollard_rho(ll x,int c){
    ll y=(rand()<<16|rand())%x,z=y;
	ll i=1,j=2;
    while (1) {
		i++;
		z=(qmul(z,z,x)+c)%x;
		ll p=gcd(x,abs(z-y));
		if (p!=1&&p!=x) return p;
		if (z==y) return x;
		if (i==j) j<<=1,y=z;
	}
}
vector<ll> ans;
void factorFind(ll x,int c){
    if (x==1) return;
    if (isprime(x)) { ans.push_back(x); return; }
    ll p=x,k=c;
    while (p>=x) p=pollard_rho(p,c--);
    factorFind(p,k); factorFind(x/p,k);
}
void solve(ll x){
    ans.clear();
    factorFind(x,110);
    sort(ans.begin(),ans.end());
    int tot=ans.size();
    for (int i=0;i<tot;++i) {
        printf("%lld ",ans[i]);
        if (i+1<tot) printf("* "); else printf("= ");
    }
    printf("%lld\n",x);
}
```

### exGCD

```C++
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
```

### CRT

```C++
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
```

### Treap

```C++
mt19937 rng((unsigned long long) new char);
struct Treap{
    int val,key; //分别表示值和堆值
	int sz; //子树大小
    int ch[2]; //0是左二子，1是右儿子
}T[MAXN];
int root,tot;
void make_data(int &now,int value){
    T[++tot].val=value;
	T[tot].key=(int)rng();
    T[tot].sz=1;
    T[tot].ch[0]=T[tot].ch[1]=0;
    now=tot;
}
void update(int now){
    T[now].sz=T[T[now].ch[0]].sz+T[T[now].ch[1]].sz+1;
}
void merge(int &now,int s,int b){
    if(!s||!b){
        now=s+b; return;
    }
    if(T[s].key<T[b].key)
        now=s,merge(T[now].ch[1],T[s].ch[1],b);
    else
        now=b,merge(T[now].ch[0],s,T[b].ch[0]);
    update(now);
}
void split(int now,int &ltr,int &rtr,int value){
    if(!now){
        ltr=rtr=0;
        return;
    }
    if(T[now].val<=value)
        ltr=now,split(T[now].ch[1],T[ltr].ch[1],rtr,value);
    else
        rtr=now,split(T[now].ch[0],ltr,T[rtr].ch[0],value);
    update(now);
}
void ins(int value){
    int x=0,y=0,z=0;
    make_data(z,value);
    split(root,x,y,value);
    merge(x,x,z);
    merge(root,x,y);
}
void del(int value){
    int x=0,y=0,z=0;
    split(root,x,y,value);
    split(x,x,z,value-1);
    merge(z,T[z].ch[0],T[z].ch[1]);
    merge(x,x,z);merge(root,x,y);
}
void getrank(int value){
    int x=0,y=0;
    split(root,x,y,value-1);
    printf("%d\n",T[x].sz+1);
    merge(root,x,y);
}
void findKth(int now,int x){
    while (T[T[now].ch[0]].sz+1!=x) {
        if (T[T[now].ch[0]].sz>=x)
            now=T[now].ch[0];
        else
            x-=(T[T[now].ch[0]].sz+1),now=T[now].ch[1];
    }
    printf("%d\n",T[now].val);
}
void las(int value){
    int x=0,y=0;
    split(root,x,y,value-1);
    findKth(x,T[x].sz);
    merge(root,x,y);
}
void nex(int value){
    int x=0,y=0;
    split(root,x,y,value);
    findKth(y,1);
    merge(root,x,y);
}
```

### Tarjan

```C++
#include <stack>
#include <vector>
stack<int> stk;
vector<int> G[MAXN];
int tot,times,dfn[MAXN],low[MAXN],vis[MAXN];
void tarjan(int u){
	dfn[u]=low[u]=++times;
	stk.push(u); vis[u]=-1;
	for(int i=0;i<G[u].size();++i) {
		int v=G[u][i];
		if (vis[v]==0) {
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else {
			if (vis[v]==-1) low[u]=min(low[u],dfn[v]);
		}
	}
	if (dfn[u]==low[u]) {
		tot++;
		while (!stk.empty()) {
			int v=stk.top(); stk.pop();
			vis[v]=1;
			if (v==u) break;
		}
	}
}
void solve(int n){
	times=tot=0;
	for (int i=1;i<=n;++i) if (vis[i]==0) tarjan(i);
}
```

### LCT

```C++
#include <bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for (int i=(a);i<=(b);++i)
#define ROF(i,a,b) for (int i=(a);i>=(b);--i)
typedef long long ll;
inline int read(){
    int x=0,f=1;char ch=getchar();
    while (!isdigit(ch)) {if (ch=='-')f=-1;ch=getchar();}
    while (isdigit(ch)) {x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

const int MAXN=100005,Mo=51061;
bool rev[MAXN];
int n,m,x,y,z,top;
int que[MAXN],fa[MAXN],ch[MAXN][2];
int sum[MAXN],mul[MAXN],add[MAXN],v[MAXN],size[MAXN];
inline bool isroot(int x) { return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x; }
void update(int k,int m,int a){
	if (!k)return;
	v[k]=(v[k]*m+a)%Mo;
	sum[k]=(sum[k]*m+a*size[k])%Mo;
	add[k]=(add[k]*m+a)%Mo;
	mul[k]=(mul[k]*m)%Mo;
}
void pushup(int k){
	int l=ch[k][0],r=ch[k][1];
	sum[k]=(sum[l]+sum[r]+v[k])%Mo;
	size[k]=(size[l]+size[r]+1)%Mo;
}
void pushdown(int k){
	int l=ch[k][0],r=ch[k][1];
	if (rev[k]) {
        rev[k]^=1; rev[l]^=1; rev[r]^=1;
        swap(ch[k][0],ch[k][1]);
    }
	int m=mul[k],a=add[k]; mul[k]=1; add[k]=0;
	if (m!=1||a!=0) { update(l,m,a); update(r,m,a); }
}
void rotate(int x){
	int l,r,y=fa[x],z=fa[y];
	if (ch[y][0]==x) l=0; else l=1;
    r=l^1;
	if (!isroot(y)) {
        if (ch[z][0]==y) ch[z][0]=x;
        else ch[z][1]=x;
    }
	fa[x]=z; fa[y]=x; fa[ch[x][r]]=y;
	ch[y][l]=ch[x][r]; ch[x][r]=y;
    pushup(y); pushup(x);
}
void splay(int x){
	top=0; que[++top]=x;
	for (int i=x;!isroot(i);i=fa[i]) que[++top]=fa[i];
	for (int i=top;i;i--) pushdown(que[i]);
	while (!isroot(x)) {
		int y=fa[x],z=fa[y];
		if (!isroot(y)) {
            if ((ch[y][0]==x)^(ch[z][0]==y)) rotate(x);
            else rotate(y);
        }
		rotate(x);
	}
}
void access(int x){
	int tmp=0;
	while (x) {
        splay(x); ch[x][1]=tmp; pushup(x);
        tmp=x; x=fa[x];
    }
}
void makeroot(int x){ access(x); splay(x); rev[x]^=1; }
void link(int x,int y){ makeroot(x); fa[x]=y; access(x); }
//要求原树中存在x-y这条边
void cut(int x,int y){ makeroot(x); access(y); splay(y); ch[y][0]=fa[x]=0; pushup(y); }
int main(){
	int i;
	n=read(); m=read();
	for (i=1;i<=n;i++) v[i]=sum[i]=mul[i]=size[i]=1;
    for (i=1;i<n;i++) {
        int u=read(),v=read();
        link(u,v);
    }
	for (i=1;i<=m;i++) {
        char c[5];
		scanf("%s",c); x=read(); y=read();
		switch (c[0]) {
			case '+':{
                z=read();
                makeroot(x); access(y); splay(y);
                update(y,1,z); break;
            }
			case '-':{
                cut(x,y);
                x=read(); y=read(); link(x,y); break;
            }
			case '*':{
                z=read();
                makeroot(x); access(y); splay(y);
                update(y,z,0); break;
            }
			case '/':{
                makeroot(x); access(y); splay(y);
                printf("%u\n",sum[y]); break;
            }
		}
	}
	return 0;
}
```

### 折纸（easy poj1921）

```C++
...
二维几何板子
...
const int MAXN=10004;
#define mp(x,y) ((1ll*(x))<<32|(y))
map<ll,int> E;
Point p[MAXN],p1,p2;
int psize,Psize,lastp,lastP,f[MAXN];
struct Polygon{
	int pid[26],tot;
	Polygon(){ memset(pid,0,sizeof(pid)); tot=0; }
	void add(int id){ pid[++tot]=id; }
	void init(){ pid[0]=pid[tot],pid[tot+1]=pid[1]; }
	void print(){
		printf("{");
		FOR(i,1,tot) printf("%d ",pid[i]);
		printf("}\n");
	}
}P[MAXN];
void addPoint(Point p0){ p[++psize]=p0; }
int checkEdge(int id1,int id2){
	if (E.find(mp(id1,id2))!=E.end()) return E[mp(id1,id2)];
	addPoint(lineIntersect(p[id1],p[id2]-p[id1],p1,p2));
	return E[mp(id1,id2)]=E[mp(id2,id1)]=psize;
}
void init(){
	psize=0,Psize=1;
	addPoint(Point(0,0)),addPoint(Point(1,0));
	addPoint(Point(1,1)),addPoint(Point(0,1));
	P[1].tot=4;
	FOR(i,1,4) P[1].pid[i]=i;
	P[1].init();
}
int s[26];
void reflection(Polygon &P){
	FOR(i,1,P.tot) f[P.pid[i]]=1;
}
void fold(int x){
	int num1=0,num2=0;
	FOR(I,1,P[x].tot) {
		s[I]=sgn(Cross(p[P[x].pid[I]]-p1,p2));
		if (s[I]>0) num1++; else if (s[I]<0) num2++;
	}
	if (num1==0) {
		reflection(P[x]);
		FOR(i,1,P[x].tot/2) swap(P[x].pid[i],P[x].pid[P[x].tot+1-i]);
		P[x].init();
		return;
	}
	if (num2==0) return;
	Polygon P1,P2;
	FOR(I,1,P[x].tot) {
		int i=I,j=(I+1>P[x].tot?1:I+1);
		if (s[i]==0) P1.add(P[x].pid[I]),P2.add(P[x].pid[I]);
		else if (s[i]>0) {
			P1.add(P[x].pid[I]);
			if (s[j]<0) {
				int id=checkEdge(P[x].pid[I],P[x].pid[I+1]);
				P1.add(id),P2.add(id);
			}
		}
		else {
			P2.add(P[x].pid[I]);
			if (s[j]>0) {
				int id=checkEdge(P[x].pid[I],P[x].pid[I+1]);
				P1.add(id),P2.add(id);
			}
		}
	}
	reflection(P2);
	FOR(i,1,P2.tot/2) swap(P2.pid[i],P2.pid[P2.tot+1-i]);
	P1.init(),P2.init();
	P[x]=P1; P[++Psize]=P2;
}
void dfs(int x){
	f[x]=1;
	FOR(I,1,P[x].tot) {
		int i=I,j=I+1;
		if (sgn(Cross(p[P[x].pid[i]]-p1,p2))==0&&sgn(Cross(p[P[x].pid[j]]-p1,p2))==0) continue;
		FOR(y,1,Psize)
		if (!f[y]) {
			FOR(J,1,P[y].tot)
			if (P[x].pid[i]==P[y].pid[J]&&P[x].pid[j]==P[y].pid[J+1]) { dfs(y); break; }
		}
	}
}
int cut(){
	FOR(i,1,Psize) f[i]=0;
	int ans=0;
	FOR(i,1,Psize) if (!f[i]) dfs(i),ans++;
	return ans;
}
int main(){
	int T=read();
	while (T--) {
		init();
		int n=read()+1;
		while (n--) {
			scanf("%lf%lf%lf%lf",&p1.x,&p1.y,&p2.x,&p2.y);
			p2=p2-p1;
			lastP=Psize,lastp=psize;
			E.clear();
			FOR(i,1,lastp) f[i]=0;
			FOR(i,1,lastP) fold(i);
			FOR(i,1,lastp)
			if (f[i]&&sgn(Cross(p[i]-p1,p2))) {
				Point p0=Project(p[i],p1,p2);
				p[i]=p0*2-p[i];
			}
			// FOR(i,1,lastp) printf("%d%c",f[i]," \n"[i==lastp]);
			// FOR(i,1,psize) printf("p[%d]:(%.8f,%.8f)\n",i,p[i].x,p[i].y);
			// FOR(i,1,Psize) {
				// printf("Polygon[%d]:",i);
				// P[i].print();
			// }
		}
		printf("%d\n",cut());
	}
	return 0;
}

/*
4
1
0 0.5 1 1
0.5 0 0.5 1
1
0 0.5 1 1
0 0.4 1 0.4
0
0 0 1 0
1
0.30 0.10 0.00 0.90
0.70 0.70 0.50 0.40

*/
```

### 折纸（hard poj3806）

```C++
...
二维几何板子
...
const int MAXN=10004;
#define mix(x,y) ((1ll*(x))<<32|(y))
map<ll,int> E;
Point p[MAXN],p1,p2;
int psize,Psize,lastp,lastP,f[MAXN],g[MAXN],h[MAXN];
struct Polygon{
	int pid[26],tot,depth;
	Polygon(){ memset(pid,0,sizeof(pid)); depth=tot=0; }
	bool operator <(const Polygon &Q)const{ return depth<Q.depth; }
	void print(){
		printf("{");
		FOR(i,1,tot) printf("%d ",pid[i]);
		printf("}\n");
	}
	void add(int id){ pid[++tot]=id; }
	void init(){ pid[0]=pid[tot],pid[tot+1]=pid[1]; }
	int checkIn(Point O){
		FOR(i,1,tot) if (sgn(Cross(p[pid[i]],p[pid[i+1]],O))==0) return -1;
		Point OO=O+Point(INF,0);
		int num=0;
		FOR(i,1,tot) {
			int si=segIntersect(O,OO,p[pid[i]],p[pid[i+1]]);
			if (si==1) num++;
			else if (si==2) {
				if (sgn(Cross(p[pid[i]],O,OO))<0) num++;
				else if (sgn(Cross(p[pid[i+1]],O,OO))<0) num++;
			}
		}
		return (num&1);
	}
}P[MAXN];
//map<ll,int> cover;
int s[26];
int checkIntersect(int x,int y){
	//if (cover.find(mix(x,y))!=cover.end()) return cover[mix(x,y)];
	// printf("%d<--->%d\n",x,y);
	// FOR(i,1,P[x].tot) printf("%d%c",P[x].pid[i]," \n"[i==P[x].tot]);
	// FOR(i,1,P[y].tot) printf("%d%c",P[y].pid[i]," \n"[i==P[y].tot]);
	FOR(i,1,P[x].tot) {
		int num=0;
		FOR(j,1,P[y].tot)
		if (sgn(Cross(p[P[y].pid[j]],p[P[x].pid[i+1]],p[P[x].pid[i]]))>=0) num++;
		if (num==P[y].tot) return 0;//cover[mix(x,y)]=cover[mix(y,x)]=0;
	}
	swap(x,y);
	FOR(i,1,P[x].tot) {
		int num=0;
		FOR(j,1,P[y].tot)
		if (sgn(Cross(p[P[y].pid[j]],p[P[x].pid[i+1]],p[P[x].pid[i]]))>=0) num++;
		if (num==P[y].tot) return 0;//cover[mix(x,y)]=cover[mix(y,x)]=0;
	}
	return 1;//cover[mix(x,y)]=cover[mix(y,x)]=1;
}
void addPoint(Point p0){ p[++psize]=p0; }
void init(){
	psize=0,Psize=1;
	addPoint(Point(0,0)),addPoint(Point(100,0));
	addPoint(Point(100,100)),addPoint(Point(0,100));
	P[1].tot=4,P[1].depth=1;
	FOR(i,1,4) P[1].pid[i]=i;
	P[1].init();
	memset(f,0,sizeof(f));
}
int checkEdge(int id1,int id2){
	if (E.find(mix(id1,id2))!=E.end()) return E[mix(id1,id2)];
	addPoint(lineIntersect(p[id1],p[id2]-p[id1],p1,p2));
	return E[mix(id1,id2)]=E[mix(id2,id1)]=psize;
}
void cut(int x){
	int num1=0,num2=0;
	FOR(I,1,P[x].tot) {
		s[I]=sgn(Cross(p[P[x].pid[I]]-p1,p2));
		if (s[I]>0) num1++; else if (s[I]<0) num2++;
	}
	if (num1==0||num2==0) return;
	Polygon P1,P2;
	FOR(I,1,P[x].tot) {
		int i=I,j=(I+1>P[x].tot?1:I+1);
		if (s[i]==0) P1.add(P[x].pid[I]),P2.add(P[x].pid[I]);
		else if (s[i]>0) {
			P1.add(P[x].pid[I]);
			if (s[j]<0) {
				int id=checkEdge(P[x].pid[I],P[x].pid[I+1]);
				P1.add(id),P2.add(id);
			}
		}
		else {
			P2.add(P[x].pid[I]);
			if (s[j]>0) {
				int id=checkEdge(P[x].pid[I],P[x].pid[I+1]);
				P1.add(id),P2.add(id);
			}
		}
	}
	P1.init(),P2.init();
	P[x]=P1; P[++Psize]=P2;
	P[x].depth=P[Psize].depth=1;
	FOR(y,1,Psize) {
		if (y==Psize||y>=x&&y<=lastP) continue;
		if (checkIntersect(x,y)) P[x].depth=max(P[x].depth,P[y].depth+1);
		if (checkIntersect(Psize,y)) P[Psize].depth=max(P[Psize].depth,P[y].depth+1);
	}
}
void dfs(int x){
	// printf("%d st\n",x);
	FOR(i,1,P[x].tot) g[P[x].pid[i]]=1;
	f[x]=1;
	FOR(y,1,Psize)
	if (!f[y]&&P[y].depth>P[x].depth&&checkIntersect(y,x)) dfs(y);
	FOR(i,1,P[x].tot) {
		if (sgn(Cross(p[P[x].pid[i]]-p1,p2))==0&&sgn(Cross(p[P[x].pid[i+1]]-p1,p2))==0) continue;
		FOR(y,1,Psize)
		if (!f[y]) {
			FOR(j,1,P[y].tot)
			if ((P[x].pid[i]==P[y].pid[j]&&P[x].pid[i+1]==P[y].pid[j+1])
			  ||(P[x].pid[i]==P[y].pid[j+1]&&P[x].pid[i+1]==P[y].pid[j])) { dfs(y); break; }
		}
	}
	// printf("%d ed\n",x);
}
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define PII pair<int,int>
vector<PII > l;
int main(){
	int n;
	while (n=read()) {
		init();
		while (n--) {
			Point A,B;
			A.x=read(),A.y=read(),B.x=read(),B.y=read();
			p1=(A+B)/2;
			p2=Rot(B-A,PI/2);
			lastP=Psize,lastp=psize;
			E.clear(); //cover.clear();
			FOR(i,1,lastP) cut(i);
			int root=0,tmp=0;
			FOR(i,1,Psize)
			if (P[i].checkIn(A)&&tmp<P[i].depth) tmp=P[i].depth,root=i;
			FOR(i,1,Psize) f[i]=0;
			FOR(i,1,psize) g[i]=0;
			dfs(root);
			// puts("prepare");
			// printf("nowroot=%d\n",root);
			// FOR(i,1,psize) printf("%d%c",g[i]," \n"[i==psize]);
			// FOR(i,1,Psize) printf("%d%c",f[i]," \n"[i==Psize]);
			// FOR(i,1,psize) printf("p[%d]:(%.8f,%.8f)\n",i,p[i].x,p[i].y);
			// FOR(i,1,Psize) {
				// printf("Polygon[%d] depth=%d:",i,P[i].depth);
				// P[i].print();
			// }
			// puts("main");
			FOR(i,1,psize)
			if (g[i]&&sgn(Cross(p[i]-p1,p2))) {
				Point tmp=Project(p[i],p1,p2);
				p[i]=tmp*2-p[i];
			}
			// FOR(i,1,psize) printf("p[%d]:(%.8f,%.8f)\n",i,p[i].x,p[i].y);
			l.resize(0);
			FOR(i,1,Psize)
			if (f[i]) {
				l.pb(mp(P[i].depth,i));
				FOR(j,1,P[i].tot/2) swap(P[i].pid[j],P[i].pid[P[i].tot+1-j]);
				P[i].init();
			}
			sort(l.begin(),l.end());
			int top=l.size();
			//cover.clear();
			while (top--) {
				int x=l[top].se;
				// printf("%d\n",x);
				P[x].depth=1;
				FOR(i,1,Psize)
				if (!f[i]&&checkIntersect(x,i)) P[x].depth=max(P[x].depth,P[i].depth+1);
				f[x]=0;
			}
			// FOR(i,1,Psize) {
				// printf("Polygon[%d] depth=%d:",i,P[i].depth);
				// P[i].print();
			// }
			sort(P+1,P+1+Psize);
		}
		Point H; H.x=read(),H.y=read();
		int ans=0;
		FOR(i,1,Psize) if (P[i].checkIn(H)) ans++;
		printf("%d\n",ans);
	}
	return 0;
}

/*
2
90 90 80 20
80 20 75 50
50 35
2
90 90 80 20
75 50 80 20
55 20
3
5 90 15 70
95 90 85 75
20 67 20 73
20 75
3
5 90 15 70
5 10 15 55
20 67 20 73
75 80
8
1 48 1 50
10 73 10 75
31 87 31 89
91 94 91 96
63 97 62 96
63 80 61 82
39 97 41 95
62 89 62 90
41 93
5
2 1 1 1
-95 1 -96 1
-190 1 -191 1
-283 1 -284 1
-373 1 -374 1
-450 1
2
77 17 89 8
103 13 85 10
53 36
0

*/
```
