#ifndef SCENE_H
#define SCENE_H

#include <cstdio>
#include <iostream>
#include "lxhash.h"



class Scene{
private:
	long long m;
	int n,tot,p,base;
	char s[100];
	FILE *fp;
	struct Data{
		long long PhoneNumber;
		char name[100];
		bool flag;
	}*A;
public:
	Scene(int M);
	~Scene();
	void ShowData();
	int change(char a[]);
	int Modify(int p);
	int work(char a[],hash *phone=NULL,hash *name=NULL);
};

#endif
