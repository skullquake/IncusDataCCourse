/*!@file: ./src/main.c
 * @brief: Some demonstrations indicating that <type>[] is fundamentally 
 *         different from <type>*
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
		char a[]="foo bar baz qux";
		char*b="foo bar baz qux";
		printf("sizeof(a): %zu\n",sizeof(a));	//sizeof(a): 16
		printf("sizeof(b): %zu\n",sizeof(b));	//sizeof(b): 8
	}
	{
		char a[][16]={
			"foo",
			"bar",
			"baz",
			"qux"
		};
		char**b={
			"foo",
			"bar",
			"baz",
			"qux"
		};
		printf("sizeof(a): %zu\n",sizeof(a));	//sizeof(a): 64
		printf("sizeof(b): %zu\n",sizeof(b));	//sizeof(b): 8

	}
	{
		char a[]="foo bar baz qux";
		char**b=&a;
		char(*c)[ 4]=&a;
		char(*d)[ 8]=&a;
		char(*e)[16]=&a;
		printf("sizeof( b): %zu\n",sizeof( b));	//sizeof( b): 8
		printf("sizeof( c): %zu\n",sizeof( c));	//sizeof( c): 8
		printf("sizeof( d): %zu\n",sizeof( c));	//sizeof( d): 8
		printf("sizeof( e): %zu\n",sizeof( e));	//sizeof( e): 8
		printf("sizeof(*b): %zu\n",sizeof(*b));	//sizeof(*b): 8
		printf("sizeof(*c): %zu\n",sizeof(*c));	//sizeof(*c): 4
		printf("sizeof(*d): %zu\n",sizeof(*d));	//sizeof(*d): 8
		printf("sizeof(*e): %zu\n",sizeof(*e));	//sizeof(*e): 16
		printf("sizeof(&a): %zu\n",sizeof(&b));	//sizeof(&a): 8
		printf("sizeof(&b): %zu\n",sizeof(&c));	//sizeof(&b): 8
		printf("sizeof(&d): %zu\n",sizeof(&d));	//sizeof(&d): 8
		printf("sizeof(&e): %zu\n",sizeof(&e));	//sizeof(&e): 8
		printf("b+0:    %p\n",b+0);		//b+0:    000000000067FDE0
		printf("c+0:    %p\n",c+0);		//c+0:    000000000067FDE0
		printf("d+0:    %p\n",d+0);		//d+0:    000000000067FDE0
		printf("e+0:    %p\n",e+0);		//e+0:    000000000067FDE0
		printf("b+1:    %p\n",b+1);		//b+1:    000000000067FDE8
		printf("c+1:    %p\n",c+1);		//c+1:    000000000067FDE4
		printf("d+1:    %p\n",c+1);		//d+1:    000000000067FDE4
		printf("e+1:    %p\n",c+1);		//e+1:    000000000067FDE4
		printf("*(b+0): %p\n",*(b+0));		//*(b+0): 20726162206F6F66
		printf("*(c+0): %p\n",*(c+0));		//*(c+0): 000000000067FDE0
		printf("*(d+0): %p\n",*(d+0));		//*(d+0): 000000000067FDE0
		printf("*(e+0): %p\n",*(e+0));		//*(e+0): 000000000067FDE0
		printf("*(b+1): %p\n",*(b+1));		//*(b+1): 00787571207A6162_
		printf("*(c+1): %p\n",*(c+1));		//*(c+1): 000000000067FDE4 |
		printf("*(d+1): %p\n",*(d+1));		//*(d+1): 000000000067FDE8 |- take note
		printf("*(e+1): %p\n",*(e+1));		//*(e+1): 000000000067FDF0_|

	}
	return EXIT_SUCCESS;
}
