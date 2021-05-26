#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <netdb.h>

#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "bencode.h"

#define QLEN 32
#define BUFSIZE 4096

#define HTTP_GET_RES "HTTP/1.1 200 OK\r\nContent-Length: %d\r\n\r\n"

struct data{
	int num;
	unsigned char infohash[20];
	unsigned int ip[100],port[100];
}list[10];

int errno;
unsigned short portbase=0;
char filename[100]="./tracker.bak";
int torrentnum;
char torrentname[100][1000];
unsigned char matebuf[100*1024];

int errexit(const char *format,...);
int passiveTCP(const char *service,int qlen);
int passivesock(const char*service,const char*transport,int qlen);
int work(int fd);
int loadTrackerBak();
int saveTrackerBak();
int httptrackerSend(int fd,char *buff,int size);
int httptrackerRecv(int fd,char *buff,int size);

int main(int argc,char *argv[]){
	const char *service="http";
	struct sockaddr_in fsin;
	int msock;
	fd_set rfds;
	fd_set afds;
	unsigned int alen;
	int fd,nfds;
	
	switch (argc) {
	case 1:
		break;
	case 2:
		service=argv[1];
		break;
	default:
		errexit("usage: %s [ port ]\n",argv[0]);
	}
	
	loadTrackerBak();
	msock=passiveTCP(service,QLEN);
	
	nfds=getdtablesize();
	FD_ZERO(&afds);
	FD_SET(msock,&afds);
	//FD_SET(0,&afds);//keyboard input

	while (1) {
		fflush(stdout);
		fflush(stderr);
		memcpy(&rfds,&afds,sizeof(rfds));
		int tmp;
		timeval tv={5,0};
		if ((tmp=select(nfds,&rfds,NULL,NULL,&tv))<0)
			errexit("select: %s\n",strerror(errno));
		if (FD_ISSET(msock,&rfds)) {
			int ssock;
			alen=sizeof(fsin);
			ssock=accept(msock,(struct sockaddr *)&fsin,&alen);
			fprintf(stdout,"have new connection\n");
			if (ssock<0) errexit("accept: %s\n",strerror(errno));
			FD_SET(ssock,&afds);
		}
		/*if (FD_ISSET(0,&rfds)) {
			char ch;
			fscanf(stdin,"%c",&ch);
			if (ch=='q') break;
		}*/
		if (tmp)
			for (fd=1;fd<nfds;++fd)
			if (fd!=msock&&FD_ISSET(fd,&rfds)&&work(fd)<0) {
				(void)close(fd);
				FD_CLR(fd,&afds);
			}
	}
	saveTrackerBak();
	
	return 0;
}

int work(int fd){
	char buf[BUFSIZE];
	int len,ret=0;
	
	fprintf(stdout,"read something\n");
	len=httptrackerRecv(fd,buf,4);
	if (len<=0) return -1;
	if (buf[0]=='G' && buf[1]=='E' && buf[2]=='T') {
		//http tracker
		len=recv(fd,buf+4,BUFSIZE-4,0)+4;
		unsigned char nowinfohash[20];
		int opt=-1,infostart=-1,infoend=-1;
		for (int i=0;i<len;++i) {
			if (i+8<len&&!strncmp(buf+i,"info_hash",9))
				infostart=i+10;
			if (infostart!=-1&&infoend==-1&&buf[i]=='&')
				infoend=i;
		}
		if (infostart==-1||infoend==-1) {
			fprintf(stderr,"infohash not find!\n");
			return -1;
		}
		for (int i=0,j=0;i<20;++i) {
			if (buf[infostart+j]=='%') {
				unsigned char x=0;
				if (buf[infostart+j+1]>='a') x=buf[infostart+j+1]-'a'+10;
				else x=buf[infostart+j+1]-'0';
				x=x*16;
				if (buf[infostart+j+2]>='a') x+=buf[infostart+j+2]-'a'+10;
				else x+=buf[infostart+j+2]-'0';
				nowinfohash[i]=x;
				j+=3;
			}
			else {
				nowinfohash[i]=buf[infostart+j];
				j++;
			}
		}
		for (int i=0;i<torrentnum;++i) {
			bool flag=true;
			for (int j=0;j<20;++j)
			if (list[i].infohash[j]!=nowinfohash[j]) { flag=false; break; }
			if (flag) opt=i;
		}
		if (opt==-1) {
			fprintf(stderr,"infohash is wrong!\n");
			return -1;
		}
		b_element *top=NULL,*tmp1=NULL,*tmp2=NULL;
		new_dic(&top);
		new_str(&tmp1,(char *)"complete",8);
		new_int(&tmp2,list[opt].num);
		dic_add(top,tmp1,tmp2);
		new_str(&tmp1,(char *)"incomplete",10);
		new_int(&tmp2,0);
		dic_add(top,tmp1,tmp2);
		new_str(&tmp1,(char *)"downloaded",10);
		new_int(&tmp2,0);
		dic_add(top,tmp1,tmp2);
		new_str(&tmp1,(char *)"interval",8);
		new_int(&tmp2,1000);
		dic_add(top,tmp1,tmp2);
		new_str(&tmp1,(char *)"peers",5);
		for (int i=0;i<list[opt].num;++i) {
			*((unsigned int *)(buf+i*6))=list[opt].ip[i];
			*((unsigned short *)(buf+i*6+4))=list[opt].port[i];
		}
		new_str(&tmp2,buf,list[opt].num*6);
		dic_add(top,tmp1,tmp2);
		
		b_element_init();
		b_element_show(top);
		
		be_buf[be_now]=0;
		memset(buf,0,sizeof(buf));
		sprintf(buf,HTTP_GET_RES,be_now);
		int len=0;
		while (buf[len]!='\r'||buf[len+1]!='\n'||buf[len+2]!='\r'||buf[len+3]!='\n') len++;
		fprintf(stdout,"len %d\n",len);
		len+=4;
		memcpy(buf+len,be_buf,be_now);
		len+=be_now;
		buf[len]='\r',buf[len+1]='\n',len+=2;
		buf[len]='\r',buf[len+1]='\n',len+=2;
		
		for (int i=0;i<len;++i)
			fprintf(stdout,"%c",buf[i]);
		ret=httptrackerSend(fd,buf,len);
	}
	else {
		//get home page and torrent
		int opt=ntohl(*((int *)buf));
		fprintf(stdout,"opt=%d\n",opt);
		if (opt==0) { //get home page
			len=4;
			*((int *)(buf+4))=htonl(torrentnum);
			for (int i=0;i<torrentnum;++i) {
				int tlen=strlen(torrentname[i])+1;
				memcpy(buf+4+len,torrentname[i],tlen);
				len+=tlen;
			}
			*((int *)buf)=htonl(len);
			ret=httptrackerSend(fd,buf,len+4);
		}
		else { //get torrent
			FILE *f=fopen(torrentname[opt-1],"rb");
			if (f==NULL) {
				*((int *)buf)=htonl(0);
				httptrackerSend(fd,buf,4);
				return -1;
			}
			int realnum=fread(matebuf,sizeof(char),100*1024,f);
			fclose(f);
			*((int *)buf)=htonl(realnum);
			ret=httptrackerSend(fd,buf,4);
			fprintf(stdout,"filelength=%d\n",realnum);
			if (ret<0) return -1;
			ret=httptrackerSend(fd,(char *)matebuf,realnum);
		}
	}
	
	return ret;
}

