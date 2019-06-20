#include <cstdio>
#include <cstring>
#include "ProcessManager.h"

int PM::init(){
	resourceManager->init();
	nowRunning=new PCB("init",RUNNING,INIT);
	for (int i=0;i<3;++i)
		while (!readyList[i].empty()) readyList[i].pop();
	while (!blockList.empty()) blockList.pop();
	name2PCB.clear();
	std::string name=nowRunning->getPname();
	name2PCB[name]=nowRunning;
	puts("init process is running");
	return 0;
}

int PM::create(char *name,int Priority){
	std::string Name=name;
	if (name2PCB[Name]!=NULL) {
		printf("Error:process %s is already created.\n",name);
		return 1;
	}
	PCB *newnode=new PCB(name,READY,Priority);
	name2PCB[Name]=newnode;
	newnode->father=nowRunning;
	if (nowRunning->son!=NULL) {
		nowRunning->son->brother=newnode;
		nowRunning->son=newnode;
	}
	else nowRunning->son=newnode;
	readyList[Priority].push(newnode);
	PCB *tmp=nowRunning;
	scheduler(0);
	if (tmp->getStatus()==READY)
		printf("process %s is ready.\n",tmp->getPname());
	else if (newnode->getStatus()==READY)
		printf("process %s is ready.\n",newnode->getPname());
	else putchar('\n');
	return 0;
}

int PM::destroy(char *name,bool flag){
	std::string Name=name;
	PCB *nowNode=name2PCB[Name];
	if (nowNode==NULL) {
		printf("Error:process %s don't exist.\n",name);
		return 1;
	}
	resourceList.clear();
	if (!nowNode->getResource(resourceList)) {
		for (int i=0;i<resourceList.size();++i) {
			std::pair<int,int> pii;
			resourceManager->release(pii.first,pii.second);
			printf("process %s release R%d.\n",name,pii.first+1);
			int num;
			PCB *p;
			resourceManager->getHead(pii.first,num,&p);
			while (p!=NULL&&!resourceManager->request(pii.first,num)) {
				resourceManager->popHead(pii.first);
				p->modifyResource(pii.first,num);
				printf("process %s get R%d and ready.\n",p->getPname(),pii.first+1);
				p->setStatus(READY);
				resourceManager->getHead(pii.first,num,&p);
			}
		}
		std::queue<PCB *> tmp;
		while (!tmp.empty()) tmp.pop();
		while (!blockList.empty()) {
			PCB *p=blockList.front();
			blockList.pop();
			if (p->getStatus()==READY) {
				int priority=p->getPriority();
				readyList[priority].push(p);
				continue;
			}
			tmp.push(p);
		}
		blockList=tmp;
	}
	int status=nowNode->getStatus();
	if (status==RUNNING) nowRunning=NULL;
	else if (status==READY) {
		int priority=nowNode->getPriority(),pid=nowNode->getPID();
		std::queue<PCB *> tmp;
		while (!tmp.empty()) tmp.pop();
		while (!readyList[priority].empty()) {
			PCB *p=readyList[priority].front();
			readyList[priority].pop();
			if (p->getPID()==pid) continue;
			tmp.push(p);
		}
		readyList[priority]=tmp;
	}
	else {
		int pid=nowNode->getPID();
		std::queue<PCB *> tmp;
		while (!tmp.empty()) tmp.pop();
		while (!blockList.empty()) {
			PCB *p=blockList.front();
			blockList.pop();
			if (p->getPID()==pid) continue;
			tmp.push(p);
		}
		blockList=tmp;
	}
	delete nowNode;
	nowNode=name2PCB[Name]=NULL;
	if (flag) {
		scheduler(0);
		printf("process %s is destroyed.\n",name);
	}
	return 0;
}

int PM::killTree(PCB *nowNode,bool flag){
	if (flag&&nowNode->father!=NULL) {
		PCB *p1=nowNode->father->son;
		int pid=nowNode->getPID();
		if (p1->getPID()==pid) nowNode->father->son=p1->brother;
		else {
			while (p1->brother->getPID()!=pid) p1=p1->brother;
			p1->brother=nowNode->brother;
		}
	}
	if (nowNode->son!=NULL) killTree(nowNode->son,0);
	if (!flag&&nowNode->brother!=NULL) killTree(nowNode->brother,0);
	std::string Name=nowNode->getPname();
	destroy(nowNode->getPname(),0);
	if (flag) {
		scheduler(0);
		printf("process %s and its tree are destroyed.\n",Name.c_str());
	}
	return 0;
}

