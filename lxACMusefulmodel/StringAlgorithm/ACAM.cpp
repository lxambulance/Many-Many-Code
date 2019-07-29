struct Trie{
	int size,root,nt[MAXN][26],fl[MAXN],ed[MAXN],g[MAXN];
	// g数组用于加速fail指针跳跃，快速定位到最近的终结点
	void clear(){
		size=root=0;
		memset(nt,-1,sizeof(nt));
		memset(ed,0,sizeof(ed));
	}
	void insert(char s[],int id){
		int len=strlen(s+1),now=root;
		FOR(i,1,len) {
			if (!~nt[now][s[i]-'a']) nt[now][s[i]-'a']=++size;
			now=nt[now][s[i]-'a'];
		}
		ed[now]=id;
	}
	void build(){
		queue<int> Q;
		FOR(k,0,25)
		if (!~nt[root][k]) nt[root][k]=root;
		else fl[nt[root][k]]=root,g[nt[root][k]]=root,Q.push(nt[root][k]);
		while (!Q.empty()) {
			int x=Q.front(); Q.pop();
			FOR(k,0,25) {
				if (!~nt[x][k]) nt[x][k]=nt[fl[x]][k];
				else {
					fl[nt[x][k]]=nt[fl[x]][k],Q.push(nt[x][k]);
					if (ed[nt[fl[x]][k]]) g[nt[x][k]]=nt[fl[x]][k];
					else g[nt[x][k]]=g[nt[fl[x]][k]];
				}
			}
		}
	}
	void query(char s[]){
		int len=strlen(s+1),now=root;
		FOR(i,1,len) {
			now=nt[now][s[i]-'a'];
			int tmp=now;
			while (tmp!=root) {
				//...
				tmp=fl[tmp];
			}
		}
	}
}AC;