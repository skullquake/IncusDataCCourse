/*!@file: ./src/main.c
 * @brief: The `#define` preprocessor directive can be used to define macros
 *         Note, make judicious use of parenthesis to avoid compile time errors
 *         due to invalid syntax resulting from using the macro, as well as
 *         to avoid ambiguous results.
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define MAX(A,B) (((A)<(B))?(B):(A))
int main(int argc,char**argv,char**envp){
	argc=argc;
	argv=argv;
	envp=envp;
	printf("Content-Type: text/plain\n\n");
	printf("max: %d\n",MAX(4,2));
	printf("max: %d\n",MAX(2,4));
	return EXIT_SUCCESS;
}
