#include <cstdio>
#include "ResourceManager.h"

int RM::checkId(int rid){
	if (rid<0||rid>=maxNumber) {
		printf("Error:waitingList number out of range[1,%d]\n",maxNumber);
		return 1;
	}
	return 0;
}

int RM::init(){
	for (int i=0;i<maxNumber;++i) {
		resourceNum[i]=i+1;
		while (!waitingList[i].empty()) waitingList[i].pop();
	}
	return 0;
}

int RM::request(int rid,int num){
	if (checkId(rid)) return 1;
	if (num>rid+1) {
		printf("Error:no enough resource[%d].\n",num);
		return 2;
	}
	if (resourceNum[rid]<num) return 3;
	resourceNum[rid]-=num;
	return 0;
}

int RM::release(int rid,int num){
	if (checkId(rid)) return 1;
	resourceNum[rid]+=num;
	return 0;
}

int RM::popHead(int rid){
	if (checkId(rid)) return 1;
	if (waitingList[rid].empty()) {
		printf("Warning:nothing to be popped in waitingList[%d].\n",rid);
		return 2;
	}
	waitingList[rid].pop();
	return 0;
}

int RM::getHead(int rid,int &num,PCB **p){
	if (checkId(rid)) return 1;
	if (waitingList[rid].empty()) {
		*p=NULL;
		//printf("Warning:nothing in waitingList[%d].\n",rid);
		return 2;
	}
	num=waitingList[rid].front().second;
	*p=waitingList[rid].front().first;
	return 0;
}

int RM::pushTail(int rid,int num,PCB *p){
	if (checkId(rid)) return 1;
	waitingList[rid].push(std::make_pair(p,num));
	return 0;
}

int RM::print(){
	puts("Resource list");
	for (int i=0;i<maxNumber;++i) {
		printf("\tR%d,remain=%d\n",i+1,resourceNum[i]);
		putchar('\t');
		std::queue<std::pair<PCB *,int> >tmp;
		while (!tmp.empty()) tmp.pop();
		while (!waitingList[i].empty()) {
			std::pair<PCB *,int> pii=waitingList[i].front();
			waitingList[i].pop();
			if (!tmp.empty()) putchar('-');
			printf("(%s,%d)",pii.first->getPname(),pii.second);
			tmp.push(pii);
		}
		if (tmp.empty()) puts("nothing in waitingList.");
		else putchar('\n');
		waitingList[i]=tmp;
	}
	return 0;
}
