const int MAXH=20;
void dfs(int u,int fa){
	d[u]=d[fa]+1; p[u][0]=fa;
	for (int i=1;i<MAXH;i++) p[u][i]=p[p[u][i-1]][i-1];
	int sz=edge[u].size();
	for (int i=0;i<sz;i++){
		int v=edge[u][i];
		if (v==fa) continue;
		dfs(v,u);
	}
}
int lca(int x,int y){
	if (d[x]>d[y]) swap(x,y);
	if (d[x]<d[y]) {
		int del=d[y]-d[x];
		for (int i=0;i<MAXH;i++) if(del&(1<<i)) y=p[y][i];
	}
	if (x!=y) {
		for (int i=MAXH-1;i>=0;i--) 
		if (p[x][i]!=p[y][i]) x=p[x][i],y=p[y][i];
		x=p[x][0],y=p[y][0];
	}
	return x;
}