#include <ctime>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdarg.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "SHA1.h"
#include "bencode.h"
#include "connectionwithpeer.h"

#define HTTP_GET "GET /announce?info_hash=%s&peer_id=%s&port=%s&"\
"uploaded=0&downloaded=%lld&left=%lld&event=started&compact=1 "\
"HTTP/1.1\r\nHost: %s:%s\r\nAccept: */*\r\nConnection: Close\r\n\r\n"

char *hostip;
int portbase=0;
char serviceport[]="6881";
char buf[3000];
char server[255],servport[15],filename[300];
unchar mateinfobuf[1024*1024*2],piecebuf[1024*1024*2];
connectionwp *con[100];
int request[40000],request2[40000];
bool bitField[40000]; //isDownloaded
int bitFlag[40000],order[40000],windowleft,windowright;
int piecenum,downloadpiecenum;
long int filelength;
long int piecelength,blocklength=(1<<14),blocknum;
const char *piecestart;
bencode_t mateben,bentmp,infoben;
const char *infostart;
int infolen;
unchar infohash[20],peerid[20];
char info_hash[100],peer_id[100];
int contentstart,contentlen;
int peerNum;
bool peerOK[100];
unint peerIP[100],peerPort[100];

int parseMateinfo(char *filename);
int getPieceLen();
int calcInfohash();
int httptrackerSocketCreate(int &sd);
int parseHttpResponse();

int httptrackerSend(int fd,char *buff,int size);
int httptrackerRecv(int fd,char *buff,int size);

int bitFieldReload(unchar *infohash);
int bitFieldSave(unchar *infohash);

int pieceOpen(int pid);
int pieceClose(int pid);
bool pieceCheck(int pid);

int peerSocketCreate(unint peerip,unint peerport);
int checkPeerConnect(int &maxfd,fd_set &base,int timelimit=10,int sec=5);

int errexit(const char *format,...);
int connectTCP(const char *host,const char *service);
int connectsock(const char *host,const char *service,const char *transport);
int passiveTCP(const char *service,int qlen);
int passivesock(const char*service,const char*transport,int qlen);
int getHomepageandTorrent(const char *host, const char *service);

