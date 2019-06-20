#include <cstdio>
#include <cstring>
#include "ProcessControlBlock.h"

PCB::ProcessControlBlock(const char *name,int Status,int Priority){
	PCBnum++;
	PID=++PCBnowID;
	int namelen=strlen(name)+1;
	Pname=new char[namelen];
	memcpy(Pname,name,namelen+1);
	resource_occupied.clear();
	status=Status;
	priority=Priority;
	father=son=brother=NULL;
}

PCB::~ProcessControlBlock(){
	PCBnum--;
	if (PCBnowID==PID) PCBnowID--;
	delete Pname;
	Pname=NULL;
}

int PCB::setStatus(int nowstatus){
	status=nowstatus;
	return 0;
}

int PCB::modifyResource(int target,int delta){
	if (delta==0) return 0;
	for (int i=0;i<resource_occupied.size();++i)
	if (target==resource_occupied[i].first) {
		if (resource_occupied[i].second+delta<0) {
			printf("Error: this Process haven't enough resource %d to release.\n",target);
			return 1;
		}
		resource_occupied[i].second+=delta;
		return 0;
	}
	if (delta<0) {
		printf("Error: this Process haven't resource %d.\n",target);
		return 2;
	}
	resource_occupied.push_back(std::make_pair(target,delta));
	return 0;
}

int PCB::getPID(){
	return PID;
}

char *PCB::getPname(){
	return Pname;
}

int PCB::getResource(std::vector<std::pair<int,int> > &resourceList){
	if (!resource_occupied.size()) return 1;
	for (int i=0;i<resource_occupied.size();++i) {
		std::pair<int,int> ri=resource_occupied[i];
		resourceList.push_back(ri);
	}
	return 0;
}

int PCB::getStatus(){
	return status;
}

int PCB::getPriority(){
	return priority;
}

int PCB::print(){
	printf("PID:%d,Pname:%s",PID,Pname);
	printf(",status=");
	switch(status){
		case READY:printf("ready");break;
		case RUNNING:printf("running");break;
		case BLOCK:printf("block");break;
	}
	printf(",priority=");
	switch(priority){
		case INIT:printf("init");break;
		case USER:printf("user");break;
		case SYSTEM:printf("system");break;
	}
	putchar('\n');
	putchar('\t');
	printf("have:");
	for (int i=0;i<resource_occupied.size();++i) {
		if (i) putchar('-');
		printf("(R%d,%d)",resource_occupied[i].first+1,resource_occupied[i].second);
	}
	if (!resource_occupied.size()) puts("nothing");
	else putchar('\n');
	return 0;
}
