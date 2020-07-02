/*!@file: ./src/main.c
 * @brief: `bitfield` demonstration
 *         todo: incorporate binary printer to verify memory layout
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<limits.h>
#include"tobin.h"
typedef struct A{
	unsigned char a:4;//note output
	unsigned short b:4;
	unsigned int c:4;
	unsigned long d:4;
	unsigned long long e:4;
}A;//note the : tokens, indicating that this is not a normal structure, but a bitfield
int main(int argc,char**argv,char**envp){
	argc=argc;
	argv=argv;
	envp=envp;
	printf("Content-Type: text/plain\n\n");
	printf("%zu\n",sizeof(A));
	A a;
	a.a=UCHAR_MAX;
	a.b=USHRT_MAX;
	a.c=UINT_MAX;
	a.d=ULONG_MAX;
	a.e=ULLONG_MAX;
	printf("%d\n",a.a);
	printf("%d\n",a.b);
	printf("%d\n",a.c);
	printf("%ld\n",a.d);
	printf("%ld\n",a.e);
	printf("A:  ");tobinstream(&a,sizeof(a),stdout);
	return EXIT_SUCCESS;
}
