#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN=500005;
char ch[MAXN],ans[MAXN];
int ss,rodd,reven,last;
int next[MAXN][2],fail[MAXN],len[MAXN];
void prepare() {
	memset(next,0,sizeof(next));
	memset(fail,0,sizeof(fail));
	for (i=0;i<=MAXN;i++) len[i]=-2;
	rodd=1; len[1]=-1; fail[1]=1; 
	reven=2; len[2]=0; fail[2]=1; last=1; ss=2;
}
bool check(int x,int id,int chr) { return ch[id-1-len[x]]-'a'==chr; }
void add(int &last,int chr,int id) {
	for (;!check(last,id,chr);last=fail[last]) ;
	if (next[last][chr]) last=next[last][chr];
	else {
		int x=last;
		next[x][chr]=++ss; len[ss]=len[x]+2;
		if (x==rodd) fail[ss]=reven;
		else {
			x=fail[x];
			for (;x!=rodd&&(!next[x][chr]||!check(x,id,chr));x=fail[x]);
			if (next[x][chr]&&check(x,id,chr)) fail[ss]=next[x][chr];
			else fail[ss]=rodd;
		}
		last=ss;
	}
}
int main() {
	int len,tmp,i;
	gets(ch+1); len=strlen(ch+1); prepare(); 
	for (i=1;i<=len;i++) {
		tmp=ss; add(last,ch[i]-'a',i);
		if (tmp!=ss) ans[i]='1'; else ans[i]='0';
	}
	ans[len+1]='\0'; puts(ans+1);
	return 0;
}
