#include <cstdio>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <arpa/inet.h>

#include "bencode.h"

unsigned char a[4]={104u,194u,75u,50u};
unsigned int b[1]={6880u};
int main(){
	b_element *top=NULL,*tmp1=NULL,*tmp2=NULL;
	new_dic(&top);
	new_str(&tmp1,(char *)"complete",8);
	new_int(&tmp2,1);
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
	
	b_element_init();
	b_element_show(top);
	for (int i=0;i<be_now;++i) printf("%c",be_buf[i]);
	printf("\n");
	
	unsigned int ip,port;
	ip=*((unsigned int *)a);
	printf("ip %u\n",ip);
	for (int i=0;i<10;++i) {
		port=b[0]+i;
		port=htons(port);
		printf("port[%u] %u\n",b[0]+i,port);
	}
	return 0;
	
	int rate=0;
	char bar[102]={0};
	const char *sta="-\\|/";
	while(rate<=100) {
		printf("[%-100s],%d%%,[%c]\r",bar,rate,sta[rate%4]);
		usleep(100000);
		bar[rate]='*';
		rate++;
		bar[rate]='\0';
	}
	char ch=getchar();

	bencode_t b1, b2, b3;
	char *str=strdup("d4:infod3:keyl4:test3:fooe3:foo0:ee");
	const char *ren;
	int len;
	
	bencode_init(&b1, str, strlen(str));
	bencode_dict_get_next(&b1, &b2, &ren, &len);

	printf("ren=%s len=%d\n", ren, len);

	bencode_dict_get_start_and_len(&b2, &ren, &len);
	printf("ren=%s len=%d\nb2:%s %d %s\n",ren,len,b2.start,b2.len,b2.str);
	bencode_dict_get_next(&b2, &b3, &ren, &len);
	
	printf("b2:%s %d %s\n", b2.start, b2.len, b2.str);
	printf("ren=%s len=%d\nb3:%s %d %s\n", ren, len, b3.start, b3.len, b3.str);

	while (bencode_dict_has_next(&b2)) {
		bencode_dict_get_next(&b2, &b3, &ren, &len);
		printf("b2:%s %s\n", b2.start, b2.str);
		printf("b3:%s %d\n", b3.start, b3.len);
	}

	printf("b2str:%s\n", b2.str);
	free(str);
	return 0;
}

