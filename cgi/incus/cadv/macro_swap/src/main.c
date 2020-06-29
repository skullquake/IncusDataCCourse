/*!@file: ./src/main.c
 * @brief: Because of the generality of preprocessor macros, we can use them
 *         to write generic 'functions', as in the following swap 'function'.
 *         It is not really a function, as it just expands to c code. The below
 *         `SWAP` macro does indeed generate a function, but itself is not a function.
 *         We first generate the functions using GENSWAP, then call them using CALLSWAP
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

//preprocessor swap function generator
#define GENSWAP(TYPE)\
void SWAP_##TYPE(TYPE*A,TYPE*B){\
	TYPE C; \
	C=*A; \
	*A=*B; \
	*B=C; \
}

//preprocessor swap function caller

#define CALLSWAP(TYPE,A,B)\
SWAP_##TYPE(&A,&B);

//test struct
typedef struct StructA{
	char sc;
	short ss;
	int si;
	long sl;
	long long sll;
	
}StructA;

//create functions using GENSWAP
GENSWAP(char)
GENSWAP(short)
GENSWAP(int)
GENSWAP(long)

//GENSWAP(long long)//will not work yet
GENSWAP(float)
GENSWAP(double)
//GENSWAP(long double)//will not work yet
GENSWAP(StructA)

/*! main driver function
 *  @param argc argument count
 *  @param argv argument vector
 *  @param envp environment pointer
 *  @return EXIT_SUCCESS
 */
int main(int argc,char**argv,char**envp){
	argc=argc;
	argv=argv;
	envp=envp;
	printf("Content-Type: text/plain\n\n");
	{
		char a=0;
		char b=1;
		printf("%d,%d\n",a,b);
		CALLSWAP(char,a,b);
		printf("%d,%d\n",a,b);
	}
	{
		short a=0;
		short b=1;
		printf("%d,%d\n",a,b);
		CALLSWAP(short,a,b);
		printf("%d,%d\n",a,b);
	}
	{
		long a=0;
		long b=1;
		printf("%ld,%ld\n",a,b);
		CALLSWAP(long ,a,b);
		printf("%d,%d\n",a,b);
	}
	{
		float a=0;
		float b=1;
		printf("%f,%f\n",a,b);
		CALLSWAP(int,a,b);
		printf("%f,%f\n",a,b);
	}
	{
		double a=0;
		double b=1;
		printf("%lf,%lf\n",a,b);
		CALLSWAP(double,a,b);
		printf("%lf,%lf\n",a,b);
	}
	{
		StructA a={'a',0,1,2,3};
		StructA b={'b',3,2,1,0};
		CALLSWAP(StructA,a,b);
	}
	return EXIT_SUCCESS;
}
