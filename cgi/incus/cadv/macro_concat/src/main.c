/*!@file: ./src/main.c
 * @brief: Concatenation in macros are performed with IDENT##IDENT
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdlib.h>
#include"cJSON/cJSON.h"
#define CONCAT(A,B) A##B
int main(int argc,char**argv,char**envp){
	argc=argc;
	argv=argv;
	envp=envp;
	printf("Content-Type: text/plain\n\n");
	printf("%d\n",CONCAT(4,2));
	return EXIT_SUCCESS;
}
