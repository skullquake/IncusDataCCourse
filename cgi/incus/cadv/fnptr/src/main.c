/*!@file: ./src/main.c
 * @brief: function pointers as arguments to function
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdlib.h>
#include"cJSON/cJSON.h"
void dowork(int*beg,int*end,void(*cb)(int));
void f0(int i){
	printf("%d\n",i);
}
void f1(int i){
	printf("%d\n",i*2);
}
int main(int argc,char**argv,char**envp){
	argc=argc;
	argv=argv;
	envp=envp;//shutup
	printf("Content-Type: text/plain\r\n\r\n");
	int buf[]={0,1,2,3};
	dowork(buf,buf+4,f0);
	dowork(buf,buf+4,f1);
	return EXIT_SUCCESS;
}
void dowork(int*beg,int*end,void(*cb)(int)){
	for(int*pos=beg;pos!=end;++pos){
		cb(*pos);
	}
}
