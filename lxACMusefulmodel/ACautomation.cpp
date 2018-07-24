struct Trie{
	int size,root,nt[MAXN][26],fl[MAXN],g[MAXN],ed[MAXN];
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
		ed[now]=1; c[id]=len; M[now].push_back(id);
	}
	void build(){
		queue<int> Q;
		FOR(k,0,25)
		if (!~nt[root][k]) nt[root][k]=root;
		else fl[nt[root][k]]=root,g[nt[root][k]]=root,Q.push(nt[root][k]);
		while (!Q.empty()) {
			int x=Q.front(); Q.pop();
			FOR(k,0,25) {
				int tmp=nt[fl[x]][k];
				if (!ed[tmp]) tmp=fl[tmp];
				if (!~nt[x][k]) nt[x][k]=nt[fl[x]][k];
				else {
					fl[nt[x][k]]=nt[fl[x]][k],Q.push(nt[x][k]);
					if (ed[nt[fl[x]][k]]) g[nt[x][k]]=nt[fl[x]][k];
					else g[nt[x][k]]=g[nt[fl[x]][k]];
				}
			}
		}
		// FOR(i,0,size) {
			// printf("%d:f=%d\n",i,fl[i]);
			// for (int j=0;j<M[i].size();++j) printf("%d ",M[i][j]);
			// printf("\n");
		// }
	}
	void query(char s[]){
		int len=strlen(s+1),now=root;
		FOR(i,1,len) {
			now=nt[now][s[i]-'a'];
			int tmp=now;
			while (tmp!=root) {
				for (int k=0;k<M[tmp].size();++k) {
					int x=M[tmp][k];
					//printf("i=%d x=%d a[x]=%d c[x]=%d\n",i,x,a[x],c[x]);
					if (a[x]<=i-c[x]) b[x]++,a[x]=i;
				}
				tmp=fl[tmp];
			}
		}
	}
}AC;