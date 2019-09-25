#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
using namespace std;

const int Maxn=200005;
int n,m;
int a[Maxn];

struct SplayTree {
	int nodeCnt,root,stackCnt;
	int type[Maxn],parent[Maxn],key[Maxn],size[Maxn],childs[Maxn][2],reversed[Maxn],stack[Maxn];
	
	void clear() {
		root=0;
		size[0]=0;
		nodeCnt=0;
	}
	void malloc(int &x,int k) {
		x=++nodeCnt;
		key[x]=k;
		type[x]=2;
		childs[x][0]=childs[x][1]=0;
		size[x]=1;
		reversed[x]=0;
	}
	void update(int x) {
		size[x]=size[childs[x][0]]+1+size[childs[x][1]];
	}
	void pass(int x) {
		if (reversed[x]) {
			swap(childs[x][0],childs[x][1]);
			type[childs[x][0]]=0;
			type[childs[x][1]]=1;
			reversed[childs[x][0]]^=1;
			reversed[childs[x][1]]^=1;
			reversed[x]=0;
		}
	}
	void rotate(int x) {
		int t=type[x],y=parent[x],z=childs[x][1-t];
		type[x]=type[y];
		parent[x]=parent[y];
		if (type[x]!=2) childs[parent[x]][type[x]]=x;
		type[y]=1-t;
		parent[y]=x;
		childs[x][1-t]=y;
		if (z) {
			type[z]=t;
			parent[z]=y;
		}
		childs[y][t]=z;
		update(y);
	}
	void splay(int x) {
		int stackCnt=0;
		stack[stackCnt++]=x;
		for (int i=x;type[i]!=2;i=parent[i]) stack[stackCnt++]=parent[i];
		for (int i=stackCnt-1;i>=0;--i) pass(stack[i]);
		while (type[x]!=2) {
			int y=parent[x];
			if (type[x]==type[y]) rotate(y);
			else rotate(x);
			if (type[x]==2) break;
			rotate(x);
		}
		update(x);
	}
	int find(int x,int rank) {
		while (true) {
			pass(x);
			if (size[childs[x][0]]+1==rank) break;
			if (rank<=size[childs[x][0]]) x=childs[x][0];
			else {
				rank-=size[childs[x][0]]+1;
				x=childs[x][1];
			}
		}
		return x;
	}
	void split(int &x,int &y,int a) {
		y=find(x,a+1);
		splay(y);
		x=childs[y][0];
		type[x]=2;
		childs[y][0]=0;
		update(y);
	}
	void join(int &x,int y) {
		x=find(x,size[x]);
		splay(x);
		childs[x][1]=y;
		type[y]=1;
		parent[y]=x;
		update(x);
	}
	int gerRank(int x) {
		splay(x);
		root=x;
		return size[childs[x][0]];
	}
	void reverse(int a,int b) {
		int x,y;
		split(root,y,b);
		split(root,x,a-1);
		reversed[x]^=1;
		join(x,y);
		join(root,x);	
	}
	void insert(int k) {
		int x;
		malloc(x,k);
		if (root==0) root=x;
		else join(root,x);
	}
	void midout(int x) {
		if (x) {
			pass(x);
			midout(childs[x][0]);
			if (key[x]>0&&key[x]<=n) printf("%d ",a[key[x]]);
			midout(childs[x][1]);
		}
	}
}Tree;

int main() {
	int i,j,k;
	scanf("%d",&n);
	for (i=1;i<=n;++i) scanf("%d",&a[i]);
	for (i=0;i<=n+1;++i) Tree.insert(i);
	scanf("%d",&m);
	for (i=1;i<=m;++i) {
		scanf("%d%d",&j,&k);
		Tree.reverse(j+1,k+1);
	}
	Tree.midout(Tree.root); printf("\n"); 
}

