/*!@file: ./src/main.c
 * @brief: `intptr_t` and `uintptr_t` can be used to store pointers to integers in a portable way.
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
int main(int argc,char**argv,char**envp){
	argc=argc;
	argv=argv;
	envp=envp;
	printf("Content-Type: text/plain\n\n");
	{
		signed int a;
		intptr_t*b=&a;
		unsigned int c;
		uintptr_t*d=&c;
		d=&a;//should report syntax error???
	}
	return EXIT_SUCCESS;
}