int main(int argc,char *argv[]){
	if (access("./.lxtmp",0))
		if (mkdir("./.lxtmp",0777))
			fprintf(stderr,"mkdir failed\n");
	else
		fprintf(stdout,"file .lxtmp already exist\n");
	//printf("argc=%d\n",argc);
	//for (int i=0;i<argc;++i) printf("argv[%d]=%s\n",i,argv[i]);
	if (argc>=2) {
		if (argc!=3||argv[1][0]!='-'||argv[1][1]<'a'||argv[1][1]>'c') {
			fprintf(stderr,"Please use format: %s -a file_name|-b file_name|-c ip:port\n",argv[0]);
			return 0;
		}
		else {
			if (argv[1][1]=='a') {
				fprintf(stdout,"mode a. download data.\n");
				FILE *f=fopen(argv[2],"r");
				if (f==NULL) {
					fprintf(stderr,"file[%s] don't exist\n",argv[2]);
					return 0;
				}
				fclose(f);
			}
			else if (argv[1][1]=='b') {
				fprintf(stdout,"mode b. make torrent.\n");
				FILE *f=fopen(argv[2],"rb");
				if (f==NULL) {
					fprintf(stderr,"file[%s] don't exist\n",argv[2]);
					return 0;
				}
				
				struct stat statbuf;
				stat(argv[2],&statbuf);
				long long size=statbuf.st_size;
				fprintf(stdout,"file size = %lld Bytes\n",size);
				piecelength=(size>=64*1024*1024?(1<<20):(1<<18));
				
				b_element *top=NULL,*tmp1=NULL,*tmp2=NULL;
				new_dic(&top);
				new_str(&tmp1,(char *)"name",4),new_str(&tmp2,argv[2],strlen(argv[2]));
				dic_add(top,tmp1,tmp2);
				new_str(&tmp1,(char *)"length",6),new_int(&tmp2,size);
				dic_add(top,tmp1,tmp2);
				new_str(&tmp1,(char *)"piece length",12),new_int(&tmp2,piecelength);
				dic_add(top,tmp1,tmp2);
				
				int piecen=0;
				piecestart=(const char *)mateinfobuf;
				while (size) {
					int realnum=fread(piecebuf,sizeof(unchar),piecelength,f);
					//fprintf(stdout,"piece[%d] %d\n",piecen,realnum);
					
					SHA1Context sha;
					uint8_t Message_Digest[20];
					int err;

					err=SHA1Reset(&sha);
					err=SHA1Input(&sha,(const unchar *)piecebuf,realnum);
					err=SHA1Result(&sha,Message_Digest);
					
					memcpy(mateinfobuf+piecen*20,Message_Digest,20);
					if (realnum!=piecelength) {
						for (int i=0;i<piecelength-realnum;++i)
							piecebuf[realnum+i]=0;
					}
					//fprintf(stdout,"calc hash ok!\n");
					pieceClose(piecen);
					request2[piecen]=(1ll<<31)-1;
					piecen++,size-=realnum;
				}
				piecenum=piecen;
				fclose(f);
				fprintf(stdout,"piecenum = %d\n",piecen);
				fprintf(stdout,"cut into pieces and calculate piece hash ok!\n");
				
				new_str(&tmp1,(char *)"pieces",6),new_str(&tmp2,(char *)mateinfobuf,piecen*20);
				dic_add(top,tmp1,tmp2);
				
				b_element_init();
				b_element_show_notdel(top);
				
				SHA1Context sha;
				uint8_t Message_Digest[20];
				int err;
				err=SHA1Reset(&sha);
				err=SHA1Input(&sha,(const unchar *)be_buf,be_now);
				err=SHA1Result(&sha,Message_Digest);
				fprintf(stdout,"get infohash:");
				for (int i=0;i<20;++i) fprintf(stdout,"%02x",Message_Digest[i]);
				fprintf(stdout,"\n");
				bitFieldSave((unchar *)Message_Digest);
				
				b_element *tmp3=top;
				new_dic(&top);
				int len;
				char trackername[100]="http://";
				fprintf(stdout,"Please input http tracker ip&port(*.*.*.*:*):\n");
				while (1) {
					len=7;
					char ch; fscanf(stdin,"%c",&ch);
					while (ch!='\n') trackername[len++]=ch,fscanf(stdin,"%c",&ch);
					int count1=0,count2=0;
					for (int i=7;i<len;++i) {
						if (trackername[i]==':') count2++;
						if (trackername[i]=='.') count1++;
					}
					if (count1&&count2==1) break;
					fprintf(stdout,"Please try again.\n");
				}
				memcpy(trackername+len,"/announce",9),len+=9;
				new_str(&tmp1,(char *)"announce",8),new_str(&tmp2,trackername,len);
				dic_add(top,tmp1,tmp2);
				new_str(&tmp1,(char *)"created by",10),new_str(&tmp2,(char *)"lxclientV1.0",12);
				dic_add(top,tmp1,tmp2);
				new_str(&tmp1,(char *)"encoding",8),new_str(&tmp2,(char *)"utf-8",5);
				dic_add(top,tmp1,tmp2);
				new_str(&tmp1,(char *)"info",4);
				dic_add(top,tmp1,tmp3);
				b_element_init();
				b_element_show(top);
				
				len=strlen(argv[2]);
				memcpy(filename,argv[2],len);
				memcpy(filename+len,(char *)".torrent",8);
				len+=8;
				filename[len]=0;
				f=fopen(filename,"wb");
				fwrite(be_buf,sizeof(char),be_now,f);
				fclose(f);
				
				return 0;
			}
			else if (argv[1][1]=='c') {
				fprintf(stdout,"mode c. get torrent.\n");
				int len=strlen(argv[2]);
				memcpy(buf,argv[2],len);
				int start=0;
				for (int i=0;i<len;++i) {
					if (buf[i]==':') {
						start=i;
						break;
					}
				}
				if (start==0) {
					fprintf(stderr,"port don't exist\n");
					return 0;
				}
				buf[start]=buf[len+1]=0;
				getHomepageandTorrent(buf,buf+start+1);
				return 0;
			}
		}
	}
	else {
		fprintf(stderr,"Please choose mode: %s -a|-b|-c\n",argv[0]);
		return 0;
	}
/*---------------parse torrent----------------*/
	parseMateinfo(argv[2]);
	getPieceLen();
	calcInfohash();
	bitFieldReload(infohash);
	
	int sd=-1,ret;
	if (downloadpiecenum!=piecenum) {
		ret=httptrackerSocketCreate(sd);
		if (ret) return 0;
/*---------conmunicate with tracker-----------*/
		sprintf(buf,HTTP_GET,info_hash,peer_id,serviceport,((long long)downloadpiecenum)*piecelength,(long long)filelength,hostip,servport);
		fprintf(stdout,"%s\n",buf);
		if (httptrackerSend(sd,buf,strlen(buf))<0) {
			fprintf(stderr,"http send() error");
			return -1;
		}
		FILE *f=fopen("lx.out","wb");
		int recvnum=recv(sd,buf,2048,0);
		fprintf(stdout,"http response receive length = %d\n",recvnum);
		for (int i=0;i<recvnum;++i) printf("%c",buf[i]);
		fwrite(buf,sizeof(char),recvnum,f);
		fclose(f);
		close(sd);
		
		parseHttpResponse();
	}
/*----------communicate with peers------------*/
	srand(time(0));
	memset(bitFlag,0,sizeof(bitFlag));
	windowleft=windowright=0;
	for (int i=0;i<piecenum;++i) order[i]=i;
	std::random_shuffle(order,order+piecenum);
	
	timeval tv;
	fd_set rfds,wfds,efds,base;
	FD_ZERO(&base);
	
	int sockfd,maxsock=0,conNum=0,delNum=0;
	if (downloadpiecenum!=piecenum) {
		peerNum=std::min(peerNum,30);
		for (int i=0;i<peerNum;++i) {
			sockfd=peerSocketCreate(peerIP[i],peerPort[i]);
			if (sockfd<0) continue;
			FD_SET(sockfd,&base);
			maxsock=std::max(maxsock,sockfd);
		}
		
		checkPeerConnect(maxsock,base);
		
		if (maxsock==0) {
			fprintf(stdout,"not find a valid peer\n");
			return -1;
		}
		else {
			fprintf(stdout,"find at least a sockfd");
			for (int i=0;i<=maxsock;++i)
			if (FD_ISSET(i,&base)) {
				fprintf(stdout,"%d,",i);
				con[conNum]=new connectionwp(i);
				conNum++;
			}
			fprintf(stdout,"\n");
		}
	}
	
	serviceport[3]='0'+rand()%10;
	int msock=passiveTCP(serviceport,32);
	int flags=fcntl(msock,F_GETFL,0);
	fcntl(msock,F_SETFL,flags|O_NONBLOCK);
	FD_SET(msock,&base);
	fprintf(stdout,"listen port[%s] is ok!\n",serviceport);
	
	while (1) {
		maxsock=msock;
		for (int i=0;i<conNum;++i) 
			maxsock=std::max(maxsock,con[i]->sockfd);
		
		fflush(stdout);
		fflush(stderr);
		//initial
		rfds=wfds=base;
		int ret=0;

		//write
		tv={1,0};
		ret=select(maxsock+1,NULL,&wfds,NULL,&tv);
		if (ret<0) {
			fprintf(stderr,"select error in write\n");
			break;
		}
		for (int i=0;i<conNum;++i)
		if (FD_ISSET(con[i]->sockfd,&wfds)) {
			if (!con[i]->isFinishedWrite()) {
				ret=con[i]->finishWrite();
			}
			else {
				int status=con[i]->nowStatus();
				if (status==0) {
					ret=con[i]->handshake(infohash,peerid);
					con[i]->setStatus(1);
				}
				else if (status==2) {
					ret=con[i]->bitfield(piecenum,bitField);
					con[i]->setStatus(3);
				}
				else if (status==4) {
					//something to check
					ret=con[i]->setInterested(1);
					con[i]->setStatus(5);
				}
				else if (status==6) {
					bool flag=false;
					if (!con[i]->peer_choking && con[i]->am_interested) {
						while (windowright<piecenum && bitField[order[windowright]]) windowright++;
						while (windowleft<windowright && bitField[order[windowleft]]) windowleft++;
						if (windowright<piecenum && windowleft+5 > windowright) {
							windowright++;
						}
						for (int j=windowright-1;j>=windowleft;--j)
						if (!bitField[order[j]] && ((bitFlag[order[j]]>>i)&1)) {
							int pl=(order[j]==piecenum-1?filelength-piecelength*order[j]:piecelength),bn=(order[j]==piecenum-1?(pl+blocklength-1)/blocklength:blocknum);
							for (int k=0;k<bn;++k)
							if (!((request[order[j]]>>k)&1)) {
								int len=(k==bn-1?pl-blocklength*k:blocklength);
								//fprintf(stdout,"ask socket[%d] piece[%d.%d] len=%d\n",con[i]->sockfd,order[j],k,len);
								flag=true;
								ret=con[i]->request(order[j],k*blocklength,len);
								if (!ret) request[order[j]]|=(1<<k);
								break;
							}
							break;
						}
					}
					if (!flag && rand()%100<20) {
						for (int j=windowright-1;j>=windowleft;--j)
						if (!bitField[order[j]] && ((bitFlag[order[j]]>>i)&1)) {
							int pl=(order[j]==piecenum-1?filelength-piecelength*order[j]:piecelength),bn=(order[j]==piecenum-1?(pl+blocklength-1)/blocklength:blocknum);
							for (int k=0;k<bn;++k)
							if (!((request2[order[j]]>>k)&1)) {
								int len=(k==bn-1?pl-blocklength*k:blocklength);
								//fprintf(stdout,"ask socket[%d] piece[%d.%d] len=%d\n",con[i]->sockfd,order[j],k,len);
								flag=true;
								ret=con[i]->request(order[j],k*blocklength,len);
								if (!ret) request[order[j]]|=(1<<k);
								break;
							}
							break;
						}
					}
					if (!flag && rand()%100<10) ret=con[i]->keepAlive();
				}
			}
			if (ret<0) {
				fprintf(stderr,"connection[%d] error in write\n",con[i]->sockfd);
				FD_CLR(con[i]->sockfd,&base);
				delNum++;
			}
		}

		//read
		tv={2,0};
		FD_SET(0,&rfds);//keyboard input
		ret=select(maxsock+1,&rfds,NULL,NULL,&tv);
		if (ret<0) {
			fprintf(stderr,"select error in read\n");
			break;
		}
		if (FD_ISSET(0,&rfds)) {
			char ch;
			fscanf(stdin,"%c",&ch);
			if (ch=='q') {
				bitFieldSave(infohash);
				break;
			}
		}
		if (FD_ISSET(msock,&rfds)) {
			fprintf(stdout,"find a new connection\n");
			struct sockaddr_in fsin;
			unsigned int len=sizeof(fsin);
			int ssock=accept(msock,(struct sockaddr *)&fsin,&len);
			if (ssock<0)
				fprintf(stderr,"accept: %s\n",strerror(errno));
			else {
				FD_SET(ssock,&base);
				con[conNum++]=new connectionwp(ssock);
				fprintf(stdout,"new connection create\n");
			}
		}
		for (int i=0;i<conNum;++i)
		if (FD_ISSET(con[i]->sockfd,&rfds)) {
			if (!con[i]->isFinishedRead())
				ret=con[i]->finishRead();
			else
				ret=con[i]->readPacket();
			if (ret<0) {
				fprintf(stderr,"connection[%d] error in read1\n",con[i]->sockfd);
				FD_CLR(con[i]->sockfd,&base);
				delNum++;
				continue;
			}
			if (con[i]->mslen) {
				int msid=con[i]->msid,mslen=con[i]->mslen-1;
				//fprintf(stdout,"sock[%d] get a message[%d](%d).\n",con[i]->sockfd,msid,mslen);
				if (msid==0||msid==1) {
					con[i]->peer_choking=(!msid);
					if (msid) con[i]->setStatus(6);
					else con[i]->setStatus(5);
				}
				else if (msid==2||msid==3) {
					con[i]->peer_interested=(!(msid&1));
					if (con[i]->peer_interested) con[i]->setChoke(0);
				}
				else if (msid==4) {
					int pieceid=ntohl(*((unint *)con[i]->msstart));
					bitFlag[pieceid]|=(1<<i);
				}
				else if (msid==5) {
					int count=piecenum;
					for (int j=0;j<mslen;++j) {
						unchar x=con[i]->msstart[j];
						for (int k=0;k<8;++k)
						if ((x>>(7-k))&1)
							bitFlag[j*8+k]|=(1<<i);
						else
							bitFlag[j*8+k]&=(1<<conNum)-1-(1<<i);
					}
					con[i]->setStatus(4);
					//fprintf(stdout,"sock[%d] piece[1590] %d\n",con[i]->sockfd,(((bitFlag[1590])>>i)&1));
				}
				else if (msid==6) {
					int pieceid=ntohl(*((unint *)con[i]->msstart));
					int begin=ntohl(*(unint *)(con[i]->msstart+4));
					int len=ntohl(*(unint *)(con[i]->msstart+8));
					if (bitField[pieceid]) {
						ret=pieceOpen(pieceid);
						ret=con[i]->piece(pieceid,begin,len,piecebuf+begin);
						fprintf(stdout,"sock[%d] need piece[%d]%d\n",con[i]->sockfd,pieceid,len);
					}
				}
				else if (msid==7) {
					int pieceid=ntohl(*((unint *)con[i]->msstart));
					int begin=ntohl(*((unint *)(con[i]->msstart+4)));
					//fprintf(stdout,"sock[%d] get message[7]<piece> pieceid=%d,begin=%d,len=%d piecestatus=%d %d\n",con[i]->sockfd,pieceid,begin,mslen-8,request[pieceid],request2[pieceid]);
					if (!bitField[pieceid]) {
						ret=pieceOpen(pieceid);
						memcpy(piecebuf+begin,con[i]->msstart+8,mslen-8);
						request2[pieceid]|=(1<<(begin/blocklength));
						int full=(pieceid==piecenum-1?(1<<((filelength-pieceid*piecelength+blocklength-1)/blocklength)):(1<<blocknum))-1;
						//fprintf(stdout,"pieceid[%d] %d\n",pieceid,full);
						if (request2[pieceid]==full) {
							if (!pieceCheck(pieceid)) {
								request[pieceid]=request2[pieceid]=0;
							}
							else {
								bitField[pieceid]=1;
								downloadpiecenum++;
								while (windowleft<windowright && bitField[order[windowleft]]) windowleft++;
								for (int j=0;j<conNum;++j)
								if (i!=j&&FD_ISSET(con[j]->sockfd,&base)) {
									con[j]->have(pieceid);
									con[j]->cancel(pieceid,begin,mslen-8);
								}
								fprintf(stdout,"download piece[%d] ok! pieces download (%d/%d) del/con(%d/%d) window[%d,%d]\n",pieceid,downloadpiecenum,piecenum,delNum,conNum,windowleft,windowright);
								if (downloadpiecenum==piecenum) {
									bitFieldSave(infohash);
									goto endwhile;
								}
								if (downloadpiecenum%50==0) bitFieldSave(infohash);
							}
						}
						ret=pieceClose(pieceid);
					}
				}
				else if (msid==8) {
					int pieceid=ntohl(*((unint *)con[i]->msstart));
					int begin=ntohl(*(unint *)(con[i]->msstart+4));
					int len=ntohl(*(unint *)(con[i]->msstart+8));
					ret=con[i]->cancelWaitEvent(pieceid,begin,len);
				}
				else {
				}
				con[i]->mslen=0;
			}
			else if (con[i]->hslen) {
				bool flag=true;
				for (int j=0;j<20;++j)
				if (infohash[j]!=con[i]->infohashstart[j]) {
					flag=false;
					break;
				}
				if (!flag) {
					fprintf(stderr,"connection[%d] header wrong\n",con[i]->sockfd);
					FD_CLR(con[i]->sockfd,&base),delNum++;
				}
				else con[i]->setStatus(2);
				con[i]->hslen=0;
			}
			if (ret<0) {
				fprintf(stderr,"connection[%d] error in read2\n",con[i]->sockfd);
				FD_CLR(con[i]->sockfd,&base);
				delNum++;
			}
		}
		
		//show
		/*
		for (int i=0;i<conNum;++i)
		if (FD_ISSET(con[i]->sockfd,&base)) {
			printf("sockfd=%d status=%s\n",con[i]->sockfd,connectionstatus[con[i]->nowStatus()]);
		}
		//fprintf(stdout,"pieces download (%d/%d) window[%d %d] conNum/delNum(%d/%d)\n",downloadpiecenum,piecenum,windowleft,windowright,conNum,delNum);
		*/
		//delete
		if (downloadpiecenum!=piecenum)
		if (delNum==conNum&&conNum>0||conNum>30) {
			for (int i=0;i<conNum;++i) {
				close(con[i]->sockfd);
				delete con[i];
			}
			delNum=conNum=0;
			fprintf(stdout,"reconnection start\n");
			int newmax=0;
			FD_ZERO(&base);
			for (int i=0;i<peerNum;++i) {
				sockfd=peerSocketCreate(peerIP[i],peerPort[i]);
				if (sockfd<0) continue;
				FD_SET(sockfd,&base);
				newmax=std::max(newmax,sockfd);
			}
			checkPeerConnect(newmax,base);
			if (!newmax) {
				fprintf(stderr,"no peers now\n");
				break;
			}
			fprintf(stdout,"reconnect some socket\n");
			for (int i=0;i<=newmax;++i)
			if (FD_ISSET(i,&base)) con[conNum++]=new connectionwp(i);
			for (int i=0;i<piecenum;++i)
				request[i]=request2[i],bitFlag[i]=0;
			fprintf(stdout,"pieces download (%d/%d) con/del(%d/%d) window[%d,%d]\n",downloadpiecenum,piecenum,conNum,delNum,windowleft,windowright);
		}
	}

/*-------------save tmp and file--------------*/
endwhile:
	close(msock);
	if (downloadpiecenum==piecenum) {
		FILE *downloadFile=fopen(filename,"wb");
		for (int i=0;i<piecenum;++i) {
			pieceOpen(i);
			int len=(i==piecenum-1?filelength-piecelength*i:piecelength);
			fwrite(piecebuf,sizeof(char),len,downloadFile);
		}
		fclose(downloadFile);
	}
	
	return 0;
}

