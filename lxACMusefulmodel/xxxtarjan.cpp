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
