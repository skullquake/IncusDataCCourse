/*!@file: ./src/main.c
 * @brief: Self referential structs demontration;
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct A{
	int a;
	struct A*b;
};

typedef struct B B;
struct B{
	int a;
	B *b;
};

int main(int argc,char**argv,char**envp){
	argc=argc;
	argv=argv;
	envp=envp;
	printf("Content-Type: text/plain\n\n");
	{
		struct A a;
		a.b=(struct A*)malloc(sizeof(struct A));
		a.b->b=(struct A*)malloc(sizeof(struct A));
		a.b->b->b=(struct A*)malloc(sizeof(struct A));
		a.b->b->b->b=(struct A*)malloc(sizeof(struct A));
		free(a.b->b->b->b);
		free(a.b->b->b);
		free(a.b->b);
		free(a.b);
	}
	{
		B a;
		a.b=(B*)malloc(sizeof(B));
		a.b->b=(B*)malloc(sizeof(B));
		a.b->b->b=(B*)malloc(sizeof(B));
		a.b->b->b->b=(B*)malloc(sizeof(B));
		a.b->b->b->b->b=(B*)malloc(sizeof(B));
		a.b->b->b->b->b->b=(B*)malloc(sizeof(B));
		a.b->b->b->b->b->b->b=(B*)malloc(sizeof(B));
		free(a.b->b->b->b->b->b);
		free(a.b->b->b->b->b);
		free(a.b->b->b->b);
		free(a.b->b->b);
		free(a.b->b);
		free(a.b);
	}
	{//how to execute one line initialization of chain with ability to free all?
		//initialize
		B*root;
		(((root=(((B*)malloc(sizeof(B)))))))->b=
		(((B*)malloc(sizeof(B)))->b)=
		(((B*)malloc(sizeof(B)))->b)=
		(((B*)malloc(sizeof(B)))->b)=
		(((B*)malloc(sizeof(B)))->b)=
		(((B*)malloc(sizeof(B)))->b)=
		(((B*)malloc(sizeof(B)))->b)=
		(((B*)malloc(sizeof(B)))->b)=
		(((B*)malloc(sizeof(B)))->b=NULL);
		B*pos;
		//populate
		int idx=0;
		for(pos=root;pos!=NULL;pos=pos->b){
			pos->a=idx;
			++idx;
		}
		//print
		for(pos=root;pos!=NULL;pos=pos->b){
			printf("%d\n",pos->a);
		}
		//free
		for(pos=root;pos!=NULL;){
			B*prv=pos;
			pos=pos->b;
			free(prv);
		}
		free(pos);
		root=NULL;
	}
	return EXIT_SUCCESS;
}
