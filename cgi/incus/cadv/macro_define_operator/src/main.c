/*!@file: ./src/main.c
 * @brief: You can use `#define` to define operators, illustrated as follows
 */
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#define EQ ==
int main(int argc,char**argv,char**envp){
	argc=argc;
	argv=argv;
	envp=envp;
	printf("Content-Type: text/plain\n\n");
	printf("%s\n",0 EQ 0?"TRUE":"FALSE");
	return EXIT_SUCCESS;
}