int errexit(const char* format,...){
	va_list args;
	va_start(args,format);
	vfprintf(stderr,format,args);
	va_end(args);
	exit(1);
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

int loadTrackerBak(){
	FILE *f=fopen(filename,"r");
	fscanf(f,"%d",&torrentnum);
	char ch;
	fscanf(f,"%c",&ch);
	for (int i=0;i<torrentnum;++i) {
		while (ch=='\n'||ch=='\r') fscanf(f,"%c",&ch);
		int len=0;
		while (ch!='\n'&&ch!='\r') {
			torrentname[i][len++]=ch;
			fscanf(f,"%c",&ch);
		}
		torrentname[i][len]=0;
	}
	for (int i=0;i<torrentnum;++i) {
		while (ch=='\n'||ch=='\r') fscanf(f,"%c",&ch);
		int len=0,x=0;
		while (ch!='\n'&&ch!='\r') {
			if (!(len&1)) {
				if (ch>='a') x=ch-'a'+10; else x=ch-'0';
				x=x*16;
			}
			else {
				if (ch>='a') x+=ch-'a'+10; else x+=ch-'0';
				list[i].infohash[len/2]=x;
			}
			len++;
			fscanf(f,"%c",&ch);
		}
		fscanf(f,"%d",&list[i].num);
		for (int j=0;j<list[i].num;++j)
			fscanf(f,"%u%u",&list[i].ip[j],&list[i].port[j]);
	}
	fclose(f);
	
	fprintf(stdout,"get torrent %d\n",torrentnum);
	for (int i=0;i<torrentnum;++i) {
		fprintf(stdout,"[%d] %s\n",i+1,torrentname[i]);
		fprintf(stdout,"peernum=%d ",list[i].num);
		for (int j=0;j<20;++j) fprintf(stdout,"%02x",list[i].infohash[j]);
		fprintf(stdout,"\n");
		for (int j=0;j<list[i].num;++j)
			fprintf(stdout,"%u %u\n",list[i].ip[j],list[i].port[j]);
	}
}

int saveTrackerBak(){
	FILE *f=fopen(filename,"w");
	fprintf(f,"%d\n",torrentnum);
	for (int i=0;i<torrentnum;++i)
		fprintf(f,"%s\n",torrentname[i]);
	for (int i=0;i<torrentnum;++i) {
		for (int j=0;j<20;++j) fprintf(f,"%02x",list[i].infohash[j]);
		fprintf(f,"\n");
		fprintf(f,"%d\n",list[i].num);
		for (int j=0;j<list[i].num;++j)
			fprintf(f,"%u %u\n",list[i].ip[j],list[i].port[j]);
	}
	fclose(f);
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

