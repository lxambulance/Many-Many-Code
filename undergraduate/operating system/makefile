testShell:main.cpp ProcessManager.o ProcessControlBlock.o ResourceManager.o
	g++ main.cpp ProcessManager.o ProcessControlBlock.o ResourceManager.o -std=c++11 -o testShell
ProcessManager.o:ProcessManager.cpp ProcessManager.h ProcessControlBlock.h ResourceManager.h
	g++ -c ProcessManager.cpp -std=c++11
ProcessControlBlock.o:ProcessControlBlock.cpp ProcessControlBlock.h
	g++ -c ProcessControlBlock.cpp -std=c++11
ResourceManager.o:ResourceManager.cpp ResourceManager.h
	g++ -c ResourceManager.cpp -std=c++11

clear:
	rm -rf *.o
