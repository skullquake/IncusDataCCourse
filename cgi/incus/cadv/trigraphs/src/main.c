/*!@file: ./src/main.c
 * @brief: trigraph example
 * references
 *   https://en.wikipedia.org/wiki/Digraphs_and_trigraphs 
 */
#include<stdio.h>
#include<stdlib.h>
#include"cJSON/cJSON.h"
int main(int argc,char**argv,char**envp){
	argc=argc;
	argv=argv;
	envp=envp;
	printf("Content-Type: text/plain\r\n\r\n");
	printf("??=\n");// 	#
	printf("??/\n");// 	backslash
	printf("??'\n");// 	^
	printf("??(\n");// 	[
	printf("??)\n");// 	]
	printf("??!\n");// 	|
	printf("??<\n");// 	{
	printf("??>\n");// 	}
	printf("??-\n");// 	~
	return EXIT_SUCCESS;
}
