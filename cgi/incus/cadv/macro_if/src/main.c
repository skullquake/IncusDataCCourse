/*!@file: ./src/main.c
 * @brief: You can use `#if` for conditional preprocessor parsing.
 *         `#if` preprocessor directives can be nested
 */
#if 0
	#if 0
		#define FOO 420
	#else
		#define FOO 42
	#endif
#else
	#if 0
		#define FOO 240
	#else
		#define FOO 24
	#endif
#endif
#include<stdio.h>
#include<stdlib.h>
#include<stdlib.h>
#include"cJSON/cJSON.h"
int main(int argc,char**argv,char**envp){
	argc=argc;
	argv=argv;
	envp=envp;
	printf("Content-Type: text/plain\n\n");
	printf("%d\n",FOO);
	return EXIT_SUCCESS;
}
