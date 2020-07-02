/*!@file: ./src/main.c
 * @brief: `ptrdiff_t` demonstration
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<stddef.h>
int main(int argc,char**argv,char**envp){
	argc=argc;
	argv=argv;
	envp=envp;
	printf("Content-Type: text/plain\n\n");
	{
		int a=42;
		int b=24;
		int c=24;
		ptrdiff_t d=&b-&a;
		ptrdiff_t e=&c-&a;
		ptrdiff_t f=&c-&b;
		printf("a:   %p\n",&a);
		printf("b:   %p\n",&b);
		printf("c:   %p\n",&c);
		printf("b-a: %td\n",d);
		printf("c-a: %td\n",e);
		printf("c-b: %td\n",f);
	}
	return EXIT_SUCCESS;
}
