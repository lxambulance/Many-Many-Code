#ifndef LXHASH_H
#define LXHASH_H

class hash{
private:
	int Mo,lx,tot;
	int *element,*key;
	void lazy();
public:
	hash(int a=313581,int b=52);
	~hash();
	int FindNextPrime(int x);
	void ShowMyself();
	int CalcKey(int x);
	int FindElement(int x); //-1 mean not find!
	int Insert(int x,int y);//-1 mean Full,insert fail! 0 mean same ID
	int Delete(int x,int y);//-1 mean delete fail!
};

#endif
