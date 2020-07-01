/*!@file: ./src/main.c
 * @brief: using the address of operator with <type>[]
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
int main(int argc,char**argv,char**envp){
	argc=argc;
	argv=argv;
	envp=envp;
	printf("Content-Type: text/plain\r\n\r\n");
	char a[]="lorem";
	char*b=a;
	b=&a;
	while(*b!='\0'){
		putchar(*b);
		++b;
	}putchar('\n');
	printf("a:     %p\n",a);
	printf("&a:    %p\n",&a);
	printf("&a:    %p\n",&a);
	printf("&a[0]: %p\n",&a[0]);
	printf("(a+0): %p\n",(a+0));
	printf("&a[1]: %p\n",&a[1]);
	printf("(a+1): %p\n",(a+1));
	printf("&a[2]: %p\n",&a[2]);
	printf("(a+2): %p\n",(a+2));
	return EXIT_SUCCESS;
}