int parseMateinfo(char *filename){
	int realnum=0;
	FILE *mateinfo=fopen(filename,"rb");
	realnum=fread(mateinfobuf,sizeof(char),100*1024,mateinfo);
	fclose(mateinfo);
	
	bencode_init(&mateben,(const char *) mateinfobuf,realnum);
	const char *key;
	int klen;
	const char *serverstart;
	int serverlen;
	while (bencode_dict_has_next(&mateben)) {
		bencode_dict_get_next(&mateben,&bentmp,&key,&klen);
		if (!strncmp(key,"announce",klen)) {
			if (bencode_is_string(&bentmp))
				bencode_string_value(&bentmp,&serverstart,&serverlen);
		}
		if (!strncmp(key,"comment",klen)) {
		}
		if (!strncmp(key,"info",klen)) {
			bencode_clone(&bentmp,&infoben);
		}
	}
	bencode_dict_get_start_and_len(&infoben,&infostart,&infolen);
	fprintf(stdout,"get infostart %c infolen %d\n",*infostart,infolen);
	if (serverstart[0]=='h'&&serverstart[1]=='t'&&serverstart[2]=='t'&&serverstart[3]=='p') {
		int p1=-1,p2=-1,p3=-1;
		for (int i=0;i<serverlen;++i) {
			if (serverstart[i]=='/'&&serverstart[i+1]=='/') p1=i+2;
			if (p1!=-1&&p2==-1&&serverstart[i]==':') p2=i+1;
			if (p2!=-1&&serverstart[i]=='/') p3=i+1;
		}
		if (p1!=-1&&p2!=-1&&p3!=-1) {
			memcpy(server,serverstart+p1,p2-p1-1);
			memcpy(servport,serverstart+p2,p3-p2-1);
			server[p2-p1-1]=servport[p3-p2-1]=0;	
			return 0;
		}
	}
	fprintf(stderr,"tracker not support\n");
	exit(1);
}

