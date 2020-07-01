/*!@file ./src/main.c
 * @brief Simple test program
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"foo/foo.h"
/*!@brief Main entry point
 * @param argc Argument count
 * @param argv Argument vector
 * @param envp Environment pointer
 * @return `int` value process return
 */
int main(int argc,char**argv,char**envp){
	argc=argc;
	argv=argv;
	envp=envp;
	printf("Content-Type: text/plain\n\n");
	foo();
	return EXIT_SUCCESS;
}
