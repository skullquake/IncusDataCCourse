/*!@file: ./src/main.c
 * @brief: Demonstrates arguments on stack. The C language provides
 *         a way to pass in a variable amount of arguments to a function,
 *         by means of the ellipse, e.g. <type><ident>(<type><ident>,...);
 *         It does not, however, supply a way to access the elements,
 *         a seperate library or custom code needs to be used for this.
 *
 *         K&R provides varargs.h and ANSI/ISO provides stdarg.h
 *         These are headers containing macros that help iterating
 *         through variable length arguments.
 *
 *         If you want to write your own code to access the arguments,
 *         you have to take into account how the compiler calls the function.
 *         Two calling conventions are the C calling convention and the
 *         Pascal calling convention. The point is, you need to be able to
 *         access the variable length arguments in some way using the address
 *         of the first argument.
 *
 *         If you run the below on the old BCC compiler you should see it works,
 *         however if you use a fairly modern GCC the results wont be as expected
 *
 *         You can find out about the callstack by inspecting the following in a normal function:
 *           * address of the function
 *           * address of the Nth argument, just give it a bunch of int arguments for a test
 *           * check if the addresses increase or decrease
 *           * what is the position of the arguments relative to the function?
 *
 *         In the old BCC compiler, the addresses of the argument increase
 *         In the GCC, it decreases
 *
 *         So all of this depends on the compiler, and you need to check that when compiling
 *         using conditional preprocessor directives. In order to inspect your compiler defines,
 *         you can run something like this
 *         strings `which gcc`|grep __
 *         or
 *         strings /mnt/c//tmp/dosdrive/opt/bcc3135/bin/bcc.exe|grep __
 */
#include<stdio.h>
#ifndef __BORLANDC__
	#include<stdlib.h>
	#include<stdbool.h>
#else
	#define EXIT_SUCCESS 0
	#define EXIT_FAILURE 1
#endif
extern void f0(int,int,int);
extern void f1(int,...);
int main(int argc,char**argv,char**envp){
	argc=argc;
	argv=argv;
	envp=envp;
	printf("Content-Type: text/plain\n\n");
	f0(1,2,3);
	f1(3,10,20,30,40);
	return EXIT_SUCCESS;

}
void f0(int a,int b,int c){
	printf("f0:  %p\n",f0);
	printf("a:   %p:%d-+- note offsets\n",(void*)&a,a);
	printf("b:   %p:%d-|\n",(void*)&b,b);
	printf("c:   %p:%d-+\n",(void*)&c,c);
}
void f1(int narg,...){
#ifdef __BORLANDC__
	#ifndef __PASCAL__
	int*aptr;
	int i;
	printf("f1:  %p\n",f1);
	printf("a[0]:%p:%16d -+- note offsets\n",&narg,narg);
	aptr=&narg+1;
	for(i=0;i<narg;++i,++aptr){
		printf(
			"a[%d]:%p:%16d %s-%s\n",
			i+1,
			aptr,
			*aptr,
			i==narg-1?"-":" ",
			i==narg-1?"+":"|"
		);
	}
	#else
		fprintf(stderr,"error:f1:unimplemented\n");
	#endif
#else
	fprintf(stderr,"error:f1:unimplemented\n");
#endif
/*
0x7fffff027db0:              40  -| <- arg4
0x7fffff027dac:               0  -|
0x7fffff027da8:              30  -| <- arg3
0x7fffff027da4:               0  -|
0x7fffff027da0:              20  -| <- arg2
0x7fffff027d9c:               0  -|
0x7fffff027d98:              10  -| <- arg1
0x7fffff027d94:               0  -|
0x7fffff027d90:               0  -|
0x7fffff027d8c:           32767  -|
0x7fffff027d88:       -16614008  -|
0x7fffff027d84:              30  -|
0x7fffff027d80:               3  -| <- arg0
*/
}