int getPieceLen(){
	const char *key;
	int klen;
	const char *filenamestart;
	int filenamelen;
	while (bencode_dict_has_next(&infoben)) {
		bencode_dict_get_next(&infoben,&bentmp,&key,&klen);
		if (!strncmp(key,"name",klen)) {
			if (bencode_is_string(&bentmp))
				bencode_string_value(&bentmp,&filenamestart,&filenamelen);
		}
		if (!strncmp(key,"length",klen)) {
			if (bencode_is_int(&bentmp))
				bencode_int_value(&bentmp,&filelength);
		}
		if (!strncmp(key,"piece length",klen)) {
			if (bencode_is_int(&bentmp))
				bencode_int_value(&bentmp,&piecelength);
		}
		if (!strncmp(key,"pieces",klen)) {
			if (bencode_is_string(&bentmp))
				bencode_string_value(&bentmp,&piecestart,&piecenum);
		}
	}
	memcpy(filename,filenamestart,filenamelen);
	filename[filenamelen]=0;
	piecenum/=20,downloadpiecenum=0;
	blocklength=piecelength/16;
	blocknum=(piecelength+blocklength-1)/blocklength;
	fprintf(stdout,"get plen=%li pnum=%d filelen=%li\n",piecelength,piecenum,filelength);
}

