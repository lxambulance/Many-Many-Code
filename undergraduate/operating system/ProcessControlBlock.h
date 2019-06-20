#ifndef __PROCESSCONTROLBLOCK_H__
#define __PROCESSCONTROLBLOCK_H__

#include <vector>

#define READY 0
#define RUNNING 1
#define BLOCK 2
#define INIT 0
#define USER 1
#define SYSTEM 2

class ProcessControlBlock{
private:
	int PID;
	char* Pname;
	std::vector<std::pair<int,int> >resource_occupied;
	int status;
	int priority;

public:
	static int PCBnum,PCBnowID;
	ProcessControlBlock *father,*son,*brother;
	ProcessControlBlock(const char* name,int Status,int Priority);
	~ProcessControlBlock();
	int setStatus(int nowstatus);
	int modifyResource(int target,int delta);
	
	int getPID();
	char *getPname();
	int getResource(std::vector<std::pair<int,int> > &resourceList); //1 nothing
	int getStatus();
	int getPriority();
	int print();
};
typedef ProcessControlBlock PCB;

#endif
