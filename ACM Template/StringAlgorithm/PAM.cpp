namespace PAM{
	static const int H=26;
	int last,Slen,size;
	int nt[MAXN][H],fl[MAXN],cnt[MAXN],num[MAXN],len[MAXN],S[MAXN];
	int newnode(int l){
		for (int i=0;i<H;++i) nt[size][i]=0;
		cnt[size]=num[size]=0,len[size]=l;
		return size++;
	}
	void init(){
		size=last=Slen=0;
		newnode(0),newnode(-1);
		S[Slen]=-1,fl[0]=1;
	}
	int getFail(int x){
		while (S[Slen-len[x]-1]!=S[Slen]) x=fl[x];
		return x;
	}
	int add(int c){
		S[++Slen]=(c-='a');
		int cur=getFail(last),ret=0;
		if (!nt[cur][c]) {
			int now=newnode(len[cur]+2);
			fl[now]=nt[getFail(fl[cur])][c],nt[cur][c]=now;
			num[now]=num[fl[now]]+1,ret=1;
		}
		last=nt[cur][c],cnt[last]++;
		return ret;
	}
	void count(){
		for (int i=size-1;i>=0;--i) cnt[fl[i]]+=cnt[i];
	}
};