int calcInfohash(){
	SHA1Context sha;
	uint8_t Message_Digest[20];
	int err;

	err=SHA1Reset(&sha);
	err=SHA1Input(&sha,(const unchar *)infostart,infolen);
	err=SHA1Result(&sha,Message_Digest);

	fprintf(stdout,"get infohash ");
	for (int i=0,j=0;i<20;i++) {
		unchar x=Message_Digest[i];
		fprintf(stdout,"%02x",x);
		infohash[i]=x;
		if (x>='0'&&x<='9'||x>='a'&&x<='z'||x>='A'&&x<='Z') {
			sprintf(info_hash+j,"%c",x);
			j++;
		}
		else {
			sprintf(info_hash+j,"%%%02x",x);
			j+=3;
		}
		//fprintf(stdout,"%d %d %02x\n",i,j,x);
		if (i==19) info_hash[j]=0;
	}
	fprintf(stdout,"\n");
	//fprintf(stdout,"info_hash %s\n",info_hash);
	for (int i=0;i<20;++i) peer_id[i]=peerid[i]='A'+i;
	peer_id[20]=0;
	//exit(1);
}

int httptrackerSocketCreate(int &sd){
	int rc;
	struct addrinfo hints,*res=NULL;

	memset(&hints,0x00,sizeof(hints));
	hints.ai_flags=AI_NUMERICSERV;
	hints.ai_family=AF_UNSPEC;
	hints.ai_socktype=SOCK_STREAM;
	
	rc=getaddrinfo(server,servport,&hints,&res);
	if (rc!=0) {
		fprintf(stderr,"Host not found %s\n",gai_strerror(rc));
		if (rc==EAI_SYSTEM) fprintf(stderr,"getaddrinfo() failed\n");
		return -1;
	}
	
	sd=socket(res->ai_family,res->ai_socktype,res->ai_protocol);
	if (sd<0) {
		fprintf(stderr,"httptracker socket() failed\n");
		return -1;
	}
	
	hostip=inet_ntoa(((sockaddr_in *)res->ai_addr)->sin_addr);
	fprintf(stdout,"get httptracker ip:%s\n",hostip);
	
	rc=connect(sd,res->ai_addr,res->ai_addrlen);
	if (rc<0) {
		fprintf(stderr,"httptracker connect() failed\n");
		return -1;
	}
	
	return 0;
}

