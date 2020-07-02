/*!@file: ./src/main.c
 * @brief: macro stringization
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdlib.h>
#include"cJSON/cJSON.h"
#define A(B) #B#B
int main(int argc,char**argv,char**envp){
	argc=argc;
	argv=argv;
	envp=envp;
	printf("Content-Type: text/plain\n\n");
	printf(A(foo)"\n");
	return EXIT_SUCCESS;
}
