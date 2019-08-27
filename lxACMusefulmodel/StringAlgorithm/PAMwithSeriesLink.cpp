#include <bits/stdc++.h>
using namespace std;
#define PII pair<int,int>
#define mp make_pair
#define pb push_back
#define FOR(i,a,b) for (int i=(a);i<=(b);++i)
#define ROF(i,a,b) for (int i=(a);i>=(b);--i)
typedef long long ll;
inline int read(){
	int x=0,f=1; char ch=getchar();
	while (!isdigit(ch)) { if (ch=='-') f=-1; ch=getchar(); }
	while (isdigit(ch)) { x=x*10+ch-'0'; ch=getchar(); }
	return x*f;
}

const int MAXN=1000006,INF=1e9;
int flag;
vector< PII > ans;
namespace PAM{
	static const int H=26;
	int last,Slen,size;
	int nt[MAXN][H],fl[MAXN],len[MAXN],S[MAXN];
	int seriesLink[MAXN],f[MAXN][2],g[MAXN][2];
	int newnode(int l){
		FOR(i,0,H-1) nt[size][i]=0;
		len[size]=l;
		return size++;
	}
	inline int diff(int x){ return len[x]-len[fl[x]]; }
	void init(){
		size=last=Slen=0;
		newnode(0),newnode(-1);
		S[Slen]=-1,fl[0]=1,fl[1]=1;
		seriesLink[0]=1,seriesLink[1]=1;
		f[0][0]=0,g[0][0]=g[1][0]=INF;
	}
	int getFail(int x){
		while (S[Slen-len[x]-1]!=S[Slen]) x=fl[x];
		return x;
	}
	inline void update(int x[],int y,int z){ if (x[0]>y) x[0]=y,x[1]=z; }
	PII getMin(int x){
		int y=Slen-(len[seriesLink[x]]+diff(x));
		g[x][0]=f[y][0],g[x][1]=y;
		if (diff(x)==diff(fl[x])) update(g[x],g[fl[x]][0],g[fl[x]][1]);
		return mp(g[x][0]+1,g[x][1]);
	}
	void add(int c){
		S[++Slen]=(c-='a');
		int cur=getFail(last);
		if (!nt[cur][c]) {
			int now=newnode(len[cur]+2);
			fl[now]=nt[getFail(fl[cur])][c],nt[cur][c]=now;
			if (diff(now)==diff(fl[now]))
				seriesLink[now]=seriesLink[fl[now]];
			else
				seriesLink[now]=fl[now];
		}
		last=nt[cur][c];
		f[Slen][0]=INF,g[last][0]=INF;
		for (int now=last;len[now]>0;now=seriesLink[now]) {
			PII mf=getMin(now);
			if (!(Slen&1)) update(f[Slen],mf.first,mf.second);
		}
		if (Slen>1&&S[Slen]==S[Slen-1]&&!(Slen&1))
			update(f[Slen],f[Slen-2][0],Slen-2);
	}
	void print(){
		FOR(i,0,size-1) {
			printf("%d:fail[%d]=%d,len[%d]=%d\n",i,i,fl[i],i,len[i]);
			FOR(j,0,H-1)
			if (nt[i][j]) printf("(%c%d)",'a'+j,nt[i][j]);
			puts("");
		}
	}
	void work(){
		//FOR(i,1,Slen) printf("%c",S[i]+'a');
		//puts("");
		//FOR(i,1,Slen) printf("%d:%d %d\n",i,f[i][0],f[i][1]);
		flag=1;
		if (f[Slen][0]==INF) { flag=0; return; }
		int now=Slen;
		while (now>0) {
			int tmp=f[now][1];
			if (now-tmp>2) ans.pb(mp((tmp+2)/2,(now+1)/2));
			now=tmp;
		}
	}
};
int n,m,q;
char s[MAXN],t[MAXN];
int main(){
	scanf("%s%s",s+1,t+1); n=strlen(s+1);
	PAM::init();
	FOR(i,1,n) PAM::add(s[i]),PAM::add(t[i]);
	//PAM::print();
	PAM::work();
	if (!flag) { puts("-1"); return 0; }
	int tot=ans.size();
	printf("%d\n",tot);
	FOR(i,0,tot-1) printf("%d %d\n",ans[i].first,ans[i].second);
	
	return 0;
}

/*
abcxxxdef
cbaxxxfed
ccccbcabaabbcbbaaabbcbcacbcbbbccaccaaccacabacbcbac
cbcbbaaabbcbbaabacbccccaccbbbcbcaaccaaccacbcabcbca
baabbababbbaabbbabbaaabbbbbbbaabbbabaabbbbbbaaabba
abbaabbabbbabbbabaaabbabbbbbaabbbbabbbbaabbbaaabba
cf 906E
*/

