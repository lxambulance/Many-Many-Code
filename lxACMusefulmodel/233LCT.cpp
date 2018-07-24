#include <cstdio>
#include <string>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#define mod 51061
#define Uint unsigned int
using namespace std;
inline int read() {
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9') {if (ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9') {x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN=100005;
char c[5];
bool rev[MAXN];
int n,m,x,y,z,top;
int que[MAXN],fa[MAXN],ch[MAXN][2];
//以fa相连的边为虚边，表示原树的形态；以ch相连的边为实边，记录所有树链，深度大的在右子树上，小的在左子树
Uint sum[MAXN],mul[MAXN],add[MAXN],v[MAXN],size[MAXN];
inline bool isroot(int x) { return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x; }
//判断x节点是否为root，应为没记root而且树链组成的是森林，只能这样判，否则splay没终止条件
void update(int k,int m,int a) {
	if (!k)return;
	v[k]=(v[k]*m+a)%mod;
	sum[k]=(sum[k]*m+a*size[k])%mod;
	add[k]=(add[k]*m+a)%mod;
	mul[k]=(mul[k]*m)%mod;
}
void pushup(int k) {
	int l=ch[k][0],r=ch[k][1];
	sum[k]=(sum[l]+sum[r]+v[k])%mod;
	size[k]=(size[l]+size[r]+1)%mod;
}
void pushdown(int k) {
	int l=ch[k][0],r=ch[k][1];
	if (rev[k]) { rev[k]^=1; rev[l]^=1; rev[r]^=1; swap(ch[k][0],ch[k][1]); }
	int m=mul[k],a=add[k]; mul[k]=1; add[k]=0;
	if (m!=1||a!=0) { update(l,m,a); update(r,m,a); }
}
void rotate(int x) {
	int l,r,y=fa[x],z=fa[y];
	if (ch[y][0]==x) l=0; else l=1; r=l^1;
	if (!isroot(y)) { if (ch[z][0]==y)ch[z][0]=x;else ch[z][1]=x; }
	fa[x]=z; fa[y]=x; fa[ch[x][r]]=y;
	ch[y][l]=ch[x][r]; ch[x][r]=y; pushup(y); pushup(x);
}
void splay(int x) {
	top=0; que[++top]=x;
	for (int i=x;!isroot(i);i=fa[i]) que[++top]=fa[i];
	for (int i=top;i;i--) pushdown(que[i]);
	while (!isroot(x)) {
		int y=fa[x],z=fa[y];
		if (!isroot(y)) { if (ch[y][0]==x^ch[z][0]==y) rotate(x); else rotate(y); }
		rotate(x);
	}
}
void access(int x) {
	int tmp=0;
	while (x) { splay(x); ch[x][1]=tmp; pushup(x); tmp=x; x=fa[x]; }
}
// 将x到原树的root的路径转化为实边，用了splay的右子树记录，但不要认为形成一条链(中序遍历是一条链)
void makeroot(int x) { access(x); splay(x); rev[x]^=1; }
// 继上，之后将x旋到根，实边翻转到x的右子树上，成功的实现了换根操作(由fa树可知这将x节点作为了原树的root)
void link(int x,int y) { makeroot(x); fa[x]=y; }
// 继makeroot，连一条虚边到y(fa形成的树即为原树，始终正确)
void cut(int x,int y) { makeroot(x); access(y); splay(y); ch[y][0]=fa[x]=0; }
// 继makeroot，将y到x的路径转化为实边，y旋到根，断掉x->y的虚实边
// (因为树中保证存在x->y这条边，所以x与y必定相邻，ch[y][0]与fa[x]指的是同一条边)
int main() {
	int i,j;
	n=read(); m=read();
	for (i=1;i<n;i++) { int u=read(),v=read(); link(u,v); }
	for (i=1;i<=n;i++) { v[i]=sum[i]=1; mul[i]=1; size[i]=1; }
	for (i=1;i<=m;i++) {
		scanf("%s",c); x=read(); y=read();
		switch (c[0]) {
			case '+':{ z=read(); makeroot(x); access(y); splay(y); update(y,1,z); break; }
			// +合并，将x作为root，y转为x的fa，x->y边权加z
			case '-':{ cut(x,y); x=read(); y=read(); link(x,y); break; }
			// 切割，将x->y割开
			case '*':{ z=read(); makeroot(x); access(y); splay(y); update(y,z,0); break; }
			// *合并，同1，最后权值*m
			case '/':{ makeroot(x); access(y); splay(y); printf("%u\n",sum[y]); break; }
			// 询问x->y路径的边权和
		}
	}
	return 0;
}
