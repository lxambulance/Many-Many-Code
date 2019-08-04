#include<bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for (int i=(a);i<=(b);++i)
#define ROF(i,a,b) for (int i=(a);i>=(b);--i)
typedef long long ll;
inline int read(){
	int x=0,f=1; char ch=getchar();
	while (!isdigit(ch)) { if (ch=='-') f=-1; ch=getchar(); }
	while (isdigit(ch)) { x=x*10+ch-'0'; ch=getchar(); }
	return x*f;
}

const int MAXN=500005,MAXM=50004;
namespace SAM{
	struct Node{
		int next[26],fail,len;
		void init(){ fail=-1; len=0; memset(next,-1,sizeof(next)); }
	}x[MAXM<<1];
	int size,last,type[MAXM<<1],pos[MAXN],lcs[MAXN];
	void init(){ size=last=0; x[size++].init(); }
	int newnode(){ x[size].init(); return size++; }
	void add(int c,int t){
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
				type[np]=0;
			}
		}
		last=p;
		type[p]=t;
	}
	void walk(char s[]){
		int n=strlen(s+1),now=0,len=0;
		FOR(i,1,n) {
			for (;~now&&!~x[now].next[s[i]-'a'];now=x[now].fail);
			if (!~now) now=len=0;
			else len=min(len,x[now].len)+1,now=x[now].next[s[i]-'a'];
			pos[i]=now; lcs[i]=len;
			//printf("(%d,%d)%c",pos[i],lcs[i]," \n"[i==n]);
		}
	}
	void print(){
		FOR(i,0,size-1) {
			printf("node[%d]: len=%d fail=%d\n",i,x[i].len,x[i].fail);
			FOR(j,0,2) printf("%c%d%c",'a'+j,x[i].next[j]," \n"[j==2]);
		}
	}
};
char s[MAXN],t[MAXN];
int n,m,q,fa[MAXN][15];
int u[MAXM<<1],esize;
struct edge{ int v,nt; }e[MAXM<<1];
void clear(){ memset(u,-1,sizeof(u)); esize=0; }
void addEdge(int i,int j){
	//printf("%d %d\n",i,j);
	e[esize]=(edge){j,u[i]}; u[i]=esize++;
}
void dfs1(int x,int y){
	fa[x][0]=y;
	FOR(i,1,14) fa[x][i]=fa[fa[x][i-1]][i-1];
	for (int i=u[x];~i;i=e[i].nt) {
		int v=e[i].v;
		dfs1(v,x);
	}
}
pair<int,int> ans[MAXN];
struct Data{ int l,r,i; };
vector <Data> Q[MAXM<<1];
int rt[MAXM<<1],treesize;
struct treenode{ int l,r,max,x; }tr[4000005];
void treeins(int &x,int l,int r,int k){
	if (x==0) {
		x=++treesize;
		tr[x].l=tr[x].r=tr[x].max=0;
	}
	if (l==r) {
		tr[x].max++,tr[x].x=l;
		return;
	}
	int mid=(l+r)/2;
	if (k<=mid) treeins(tr[x].l,l,mid,k);
	else treeins(tr[x].r,mid+1,r,k);
	if (tr[tr[x].l].max>=tr[tr[x].r].max) tr[x].max=tr[tr[x].l].max,tr[x].x=tr[tr[x].l].x;
	else tr[x].max=tr[tr[x].r].max,tr[x].x=tr[tr[x].r].x;
}
void treemerge(int &x,int y,int l,int r){
	if (!x||!y) { x=x+y; return; }
	if (l==r) {
		tr[x].max+=tr[y].max;
		return;
	}
	int mid=(l+r)/2;
	treemerge(tr[x].l,tr[y].l,l,mid);
	treemerge(tr[x].r,tr[y].r,mid+1,r);
	if (tr[tr[x].l].max>=tr[tr[x].r].max) tr[x].max=tr[tr[x].l].max,tr[x].x=tr[tr[x].l].x;
	else tr[x].max=tr[tr[x].r].max,tr[x].x=tr[tr[x].r].x;
}
pair<int,int> treequery(int x,int l,int r,int L,int R){
	if (!x) return make_pair(0,L);
	if (L<=l&&r<=R) return make_pair(tr[x].max,tr[x].x);
	int mid=(l+r)/2;
	pair<int,int> ans1,ans2; ans1=ans2=make_pair(0,L);
	if (L<=mid) ans1=treequery(tr[x].l,l,mid,L,R);
	if (mid<R) ans2=treequery(tr[x].r,mid+1,r,L,R);
	if (ans1.first>=ans2.first) return ans1;
	return ans2;
}
void treeprint(int x,int l,int r){
	if (!x) return;
	printf("(%d,%d,%d,[%d %d])",x,tr[x].max,tr[x].x,l,r);
	if (l==r) return;
	putchar('{');
	int mid=(l+r)/2;
	treeprint(tr[x].l,l,mid);
	treeprint(tr[x].r,mid+1,r);
	putchar('}');
}
void dfs2(int x){
	rt[x]=0;
	//printf("%d type=%d\n",x,SAM::type[x]);
	if (SAM::type[x]) treeins(rt[x],1,m,SAM::type[x]);
	//treeprint(rt[x],1,m); puts("");
	for (int i=u[x];~i;i=e[i].nt) {
		int v=e[i].v;
		dfs2(v);
		treemerge(rt[x],rt[v],1,m);
		//treeprint(rt[x],1,m); puts("");
	}
	for (int i=0;i<(int)Q[x].size();++i) ans[Q[x][i].i]=treequery(rt[x],1,m,Q[x][i].l,Q[x][i].r);
}
int main(){
	scanf("%s",s+1); n=strlen(s+1);
	SAM::init();
	m=read();
	FOR(i,1,m) {
		scanf("%s",t+1); q=strlen(t+1);
		SAM::last=0;
		FOR(j,1,q) SAM::add(t[j]-'a',i);
	}
	clear();
	FOR(i,1,SAM::size-1) addEdge(SAM::x[i].fail,i);
	dfs1(0,0);
	SAM::walk(s);
	//SAM::print();
	q=read();
	FOR(i,1,q) {
		int l=read(),r=read(),pl=read(),pr=read();
		if (pr-pl+1>SAM::lcs[pr]) { ans[i]=make_pair(0,l); continue; }
		int now=SAM::pos[pr];
		ROF(k,14,0)
		if (SAM::x[fa[now][k]].len>=pr-pl+1) now=fa[now][k];
		//printf("i=%d now=%d nowlen=%d\n",i,now,SAM::x[now].len);
		if (now&&SAM::x[now].len>=pr-pl+1) Q[now].push_back((Data){l,r,i});
		else ans[i]=make_pair(0,l);
	}
	treesize=0; dfs2(0);
	FOR(i,1,q) printf("%d %d\n",ans[i].second,ans[i].first);
	
	return 0;
}

/*
suffixtree
3
suffixtreesareawesome
cartesiantreeisworsethansegmenttree
nyeeheeheee
2
1 2 1 10
1 3 9 10

cbcbbaba
6
aba
a
bbcba
b
abc
ac
1
3 5 1 7

caccc
4
bbb
abb
bccac
baacc
1
3 4 1 4

*/
