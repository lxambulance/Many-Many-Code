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

const int MAXN=1000006,Mo=1e9+7;
namespace PAM{
	static const int H=26;
	int last,Slen,size;
	int nt[MAXN][H],fl[MAXN],len[MAXN],S[MAXN];
	int seriesLink[MAXN],f[MAXN],g[MAXN];
	int newnode(int l){
		FOR(i,0,H-1) nt[size][i]=0;
		len[size]=l; return size++;
	}
	inline int diff(int x){ return len[x]-len[fl[x]]; }
	void init(){
		size=last=Slen=0;
		newnode(0),newnode(-1);
		S[Slen]=-1,fl[0]=1,fl[1]=1;
		f[0]=1,g[0]=g[1]=0;
	}
	int getFail(int x){
		while (S[Slen-len[x]-1]!=S[Slen]) x=fl[x];
		return x;
	}
	inline void update(int x[],int y,int z){ if (x[0]>y) x[0]=y,x[1]=z; }
	int getSum(int x){
		int y=Slen-(len[seriesLink[x]]+diff(x));
		g[x]=f[y];
		if (diff(x)==diff(fl[x])) {
			g[x]+=g[fl[x]];
			if (g[x]>=Mo) g[x]-=Mo;
		}
		return g[x];
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
		f[Slen]=0;
		int tmp=0;
		for (int now=last;len[now]>0;now=seriesLink[now]) {
			int gS=getSum(now);
			if (!(Slen&1)) {
				tmp+=gS;
				if (tmp>=Mo) tmp-=Mo;
			}
		}
		f[Slen]=tmp;
	}
	void print(){
		FOR(i,1,Slen) putchar('a'+S[i]);
		puts("");
		FOR(i,1,Slen) printf("%d%c",f[i]," \n"[i==Slen]);
		FOR(i,0,size-1) {
			printf("%d:fail[%d]=%d,len[%d]=%d\n",i,i,fl[i],i,len[i]);
			FOR(j,0,H-1)
			if (nt[i][j]) printf("(%c%d)",'a'+j,nt[i][j]);
			puts("");
		}
	}
};
int n,m;
char s[MAXN];
int main(){
	scanf("%s",s+1); n=strlen(s+1);
	PAM::init();
	FOR(i,1,n/2) PAM::add(s[i]),PAM::add(s[n+1-i]);
	//PAM::print();
	printf("%d\n",PAM::f[n]);
	
	return 0;
}

/*
abcdcdab

*/

