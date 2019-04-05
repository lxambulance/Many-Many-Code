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
struct data{ int x,y; char c; }D[MAXN];
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
void base1(int x,int y){
	up(y);
	left(x);
	down(y);
	right(x);
}
void base1ni(int x,int y){
	left(x);
	up(y);
	right(x);
	down(y);
}
void base2(int x,int y){
	right(x);
	up(y+1);
	left(x);
	down(y+1);
}
void base2ni(int x,int y){
	up(y+1);
	right(x);
	down(y+1);
	left(x);
}
void base3(int x,int y){
	left(x+1);
	down(y);
	right(x+1);
	up(y);
}
void base3ni(int x,int y){
	down(y);
	left(x+1);
	up(y);
	right(x+1);
}
void base4(int x,int y){
	down(y+1);
	right(x+1);
	up(y+1);
	left(x+1);
}
void base4ni(int x,int y){
	right(x+1);
	down(y+1);
	left(x+1);
	up(y+1);
}
void work(int x1,int y1,int x2,int y2){
	if (x1==x2&&y1==y2) return;
	if (x1==x2) {
		FOR(i,y1,y2-1) base3ni(x1-1,i);
	}
	else {
		if (y1<y2)
			FOR(i,y1,y2-1) right(x1);
		if (y1>y2)
			ROF(i,y1,y2+1) left(x1);
		FOR(i,x1,x2-1) base2(i,(y2+5)%6);
	}
}
void op1(int x,int y){
	base2(x,y+1);
	right(x);
	base2(x,y+1);
	left(x);
	//printf("OP1\n");
}
void op2(int x,int y){
	right(x);
	base2ni(x,y+1);
	left(x);
	base2ni(x,y+1);
	//printf("OP2\n");
}
int main(){
	q=0;
	FOR(i,0,5)
		FOR(j,0,5) {
			char ch=getchar();
			while (!(ch>='a'&&ch<='z'||ch>='0'&&ch<='9')) ch=getchar();
			a[i][j]=ch;
			int b;
			if (ch>='a'&&ch<='z') b=ch-'a'; else b=ch-'0'+26;
			x[b]=i,y[b]=j;
		}
	//FOR(i,0,5) {
	//	FOR(j,0,5) putchar(a[i][j]);
	//	putchar('\n');	
	//}
	ROF(i,35,6) {
		int Y=i%6,X=i/6;
		work(x[i],y[i],X,Y);
		FOR(dx,0,5)
			FOR(dy,0,5) {
				int b;
				char ch=a[dx][dy];
				if (ch>='a'&&ch<='z') b=ch-'a'; else b=ch-'0'+26;
				x[b]=dx,y[b]=dy;
			}
	}
	ROF(i,5,2) {
		int Y=i%6,X=i/6;
		//printf("%d %d->%d\n",i,y[i],Y);
		if (Y==y[i]) continue;
		else {
			int tmpy=y[i];
			while (Y-tmpy>=2) op2(X,tmpy),tmpy+=2;
			if (Y-tmpy==1) op1(X,(tmpy+5)%6);
		}
		FOR(dx,0,5)
			FOR(dy,0,5) {
				int b;
				char ch=a[dx][dy];
				if (ch>='a'&&ch<='z') b=ch-'a'; else b=ch-'0'+26;
				x[b]=dx,y[b]=dy;
			}
	}
	if (a[0][0]!='a') {
		op1(0,0);
		op1(0,1);
		op2(0,3);
		right(0);
		op1(0,1);
	}
	
	return 0;
}

/*
bacdef
ghijkl
mnopqr
stuvwx
yz0123
456789

*/

