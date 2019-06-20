#include <cstdio>
#include <cstring>
#include "ProcessManager.h"

int PCB::PCBnum=0,PCB::PCBnowID=0;
PM processManager;
char op[252],name[252];
int main(int args,char **argv){
	if (args==3) {
		freopen(argv[1],"r",stdin);
		freopen(argv[2],"w",stdout);
	}
	puts("-init");
	processManager.init();
	while (true) {
		putchar('-');
		scanf("%s",op);
		if (!strcmp(op,"cr")) {
			int priority;
			scanf("%s%d",name,&priority);
			processManager.create(name,priority);
		}
		else if (!strcmp(op,"de")) {
			scanf("%s",name);
			std::string Name=name;
			PCB *p=processManager.name2PCB[Name];
			if (p==NULL) continue;
			processManager.killTree(p,true);
		}
		else if (!strcmp(op,"req")) {
			int num;
			scanf("%s%d",name,&num);
			//printf("%c %d\n",name[1],num);
			int reg=name[1]-'0';
			processManager.modifyRe(reg-1,num);
		}
		else if (!strcmp(op,"rel")) {
			int num;
			scanf("%s%d",name,&num);
			//printf("%c %d\n",name[1],num);
			int reg=name[1]-'0';
			processManager.modifyRe(reg-1,-num);
		}
		else if (!strcmp(op,"to")) {
			processManager.timeOut();
		}
		else if (!strcmp(op,"list")) {
			scanf("%s",name);
			if (!strcmp(name,"ready")) processManager.print(READY);
			else if (!strcmp(name,"block")) processManager.print(BLOCK);
			else if (!strcmp(name,"res")) processManager.print(3);
		}
		else if (!strcmp(op,"pr")) {
			scanf("%s",name);
			std::string Name=name;
			PCB *p=processManager.name2PCB[Name];
			if (p==NULL) continue;
			processManager.print(4,p);
		}
		else if (!strcmp(op,"quit")) {
			break;
		}
		else if (!strcmp(op,"exit")) {
			break;
		}
		else puts("?");
	}
	if (args==3) {
		fclose(stdin);
		fclose(stdout);
	}
	
	return 0;
}
