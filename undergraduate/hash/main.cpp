#include <cstdio>
#include <cstdlib>
#include "Scene.h"
#include "lxhash.h"
//#define __DEBUG__

inline int r(int x){ return (rand()<<16|rand())%x; }
inline int R(int a,int b){ return a+r(b-a+1); }
hash *phone,*name;
Scene *scene;
void Init(){
	int *a=new int[5];
	srand((unsigned long long)a);
	delete[] a;
	int n,m;
	phone=new hash(n=R(200000,300000),R(30,50));
	name=new hash(m=R(200000,300000),R(30,50));
	scene=new Scene(std::max(n,m));
}
void GoodBye(){
	delete phone;
	delete name;
	delete scene;
	system("cls");
	printf("GoodBye!!\n");
}
int main(){
	Init();
	
#ifdef __DEBUG__
	phone->ShowMyself();
	name->ShowMyself();
	system("pause");
#endif
	
	while (true) {
		system("cls");
		scene->work("Welcome.in");
		char ch=getchar();
		switch(ch-48){
			case 1:scene->work("Readme.txt"); break;
			case 2:scene->work("Insert.in",phone,name); break;
			case 3:scene->work("Search.in",phone,name); break;
			case 4:scene->work("Delete.in",phone,name); break;
			case 5:scene->work("LoadIn.in",phone,name); break;
			case 6:scene->work("LoadOut.in"); break;
			case 7:goto GG;
			case 8:{
				printf("Phone hash table\n");
				phone->ShowMyself();
				printf("Name hash table\n");
				name->ShowMyself();
				scene->ShowData();
				break;
			}
		}
		system("pause"); ch=getchar();
	}
	
	GG:
	GoodBye();
	return 0;
}
