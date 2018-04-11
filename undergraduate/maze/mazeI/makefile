lxmaze : main.o maze.o
	g++ -std=c++14 -O2 -Wall -o lxmaze main.o maze.o
main.o : main.cpp maze.h
	g++ -std=c++14 -O2 -c -Idir main.cpp
maze.o : maze.cpp maze.h
	g++ -std=c++14 -O2 -c -Idir maze.cpp