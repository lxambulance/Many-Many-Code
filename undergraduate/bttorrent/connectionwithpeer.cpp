#include "connectionwithpeer.h"

connectionwp::connectionwp(int fd,int bufsize){
	status=0;
	sockfd=fd;
	am_choking=peer_choking=1;
	am_interested=peer_interested=0;

	rbuf=new unchar [bufsize];
	wbuf=new unchar [bufsize];
	rlength=rnowsize=rtype=0;
	wqueue=NULL;
	
	msid=mslen=hslen=0;
	peerid=protocol=msstart=infohashstart=NULL;
}

connectionwp::~connectionwp(){
	delete [] rbuf;
	delete [] wbuf;
	delete [] peerid;
	delete [] protocol;
	while (wqueue!=NULL) {
		Wevent *next=wqueue->next;
		if (next==wqueue) {
			delete wqueue;
			wqueue=NULL;
		}
		else {
			wqueue->prev->next=next;
			next->prev=wqueue->prev;
			delete wqueue;
			wqueue=next;
		}
	}
}

int connectionwp::myRead(int len,unchar *buf){
	int readnum=recv(sockfd,buf,len,MSG_DONTWAIT);
	if (readnum>0) return readnum;
	if (readnum<0 && (errno==EINTR||errno==EWOULDBLOCK||errno==EAGAIN)) return 0;
	perror("read failed");
	return -1;
}

int connectionwp::myWrite(int len,unchar *buf){
	int writenum=send(sockfd,buf,len,MSG_DONTWAIT);
	if (writenum>0) return writenum;
	if (writenum<0 && (errno==EINTR||errno==EWOULDBLOCK||errno==EAGAIN)) return 0;
	perror("write failed");
	return -1;
}

bool connectionwp::isFinishedRead(){
	return rlength==0;
}

bool connectionwp::isFinishedWrite(){
	return wqueue==NULL;
}

int connectionwp::finishRead(){
	int ret=myRead(rlength-rnowsize,rbuf+rnowsize);
	if (ret<0) return -1;
	rnowsize+=ret;
	if (rnowsize==rlength) {
		if (rtype&1) parsePacket();
		else {
			rtype|=1;
			int x=((rtype&2)?48+rbuf[0]:ntohl(*((unint *)rbuf)));
			if (x==0) parsePacket();
			rlength+=x;
		}
	}
	return 0;
}

int connectionwp::finishWrite(){
	if (!wqueue->loadflag) {
		wqueue->loadflag=1;
		int nowpos=0;
		for (int i=0;i < wqueue->value.size();++i) {
			if (wqueue->size[i]==1) {
				wbuf[nowpos]=wqueue->value[i];
				nowpos++;
			}
			else if (wqueue->size[i]==2) {
				*((unsigned short *)(wbuf+nowpos))=htons(wqueue->value[i]);
				nowpos+=2;
			}
			else if (wqueue->size[i]==4) {
				*((unint *)(wbuf+nowpos))=htonl(wqueue->value[i]);
				nowpos+=4;
			}
			else {
				return -1;
			}
		}
	}
	int ret=myWrite(wqueue->length - wqueue->nowsize,wbuf+wqueue->nowsize);
	if (ret<0) return -1;
	wqueue->nowsize+=ret;
	if (wqueue->nowsize == wqueue->length) {
		if (wqueue->next==wqueue) {
			delete wqueue;
			wqueue=NULL;
		}
		else {
			Wevent *next=wqueue->next;
			wqueue->prev->next=next;
			next->prev=wqueue->prev;
			delete wqueue;
			wqueue=next;
			finishWrite();
		}
	}
	return 0;
}

int connectionwp::nowStatus(){
	return status;
}

int connectionwp::setStatus(int value){
	status=value;
	return 0;
}

int connectionwp::readPacket(){
	rlength=(status==1?1:4);
	rnowsize=0;
	rtype=((status==1)<<1);
	return 0;
}

int connectionwp::parsePacket(){
	mslen=hslen=0;
	if (!(rtype&2)) {
		mslen=ntohl(*((unint *)rbuf));
		msid=(mslen==0?-1:rbuf[4]);
		msstart=rbuf+5;
	}
	else {
		hslen=rbuf[0];
		protocol=new unchar[9];
		peerid=new unchar[21];
		protocol[8]=peerid[20]=0;
		memcpy(protocol,rbuf+hslen+1,8);
		memcpy(peerid,rbuf+hslen+29,20);
		infohashstart=rbuf+hslen+9;
	}
	rlength=rnowsize=rtype=0;
	return 0;
}

int connectionwp::insertWriteWaitQueue(Wevent *we){
	if (wqueue==NULL) {
		wqueue=we->prev=we->next=we;
	}
	else {
		we->prev=wqueue->prev;
		we->next=wqueue;
		wqueue->prev->next=we;
		wqueue->prev=we;
	}
	return 0;
}

