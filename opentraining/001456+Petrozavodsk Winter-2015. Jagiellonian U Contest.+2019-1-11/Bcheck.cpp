#include <bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for (int i=(a);i<=(b);++i)
#define ROF(i,b,a) for (int i=(b);i>=(a);--i)
typedef long long ll;
inline int read(){
	int x=0,f=1; char ch=getchar();
	while (ch<'0'||ch>'9') { if (ch=='-') f=-1; ch=getchar(); }
	while (ch>='0'&&ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	return x*f;
}

const int MAXN=4000006;
int n,m,q,x[36],y[36];
char a[6][6];
void up(int y){
	y%=6;
	printf("%d U 1\n",y+1);
	char tmp=a[0][y];
	FOR(i,0,4) a[i][y]=a[i+1][y];
	a[5][y]=tmp;
}
void down(int y){
	y%=6;
	printf("%d D 1\n",y+1);
	char tmp=a[5][y];
	ROF(i,4,0) a[i+1][y]=a[i][y];
	a[0][y]=tmp;
}
void left(int x){
	x%=6;
	printf("%d L 1\n",x+1);
	char tmp=a[x][0];
	FOR(i,0,4) a[x][i]=a[x][i+1];
	a[x][5]=tmp;
}
void right(int x){
	x%=6;
	printf("%d R 1\n",x+1);
	char tmp=a[x][5];
	ROF(i,4,0) a[x][i+1]=a[x][i];
	a[x][0]=tmp;
}
int main(){
	FOR(i,0,5)
		FOR(j,0,5) {
			char ch=getchar();
			while (!(ch>='a'&&ch<='z'||ch>='0'&&ch<='9')) ch=getchar();
			a[i][j]=ch;
			int b;
			if (ch>='a'&&ch<='z') b=ch-'a'; else b=ch-'0'+26;
			x[b]=i,y[b]=j;
		}
	int x,y;
	char c;
	while (1) {
		x=read();
		c=getchar();
		while (!(c=='U'||c=='D'||c=='L'||c=='R')) c=getchar();
		y=read();
		x--;
		FOR(i,1,y) {
			if (c=='U') up(x);
			if (c=='D') down(x);
			if (c=='L') left(x);
			if (c=='R') right(x);
		}
		printf("%d %c %d\n",x+1,c,y);
		FOR(i,0,5) {
			FOR(j,0,5) putchar(a[i][j]);
			putchar('\n');	
		}
	}
	return 0;
}

/*
*/

