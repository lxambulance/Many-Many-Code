#include <cmath>
#include <queue>
#include <vector>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
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

const int MAXN=500005;
struct Data{
	int u,v,w,i;
	Data(int u=0,int v=0,int w=0,int i=0):u(u),v(v),w(w),i(i){}
	bool operator <(const Data& B)const{ return w<B.w; }
}A[MAXN];
vector<int> g[MAXN];
priority_queue<Data> p;
int n,m,q,tot,a[MAXN],b[MAXN],c[MAXN],f[MAXN],rk[MAXN],x[MAXN],y[MAXN],w[MAXN],ans[MAXN];
int cmp(int i,int j){ return a[i]<a[j]; }
int ask(int i){ if (f[i]==i) return i; return ask(f[i]); }
int main(){
	n=read(); m=read();
	FOR(i,1,m) { A[i].u=read(); A[i].v=read(); A[i].w=read(); A[i].i=i; }
	sort(A+1,A+1+m);
	FOR(i,1,m) a[A[i].i]=i;
	//FOR(i,1,m) printf("%d%c",a[i]," \n"[i==m]);
	q=read();
	FOR(i,1,q) {
		b[i]=read();
		FOR(j,1,b[i]) g[i].push_back(read());
		sort(g[i].begin(),g[i].end(),cmp); p.push(Data(0,0,-A[a[g[i][0]]].w,i));
		//FOR(j,1,b[i]) printf("%d%c",g[i][j-1]," \n"[j==b[i]]);
	}
	FOR(i,1,n) f[i]=i,rk[i]=0;
	int tag=1;
	while (!p.empty()) {
		Data z=p.top(); p.pop();
		int W=z.v,M=W,R=-z.w,I=z.i;
		//printf("work %d %d %d\n",I,W,R);
		while (tag<=m&&A[tag].w<R) {
			int fu=ask(A[tag].u),fv=ask(A[tag].v);
			if (fu!=fv) {
				if (rk[fu]>rk[fv]) f[fv]=fu;
				else {
					f[fu]=fv;
					if (rk[fu]==rk[fv]) rk[fv]++;
				}
			}
			tag++;
		}
		//printf("lx1\n");
		while (M<b[I]-1&&R==A[a[g[I][M+1]]].w) M++;
		tot=0;
		FOR(i,W,M) {
			int fu=ask(A[a[g[I][i]]].u),fv=ask(A[a[g[I][i]]].v);
			if (fu!=fv) {
				if (rk[fu]>rk[fv]) {
					++tot,x[tot]=fv,y[tot]=f[fv];
					f[fv]=fu;
				}
				else {
					++tot,x[tot]=fu,y[tot]=f[fu],w[tot]=0;
					f[fu]=fv;
					if (rk[fu]==rk[fv]) rk[fv]++,w[tot]=fv;
				}
			}
			else {
				ans[I]=1;
				break;
			}
		}
		//printf("lx2\n");
		ROF(i,tot,1) {
			f[x[i]]=y[i];
			if (w[i]) rk[w[i]]--;
		}
		if (M<b[I]-1) p.push(Data(0,M+1,-A[a[g[I][M+1]]].w,I));
	}
	FOR(i,1,q) printf("%s\n",ans[i]==1?"NO":"YES");
	
	return 0;
}

/*
5 7
1 2 2
1 3 2
2 3 1
2 4 1
3 4 1
3 5 2
4 5 2
4
2 3 4
3 3 4 5
2 7 1
2 2 1

*/
