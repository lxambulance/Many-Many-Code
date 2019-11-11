# 字符串模板

lxambulance

---

[TOC]

### 后缀自动机

```C++
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
```

### 回文自动机

```C++
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
```

#### 回文自动机+series link

cf 906E：给两个长度一样的串，求一组拆分使得两个串对应部分互为反串。

```C++
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
*/
```

### AC自动机

```C++
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
```

### KMP

```C++
inline void KMP(char s[],int f[]) {
	int i,j;
	for (i=2,j=0,f[1]=0;i<=n;++i) {
		while (j>0&&s[i]!=s[j+1]) j=f[j];
		if (s[i]==s[j+1]) j++;
		f[i]=j;
	}
}
```

### EXKMP

exkmp的用途：给定一个主串s和一个子串t，求出s中每一个后缀和子串t的最长公共前缀。

```C++
int nt[MAXN],ex[MAXN];
void exKMP(char s[],int f[]){
	int len=strlen(s+1);
	f[1]=len,f[2]=0;
	while (f[2]+2<=len&&s[f[2]+1]==s[f[2]+2]) f[2]++;
	for (int i=3,p0=2;i<=len;++i) {
		if (f[i-p0+1]+i-1<f[p0]+p0-1) f[i]=f[i-p0+1];
		else {
			int j=max(0,p0+f[p0]-i);
			while (i+j<=len&&s[i+j]==s[j+1]) j++;
			f[p0=i]=j;
		}
	}
}
void getExtend(char s[],char t[],int f[]){
	int n=strlen(s+1),m=strlen(t+1);
	f[1]=0;
	while (f[1]+1<=n&&f[1]+1<=m&&s[f[1]+1]==t[f[1]+1]) f[1]++;
	for (int i=2,p0=1;i<=m;++i) {
		if (nt[i-p0+1]+i-1<f[p0]+p0-1) f[i]=nt[i-p0+1];
		else {
			int j=max(0,p0+f[p0]-i);
			while (i+j<=m&&j+1<=n&&s[j+1]==t[i+j]) j++;
			f[p0=i]=j;
		}
	}
}
```

### 最小串表示

```C++
int minstring(char s[],int n) {
	int p1,p2,k,t;
	for (p1=1,p2=2,k=0;p1<=n&&p2<=n&&k<=n;) {
		t=s[p1+k]-s[p2+k];
		if (!t) k++;
		else {
			if (t<0) p2=p2+k+1; else p1=p1+k+1;
			if (p1==p2) p2++; 
			k=0;
		}
	}
	return min(p1,p2);
}
```

### Manacher算法

```C++
//使用前字符串需要插入‘#’，长度变为n×2+1，答案长度为对应f值减一
void Manacher(char s[],int f[]){
	int len=strlen(s+1);
	for (int i=1,mx=0,id=0;i<=len;++i) {
		if (mx>i) f[i]=min(f[id*2-i],mx-i); else f[i]=1;
		while (i-f[i]>0&&i+f[i]<=len&&s[i-f[i]]==s[i+f[i]]) ++f[i];
		if (i+f[i]>mx) mx=i+f[i],id=i;
	}
	//FOR(i,1,len) printf("%d%c",f[i]," \n"[i==len]);
}
```