#include<bits/stdc++.h>
using namespace std;
const int N=200010;
vector<int>v[N];
int s[N],vis[N],ans,n,m;
void add(int x,int y){v[x].push_back(y);}
bool dfs(int x){
	if(vis[x])return 0;
	vis[x]=1;
	for(auto t:v[x]){
		if(s[t]==-1||dfs(s[t])){
			s[t]=x;s[x]=t;
			return 1;
		}
	}
	return 0;
}
int main(){
	//freopen("xxx.in","r",stdin);
	cin>>n>>m;
	for(int i=1,u,v;i<=m;i++){
		scanf("%d%d",&u,&v);
		add(u,v+n),add(v+n,u);
	}
	for(int i=1;i<=2*n;i++)s[i]=-1;
	while(1){
		for(int i=1;i<=2*n;i++)vis[i]=0;
		bool f=0;
		for(int i=1;i<=2*n;i++){
			if(s[i]==-1&&dfs(i))ans++,f=1;
		}
		if(!f)break;
	}
	cout<<n-ans-1<<endl;
	if(n-ans-1!=0){
		for(int i=1;i<=n;i++){
			if(vis[i]||vis[i+n])printf("%d ",i);
		}
		puts("");
	}
}