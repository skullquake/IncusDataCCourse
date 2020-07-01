/*!@file ./src/incus/cadv/example03.c
 * @brief Macro exercise
 * Write a macro ADD(x,y,z,n) such that z[i]=x[i]+y[i]
 */
#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#define ADD(x, y, z, n) do{\
	assert(x);\
	assert(y);\
	assert(z);\
	assert(n > 0);\
	assert( sizeof(n) == sizeof(size_t) );\
	for(size_t i=0; i<n; ++i ) {\
		z[i] = x[i] + y[i];\
	}\
}while(0)
void macrotest(void){
	int a[] = {0, 1, 2, 3};
	int b[] = {0, 2, 4, 8};
	size_t sza = sizeof(a) / sizeof(*a);
	int c[sza];
	printf("a:\n");
	for(int i = 0; i < sza; ++i ) {
		printf("a[%d]: %d\n", i, a[i]);
	}
	printf("----------------------------------------\n");
	printf("b:\n");
	for(int i=0; i < sza; ++i ) {
		printf("b[%d]: %d\n", i, b[i] );
	}
	printf("----------------------------------------\n");
	ADD(a, b, c, sza);
	printf("c:\n");
	for(int i = 0; i < sza; ++i ) {
		printf("c[%d]: %d\n", i, c[i]);
	}
	printf("----------------------------------------\n");

}
