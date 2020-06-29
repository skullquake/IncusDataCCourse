/*!@file: ./src/main.c
 * @brief: You can define macros or symbolic constants using #define
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdlib.h>
#define FOO "BAR"
#define BAR "BAZ"
#define BAZ 42
int main(int argc,char**argv,char**envp){
	argc=argc;
	argv=argv;
	envp=envp;
	printf("Content-Type: text/plain\n\n");
	printf(FOO"\n");
	printf(BAR"\n");
	printf("%d\n",BAZ);
	return EXIT_SUCCESS;
}
