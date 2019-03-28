#include <bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for (int i=(a);i<=(b);++i)
typedef long long ll;
inline int read(){
	int x=0,f=1; char ch=getchar();
	while (!isdigit(ch)) { if (ch=='-') f=-1; ch=getchar(); }
	while (isdigit(ch)) { x=x*10+ch-'0'; ch=getchar(); }
	return x*f;
}

const int MAXN=400005,INF=2147483647;
priority_queue<pair<int,int> >Q[MAXN];
int esize,u[MAXN];
struct edge{ int v,w,nt,fl; }e[MAXN];
void clear(){ memset(u,-1,sizeof(u)); esize=0; }
void addEdge(int i,int j,int k){ e[esize]=(edge){j,k,u[i],1}; u[i]=esize++; }
int n,m,q,c[MAXN];
int findmax(int x){
	while (!Q[x].empty()&&c[Q[x].top().second]) Q[x].pop();
	if (!Q[x].empty()) return Q[x].top().first;
	return -INF;
}
int od[MAXN],fa[MAXN],sum[MAXN],tot,que[MAXN],quew[MAXN];
void calc(int x,int y,int w){
	fa[x]=y; sum[x]=1; ++tot; que[tot]=x; quew[tot]=w;
	for (int i=u[x];~i;i=e[i].nt)
	if (e[i].fl) {
		int v=e[i].v;
		if (v!=y) calc(v,x,e[i].w),sum[x]+=sum[v],od[v]=i;
	}
}
int Stot=0,dist[25][MAXN],f[25][MAXN][2],g[25][MAXN],h[25][MAXN],ans[25][MAXN];
void calcDist(int x,int y,int z,int w,int op){
	dist[z][x]=w; h[z][x]=op;
	if (!c[x]) Q[op].push(make_pair(w,x));
	for (int i=u[x];~i;i=e[i].nt)
	if (e[i].fl) {
		int v=e[i].v;
		if (v!=y) calcDist(v,x,z,w+e[i].w,op);
	}
}
void build(int x,int z){
	if (!c[x]) ans[z][x]=0; else ans[z][x]=-INF;
	tot=0; calc(x,0,0);
	//cerr<<"now:x="<<x<<" z="<<z<<" tot="<<tot<<endl;
	if (tot==1) return;
	int rt=0,m=sum[x],w=0;
	FOR(i,2,tot) {
		int tmp=max(sum[que[i]],sum[x]-sum[que[i]]);
		if (tmp<=m) rt=que[i],m=tmp,w=quew[i];
	}
	f[z][x][0]=rt; f[z][x][1]=fa[rt]; g[z][x]=w; e[od[rt]].fl=e[od[rt]^1].fl=0;
	//cerr<<"choose node:"<<rt<<" "<<fa[rt]<<endl;
	calcDist(f[z][x][0],0,z,0,++Stot);
	calcDist(f[z][x][1],0,z,0,++Stot);
	//FOR(i,1,tot) cerr<<que[i]<<' '<<quew[i]<<' '<<dist[z][que[i]]<<endl;
	//cerr<<g[z][x]<<' '<<findmax(h[z][rt])<<' '<<findmax(h[z][fa[rt]])<<endl;
	build(f[z][x][0],z+1);
	build(f[z][x][1],z+1);
	ans[z][x]=max(ans[z][x],ans[z+1][f[z][x][0]]);
	ans[z][x]=max(ans[z][x],ans[z+1][f[z][x][1]]);
	int tmp1=findmax(h[z][f[z][x][0]]),tmp2=findmax(h[z][f[z][x][1]]);
	if (!Q[h[z][f[z][x][0]]].empty()&&!Q[h[z][f[z][x][1]]].empty())
		ans[z][x]=max(ans[z][x],tmp1+tmp2+g[z][x]);
	//cerr<<"z="<<z<<" x="<<x<<" ans="<<ans[z][x]<<endl;
}
void change(int x,int z,int k){
	if (!h[z][k]) return;
	int rt1=f[z][x][0],rt2=f[z][x][1];
	if (!c[k]) Q[h[z][k]].push(make_pair(dist[z][k],k));
	if (h[z][k]==h[z][rt1]) change(rt1,z+1,k); else change(rt2,z+1,k);
	ans[z][x]=max(ans[z+1][rt1],ans[z+1][rt2]);
	int tmp1=findmax(h[z][rt1]),tmp2=findmax(h[z][rt2]);
	if (!Q[h[z][rt1]].empty()&&!Q[h[z][rt2]].empty())
		ans[z][x]=max(ans[z][x],tmp1+tmp2+g[z][x]);
}
int nx[MAXN],ny[MAXN],nz[MAXN],ntot=0;
void dfs(int x,int y){
	int lt=0,lw=0;
	for (int i=u[x];~i;i=e[i].nt) {
		int j=e[i].v,k=e[i].w;
		if (j!=y) {
			if (!lt) lt=j,lw=k;
			else {
				c[++n]=1;
				ntot++; nx[ntot]=lt,ny[ntot]=n,nz[ntot]=lw;
				ntot++; nx[ntot]=j,ny[ntot]=n,nz[ntot]=k;
				//cerr<<n<<' '<<j<<endl<<n<<' '<<lt<<endl;
				lt=n; lw=0;
			}
			dfs(j,x);
		}
	}
	if (lt) {
		ntot++; nx[ntot]=lt,ny[ntot]=x,nz[ntot]=lw;
		//cerr<<x<<' '<<lt<<endl;
	}
}
int main(){
	n=read(); q=n; clear();
	FOR(i,2,n) {
		int x=read(),y=read(),z=read();
		addEdge(x,y,z); addEdge(y,x,z);
	}
	dfs(1,0); clear();
	FOR(i,1,ntot) addEdge(nx[i],ny[i],nz[i]),addEdge(ny[i],nx[i],nz[i]);
	build(1,0);
	//cerr<<"prepare ok!"<<endl;
	m=read();
	while (m--) {
		char s[5];
		scanf("%s",s);
		if (s[0]=='A') {
			if (q==0) puts("They have disappeared.");
			else printf("%d\n",ans[0][1]);
		}
		else {
			int x=read(); c[x]^=1; change(1,0,x);
			if (c[x]) q--; else q++;
		}
	}

	return 0;
}

/*
3
1 2 1
1 3 1
7
A
C 1
A
C 2
A
C 3
A

5
1 2 2
1 3 -4
1 4 5
1 5 5
3
A
C 3
A

5
1 2 -4
2 3 -4
1 4 -2
3 5 -2
5
A
C 2
C 3
A
A

 */
