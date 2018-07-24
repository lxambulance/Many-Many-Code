const int MAXN=2400005;
struct Trie {
	int nt[MAXN][26],fl[MAXN],ed[MAXN],root,L;
	inline int newnode() { for (int i=0;i<26;i++) nt[L][i]=-1; ed[L++]=0; return L-1; }
	inline void init() { L=0; root=newnode(); }
	void insert(char c[]) {
		int len=strlen(c),now=root,i;
		for(i=0;i<len;i++) {
			if (nt[now][c[i]-'a']==-1) nt[now][c[i]-'a']=newnode();
			now=nt[now][c[i]-'a'];
		}
		ed[now]++;
	}
	inline void build() {
		queue<int>Q; fl[root]=root;
		for (int i=0;i<26;i++)
		if (nt[root][i]==-1) nt[root][i]=root;
		else { fl[nt[root][i]]=root; Q.push(nt[root][i]); }
		while (!Q.empty()) {
			int now=Q.front(),i; Q.pop();
			for (i=0;i<26;i++)
			if (nt[now][i]==-1) nt[now][i]=nt[fl[now]][i];
			else { fl[nt[now][i]]=nt[fl[now]][i]; Q.push(nt[now][i]); }
		}
	}
	int query(char c[]) {
		int len=strlen(c),now=root,res=0,i;
		for(i=0;i < len;i++){
			now=nt[now][c[i]-'a'];
			int temp=now;
			while (temp!=root) {
				res+=ed[temp]; ed[temp]=0;
				temp=fl[temp];
			}
		}
		return res;
	}
}AC;
