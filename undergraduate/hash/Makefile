LxPhoneNumberCheckSystem : main.o lxhash.o Scene.o
	g++ -std=c++11 -O2 -Wall -o LxPhoneNumberCheckSystem lxhash.o Scene.o main.o
main.o : main.cpp lxhash.h scene.h
	g++ -std=c++11 -O2 -c -Idir main.cpp
lxhash.o : lxhash.cpp lxhash.h
	g++ -std=c++11 -O2 -c -Idir lxhash.cpp
Scene.o : Scene.cpp Scene.h
	g++ -std=c++11 -O2 -c -Idir Scene.cpp