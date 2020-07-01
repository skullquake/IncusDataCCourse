/*!@file: ./src/main.c
 * @brief: varargs.h, from K&R
 *         This does not compile under GCC, but can be compiled with BCC
 */
#include<stdio.h>
#include<stdlib.h>
#include<varargs.h>
int mymax();
int main(int argc,char**argv,char**envp){
	argc=argc;
	argv=argv;
	envp=envp;
	printf("Content-Type: text/plain\n\n");
	printf("%d\n",mymax(1,1));
	printf("%d\n",mymax(2,1,2));
	printf("%d\n",mymax(3,1,2,3));
	printf("%d\n",mymax(4,1,2,3,4));
	return 0;
}
int mymax(va_alist) va_dcl {
	int count;
	int maximum=0,number;
	va_list(mark);
	va_start(mark);
	count=va_arg(mark,int);
	while(count>0){
		number=va_arg(mark,int);
		if(number>maximum){
			maximum=number;
		}
		count--;
	}
	return maximum;
}
