/*!@file: ./src/main.c
 * @brief: The `#error` preprocessor directive can be used to produce compile time errors
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdlib.h>
#define FOO 1
#if FOO
	#error WONT COMPILE
#endif
int main(int argc,char**argv,char**envp){
	argc=argc;
	argv=argv;
	envp=envp;
	printf("Content-Type: text/plain\n\n");
	return EXIT_SUCCESS;
}
