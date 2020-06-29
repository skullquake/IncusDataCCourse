/*!@file: ./src/main.c
 * @brief: string exercises
 * todo: pointer iteration and indirection
 * todo: standard library string function demonstration
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdlib.h>
#include"cJSON/cJSON.h"
int main(int argc,char**argv,char**envp){
	printf("Content-type: text/plain\n\n");
	{//using fixed strides
		char buf[4][16]={
			"foo",
			"bar",
			"baz",
			"quxklutz"
		};
		printf("%zu\n",sizeof(buf));
		for(int i=0;i<4;++i){
			printf("%s\n",buf[i]);
		}
	}
	{//using compile time deduced dynamic strides
		char*buf[4]={
			"foo",
			"bar",
			"baz",
			"quxklutz"
		};
		printf("%zu\n",sizeof(buf));
		for(int i=0;i<4;++i){
			printf("%s\n",buf[i]);
		}

	}
	{//using dynamic memory allocation
		char*buf[4]={
			//calloc is like malloc but also clears
			(char*)calloc(1,2),
			(char*)calloc(1,4),
			(char*)calloc(1,8),
			(char*)calloc(1,16)
		};
		printf("%zu\n",sizeof(buf));
		snprintf(buf[0], 2,"lorem ipsum");
		snprintf(buf[1], 4,"lorem ipsum");
		snprintf(buf[2], 8,"lorem ipsum");
		snprintf(buf[3],16,"lorem ipsum");
		for(int i=0;i<4;++i){
			printf("%s\n",buf[i]);
		}
		for(int i=0;i<4;++i){
			free(buf[i]);
		}
	}
	{//string literals
		"lorem";
		"ipsum"[0];
		char*a="sit";
		char b[]="consecutar";
		char c[6]="dolor";
		{
			printf("%zu\n",sizeof(a));
			char*beg=a;
			char*end=a+sizeof(a)/sizeof(*a);
			for(char*pos=beg;pos!=end;++pos){
				putchar(*pos);
			}printf("\n");
		}
		{
			printf("%zu\n",sizeof(b));
			char*beg=b;
			char*end=b+sizeof(b)/sizeof(*b);
			for(char*pos=beg;pos!=end;++pos){
				putchar(*pos);
			}printf("\n");
		}
		{
			printf("%zu\n",sizeof(c));
			char*beg=c;
			char*end=c+sizeof(c)/sizeof(*c);
			for(char*pos=beg;pos!=end;++pos){
				putchar(*pos);
			}printf("\n");
		}
	}
	/*
	*/
	return EXIT_SUCCESS;
}
