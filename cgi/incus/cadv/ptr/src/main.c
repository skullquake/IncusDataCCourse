/*!@file: ./src/main.c
 * @brief: array to arrays iteration with pointers
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdlib.h>
#include"cJSON/cJSON.h"
int main(int argc,char**argv,char**envp){
	argc=argc;
	argv=argv;
	envp=envp;//shutup
	char buf[4][4]={
		{'a','b','c','d'},
		{'e','f','g','h'},
		{'i','j','k','l'},
		{'m','n','o','p'}
	};
	char*beg=(char*)buf;
	char*end=(char*)buf+(sizeof(buf));
	printf("Content-Type: text/plain\r\n\r\n");
	for(char*pos=beg;pos!=end;++pos){
		putchar(*pos);
		if((pos-beg)!=0&&(pos-beg)%4==0)putchar('\n');
	}
	return EXIT_SUCCESS;
}
