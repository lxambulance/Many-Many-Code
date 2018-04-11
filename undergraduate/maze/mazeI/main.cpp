#include <ctime>
#include <cstdio>
#include <cstdlib>
#include "maze.h"
//#define __DEBUG__
#define begin :{
#define end break;}

char ch,s[100];
Maze *maze;
void Init(){
	srand(time(0));
	maze=new Maze;
	maze->autoMake();
}
void GoodBye(){
	delete maze;
}
int main(){
	Init();
#ifdef __DEBUG__
#endif
	while (true) {
		system("cls");
		maze->showMeTheMap();
		printf("What do you want?\n");
		printf("q:quit.\n");
		printf("l:load from file.\n");
		printf("r:reload a random map.\n");
		printf("f:find all solution.\n");
		ch=getchar();
		switch (ch) {
			case 'q' begin goto GG; end
			case 'l' begin
				Again1:
				printf("Waiting for input:");
				scanf("%s",s);
				int ret=maze->loadMapFrom(s);
				if (ret) goto Again1;
			end
			case 'r' begin
				int x,y;
				Again2:
				printf("Please tell me the size n*m:");
				scanf("%d%d",&x,&y);
				if (x<5||y<5) {
					printf("Too small!\n");
					goto Again2;
				}
				else if (x>50||y>50) {
					printf("Too large!\n");
					goto Again2;
				}
				maze=new Maze(x,y);
				maze->autoMake();
			end
			case 'f' begin
				maze->showMeThePass();
			end
			case 's' begin
				scanf("%s",s);
				maze->saveMap(s);
			end
		}
		system("pause");
	}
	
	GG:
	GoodBye();
	return 0;
}
