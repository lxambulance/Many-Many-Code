all:lxclient lxserver test1 test2 test3
	
lxserver:trackerservice.o bencode.o
	g++ $^ -o $@
lxclient:p2psystem.o bencode.o SHA1.o connectionwithpeer.o
	g++ $^ -o $@ -std=c++11
test1:bencodetest.o bencode.o
	g++ $^ -o $@
test2:SHA1test.o SHA1.o
	g++ $^ -o $@
test3:connectiontest.o connectionwithpeer.o
	g++ $^ -o $@ -std=c++11
trackerservice.o:trackerservice.cpp
	g++ -c $^ -o $@ -std=c++11
p2psystem.o:p2psystem.cpp
	g++ -c $^ -o $@ -std=c++11
bencodetest.o:bencodetest.cpp
	g++ -c $^ -o $@
bencode.o:bencode.c
	g++ -c $^ -o $@
SHA1test.o:SHA1test.c
	g++ -c $^ -o $@
SHA1.o:SHA1.c
	g++ -c $^ -o $@
connectionwithpeer.o:connectionwithpeer.cpp
	g++ -c $^ -o $@ -std=c++11
connectiontest.o:connectiontest.cpp
	g++ -c $^ -o $@ -std=c++11

clean:
	rm -rf *.o
	rm -rf lxclient lxserver test1 test2 test3
