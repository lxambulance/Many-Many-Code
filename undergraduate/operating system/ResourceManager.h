#ifndef __RESOURCEMANAGER_H__
#define __RESOURCEMANAGER_H__

#include <queue>
#include "ProcessControlBlock.h"

class ResourceManager{
private:
	const static int maxNumber=4;
	int resourceNum[maxNumber];
	std::queue<std::pair<PCB *,int> >waitingList[maxNumber];
	int checkId(int rid);

public:
	int init();
	int request(int rid,int num); //3 should push to waitingList
	int release(int rid,int num);
	int popHead(int rid);
	int getHead(int rid,int &num,PCB **p); //2 nothing
	int pushTail(int rid,int num,PCB *p);
	int print();
};
typedef ResourceManager RM;

#endif
