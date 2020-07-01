/*!@file: ./src/main.c
 * @brief: bitfield demonstration
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdlib.h>
#include"cJSON/cJSON.h"

//create binary mapping
struct bf{
	unsigned flda:4;
	unsigned fldb:4;
	unsigned     :2;//irrelivant bits
	signed   fldc:6;
}BV;//the whole thing is a sizeof(int) big

int main(int argc,char**argv,char**envp){
	argc=argc;
	argv=argv;
	envp=envp;//shutup
	printf("Content-Type: text/plain\n\n");
	//accessible
	BV.flda;
	BV.fldb;
	BV.fldc;
	return EXIT_SUCCESS;
}
