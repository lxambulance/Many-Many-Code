#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
inline int read() {
	int s=1,x=0; char ch=getchar();
	while (ch<'0'||ch>'9') { if (ch=='-') s=-1; ch=getchar(); }
	while (ch>='0'&&ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	return s*x;
}

int n,m,next[10005];
char s[10005];
inline void KMP() {
	int i,j;
	for (i=2,j=0,next[1]=0;i<=n;++i) {
		while (j>0&&s[i]!=s[j+1]) j=next[j];
		if (s[i]==s[j+1]) j++;
		next[i]=j;
	}
}
int main() {
	int i,j,k;
	scanf("%s",s+1); n=strlen(s+1); KMP();
	for (i=1;i<=n;++i) printf("%d ",next[i]); printf("\n");
	
	return 0;
}

/*
aaaa

*/

