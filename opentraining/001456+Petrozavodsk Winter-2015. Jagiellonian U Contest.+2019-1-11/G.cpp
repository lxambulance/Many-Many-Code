#include <bits/stdc++.h>
#define N 100007
using namespace std;
int T,n,e,head[N],nxt[N*2],to[N*2],c[N*2],deg[N];
long long f[N],g[N],h[N];
void dfs(int x,int par,int cap){
    int tmp=0;
    long long sum=0;
    for(int i=head[x];i;i=nxt[i]){
        int y=to[i];
        if(y==par)continue;
        dfs(y,x,c[i]);
        if(!tmp)tmp=y;
        else if(g[y]>g[tmp])tmp=y;
        sum+=g[y];
    }
    if(!tmp)f[x]=h[x]=0,g[x]=cap;
    else if(g[tmp]<=sum-g[tmp]){
        f[x]=h[x]=sum>>1,g[x]=sum&1;
        for(int i=head[x];i;i=nxt[i]){
            int y=to[i];
            if(y==par)continue;
            f[x]+=f[y],h[x]+=h[y];
        }
        h[x]=min(h[x],(cap-g[x])>>1);
    }
    else{
        f[x]=h[x]=0;
        for(int i=head[x];i;i=nxt[i]){
            int y=to[i];
            if(y==par)continue;
            f[x]+=f[y],h[x]+=h[y];
        }
        long long k=min(h[x]-h[tmp],(g[tmp]-(sum-g[tmp]))>>1);
        f[x]+=sum-g[tmp]+k;
        g[x]=min(g[tmp]-(sum-g[tmp]+k*2),1LL*cap);
        h[x]=min(h[x]+sum-g[tmp]+k,(cap-g[x])>>1);
    }
    //cout<<x<<" "<<f[x]<<" "<<g[x]<<" "<<h[x]<<endl;
}
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n),e=0;
        for(int i=1;i<=n;++i)head[i]=deg[i]=0;
        for(int i=1,x,y,z;i<n;++i){
            scanf("%d%d%d",&x,&y,&z);
            nxt[++e]=head[x],to[head[x]=e]=y,c[e]=z;
            nxt[++e]=head[y],to[head[y]=e]=x,c[e]=z;
            ++deg[x],++deg[y];
        }
        int root=0;
        for(int i=1;i<=n;++i)
            if(deg[i]>1){root=i;break;}
        if(!root){
            if(n==1)puts("0");
            else printf("%d\n",c[head[1]]);
            continue;
        }
        dfs(root,0,0);
        cout<<f[root]<<endl;
    }
}
