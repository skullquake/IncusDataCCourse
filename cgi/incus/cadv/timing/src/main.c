/*!@file: ./src/main.c
 * @brief: description
 */
#include<stdio.h>    
#include<stdlib.h>  
#include <time.h>

extern double getTime(clock_t start);

int main(){  
	printf("Content-Type: text/plain\n\n");
	double msec = 0.0;
	clock_t begin = clock();
	clock_t start;
	int total = 1;

	int A[3][4] = { {11,12,13,14}, {21,22,23,24}, {31,32,33,34} };
	int (*p)[4] = A;

	start = clock();
	for (int r = 0; r < 3; ++r)
	   for (int c = 0; c < 4; ++c)
	      total += A[r][c];
	msec = getTime(start);
	printf("%d\n",total);
	printf("Nested for loop time = %f\n\n",msec);
	total = 0;

	start = clock();
	int* ap = (int*)A;
	for (int i = 0; i < 3 * 4; ++i)
	   total += *ap++;
	msec = getTime(start);
	printf("%d\n",total);
	printf("Pointer option1 time = %f\n\n",msec);
	total = 0;

	start = clock();
	for (int* ap = (int*)A; ap < (int*)(A + 3);  ++ap)
	   total += *ap;
	msec = getTime(start);
	printf("%d\n",total); 
	printf("Pointer option2 time = %f\n\n",msec);
	total = 0;

	start = clock();
	for (int* ap = (int*)A, *e = (int*)(A + 3); ap < e;  ++ap)
	   total += *ap; 
	msec = getTime(start);
	printf("%d\n",total);  
	printf("pointer option3 time = %f\n\n",msec);

	msec = getTime(begin);
	printf("Total time = %f\n\n",msec);
}

double getTime( clock_t start)
{
  clock_t end = clock() - start;
  return (end * 1000.0 / CLOCKS_PER_SEC);
}
