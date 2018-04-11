#ifndef MAZE_H
#define MAZE_H

class Maze{
private:
	int n,m;
	int ***a,**b,*f,*g;
	int d[4][2]={{1,0},{0,1},{-1,0},{0,-1}};//下右上左
	int ask(int x);
	int bfs(); //1 mean find pass!
public:
	Maze(int x=10,int y=10);
	~Maze();
	void autoMake();
	void showMeTheMap();
	void showMeThePass();
	void saveMap(char x[]);
	int loadMapFrom(char x[]); //-1 mean open failed, -2 mean data invalid!
};

#endif
