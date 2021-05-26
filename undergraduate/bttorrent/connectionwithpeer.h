#ifndef __CONNECTIONWITHPEER_H__
#define __CONNECTIONWITHPEER_H__

#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <cstdio>
#include <cstring>
#include <vector>
#include <string>

#define unchar unsigned char
#define unint unsigned int

const int commonsize=2*1024*1024;
const char myprotocol[]="BitTorrent protocol";
const unchar myextend[]={0u,0u,0u,0u,0u,0u,0u,0u};
const char * const connectionstatus[]={
"start new connection",
"send handshake",
"receive handshake",
"send bitfield",
"receive bitfield",
"send interesting and wait unchoking",
"start exchange pieces",
"connection end in normal",
"unexpected error"
};

struct Wevent{
	bool loadflag=0;
	//have load to write buffer
	int length,nowsize=0;
	std::vector<unint> value,size;
	Wevent *prev=NULL,*next=NULL;

	Wevent(int len):length(len){
		value.clear(),size.clear();
	}
};

class connectionwp{
	private:
		int status;
		int rlength,rnowsize,rtype;
		//rtype |0x00000001 readlength
		//rtype |0x00000002 message or handshake
		Wevent *wqueue;
		int myRead(int len,unchar *buf);
		int myWrite(int len,unchar *buf);
	
	public:
		int msid,mslen,hslen;
		unchar *rbuf,*wbuf,*protocol,*peerid,*msstart,*infohashstart;
		int sockfd,am_choking,am_interested,peer_choking,peer_interested;
		connectionwp(int fd,int bufsize=commonsize);
		~connectionwp();
		bool isFinishedRead();
		bool isFinishedWrite();
		int finishRead();
		int finishWrite();
		
		int nowStatus();
		int setStatus(int value);
		int readPacket();
		int parsePacket();
		int insertWriteWaitQueue(Wevent *we);
		int cancelWaitEvent(int pieceid,int begin,int len);

		int keepAlive();
		int setChoke(bool flag);
		int setInterested(bool flag);
		int handshake(unchar infohash[20],unchar peerid[20]);
		int bitfield(int len,bool bit[]);
		int have(int pieceid);
		int request(int pieceid,int begin,int len);
		int piece(int pieceid,int begin,int len,unchar buf[]);
		int cancel(int pieceid,int begin,int len);
		int port(int listenport);

};

#endif

