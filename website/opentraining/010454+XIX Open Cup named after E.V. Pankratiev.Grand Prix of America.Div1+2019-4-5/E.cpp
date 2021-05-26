#include <bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for (int i=(a);i<=(b);++i)
#define ROF(i,a,b) for (int i=(b);i>=(a);--i)
typedef long long ll;
inline int read(){
    int x=0,f=1; char ch=getchar();
    while (!isdigit(ch)) { if (ch=='-') f=-1; ch=getchar(); }
    while (isdigit(ch)) { x=x*10+ch-'0'; ch=getchar(); }
    return x*f;
}

const int MAXN=2000000,lx=(1<<20);
ll ans;
int n,m,q,a[21][21],b[MAXN][21],h[21],g[21][21],f[21][MAXN];
void dfs(int x,int y,int z){
    //cerr<<"x="<<x<<"y="<<y<<"z="<<z<<endl;

    if (b[x][y]) return; else b[x][y]=1;
    if (z) {
        int num=n;
        FOR(i,1,n) if (abs(h[i])!=z-1) num--;
        //cerr<<"num="<<num<<endl;
        if (!num) return;
    }
    if (y==m) {
        if (z==0) return;
        FOR(i,1,n)
        if (abs(h[i])==z-1) {
            f[i][lx]=1;
            FOR(j,1,i-1)
            if (abs(h[j])==z-1) {
                if (f[j][g[j][i]]) f[i][g[j][i]]+=f[j][g[j][i]];
                if (f[j][lx]) f[i][g[j][i]]+=f[j][lx];
            }
        }
        FOR(i,1,n)
        if (abs(h[i])==z-1) {
            ans+=f[i][lx];
            f[i][lx]=0;
            FOR(j,1,i-1)
            if (abs(h[j])==z-1) {
                ans+=f[i][g[j][i]];
                f[i][g[j][i]]=0;
            }
        }
        //FOR(i,1,n) if (abs(h[i])==z-1) cerr<<i<<endl;
        //FOR(i,1,n)
        //    FOR(j,i+1,n) cerr<<i<<' '<<j<<' '<<g[i][j]<<endl;
        //cerr<<"ans="<<ans<<endl;
        return;
    }
    
    dfs(x,y+1,z);
    FOR(i,1,n-1)
        FOR(j,i+1,n)
        if (a[i][y+1]<a[j][y+1]) g[i][j]+=(1<<y);
    int X=(x+(1<<y)),Y=y-1;
    while (Y>=0&&!((x>>Y)&1)) Y--;
    if (Y>=0) {
        FOR(i,1,n) if (a[i][Y+1]<a[i][y+1]) h[i]++; else h[i]--;
    }
    dfs(X,y+1,z+1);
    FOR(i,1,n-1)
        FOR(j,i+1,n)
        if (a[i][y+1]<a[j][y+1]) g[i][j]-=(1<<y);
    if (Y>=0) {
        FOR(i,1,n) if (a[i][Y+1]<a[i][y+1]) h[i]--; else h[i]++;
    }
}
int main(){
    while (scanf("%d%d",&n,&m)!=EOF) {
    FOR(i,1,n)
        FOR(j,1,m) a[i][j]=read();
    memset(b,0,sizeof(b));
    memset(g,0,sizeof(g));
    memset(f,0,sizeof(f));
    ans=0; dfs(0,0,0);
    cout<<ans<<endl;
    }
    return 0;
}

/*
3 3
1 2 5
7 6 4
9 8 3

 */

