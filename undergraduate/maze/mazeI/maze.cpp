#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include "maze.h"

Maze::Maze(int x,int y){
	n=x; m=y;
	a=new int**[50];
	b=new int*[50];
	for (int i=0;i<50;++i) {
		a[i]=new int*[50];
		b[i]=new int[50];
		for (int j=0;j<50;++j) {
			a[i][j]=new int[4];
			for (int k=0;k<4;++k) a[i][j][k]=0;
			b[i][j]=0;
		}
	}
	f=new int[50*50];
	g=new int[50*50];
}

Maze::~Maze(){
	for (int i=0;i<50;++i) {
		for (int j=0;j<50;++j) {
			delete[] a[i][j];
			a[i][j]=NULL;
		}
		delete[] a[i]; a[i]=NULL;
		delete[] b[i]; b[i]=NULL;
	}
	delete[] a; a=NULL;
	delete[] b; b=NULL;
	delete[] f; f=NULL;
	delete[] g; g=NULL;
}

int Maze::ask(int x){
	if (f[x]==x) return x;
	return f[x]=ask(f[x]);
}

void Maze::autoMake(){
	int t,x,y;
	for (int i=0;i<n*m;++i) f[i]=i;
	while (ask(0)!=ask(n*m-1)) {
		t=rand()%2;
		if (t==0) {
			x=(rand()<<16|rand())%n;
			y=(rand()<<16|rand())%(m-1);
			a[x][y][1]=a[x][y+1][3]=1;
			f[ask(x*m+y)]=ask(x*m+y+1);
		}
		else {
			x=(rand()<<16|rand())%(n-1);
			y=(rand()<<16|rand())%m;
			a[x][y][0]=a[x+1][y][2]=1;
			f[ask(x*m+y)]=ask(x*m+y+m);
		}
	}
}

void Maze::saveMap(char x[]){
	int tot=0;
	for (int i=0;i<n;++i)
		for (int j=0;j<m;++j) {
			if (a[i][j][0]) tot++;
			if (a[i][j][1]) tot++;
		}
	FILE *fp=fopen(x,"w");
	fprintf(fp,"%d\n",tot);
	for (int i=0;i<n;++i)
		for (int j=0;j<m;++j) {
			if (a[i][j][0]) fprintf(fp,"1 %d %d %d %d\n",i,j,i+1,j);
			if (a[i][j][1]) fprintf(fp,"0 %d %d %d %d\n",i,j,i,j+1);
		}
	fclose(fp);
}

void Maze::showMeTheMap(){
	for (int i=0;i<n;++i) {
		for (int j=0;j<m;++j) printf(" %c","- "[a[i][j][2]]);
		printf("\n");
		for (int j=0;j<m;++j) printf("%c%c","| "[a[i][j][3]],".x"[b[i][j]]);
		printf("%c\n","| "[a[i][m-1][1]]);
	}
	for (int j=0;j<m;++j) printf(" %c","- "[a[n-1][j][0]]);
	printf("\n");
}

int Maze::bfs(){
	int h=0,t=0;
	for (int i=0;i<n*m;++i) f[i]=-1;
	g[t++]=0; f[0]=-2;
	while (h<t) {
		int z=g[h++],x=z/m,y=z%m;
		for (int i=0;i<4;++i)
		if (a[x][y][i]) {
			int xx=x+d[i][0],yy=y+d[i][1];
			if (xx>=0&&xx<n&&yy>=0&&yy<m&&f[xx*m+yy]==-1) {
				f[xx*m+yy]=x*m+y;
				g[t++]=xx*m+yy;
			}
		}
	}
	for (int i=0;i<n;++i)
		for (int j=0;j<m;++j) b[i][j]=0;
	int z=n*m-1,x,y;
	while (z>0) {
		x=z/m,y=z%m;
		b[x][y]=1; z=f[z];
	}
	b[0][0]=1;
}

void Maze::showMeThePass(){
	for (int i=0;i<n*m;++i) f[i]=0;
	if (bfs()) printf("We find them!\n");
	else printf("We can not find any pass!\n");
	showMeTheMap();
}

int Maze::loadMapFrom(char x[]){
	FILE *fp;
	if ((fp=fopen(x,"r"))==NULL) {
		puts("Open failed!!\n");
		return -1;
	}
	fscanf(fp,"%d%d",&n,&m);
	int p,x1,y1,x2,y2,t;
	fscanf(fp,"%d",&p);
	for (int i=0;i<p;++i) {
		fscanf(fp,"%d%d%d%d%d",&t,&x1,&y1,&x2,&y2);//0横1竖
		if (t==0) {
			if (y1>y2) std::swap(y1,y2);
			if (x1!=x2||abs(y1-y2)!=1) { fclose(fp); return -2; }
			a[x1][y1][1]=a[x2][y2][3]=1;
		}
		else {
			if (x1>x2) std::swap(x1,x2);
			if (y1!=y2||abs(x1-x2)!=1) { fclose(fp); return -2; }
			a[x1][y1][0]=a[x2][y2][2]=1;
		}
		//printf("-->%d<--OK!\n",i+1);
	}
	fclose(fp);
	return 0;
}
