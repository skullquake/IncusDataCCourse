/*!@file: ./src/main.c
 * @brief: ISO standard includes a macro called offsetof() which will return the
 *         offset of any structure member in a portable manner. The type it
 *         results in is size_t.
 *
 *         todo: fix demonstration
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
typedef struct A{
	char a;
	int b;
}A;
int main(int argc,char**argv,char**envp){
	argc=argc;
	argv=argv;
	envp=envp;
	printf("Content-Type: text/plain\n\n");
	A a;
	printf("A.a: %zu\n",offsetof(a,0));
	printf("A.a: %zu\n",offsetof(a,1));
	return EXIT_SUCCESS;
}
