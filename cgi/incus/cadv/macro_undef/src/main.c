/*!@file: ./src/main.c
 * @brief: You can use #undef to undefine macros defined with #define
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdlib.h>
#define FOO "BAR"
#undef FOO
#define FOO "BAZ"
int main(int argc,char**argv,char**envp){
	argc=argc;
	argv=argv;
	envp=envp;
	printf("Content-Type: text/plain\n\n");
	printf("%s\n",FOO);
	#undef FOO
	#define FOO "BAR"
	printf("%s\n",FOO);
	return EXIT_SUCCESS;
}
