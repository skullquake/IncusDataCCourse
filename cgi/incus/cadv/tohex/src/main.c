/*!@file: ./src/main.c
 * @brief: Demonstrates using array subscripting pointers
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
char* tohex(char*buf,unsigned int val){
	int n=sizeof(unsigned int)*2;
	buf[n]=(char)0;
	while(n--){
		buf[n]="0123456789ABCDEF"[val%16];
		val/=16;
	}
	return buf;
}
int main(int argc,char**argv,char**envp){
	argc=argc;
	argv=argv;
	envp=envp;
	printf("Content-Type: text/plain\n\n");
	char buf[32];
	for(int i=0;i<32;++i){
		printf("0X%s\n",tohex(buf,i));
	}
	return EXIT_SUCCESS;
}
