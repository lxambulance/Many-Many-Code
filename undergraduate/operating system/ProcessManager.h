#ifndef __PROCESSMANAGER_H__
#define __PROCESSMANAGER_H__

#include <queue>
#include <vector>
#include <map>
#include <string>
#include "ProcessControlBlock.h"
#include "ResourceManager.h"

class ProcessManager{
private:
	RM *resourceManager=new RM();
	PCB *nowRunning;
	std::queue<PCB *>readyList[3];
	std::queue<PCB *>blockList;
	std::vector<std::pair<int,int> >resourceList;

public:
	std::map<std::string,PCB *> name2PCB;
	int init();
	int create(char *name,int Priority);
	int destroy(char *name,bool flag);
	int killTree(PCB *nowNode,bool flag);
	int scheduler(bool flag);
	int modifyRe(int reg,int delta);
	int timeOut();
	int print(int op,PCB *p=NULL);
};
typedef ProcessManager PM;

#endif
