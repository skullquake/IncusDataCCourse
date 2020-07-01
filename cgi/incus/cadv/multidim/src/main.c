/*!@file: ./src/main.c
 * @brief: The term multidimensional array is a misnomer.
 *         for <type><ident>[M]
 *              <ident> evaluates to <type>*
 *             *<ident> evaluates to <type>
 *         for <type><ident>[M][N], <ident>
 *               <ident> evaluates to <type>*[N]
 *              *<ident> evaluates to <type>[N]
 *             **<ident> evaluates to <type>
 *         for <type><ident>[M][N][O], <ident>
 *                <ident> evaluates to <type>*[N][O]
 *               *<ident> evaluates to <type>[N][O]
 *                   which evaluates to <type>*[O]
 *              **<ident> evaluates to <type>*
 *             ***<ident> evaluates to <type>
 *         conceptually, however, you can think of an array of arrays
 *         as a multidimentional matrix of sorts
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define D0 2
#define D1 4
int main(int argc,char**argv,char**envp){
	argc=argc;
	argv=argv;
	envp=envp;
	printf("Content-Type: text/plain\n\n");
	int a[D0][D1]={
		{0,1,2,3},
		{4,5,6,7}
	};
	int(*b)[D0][D1]=&a;	//pointer to array of arrays of int
	int(*c)[D1]=a;		//pointer to          array  of int
	int*d=a[0];		//pointer to                    int
	int e=a[0][0];		//value                         int

	//test
	for(int i=0;i<D0;++i){
		for(int j=0;j<D1;++j){
			printf("*b[%d][%d]:%d \n",i,j,(*b)[i][j]);//note: be careful with precedence: * vs []
		}printf("\n");
	}printf("----------------------------------------\n");
	for(int i=0;i<D0;++i){
		for(int j=0;j<D1;++j){
			printf(" c[%d][%d]:%d \n",i,j,c[i][j]);
		}printf("\n");
	}printf("----------------------------------------\n");
	for(int j=0;j<D1;++j){
		printf(" c[%d]:%d \n",j,d[j]);
	}printf("\n");
	printf("----------------------------------------\n");
	printf(" e:%d \n",e);
	printf("----------------------------------------\n");
	return EXIT_SUCCESS;
}
