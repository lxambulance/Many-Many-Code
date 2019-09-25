#include <bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for (int i=(a);i<=(b);++i)
#define ROF(i,a,b) for (int i=(a);i>=(b);--i)
typedef long long ll;
inline int read(){
    int x=0,f=1;char ch=getchar();
    while (!isdigit(ch)) {if (ch=='-')f=-1;ch=getchar();}
    while (isdigit(ch)) {x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

const int MAXN=100005,Mo=51061;
bool rev[MAXN];
int n,m,x,y,z,top;
int que[MAXN],fa[MAXN],ch[MAXN][2];
int sum[MAXN],mul[MAXN],add[MAXN],v[MAXN],size[MAXN];
inline bool isroot(int x) { return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x; }
void update(int k,int m,int a){
	if (!k)return;
	v[k]=(v[k]*m+a)%Mo;
	sum[k]=(sum[k]*m+a*size[k])%Mo;
	add[k]=(add[k]*m+a)%Mo;
	mul[k]=(mul[k]*m)%Mo;
}
void pushup(int k){
	int l=ch[k][0],r=ch[k][1];
	sum[k]=(sum[l]+sum[r]+v[k])%Mo;
	size[k]=(size[l]+size[r]+1)%Mo;
}
void pushdown(int k){
	int l=ch[k][0],r=ch[k][1];
	if (rev[k]) {
        rev[k]^=1; rev[l]^=1; rev[r]^=1;
        swap(ch[k][0],ch[k][1]);
    }
	int m=mul[k],a=add[k]; mul[k]=1; add[k]=0;
	if (m!=1||a!=0) { update(l,m,a); update(r,m,a); }
}
void rotate(int x){
	int l,r,y=fa[x],z=fa[y];
	if (ch[y][0]==x) l=0; else l=1;
    r=l^1;
	if (!isroot(y)) {
        if (ch[z][0]==y) ch[z][0]=x;
        else ch[z][1]=x;
    }
	fa[x]=z; fa[y]=x; fa[ch[x][r]]=y;
	ch[y][l]=ch[x][r]; ch[x][r]=y;
    pushup(y); pushup(x);
}
void splay(int x){
	top=0; que[++top]=x;
	for (int i=x;!isroot(i);i=fa[i]) que[++top]=fa[i];
	for (int i=top;i;i--) pushdown(que[i]);
	while (!isroot(x)) {
		int y=fa[x],z=fa[y];
		if (!isroot(y)) {
            if ((ch[y][0]==x)^(ch[z][0]==y)) rotate(x);
            else rotate(y);
        }
		rotate(x);
	}
}
void access(int x){
	int tmp=0;
	while (x) {
        splay(x); ch[x][1]=tmp; pushup(x);
        tmp=x; x=fa[x];
    }
}
void makeroot(int x){ access(x); splay(x); rev[x]^=1; }
void link(int x,int y){ makeroot(x); fa[x]=y; access(x); }
//要求原树中存在x-y这条边
void cut(int x,int y){ makeroot(x); access(y); splay(y); ch[y][0]=fa[x]=0; pushup(y); }
int main(){
	int i;
	n=read(); m=read();
	for (i=1;i<=n;i++) v[i]=sum[i]=mul[i]=size[i]=1;
    for (i=1;i<n;i++) {
        int u=read(),v=read();
        link(u,v);
    }
	for (i=1;i<=m;i++) {
        char c[5];
		scanf("%s",c); x=read(); y=read();
		switch (c[0]) {
			case '+':{
                z=read();
                makeroot(x); access(y); splay(y);
                update(y,1,z); break;
            }
			case '-':{
                cut(x,y);
                x=read(); y=read(); link(x,y); break;
            }
			case '*':{
                z=read();
                makeroot(x); access(y); splay(y);
                update(y,z,0); break;
            }
			case '/':{
                makeroot(x); access(y); splay(y);
                printf("%u\n",sum[y]); break;
            }
		}
	}
	return 0;
}

