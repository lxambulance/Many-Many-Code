#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
inline int read() {
	int x=0,f=1; char ch=getchar();
	while (ch<'0'||ch>'9') { if (ch=='-') f=-1; ch=getchar(); }
	while (ch>='0'&&ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	return x*f;
}

const int MAXN=2000005;
struct State {
	State *par;
	State *go[26];
	int val; //max当前状态能接收的串的最长长度
	int mi;  //min当前状态能接受的串的最短长度，即 par->val+1
	int cnt,mark; //附加域，用来计数
	int right; //right集，表示当前状态可以在多少个位置上出现
	void init(int _val=0){
		par=0;
		val=_val;
		cnt=mark=0;
		mi=0;
		right=0;
		memset(go,0,sizeof(go));
	}
	int calc(){ // 表示该状态能表示多少中不同的串
		if (par==0) return 0;
		return val-par->val;
	}
};
State *root, *last, *cur;
State nodePool[MAXN];
State* newState(int val=0) {
	cur->init(val);
	return cur++;
}
//int total; // 不同的子串个数。
void initSAM() {
	//total=0;
	cur=nodePool;
	root=newState();
	last=root;
}
void extend(int w) {
	State* p=last;
	State* np=newState(p->val+1);
	np->right=1; //设置right集
	while (p && p->go[w]==0) {
		p->go[w]=np;
		p=p->par;
	}
	if (p==0) {
		np->par=root;
		//total+=np->calc();
	}
	else {
		State* q=p->go[w];
		if (p->val+1==q->val) {
			np->par=q;
			//total+=np->calc();
		}
		else {
			State* nq=newState(p->val+1);
			memcpy(nq->go, q->go, sizeof(q->go));
			//total -= q->calc();
			nq->par=q->par;
			q->par=nq;
			np->par=nq;
			//total += q->calc()+nq->calc()+np->calc();
			while (p && p->go[w]==q) {
				p->go[w]=nq;
				p=p->par;
			}
		}
	}
	last=np;
}
int d[MAXN];
State* b[MAXN];
void topo(){ //求出parent树的拓扑序
	int cnt=cur-nodePool;
	int maxVal=0;
	memset(d,0,sizeof(d));
	for (int i=1;i<cnt;i++) maxVal=max(maxVal,nodePool[i].val),d[nodePool[i].val]++;
	for (int i=1;i<=maxVal;i++) d[i]+=d[i-1];
	for (int i=1;i<cnt;i++) b[d[nodePool[i].val]--]=&nodePool[i];
	b[0]=root;
}
void workSamInit(){ //求出SAM的附加信息
	State* p;
	int cnt=cur-nodePool;
	for (int i=cnt-1;i>0;i--){
		p=b[i];
		p->par->right+=p->right;
		p->mi=p->par->val+1;
	}
}
char s[MAXN];
void work(char s[],int x){
	int ans=0;
	int cnt=cur-nodePool;
	int len=strlen(s);
	int lcs=0; //lcs表示sam和当前匹配串匹配的最长长度
	State* p=root;
	for (int i=0;i<len;i++){
		int son=s[i]-'a';
		if (p->go[son]!=0) lcs++,p=p->go[son];
		else{
			while (p&&p->go[son]==0) p=p->par;
			if (p==0) lcs=0,p=root; else { lcs=p->val+1; p=p->go[son]; }
		}
	}
	for (int i=0;i<len;i++){
		int son=s[i]-'a';
		if (p->go[son]!=0) lcs++,p=p->go[son];
		else{
			while (p&&p->go[son]==0) p=p->par;
			if (p==0) lcs=0,p=root; else { lcs=p->val+1; p=p->go[son]; }
		}
		State* q=p;
		//printf("%d %d %d\n",p->mi,p->val,lcs);
		while (q&&q->mi>len&&q->val>=len) { q->mark=x; q=q->par; }
		if (lcs>=len&&q&&q->mi<=len&&len<=q->val&&q->mark!=x) {
			q->mark=x;
			//printf("%d %d %d %d\n",q->mi,q->val,i,q->right);
			ans+=q->right;
		}
	}
	cout<<ans<<endl;
}
int main() {
	int i,n,len;
	scanf("%s",s); len=strlen(s); initSAM();
	for (i=0;i<len;++i) extend(s[i]-'a');
	topo(); workSamInit();
	n=read();
	for (i=1;i<=n;++i) {
		scanf("%s",s);
		work(s,i);
	}
	return 0;
}

/*
baabaabaaa
5
aabaa
aaba
a
ba
baa

*/
