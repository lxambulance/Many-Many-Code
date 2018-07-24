#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
const int N=10000005;
char s[N];
int n,m;

struct SAM {
	struct Node {
		int next[5],fail,len;
		void init() { fail=-1; len=0; memset(next,0xff,sizeof(next)); }
	}x[N<<1];
	int size,last;
	void init() { size=last=0; x[size++].init(); }
	int newnode() { x[size].init(); return size++; }
	void add(int c) {
		int end=newnode(),tmp=last;
		x[end].len=x[last].len+1;
		for (;tmp!=-1&&x[tmp].next[c]==-1;tmp=x[tmp].fail) { x[tmp].next[c]=end; }
		if (tmp==-1) x[end].fail=0;
		else {
			int nxt=x[tmp].next[c];
			if (x[tmp].len+1==x[nxt].len) x[end].fail=nxt;
			else {
				int np=newnode();
				x[np]=x[nxt]; x[np].len=x[tmp].len+1; x[end].fail=x[nxt].fail=np;
				for (;tmp!=-1&&x[tmp].next[c]==nxt;tmp=x[tmp].fail) { x[tmp].next[c]=np; }
			}
		}
		last=end;
	}
}sam;
int ff(char ch) {
	if (ch=='S') return 0;
	if (ch=='N') return 1;
	if (ch=='W') return 2;
	if (ch=='E') return 3;
}
int main() {
	int i,j,k,len;
	scanf("%d%d",&n,&m); sam.init();
	scanf("%s",s); len=strlen(s);
	for (i=0;i<len;++i) sam.add(ff(s[i]));
	for (i=0;i<m;++i) {
		scanf("%s",s); k=0;
		for (j=0;j<strlen(s);++j) {
			if (sam.x[k].next[ff(s[j])]==-1) break;
			k=sam.x[k].next[ff(s[j])];
		}
		printf("%d\n",j);
	}
	return 0;
}