int parseHttpResponse(){
	bool flag=0;
	int num;
	FILE *fr=fopen("lx.out","rb");
	num=fread(buf,sizeof(char),2048,fr);
	fclose(fr);

	for (int i=0;i<num;i++) {
		if (buf[i]=='O'&&buf[i+1]=='K') flag=1;
		if (buf[i]=='\r'&&buf[i+1]=='\n') {
			contentstart=i+2;
			break;
		}
	}
	if (!flag) {
		fprintf(stderr,"HTTP get failed\n");
		return -1;
	}
	char const * cc="Content-Length";
	while (!strncmp(buf+contentstart,cc,14)) contentstart++;
	contentstart=strchr(buf+contentstart,':')-buf+1;
	while (!isdigit(buf[contentstart])) contentstart++;
	while (isdigit(buf[contentstart])) {
		contentlen=contentlen*10+buf[contentstart]-'0';
		contentstart++;
	}
	while (buf[contentstart]=='\r'||buf[contentstart]=='\n') contentstart++;
	fprintf(stdout,"get response contentlen=%d\n",contentlen);

	bencode_t b1,b2;
	char const * rem;
	int len,strlen;
	bencode_init(&b1,buf+contentstart,contentlen);
	
	char const * str;
	long int complete=0,downloaded=0,incomplete=0,interval=0;
	while (bencode_dict_has_next(&b1)) {
		bencode_dict_get_next(&b1,&b2,&rem,&len);
		if (!strncmp(rem,"complete",len)) {
			bencode_int_value(&b2,&complete);
		}
		if (!strncmp(rem,"downloaded",len)) {
			bencode_int_value(&b2,&downloaded);
		}
		if (!strncmp(rem,"incomplete",len)) {
			bencode_int_value(&b2,&incomplete);
		}
		if (!strncmp(rem,"interval",len)) {
			bencode_int_value(&b2,&interval);
		}
		if (!strncmp(rem,"peers",len)) {
			if (bencode_is_dict(&b2)) {
			}
			else {
				int tmp;
				bencode_string_value(&b2,&str,&tmp);
				strlen=tmp;
			}
		}
	}
	//printf("%s\n%s\n",b1.start,b1.str);
	fprintf(stdout,"get complete=%li downloaded=%li incomplete=%li interval=%li\n",complete,downloaded,incomplete,interval);

	peerNum=strlen/6;
	fprintf(stdout,"get peer num:%d,peer ip:",strlen/6);
	for (int i=0;i<strlen;i+=6) {
		unchar ip[8];
		memcpy(ip,str+i,6);
		peerIP[i/6]=*((unint *)ip);
		unint IP=ntohl(peerIP[i/6]);
		fprintf(stdout,"(%d.%d.%d.%d:",IP/256/256/256,IP/256/256%256,IP/256%256,IP%256);
		peerPort[i/6]=*((unint *)(ip+4));
		fprintf(stdout,"%d)",ntohs(peerPort[i/6]));
	}
	fprintf(stdout,"\n");
	for (int i=0;i<strlen/6;++i) fprintf(stdout,"%u %u\n",peerIP[i],peerPort[i]);
	fprintf(stdout,"%d\n",strlen/6);
	
	return 0;
}

