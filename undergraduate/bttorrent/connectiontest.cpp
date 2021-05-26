#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>

#include "connectionwithpeer.h"

connectionwp *con=NULL;

int pieces=1591;
bool bit[2000];
unchar infohash[20]={172u,75u,159u,174u,68u,104u,44u,24u,113u,27u,192u,152u,57u,87u,131u,193u,24u,59u,252u,72u};
unchar peerid[20]={65u,66u,67u,68u,69u,70u,71u,72u,73u,74u,75u,76u,77u,78u,79u,80u,81u,82u,83u,84u};
unsigned int ip[31]=
{880956930u,3516683778u,2615817989u,279250469u,3117779757u,2461058606u,2834023982u,244580670u,2645754174u,923677005u,4079825229u,1229604173u,4186662735u,1570663247u,2250015311u,1219798863u,3566103120u,3066317141u,748831070u,3476570718u,3994437470u,3789351290u,2544319152u,4252318642u,771986617u,4144207033u,3433301180u,1021052092u,3988544705u,1353482178u,619516117u};
unsigned short port[31]=
{1583u,21559u,34502u,49390u,57626u,14322u,58218u,3641u,9409u,62937u,5606u,37785u,18540u,18421u,3829u,59053u,59838u,56192u,27770u,21693u,40939u,57626u,41560u,17898u,55717u,345u,11341u,45642u,50918u,37575u,13525u};

int peerSocket(unsigned int peerip,unsigned int peerport){
	int ret=0,sockfd;
	struct sockaddr_in server;
	sockfd=socket(AF_INET, SOCK_STREAM|SOCK_NONBLOCK, 0);

	if (sockfd==-1) {
		perror("socket() failed");
		close(sockfd);
		return -1;
	}
	server.sin_family=AF_INET;
	server.sin_port=peerport;
	server.sin_addr.s_addr=peerip;
	bzero(&(server.sin_zero),8);

	ret=connect(sockfd, (struct sockaddr *)& server,sizeof(struct sockaddr));
	
	if (ret==0) return sockfd;
	if (ret<0 && errno!=EINPROGRESS) {
		perror("connect() failed");
		close(sockfd);
		return -1;
	}

	int times=0;
nextturn:
	timeval tv={3,0};
	fd_set rfd,wfd;
	FD_ZERO(&rfd);
	FD_SET(sockfd,&rfd);
	wfd=rfd;

	if (select(sockfd+1,&rfd,&wfd,NULL,&tv)==0) {
		times++;
		printf("select turn %d\n",times);
		if (times==2) {
			perror("connect() timeout");
			close(sockfd);
			return -1;
		}
		else {
			goto nextturn;
		}
	}

	if (FD_ISSET(sockfd,&rfd) || FD_ISSET(sockfd,&wfd)) {
		int error=0;
		socklen_t len=sizeof(error);
		if (getsockopt(sockfd,SOL_SOCKET,SO_ERROR,&error,&len)<0) {
			perror("Solaris pending error");
			close(sockfd);
			return -1;
		}
		if (error) {
			perror("Berkeley pending error");
			errno=error;
			close(sockfd);
			return -1;
		}
	}
	else {
		perror("select() error");
		close(sockfd);
		return -1;
	}

	return sockfd;
}

int main(){
	int sockfd,maxsock=0;
	for (int i=0;i<3;++i) {
		printf("number[%d]:%u:%u\n",i,ip[i],port[i]);
		sockfd=peerSocket(ip[i],port[i]);
		if (sockfd<0) continue;
		printf("number[%d] success,sockfd=%d\n",i,sockfd);
		maxsock=std::max(maxsock,sockfd);
	}
	if (maxsock==0) {
		perror("not find a valid peer");
		return -1;
	}
	puts("find at least a sockfd");
	
	puts("choose a sockfd:");
	scanf("%d",&sockfd);
	con=new connectionwp(sockfd);
	memset(bit,0,sizeof(bit));
	
	timeval tv;
	fd_set rfds,wfds;

	while (1) {
		puts("wait to operate(h,b,i,q,c):");
		int ret=0;
		char op=getchar();
		while (op=='\n') op=getchar();
		if (op=='h') {
			con->handshake(infohash,peerid);
		}
		else if (op=='b') {
			con->bitfield(pieces,bit);
		}
		else if (op=='i') {
			con->setInterested(true);
			con->setStatus(5);
		}
		else if (op=='q') {
			break;
		}
		tv={3,0};
		FD_ZERO(&wfds);
		FD_SET(con->sockfd,&wfds);
		ret=select(maxsock+1,NULL,&wfds,NULL,&tv);
		if (ret<0) {
			printf("select error\n");
			break;
		}
		puts("select write ok");
		if (FD_ISSET(con->sockfd,&wfds)) {
			if (!con->isFinishedWrite()) ret=con->finishWrite();
			else {
			
			}
			if (ret<0) {
				printf("connection error in write\n");
				break;
			}
		}
		
		tv={3,0};
		FD_ZERO(&rfds);
		FD_SET(con->sockfd,&rfds);
		ret=select(maxsock+1,&rfds,NULL,NULL,&tv);
		if (ret<0) {
			printf("select error\n");
			break;
		}
		puts("select read ok");
		if (FD_ISSET(con->sockfd,&rfds)) {
			if (!con->isFinishedRead()) ret=con->finishRead();
			else {
				if (con->mslen) {
					printf("get a message[%d],length=%d\n",con->msid,con->mslen);
					for (int i=0;i< std::min(99,con->mslen-1);++i) {
						printf("%X",con->msstart[i]);
						if (i%10==9) putchar('\n');
					}
					putchar('\n');
					con->mslen=0;
				}
				else if (con->hslen) {
					printf("get a handshake,protocol length=%d\n",con->hslen);
					for (int i=0;i<8;++i) printf("%X",con->protocol[i]);
					putchar('\n');
					for (int i=0;i<20;++i) printf("%X",con->peerid[i]);
					putchar('\n');
					for (int i=0;i<20;++i) printf("%X",con->infohashstart[i]);
					putchar('\n');
					con->hslen=0;
				}
				else {
					ret=con->readPacket();
				}
			}
			if (ret<0) {
				printf("connection error in read\n");
				break;
			}
		}
		printf("finishwrite:%d,finishread:%d\n",con->isFinishedWrite(),con->isFinishedRead());
	}

	return 0;
}

