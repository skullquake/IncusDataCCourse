/*!@file: ./src/main.c
 * @brief: If #NDEBUG is defined, means we are producing a debug compile
 *         This preprocessor definition will be passed in with the compile when compiling in debug mode,
 *         and can be used to, for example, define a logging macro as follows
 */
#define NDEBUG
#if defined NDEBUG
	#define TX(M) fprintf(stderr,"%s: %04d %s\n",__FILE__,__LINE__,M);
#else
	#define TX(M)
#endif
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
int main(int argc,char**argv,char**envp){
	argc=argc;
	argv=argv;
	envp=envp;
	printf("Content-Type: text/plain\n\n");
	TX("HI");	
	return EXIT_SUCCESS;
}
