#include <bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for (int i=(a);i<=(b);++i)
#define ROF(i,a,b) for (int i=(a);i>=(b);--i)
typedef long long LL;
inline int read(){
	int x=0,f=1; char ch=getchar();
	while (ch<'0'||ch>'9') { if (ch=='-') f=-1; ch=getchar(); }
	while (ch>='0'&&ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	return x*f;
}

const int MAXN=300005,Mo=1000000007;
struct SplayNode{
	bool rev;
	int size,value;
	SplayNode *f,*ch[2];
	//SplayNode(int v=0):value(v){ f=ch[0]=ch[1]=NULL; size=1; }
};
typedef SplayNode SN;
int top,p;
SN tr[MAXN],*sk[MAXN],*rt,*q[MAXN];
void show(SN* x){
	if (x==NULL) return;
	show(x->ch[0]);
	printf("%d ",x->value);
	show(x->ch[1]);
}
void splayInit(){
	rt=NULL; top=MAXN-1;
	FOR(i,0,MAXN-1) sk[i]=&tr[i];
}
SN* newNode(int v,SN* f){
	SN* ret=sk[top--];
	ret->rev=0;
	ret->size=1; ret->value=v;
	ret->f=f; ret->ch[0]=ret->ch[1]=NULL;
	return ret;
}
void freeNode(SN* x){
	sk[++top]=x;
}
void update(SN* x){
	x->size=1;
	if (x->ch[0]!=NULL) x->size+=x->ch[0]->size;
	if (x->ch[1]!=NULL) x->size+=x->ch[1]->size;
}
void pushdown(SN* x){
	if (!x->rev) return;
	swap(x->ch[0],x->ch[1]);
	SN *l=x->ch[0],*r=x->ch[1];
	if (l!=NULL) l->rev^=1;
	if (r!=NULL) r->rev^=1;
	x->rev=0;
}
void rotate(SN* x){
	SN* y=x->f;
	int z=(x==y->ch[1]);
	y->ch[z]=x->ch[1-z];
	if (x->ch[1-z]!=NULL) x->ch[1-z]->f=y;
	x->f=y->f;
	if (y->f!=NULL) y->f->ch[y==y->f->ch[1]]=x;
	y->f=x; x->ch[1-z]=y;
	update(y); update(x);
}
void splay(SN* x){
	SN* y=x;
	for (p=0;y!=NULL;y=y->f) q[++p]=y;
	while (p) pushdown(q[p--]);
	while (x->f!=NULL) {
		y=x->f;
		if (y->f!=NULL) {
			if ((y->f->ch[1]==y)^(y->ch[1]==x)) rotate(x);
			else rotate(y);
		}
		rotate(x);
	}
}
void insert(int v){
	if (rt==NULL) { rt=newNode(v,NULL); return; }
	int y;
	for (SN* x=rt;x;x=x->ch[y]) {
		y=(v>=x->value);
		if (x->ch[y]==NULL) {
			rt=x->ch[y]=newNode(v,x);
			splay(rt); return;
		}
	}
}
void erase(SN* x){
	splay(x);
	SN* y=x->ch[0];
	if (y!=NULL) {
		y->f=NULL;
		while (1) {
			pushdown(y);
			if (y->ch[1]!=NULL) y=y->ch[1]; else break;
		}
		splay(y);
		y->ch[1]=x->ch[1];
		if (x->ch[1]!=NULL) x->ch[1]->f=y;
		update(rt=y);
	}
	else {
		rt=x->ch[1];
		if (rt!=NULL) rt->f=NULL;
	}
	freeNode(x);
}

SN* flag[MAXN];
int n,m,a[MAXN],b[MAXN];
int cmp(int i,int j){ return a[i]<a[j]||(a[i]==a[j]&&i<j); }
int main(){
	splayInit();
	while (n=read(),n) {
		FOR(i,1,n) a[i]=read(),b[i]=i;
		sort(b+1,b+1+n,cmp);
		//FOR(i,1,n) printf("%d%c",b[i]," \n"[i==n]);
		FOR(i,1,n) insert(i),flag[i]=rt;
		FOR(i,1,n) {
			splay(rt=flag[b[i]]);
			printf("%d%c",i+(rt->ch[0]?rt->ch[0]->size:0)," \n"[i==n]);
			if (rt->ch[0]!=NULL) rt->ch[0]->rev^=1;
			erase(rt);
			//show(rt); printf("------%d %d\n",i,b[i]);
		}
	}
	return 0;
}

/*
6
3 4 5 1 6 2
4
3 3 2 1
0

*/