int httptrackerSend(int fd,char *buff,int size){
	int sent=0,tmpres=0;
	while (sent<size) {
		tmpres=send(fd,buff+sent,size-sent,0);
		if (tmpres<=0) return -1;
		sent+=tmpres;
	}
	return sent;
}

int httptrackerRecv(int fd,char *buff,int size){
	int rece=0,tmpres=0;
	while (rece<size) {
		tmpres=recv(fd,buff+rece,size-rece,0);
		if (tmpres<=0) return -1;
		rece+=tmpres;
	}
	return rece;
}

int bitFieldReload(unchar *infohash){
	char namebuf[55]=".";
	for (int i=0;i<20;++i) sprintf(namebuf+1+i*2,"%02x",infohash[i]);
	namebuf[41]=0;
	FILE *f=fopen(namebuf,"rb");
	if (f==NULL) {
		memset(request,0,sizeof(request));
		memset(request2,0,sizeof(request2));
		memset(bitField,0,sizeof(bitField));
		return -1;
	}
	else {
		fread(request,sizeof(int),piecenum,f);
		for (int i=0;i<piecenum;++i) {
			request2[i]=request[i];
			int full=(i==piecenum-1?(1<<((filelength-i*piecelength+blocklength-1)/blocklength)):(1<<blocknum))-1;
			request[i]&=full;
			request2[i]&=full;
			if (request[i]==full) bitField[i]=1,downloadpiecenum++;
			else {
				//fprintf(stdout,"piece[%d] not ok!\n",i);
				bitField[i]=0;
			}
		}
		fprintf(stdout,"piece(%d/%d)\n",downloadpiecenum,piecenum);
		fclose(f);
	}
	return 0;
}

int bitFieldSave(unchar *infohash){
	char namebuf[55]=".";
	for (int i=0;i<20;++i) sprintf(namebuf+1+i*2,"%02x",infohash[i]);
	namebuf[41]=0;
	FILE *f=fopen(namebuf,"wb");
	fwrite(request2,sizeof(int),piecenum,f);
	fclose(f);
	return 0;
}

int pieceOpen(int pid){
	char namebuf[55]="./.lxtmp/";
	for (int i=0;i<20;++i) {
		unchar x=*(piecestart+pid*20+i);
		sprintf(namebuf+9+i*2,"%02x",x);
	}
	namebuf[49]=0;
	FILE *f=fopen(namebuf,"rb");
	if (f==NULL)
		memset(piecebuf,0,piecelength);
	else {
		fread(piecebuf,sizeof(char),piecelength,f);
		fclose(f);
	}
}

int pieceClose(int pid){
	char namebuf[55]="./.lxtmp/";
	for (int i=0;i<20;++i) {
		unchar x=*(piecestart+pid*20+i);
		sprintf(namebuf+9+i*2,"%02x",x);
	}
	namebuf[49]=0;
	//fprintf(stdout,"%s\n",namebuf);
	FILE *f=fopen(namebuf,"wb");
	fwrite(piecebuf,sizeof(char),piecelength,f);
	fclose(f);
}

bool pieceCheck(int pid){
	SHA1Context sha;
	uint8_t Message_Digest[20];
	int err,len=(pid==piecenum-1?filelength-piecelength*pid:piecelength);

	err=SHA1Reset(&sha);
	err=SHA1Input(&sha,(const unchar *)piecebuf,len);
	err=SHA1Result(&sha,Message_Digest);

	for (int i=0;i<20;++i) {
		unchar x=*(piecestart+pid*20+i);
		if (Message_Digest[i]!=x) return false;
	}
	
	return true;
}

int peerSocketCreate(unint peerip,unint peerport){
	int ret=0,sockfd;
	struct sockaddr_in server;
	sockfd=socket(AF_INET,SOCK_STREAM|SOCK_NONBLOCK,0);

	if (sockfd==-1) {
		fprintf(stderr,"peer(%u,%u) socket() failed\n",peerip,peerport);
		close(sockfd);
		return -1;
	}
	server.sin_family=AF_INET;
	server.sin_port=peerport;
	server.sin_addr.s_addr=peerip;
	bzero(&(server.sin_zero),8);

	ret=connect(sockfd,(struct sockaddr *)& server,sizeof(struct sockaddr));

	if (ret<0 && errno!=EINPROGRESS) {
		fprintf(stderr,"peer(%u,%u) connect() failed\n",peerip,peerport);
		close(sockfd);
		return -1;
	}

	return sockfd;
}

int checkPeerConnect(int &maxfd,fd_set &base,int timelimit,int sec){
	int times=0;
	timeval tv={sec,0};
	fd_set rfd,wfd,newfd,oldfd;
	FD_ZERO(&newfd);
	oldfd=base;

nextturn:
	rfd=wfd=oldfd;
	times++;
	if (times>timelimit) {
		int newmaxfd=0;
		for (int i=0;i<=maxfd;++i)
		if (FD_ISSET(i,&base)) {
			if (!FD_ISSET(i,&newfd)) close(i);
			else newmaxfd=std::max(newmaxfd,i);
		}
		maxfd=newmaxfd,base=newfd;
		return 0;
	}
	if (!select(maxfd+1,&rfd,&wfd,NULL,&tv)) goto nextturn;
	
	for (int i=0;i<=maxfd;++i)
	if (FD_ISSET(i,&oldfd)) {
		if (FD_ISSET(i,&rfd) || FD_ISSET(i,&wfd)) {
			int error=0;
			socklen_t len=sizeof(error);
			if (getsockopt(i,SOL_SOCKET,SO_ERROR,&error,&len)<0) {
				//printf("Solaris pending error");
				FD_CLR(i,&oldfd);
				continue;
			}
			if (error) {
				//printf("Berkeley pending error");
				errno=error;
				FD_CLR(i,&oldfd);
				continue;
			}
			FD_CLR(i,&oldfd);
			FD_SET(i,&newfd);
		}
	}
	goto nextturn;
}

