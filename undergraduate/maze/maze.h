#ifndef MAZE_H
#define MAZE_H

class Maze{
private:
	int n,m,**a;
public:
	Maze(int x=10,int y=10);
	~Maze();
	void AutoMake();
	void ShowMeTheMap();
	void ShowMeThePass();
	void ReloadMap(int x=10,int y=10);
};

#endif
