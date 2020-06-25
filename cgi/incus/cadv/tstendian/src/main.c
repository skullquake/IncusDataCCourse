/*!@file: ./src/main.c
 * @brief: test endianness
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<stdint.h>
#include"cJSON/cJSON.h"
bool isBigEndian(void);
int main(int argc,char**argv,char**envp){
	argc=argc;
	argv=argv;
	envp=envp;
	printf("Content-Type: text/plain\r\n\r\n");
	printf(isBigEndian()?"Big Endian":"Little Endian");
	return EXIT_SUCCESS;
}
bool isBigEndian(void){
	union{
		uint16_t a;
		uint8_t  b;
	}c={1};
	return c.b[1];//???
}
