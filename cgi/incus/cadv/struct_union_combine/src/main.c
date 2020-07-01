/*!@file: ./src/main.c
 * @brief: description
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
typedef struct LH{
	unsigned char lo;
	unsigned char hi;
}LH;//assumes packed structure
typedef union SU{
	signed int s;
	unsigned int u;
}SU;
typedef union MINT{
	LH b;
	SU i;
}MINT;
int main(int argc,char**argv,char**envp){
	argc=argc;
	argv=argv;
	envp=envp;
	printf("Content-Type: text/plain\r\n\r\n");
	MINT Gvar={
		{(unsigned char)0,(unsigned char)1}
	};//initialize with values of first members
	MINT*lvar=&Gvar;
	Gvar.i.s=-100;
	Gvar.i.u= 100;
	printf("lo byte:%d\n",Gvar.b.lo);
	printf("hi byte:%d\n",Gvar.b.hi);
	return EXIT_SUCCESS;
}
