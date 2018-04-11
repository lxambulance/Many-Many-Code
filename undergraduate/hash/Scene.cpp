#include <cstring>
#include "Scene.h"

Scene::Scene(int M){
	fp=NULL;
	tot=0;
	p=19980121;
	base=100000000;
	A=new Data[M];
}

Scene::~Scene(){
	delete[] A;
}

void Scene::ShowData(){
	int x=0;
	for (int i=1;i<=tot;++i) if (A[i].flag) x++;
	printf("Total number=%d\n",x);
	for (int i=1;i<=tot;++i)
	if (A[i].flag) printf("%lld %s\n",A[i].PhoneNumber,A[i].name);
}

int Scene::change(char a[]){
	int ret=0,n=strlen(a);
	for (int i=0;i<n;++i) ret=(ret*26+a[i]-'A')%p;
	return ret;
}

int Scene::Modify(int p){
	tot--;
	for (int i=p;i<=tot;++i) A[i]=A[i+1];
	return 1;
}

int Scene::work(char a[],hash *phone,hash *name){
	if (a[0]=='W'||a[0]=='R') {
		if ((fp=fopen(a,"r"))==NULL) {
			puts("Open failed!!\n");
			return -1;
		}
		char ch;
		fscanf(fp,"%d%c",&n,&ch);
		for (int i=1;i<=n;++i) {
			fgets(s,100,fp);
			printf("%s",s);
		}
	}
	switch(a[0]){
		case 'I':{
			printf("Please input people number:\n");
			scanf("%d",&n);
			for (int i=1;i<=n;++i) {
				printf("Please input name&phone:\n");
				++tot;
				scanf("%s%lld",A[tot].name,&A[tot].PhoneNumber);
				int key=change(A[tot].name);
				if (phone->FindElement(A[tot].PhoneNumber%base)==-1&&name->FindElement(key)==-1) {
					phone->Insert(A[tot].PhoneNumber%base,tot);
					name->Insert(key,tot);
				}
				else {
					printf("Find Same ID|Number!!\n");
					tot--; continue;
				}
			}
			break;
		}
		case 'S':{
			char ch=getchar();
			Again1:
			printf("Please input search type(0=name,1=number):\n");
			ch=getchar();
			if (ch=='0') {
				printf("Please input his/her name:\n");
				scanf("%s",s);
				int position,key=change(s);
				if ((position=name->FindElement(key))!=-1&&A[position].flag)
					printf("%lld %s\n",A[position].PhoneNumber,A[position].name);
				else printf("Not Found!!\n");
			}
			else if (ch=='1') {
				printf("Please input his/her PhoneNumber:\n");
				scanf("%lld",&m);
				int position;
				if ((position=phone->FindElement(m%base))!=-1&&A[position].flag)
					printf("%lld %s\n",A[position].PhoneNumber,A[position].name);
				else printf("Not Found!!\n");
			}
			else {
				printf("RU idiot!!\n");
				goto Again1;
			}
			break;
		}
		case 'D':{
			printf("Please input people number:\n");
			scanf("%d",&n);
			char ch=getchar();
			for (int i=1;i<=n;++i) {
				printf("Please input name|phone(0=name,1=phone):\n");
				ch=getchar();
				if (ch=='0') {
					printf("Please input his/her name:\n");
					scanf("%s",s);
					int position,key=change(s);
					if ((position=name->FindElement(key))!=-1) {
						A[position].flag=0;
						name->Delete(key,position),phone->Delete(A[position].PhoneNumber%base,position);
					}
					else printf("No this one!!\n");
				}
				else if (ch=='1') {
					printf("Please input his/her PhoneNumber:\n");
					scanf("%lld",&m);
					int position;
					if ((position=phone->FindElement(m%base))!=-1) {
						A[position].flag=0;
						name->Delete(change(A[position].name),position),phone->Delete(m%base,position);
					}
					else printf("No this phone number!!\n");
				}
				else {
					printf("RU idiot!!\n");
				}
			}
			break;
		}
		case 'L':{
			n=strlen(a);
			if (n==9) {
				Again2:
				printf("More rules&formulas please goto readme!!\nPlease input your file name:\n");
				scanf("%s",s);
				if ((fp=fopen(s,"r"))==NULL) {
					puts("Open failed!!\n");
					goto Again2;
				}
				else {
					fscanf(fp,"%d",&tot);
					for (int i=1;i<=tot;++i) {
						fscanf(fp,"%s %lld",A[i].name,&A[i].PhoneNumber);
						A[i].flag=1;
						name->Insert(change(A[i].name),i);
						phone->Insert(A[i].PhoneNumber%base,i);
					}
					puts("Loading success!!\n");
					ShowData();
				}
			}
			else if (n==10) {
				fp=fopen("Data.txt","w");
				int x=0;
				for (int i=1;i<=tot;++i) if (A[i].flag) x++;
				fprintf(fp,"%d\n",x);
				for (int i=1;i<=tot;++i)
				if (A[i].flag) fprintf(fp,"%s %lld\n",A[i].name,A[i].PhoneNumber);
				printf("The Data was saved in Data.txt\n");
			}
			break;
		}
	}
	fclose(fp);
	return 1;
}
