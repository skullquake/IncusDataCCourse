/*!@file: ./src/main.c
 * @brief: `stdarg.h` fron ANSI/ISO can be used to handle variable length arguments
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<stdarg.h>
int mymax(int,...);
int main(int argc,char**argv,char**envp){
	argc=argc;
	argv=argv;
	envp=envp;
	printf("Content-Type: text/plain\n\n");
	printf("%d\n",mymax(1,1));
	printf("%d\n",mymax(2,1,2));
	printf("%d\n",mymax(3,1,2,3));
	printf("%d\n",mymax(4,1,2,3,4));
	return EXIT_SUCCESS;
}
int mymax(int n,...){
	int maximum=0,number;
	va_list mark;
	va_start(mark,n);
	while(n>0){
		number=va_arg(mark,int);
		if(number>maximum){
			maximum=number;
		}
		n--;
	}
	va_end(mark);
	return maximum;
}
