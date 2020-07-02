/*!@file: ./src/main.c
 * @brief: How to test macros. You can test macros with
 *         cat ./src/main.c|gcc -I./src -E -P -
 *         or
 *         gcc -I./src -E -P - < ./src/main.c
 *         It is perhaps a good idea to make this some makefile target
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdlib.h>
#include"cJSON/cJSON.h"
int main(int argc,char**argv,char**envp){
	argc=argc;
	argv=argv;
	envp=envp;
	printf("Content-Type: text/plain\n\n");
	return EXIT_SUCCESS;
}
