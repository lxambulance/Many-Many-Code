#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define FOR(i,a,b) for (int i=(a);i<=(b);++i)
#define ROF(i,b,a) for (int i=(b);i>=(a);--i)
typedef long long LL;
inline int read(){
	int x=0,f=1; char ch=getchar();
	while (ch<'0'||ch>'9') { if (ch=='-') f=-1; ch=getchar(); }
	while (ch>='0'&&ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	return x*f;
}

const int MAXN=600005;
struct SAM{
	vector<int> u[MAXN];
	int *nt[MAXN],len[MAXN],fa[MAXN],x[MAXN],y[MAXN],sz,lt;
	int newNode(int L){
		if (nt[sz]==NULL) nt[sz]=new int[26];
		FOR(i,0,25) nt[sz][i]=-1;
		len[sz]=L; x[sz]=0;
		return sz++;
	}
	void clear(){ memset(nt,0,sizeof(nt)); newNode(sz=lt=0); fa[0]=-1; }
	void extend(int ch){
		int now=newNode(len[lt]+1),p=lt; x[now]=1;
		while (~p&&!~nt[p][ch]) nt[p][ch]=now,p=fa[p];
		if (!~p) fa[now]=0;
		else {
			int q=nt[p][ch];
			if (len[p]+1==len[q]) fa[now]=q;
			else {
				int nq=newNode(len[p]+1);
				FOR(i,0,25) nt[nq][i]=nt[q][i];
				fa[nq]=fa[q]; fa[q]=fa[now]=nq;
				while (~p&&nt[p][ch]==q) nt[p][ch]=nq,p=fa[p];
			}
		}
		lt=now;
	}
	int dfs(int now){
		int num=x[now];
		for (int i=0;i<u[now].size();++i) num+=dfs(u[now][i]);
		//printf("%d %d\n",now,num);
		y[len[now]]=max(y[len[now]],num);
		return num;
	}
	void work(){
		/*FOR(i,0,sz-1) {
			printf("id=%d;fa=%d;x=%d ",i,fa[i],x[i]);
			FOR(j,0,1) printf("%d:%d%c",j,nt[i][j]," \n"[j==1]);
		}*/
		FOR(i,0,sz-1) u[i].clear(),y[i]=0;
		FOR(i,1,sz-1) u[fa[i]].pb(i);
		//FOR(i,0,sz-1) printf("%d%c",len[i]," \n"[i==sz-1]);
		dfs(0);
		//FOR(i,0,sz-1) printf("%d%c",y[i]," \n"[i==sz-1]);
		for (int i=sz-1,M=0;i>=0;--i) M=max(M,y[i]),y[i]=M;
	}
}sam;
char s[MAXN];
int n,m,q,a[MAXN],b[MAXN];
int main(){
	scanf("%s",s+1); n=strlen(s+1); sam.clear();
	FOR(i,1,n) sam.extend(s[i]-'a');
	sam.work();
	FOR(i,1,n) printf("%d\n",sam.y[i]);
	
	return 0;
}

/*
bbaabb
*/
