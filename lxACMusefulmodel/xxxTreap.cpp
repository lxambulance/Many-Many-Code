#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
inline int read() {
	int x=0,f=1; char ch=getchar();
	while (ch<'0'||ch>'9') { if (ch=='-') f=-1; ch=getchar(); }
	while (ch>='0'&&ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	return x*f;
}

const int MAXN=200005;
struct data{ int l,r,v,w,rnd,size; }T[MAXN];
int n,ans,top,size,root,mp[MAXN];
inline void update(int k) { T[k].size=T[T[k].l].size+T[T[k].r].size+T[k].w; }
void rturn(int &k) { int t=T[k].l; T[k].l=T[t].r; T[t].r=k; T[t].size=T[k].size; update(k); k=t; }
void lturn(int &k) { int t=T[k].r; T[k].r=T[t].l; T[t].l=k; T[t].size=T[k].size; update(k); k=t; }
void Tree_ins(int &k,int x) {
	if (k==0) { 
		if (top!=0) k=mp[top--]; else k=++size;
		T[k].l=T[k].r=0; T[k].size=T[k].w=1; T[k].v=x; T[k].rnd=rand();
		return;
	}
	T[k].size++;
	if (T[k].v==x)T[k].w++;
	else if (x>T[k].v) {
		Tree_ins(T[k].r,x);
		if (T[T[k].r].rnd<T[k].rnd) lturn(k);
	}
	else {
		Tree_ins(T[k].l,x);
		if (T[T[k].l].rnd<T[k].rnd) rturn(k);
	} 
}
void Tree_del(int &k,int x) {
	if (k==0) return; 
	if (T[k].v==x) {
		if (T[k].w>1) { T[k].w--; T[k].size--; return; }
		if (T[k].l*T[k].r==0) { mp[++top]=k; k=T[k].l+T[k].r; }
		else if (T[T[k].l].rnd<T[T[k].r].rnd) rturn(k),Tree_del(k,x);
		else lturn(k),Tree_del(k,x);
	}
	else if (x>T[k].v) T[k].size--,Tree_del(T[k].r,x);
	else T[k].size--,Tree_del(T[k].l,x);
}
int query_rank(int k,int x) {
	if (k==0) return 0;
	if (T[k].v==x) return T[T[k].l].size+1;
	else if(x>T[k].v) return T[T[k].l].size+T[k].w+query_rank(T[k].r,x);
	else return query_rank(T[k].l,x);
}
int query_num(int k,int x) {
	if (k==0) return 0;
	if (x<=T[T[k].l].size) return query_num(T[k].l,x);
	else if(x>T[T[k].l].size+T[k].w) return query_num(T[k].r,x-T[T[k].l].size-T[k].w);
	else return T[k].v;
}
void query_pro(int k,int x) {
	if (k==0) return;
	if (T[k].v<x) { ans=k; query_pro(T[k].r,x); }
	else query_pro(T[k].l,x);
}
//result in ans
void query_sub(int k,int x) {
	if (k==0) return;
	if (T[k].v>x) { ans=k; query_sub(T[k].l,x); }
	else query_sub(T[k].r,x);
}
//result in ans
int query_max(int k) {
	while (T[k].r>0) k=T[k].r;
	return T[k].v;
}
int query_min(int k) {
	while (T[k].l>0) k=T[k].l;
	return T[k].v;
}
int main() {
	int opt,x; n=read();
	for(int i=1;i<=n;i++) {
		opt=read(); x=read();
		switch(opt) {
			case 1:Tree_ins(root,x); break;
			case 2:Tree_del(root,x); break;
			case 3:printf("%d\n",query_rank(root,x)); break;
			case 4:printf("%d\n",query_num(root,x)); break;
			case 5:ans=0; query_pro(root,x); printf("%d\n",T[ans].v); break;
			case 6:ans=0; query_sub(root,x); printf("%d\n",T[ans].v); break;
		}
	}
	return 0;
}

/*
*/
