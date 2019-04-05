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

const int MAXN=2000006;
int n,m,q,a[1003][1003],b[1003][1003],f[1003],g[1003],x[1003],y[1003];
int main(){
    n=read(); m=read();
    FOR(i,1,n)
        FOR(j,1,m) {
            char ch=getchar();
            while (ch!='X'&&ch!='O') ch=getchar();
            a[i][j]=(ch=='X'?1:0);
        }
    memset(f,0,sizeof(f));
    memset(g,0,sizeof(g));
    FOR(i,1,n)
        FOR(j,1,m) {
            char ch=getchar();
            while (ch!='X'&&ch!='O') ch=getchar();
            b[i][j]=(ch=='X'?1:0);
            if (b[i][j]) f[i]++,g[j]++;
        }
    memset(x,0,sizeof(x));
    memset(y,0,sizeof(y));
    FOR(i,1,n)
        FOR(j,1,m)
        if ((f[i]>=2||g[j]>=2)&&b[i][j]) x[i]=1,y[j]=1;
    bool flag=1;
    FOR(i,1,n)
        FOR(j,1,m)
        if (a[i][j]!=b[i][j]) flag=0;
    if (flag) { puts("1"); return 0; }
    flag=1;
    //FOR(i,1,n) if (x[i]) cerr<<"x:"<<i<<endl;
    //FOR(i,1,m) if (y[i]) cerr<<"y:"<<i<<endl;
    FOR(i,1,n)
        FOR(j,1,m)
        if (x[i]&&y[j]&&a[i][j]!=b[i][j]) flag=0;
    if (!flag) { puts("0"); return 0; }
    flag=0;
    FOR(i,1,n)
        FOR(j,1,m)
        if (!x[i]&&!y[j]&&a[i][j]==0) flag=1;
    if (flag) {
        flag=0;
        FOR(i,1,n)
            FOR(j,1,m)
            if (!x[i]&&!y[j]&&b[i][j]==1) flag=1;
    }
    printf("%d\n",flag);
    return 0;
}

/*
4 2
XO
OX
XO
OX
OX
OO
XO
OO

 */

