/*!@file: ./src/main.c
 * @brief: The macro & operator is used to maintain the original form of an argument
 *         In other words, 0x01 will not be expanded to 1, but to 0x01 if the & is used
 *         Todo: fix up demonstration, for now test with cat ./src/main.c|gcc -I./src -E -P -
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdlib.h>
#include"cJSON/cJSON.h"
#define A(B) #B
#define C(D) (#D) &
int main(int argc,char**argv,char**envp){
	argc=argc;
	argv=argv;
	envp=envp;
	printf("Content-Type: text/plain\r\n\r\n");
	printf(A(0x0003)"\n");
	printf(C(0x0003)"\n");
	return EXIT_SUCCESS;
}