int PM::scheduler(bool flag){
	int I=-1;
	for (int i=2;i>=0;--i)
	if (!readyList[i].empty()) { I=i; break; }
	if (I!=-1) {
		PCB *p=readyList[I].front();
		if (nowRunning!=NULL) {
			if (p->getPriority()>nowRunning->getPriority()) {
				readyList[I].pop();
				nowRunning->setStatus(READY);
				readyList[nowRunning->getPriority()].push(nowRunning);
				nowRunning=p;
			}
		}
		else {
			readyList[I].pop();
			nowRunning=p;
		}
	}
	else {
		if (nowRunning==NULL) {
			puts("Error:nothing is running now.");
			exit(0);
		}
	}
	nowRunning->setStatus(RUNNING);
	printf("process %s is running.",nowRunning->getPname());
	if (flag) putchar('\n');
	return 0;
}

int PM::modifyRe(int reg,int delta){
	if (delta==0) return 0;
	if (delta<0) {
		if (nowRunning->modifyResource(reg,delta)) return 1;
		resourceManager->release(reg,-delta);
		printf("process %s release R%d.\n",nowRunning->getPname(),reg+1);
		int num;
		PCB *p;
		resourceManager->getHead(reg,num,&p);
		while (p!=NULL&&!resourceManager->request(reg,num)) {
			resourceManager->popHead(reg);
			p->modifyResource(reg,num);
			printf("process %s get R%d and ready.\n",p->getPname(),reg+1);
			p->setStatus(READY);
			resourceManager->getHead(reg,num,&p);
		}
		std::queue<PCB *> tmp;
		while (!tmp.empty()) tmp.pop();
		while (!blockList.empty()) {
			PCB *p=blockList.front();
			blockList.pop();
			if (p->getStatus()==READY) {
				int priority=p->getPriority();
				readyList[priority].push(p);
				continue;
			}
			tmp.push(p);
		}
		blockList=tmp;
	}
	else {
		int flag=resourceManager->request(reg,delta);
		if (flag==3) {
			printf("process %s is blocked.\n",nowRunning->getPname());
			blockList.push(nowRunning);
			nowRunning->setStatus(BLOCK);
			resourceManager->pushTail(reg,delta,nowRunning);
			nowRunning=NULL;
		}
		else if (flag==0) {
			printf("process %s get R%d.\n",nowRunning->getPname(),reg+1);
			nowRunning->modifyResource(reg,delta);
		}
	}
	scheduler(1);
	return 0;
}

int PM::timeOut(){
	char *name=nowRunning->getPname();
	int Priority=nowRunning->getPriority(),pid=nowRunning->getPID();
	readyList[Priority].push(nowRunning);
	nowRunning->setStatus(READY);
	nowRunning=NULL;
	scheduler(0);
	if (pid!=nowRunning->getPID())
		printf("process %s is ready.\n",name);
	else putchar('\n');
	return 0;
}

int PM::print(int op,PCB *p){
	if (op==READY) {
		puts("Ready list");
		for (int i=0;i<3;++i) {
			printf("%d:",i);
			std::queue<PCB *> tmp;
			while (!tmp.empty()) tmp.pop();
			while (!readyList[i].empty()) {
				PCB *p=readyList[i].front();
				readyList[i].pop();
				if (!tmp.empty()) putchar('-');
				printf("(%s)",p->getPname());
				tmp.push(p);
			}
			readyList[i]=tmp;
			putchar('\n');
		}
	}
	else if (op==BLOCK) {
		puts("Block list");
		std::queue<PCB *> tmp;
		while (!tmp.empty()) tmp.pop();
		while (!blockList.empty()) {
			PCB *p=blockList.front();
			blockList.pop();
			if (!tmp.empty()) putchar('-');
			printf("(%s)",p->getPname());
			tmp.push(p);
		}
		blockList=tmp;
		putchar('\n');
	}
	else if (op==3) {
		resourceManager->print();
	}
	else if (op==4) {
		p->print();
	}
	
	return 0;
}
