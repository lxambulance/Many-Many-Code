#include<bits/stdc++.h>

#define fast ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define ll long long
#define ull unsigned long long
#define ld long double
//#define int ll
#define mkp(x,y) make_pair(x,y)
#define pushb(x) push_back(x)
#define f first
#define s second
#define pii pair<int,int>
#define pll pair<ll,ll>
#define piii pair<pii,int>
#define writeln cout<<endl
#define endl '\n'
#define sqr(a) (a)*(a)
#define all(a) a.begin() ,a.end()

using namespace std;

const int N = 1e5 + 121;

int a[N],b[N],last[N],pa[N],pb[N],plast[N],pkol,kol,st[N],v,u,ans,i,l,r;
int usd[N],usdd[N];

inline void add()
{
    ++kol;
    a[kol]=u;
    b[kol]=last[v];
    last[v]=kol;
}

inline void padd()
{
    ++pkol;
    pa[pkol]=v;
    pb[pkol]=plast[u];
    plast[u]=pkol;
}

void dfs(int v)
{
   // cout<<i<<' '<<v<<' '<<st[l]<<endl;
    usd[v]=i;
    ++ans;
     int x = last[v];
      while(x)
      {
          if(usd[a[x]]<i) dfs(a[x]);
          x=b[x];
      }
}

 int main()
 {

    // freopen("input.txt","r",stdin);
    // freopen("output.txt","w",stdout);

    fast;

        int n,m;
     cin>>n>>m;
      for(i=1; i<=m; ++i)
      {
          cin>>v>>u;
          add();
          padd();
      }

      int answer = 0;

      for(i=1; i<=n; ++i)
      {
          st[1]=i;
        usdd[st[1]]=i;
        l=1;
        r=1;
        ans=0;
         while(l<=r)
         {
             if(usd[st[l]]<i)
           dfs(st[l]);
           int x = plast[st[l]];
             while(x)
              {
               if(usdd[pa[x]]<i)
                {
                  ++r;
                  st[r]=pa[x];
                  usdd[pa[x]]=i;
                }
                x=pb[x];
               }
               ++l;
             }
          answer+=ans;
         }

         printf("%d\n",answer);

    return 0;
 }