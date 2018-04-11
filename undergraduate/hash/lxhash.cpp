#include <cstdio>
#include "lxhash.h"

hash::hash(int a,int b){
	Mo=FindNextPrime(a);
	lx=FindNextPrime(b);
	tot=0;
	element=new int[Mo];
	key=new int[Mo];
	for (int i=0;i<Mo;++i) key[i]=element[i]=-1;
}

hash::~hash(){
	delete[] element;
	delete[] key;
}

void hash::lazy(){
	printf("Hash Table is Full!!\n");
}

void hash::ShowMyself(){
	printf("hash table: Mo=%d tot=%d\n",Mo,tot);
}

int hash::FindNextPrime(int x){
	bool flag;
	do{
		flag=true;
		for (int i=2;i*i<=x;++i) if (x%i==0) { flag=false; break; }
		if (!flag) x++;
	}while(!flag);
	return x;
}

int hash::CalcKey(int x){
	return ((x*lx+((x>>5)^0x3a91b4c1))%Mo+Mo)%Mo;
}

int hash::FindElement(int x){
	int K=CalcKey(x),b=K;
	while (key[K]!=-1&&key[K]!=x) {
		K=(K==Mo-1?0:K+1);
		if (K==b) return -1;
	}
	return element[K];
}

int hash::Insert(int x,int y){
	int K=CalcKey(x),b=K;
	while (key[K]!=-1&&key[K]!=x) {
		K=(K==Mo-1?0:K+1);
		if (K==b) {
			lazy();
			printf("Ignore this insert!!\n");
			return -1;
		}
	}
	if (key[K]==-1) {
		printf("Insert success!!\n");
		tot++,key[K]=x,element[K]=y;
		return 1;
	}
	else {
		printf("Same ID!!Ignore!!\n");
		return 0;
	}
}

int hash::Delete(int x,int y){
	int K=CalcKey(x),b=K;
	while (key[K]!=-1&&key[K]!=x) {
		K=(K==Mo-1?0:K+1);
		if (K==b) {
			printf("Not Find!!\n");
			return -1;
		}
	}
	if (key[K]==-1) {
		printf("Not Find!!\n");
		return -1;
	}
	else {
		printf("Delete success!!\n");
		tot--,key[K]=element[K]=-1;
		return 1;
	}
}