int connectsock(const char *host,const char *service,const char *transport){
	struct hostent *phe;
	struct servent *pse;
	struct protoent *ppe;
	struct sockaddr_in sin;
	int s,type;
	
	memset(&sin,0,sizeof(sin));
	sin.sin_family=AF_INET;
	if (pse=getservbyname(service,transport))
		sin.sin_port=pse->s_port;
	else if ((sin.sin_port=htons((unsigned short)atoi(service)))==0)
		errexit("can't get \"%s\" service entry\n",service);
	
	if (phe=gethostbyname(host))
		memcpy(&sin.sin_addr,phe->h_addr,phe->h_length);
	else if ((sin.sin_addr.s_addr=inet_addr(host))==INADDR_NONE)
		errexit("can't get \"%s\" host entry\n",host);
	
	if ((ppe=getprotobyname(transport))==0)
		errexit("can't get \"%s\" protocol entry\n",transport);
	
	if (strcmp(transport,"udp")==0)
		type=SOCK_DGRAM;
	else
		type=SOCK_STREAM;
	
	s=socket(PF_INET,type,ppe->p_proto);
	if (s<0)
		errexit("can't create socket: %s\n",strerror(errno));
	
	if (connect(s,(struct sockaddr *)&sin,sizeof(sin))<0)
		errexit("can't connect to %s.%s: %s\n",host,service,strerror(errno));
	return s;
}

int errexit(const char *format,...){
	va_list args;
	va_start(args,format);
	vfprintf(stderr,format,args);
	va_end(args);
	exit(1);
}

int connectTCP(const char *host,const char *service){
	return connectsock(host,service,"tcp");
}


int passiveTCP(const char* service,int qlen){
	return passivesock(service,"tcp",qlen);
}

int passivesock(const char*service,const char*transport,int qlen){
	struct servent *pse;
	struct protoent *ppe;
	struct sockaddr_in sin;
	int s,type;

	memset(&sin,0,sizeof(sin));
	sin.sin_family=AF_INET;
	sin.sin_addr.s_addr=INADDR_ANY;
	
	if (pse=getservbyname(service,transport))
		sin.sin_port=htons(ntohs((unsigned short)pse->s_port)+portbase);
	else if ((sin.sin_port=htons((unsigned short)atoi(service)))==0)
		errexit("can't get \"%s\" service entry\n",service);
	
	if ((ppe=getprotobyname(transport))==0)
		errexit("can't get \"%s\" protocol entry\n",transport);
	
	if (strcmp(transport,"udp")==0)
		type=SOCK_DGRAM;
	else
		type=SOCK_STREAM;
	
	s=socket(PF_INET,type,ppe->p_proto);
	if (s<0)
		errexit("can't create socket: %s\n",strerror(errno));
	
	if (bind(s,(struct sockaddr *)&sin,sizeof(sin))<0)
		errexit("can't bind to %s port: %s\n",service,strerror(errno));
	
	if (type==SOCK_STREAM&&listen(s,qlen)<0)
		errexit("can't listen on %s port: %s\n",service,strerror(errno));
	return s;
}

int getHomepageandTorrent(const char *host,const char *service){
	int s,len,torrentnum;
	char *torrentname[100];
	char buf[1005];
	
	s=connectTCP(host,service);
	*((int *)buf)=htonl(0);
	httptrackerSend(s,buf,4);
	
	httptrackerRecv(s,buf,4);
	len=ntohl(*((int *)buf));
	len=httptrackerRecv(s,buf,len);
	torrentnum=ntohl(*((int *)buf));
	buf[3]=0;
	for (int i=4,j=0;i<len;++i)
	if (buf[i-1]==0) torrentname[j++]=buf+i;
	
	fprintf(stdout,"torrent num = %d\n",torrentnum);
	for (int i=0;i<torrentnum;++i) {
		//FILE *f=fopen(torrentname[i],"rb");
		fprintf(stdout,"%d: %s\n",i+1,torrentname[i]);
		//if (f!=NULL) fclose(f);
	}
	
	int id=0;
	while (id<1||id>torrentnum) {
		fprintf(stdout,"Please choose a torrent to download\n");
		fscanf(stdin,"%d",&id);
	}
	
	*((int *)buf)=htonl(id);
	httptrackerSend(s,buf,4);
	
	httptrackerRecv(s,buf,4);
	len=ntohl(*((int *)buf));
	if (len==0) {
		fprintf(stderr,"torrent[%d] download failed!\n",id);
		close(s);
		return -1;
	}
	len=httptrackerRecv(s,(char *)mateinfobuf,len);
	
	FILE *f=fopen(torrentname[id-1],"wb");
	fwrite(mateinfobuf,sizeof(char),len,f);
	fclose(f);
	
	fprintf(stdout,"torrent[%d] download ok!\n",id);
	
	close(s);
	return 0;
}

