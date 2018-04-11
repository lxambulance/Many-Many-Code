#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define FOR(i,a,b) for (int i=(a);i<=(b);++i)
#define ROF(i,b,a) for (int i=(b);i>=(a);--i)
//#define __DEBUG__


unsigned char ch,tmp1,tmp2;
char s[256];
FILE *fI,*fO;
int fileOpen(char s[],int type){
	int len=strlen(s);
	if ((fI=fopen(s,"rb"))==NULL) {
		printf("No such file!\n");
		return 0;
	}
	printf("%s open success!\n",s);
	if (type==1) {
		s[len+2]=s[len];
		s[len]='L';
		s[len+1]='X';
	}
	else if (type==2) {
		if (!(s[len-2]=='L'&&s[len-1]=='X'&&len>2)) {
			printf("Seems the file's type is not right!\n");
			return 0;
		}
		len-=2;
		s[len]=s[len+2];
	}
	return 1;
}

vector<unsigned char> Q;
int n,m,len[256],a[256][256],b[512],c[512],fa[512],type[512],child[512][2];
int cmp(int i,int j){ return b[i]<b[j]; }
void compress(){
	if (fileOpen(s,1)==0) return;
	Q.clear(); n=0;
	memset(b,0,sizeof(b));
	while (fscanf(fI,"%c",&ch)!=EOF) {
		//printf("%c",ch);
		b[ch]++; n++;
		Q.push_back(ch);
	}
	FOR(i,0,511) c[i]=i,fa[i]=0;
	sort(c,c+256,cmp);
	int h=0,l=256,r=256,x,y,z;
	while (r<511) {
		if (l==r||h<256&&b[c[h]]<b[c[l]]) x=h++;
		else x=l++;
		if (l==r||h<256&&b[c[h]]<b[c[l]]) y=h++;
		else y=l++;
		fa[x]=fa[y]=r;
		type[x]=0,type[y]=1;
		b[c[r++]]=b[c[x]]+b[c[y]];
	}
	memset(len,0,sizeof(len));
	memset(a,0,sizeof(a));
	FOR(i,0,255) {
		int x=c[i],y=i;
		while (y!=510) {
			a[x][len[x]++]=type[y];
			y=fa[y];
		}
	}
	
	fO=fopen(s,"wb");
	FOR(i,0,255) fprintf(fO,"%c",(unsigned char)c[i]);
	FOR(i,0,510) {
		fprintf(fO,"%c",(unsigned char)(fa[i]&255));
		fprintf(fO,"%c",(unsigned char)(((fa[i]>>8)|(type[i]<<1))&255));
	}
	x=0,y=8; m=0;
	FOR(i,0,n-1) {
		z=Q[i];
		ROF(j,len[z]-1,0) {
			y--;
			if (a[z][j]) x|=(1<<y);
			if (y==0) {
				fprintf(fO,"%c",(unsigned char)x),++m;
				x=0,y=8;
			}
		}
	}
	fprintf(fO,"%c",(unsigned char)x),++m;
	fprintf(fO,"%c",(unsigned char)y);
	fclose(fO);
	
#ifdef __DEBUG__
	printf("%d\n",(unsigned char)x);
	printf("%d\n",(unsigned char)y);
	FOR(i,0,255) {
		printf("%d:",c[i]);
		int x=c[i];
		ROF(j,len[x]-1,0) printf("%c","01"[a[x][j]]);
		printf("\n");
	}
	FOR(i,0,255) printf("%d:%d%c\n",i,b[i],(unsigned char)i);
	int ans=0;
	FOR(i,0,255) ans+=len[i]*b[i];
	printf("%d %d %d %d\n",n,n*8,ans,m);
#endif
}
void decompress(){
	if (fileOpen(s,2)==0) return;
	FOR(i,0,255) { fscanf(fI,"%c",&ch); c[i]=ch; }
	FOR(i,0,511) child[i][0]=child[i][1]=-1;
	FOR(i,0,510) {
		fscanf(fI,"%c",&ch); fa[i]=ch;
		fscanf(fI,"%c",&ch);
		if (ch&1) fa[i]+=256;
		if (ch&2) type[i]=1; else type[i]=0;
		if (fa[i]) child[fa[i]][type[i]]=i;
	}
	
	fO=fopen(s,"wb");
	int x,z=510; n=0;
	fscanf(fI,"%c",&ch);
	fscanf(fI,"%c",&tmp1);
	while (fscanf(fI,"%c",&tmp2)!=EOF) {
		ROF(y,7,0) {
			x=(((int)(ch)>>y)&1);
			z=child[z][x];
			if (z<256) {
				n++;
				fprintf(fO,"%c",(unsigned char)c[z]);
				z=510;
			}
		}
		ch=tmp1; tmp1=tmp2;
	}
	ROF(y,7,tmp1) {
		x=(((int)(ch)>>y)&1);
		z=child[z][x];
		if (z<256) {
			n++;
			fprintf(fO,"%c",(unsigned char)c[z]);
			z=510;
		}
	}
	fclose(fO);
#ifdef __DEBUG__
	memset(a,0,sizeof(a));
	memset(len,0,sizeof(len));
	FOR(i,0,255) {
		printf("%d:",c[i]);
		int x=c[i],y=i;
		while (y!=510) {
			a[x][len[x]++]=type[y];
			y=fa[y];
		}
		ROF(j,len[x]-1,0) printf("%c","01"[a[x][j]]);
		printf("\n");
	}
	printf("%d\n",n);
#endif
}
int main(){
	while (true) {
		system("cls");
		printf("Hello!\n");
		printf("What do U want to do?\n");
		printf("1.compress.\n");
		printf("2.decompress.\n");
		printf("3.quit.\n");
		for (ch=getchar();ch!='1'&&ch!='2'&&ch!='3';ch=getchar());
		if (ch=='3') break;
		printf("please input the file name:\n");
		scanf("%s",s);
		if (ch=='1') compress();
		if (ch=='2') decompress();
		system("pause");
	}
	printf("Goodbye!\n");
	if (fI!=NULL) fclose(fI);
	return 0;
}
