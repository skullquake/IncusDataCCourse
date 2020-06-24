/*!@file: ./src/main.c
 * @brief: string exercises
 * todo: pointer iteration and indirection
 * todo: standard library string function demonstration
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdlib.h>
#include"cJSON/cJSON.h"
typedef struct ST{
	int a;
	float b;
	char c[32];
}ST;
ST f0(ST s){
	return s;
}
int main(int argc,char**argv,char**envp){
	printf("Content-type: text/plain\r\n");
	printf("\r\n");
	{
		ST s={0,1.2,"3.45"};
	}
	{//compound literals (c99)
		ST s;
		s=(ST){0,1.2,"3.45"};
		s=f0((ST){0,1.2,"3.45"});
		(ST){0,1.2,"3.45"};
	}
	{//compound literals and arrays (c99)
		(int[]){0,1,2,3};
		int*a=(int[]){0,1,2,3};
		//char b[32]=(char*){"foo","bar","baz","qux"};//??
		(ST[]){
			(ST){0,1.2,"3.45"},
			(ST){0,1.2,"3.45"},
			(ST){0,1.2,"3.45"},
			(ST){0,1.2,"3.45"}
		};
	}
	{//designated initializers (c99)
		(ST[]){
			(ST){.a=0},
			(ST){.a=0,.b=1.2},
			(ST){.a=0,.b=1.2,.c="3.45"}
		};
	}
	return EXIT_SUCCESS;
}
