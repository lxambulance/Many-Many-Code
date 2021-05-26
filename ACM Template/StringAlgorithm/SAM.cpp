namespace SAM{
	struct Node{
		int next[26],fail,len;
		void init(){ fail=-1; len=0; memset(next,-1,sizeof(next)); }
	}x[MAXN<<1];
	int size,last;
	void init(){ size=last=0; x[size++].init(); }
	int newnode(){ x[size].init(); return size++; }
	void add(int c){
		int p=newnode(),tmp=last;
		x[p].len=x[last].len+1;
		for (;~tmp&&!~x[tmp].next[c];tmp=x[tmp].fail) x[tmp].next[c]=p;
		if (!~tmp) x[p].fail=0;
		else {
			int q=x[tmp].next[c];
			if (x[tmp].len+1==x[q].len) x[p].fail=q;
			else {
				int np=newnode();
				x[np]=x[q]; x[np].len=x[tmp].len+1; x[p].fail=x[q].fail=np;
				for (;~tmp&&x[tmp].next[c]==q;tmp=x[tmp].fail) x[tmp].next[c]=np;
			}
		}
		last=p;
	}
	int walk(char s[]){
		int n=strlen(s+1),now=0,len=0,ans=0;
		FOR(i,1,n) {
			for (;~now&&!~x[now].next[s[i]-'a'];now=x[now].fail);
			if (!~now) len=now=0;
			else len=min(len,x[now].len)+1,now=x[now].next[s[i]-'a'];
			ans=max(ans,len);
		}
		return ans;
	}
};
//parent树上的操作首先考虑能否转成topo序下的DP，不行再考虑dfs搜索