int connectionwp::cancelWaitEvent(int pieceid,int begin,int len){
	if (wqueue!=NULL) {
		bool flag=false;
		Wevent *tmp=wqueue;
		do{
			if (tmp->length == 13+len && tmp->value[0] == 9+len && tmp->value[1] == 7 && tmp->value[2] == pieceid && tmp->value[3] == begin) {
				flag=true;
				break;
			}
			tmp=tmp->next;
		}while(tmp!=wqueue);
		if (flag) {
			if (wqueue==wqueue->next) {
				delete wqueue;
				wqueue=NULL;
			}
			else {
				if (wqueue==tmp) wqueue=wqueue->next;
				tmp->prev->next=tmp->next;
				tmp->next->prev=tmp->prev;
				delete tmp;
				tmp=NULL;
			}
		}
	}
}

int connectionwp::handshake(unchar infohash[20],unchar peerid[20]){
	Wevent *we=new Wevent(68);
	we->value.push_back(19),we->size.push_back(1);
	for (int i=0;i<19;++i)
		we->value.push_back(myprotocol[i]),we->size.push_back(1);
	for (int i=0;i<8;++i)
		we->value.push_back(myextend[i]),we->size.push_back(1);
	for (int i=0;i<20;++i)
		we->value.push_back(infohash[i]),we->size.push_back(1);
	for (int i=0;i<20;++i)
		we->value.push_back(peerid[i]),we->size.push_back(1);
	insertWriteWaitQueue(we);
	return 0;
}

int connectionwp::keepAlive(){
	Wevent *we=new Wevent(4);
	we->value.push_back(0),we->size.push_back(4);
	insertWriteWaitQueue(we);
	return 0;
}

int connectionwp::setChoke(bool flag){
	am_choking=flag;
	Wevent *we=new Wevent(5);
	we->value.push_back(1),we->size.push_back(4);
	we->value.push_back(!flag),we->size.push_back(1);
	insertWriteWaitQueue(we);
	return 0;
}

int connectionwp::setInterested(bool flag){
	am_interested=flag;
	Wevent *we=new Wevent(5);
	we->value.push_back(1),we->size.push_back(4);
	we->value.push_back((!flag)|2),we->size.push_back(1);
	insertWriteWaitQueue(we);
	return 0;
}

int connectionwp::have(int pieceid){
	Wevent *we=new Wevent(9);
	we->value.push_back(5),we->size.push_back(4);
	we->value.push_back(4),we->size.push_back(1);
	we->value.push_back(pieceid),we->size.push_back(4);
	insertWriteWaitQueue(we);
	return 0;
}

int connectionwp::bitfield(int len,bool bit[]){
	int blen=(len+7)/8,rem=blen*8-len;
	Wevent *we=new Wevent(blen+5);
	we->value.push_back(blen+1),we->size.push_back(4);
	we->value.push_back(5),we->size.push_back(1);
	unchar now=0;
	for (int i=0;i<len;++i) {
		now=((now<<1)|bit[i]);
		if (i%8==7) {
			we->value.push_back(now),we->size.push_back(1);
			now=0;
		}
	}
	if (rem) {
		now<<=rem;
		we->value.push_back(now),we->size.push_back(1);
	}
	insertWriteWaitQueue(we);
	return 0;
}

int connectionwp::request(int pieceid,int begin,int len){
	Wevent *we=new Wevent(17);
	we->value.push_back(13),we->size.push_back(4);
	we->value.push_back(6),we->size.push_back(1);
	we->value.push_back(pieceid),we->size.push_back(4);
	we->value.push_back(begin),we->size.push_back(4);
	we->value.push_back(len),we->size.push_back(4);
	insertWriteWaitQueue(we);
	return 0;
}

int connectionwp::piece(int pieceid,int begin,int len,unchar buf[]){
	Wevent *we=new Wevent(13+len);
	we->value.push_back(9+len),we->size.push_back(4);
	we->value.push_back(7),we->size.push_back(1);
	we->value.push_back(pieceid),we->size.push_back(4);
	we->value.push_back(begin),we->size.push_back(4);
	for (int i=0;i<len;++i)
		we->value.push_back(buf[i]),we->size.push_back(1);
	insertWriteWaitQueue(we);
	return 0;
}

int connectionwp::cancel(int pieceid,int begin,int len){
	Wevent *we=new Wevent(17);
	we->value.push_back(13),we->size.push_back(4);
	we->value.push_back(8),we->size.push_back(1);
	we->value.push_back(pieceid),we->size.push_back(4);
	we->value.push_back(begin),we->size.push_back(4);
	we->value.push_back(len),we->size.push_back(4);
	insertWriteWaitQueue(we);
	return 0;
}

int connectionwp::port(int listenport){
	return 0;
}

