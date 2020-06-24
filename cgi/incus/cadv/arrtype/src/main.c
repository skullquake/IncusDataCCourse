/*!@file  main.c
 * @brief array pointer and types exercise
 */
#include "main.h"
int sum2d (int parm[][3], int rows);
/*! main driver function
 * \param argc argument count
 * \param argv argument vector
 * \param envp environment vector, for cgi (not used here)
 */
int main(int argc,char* argv[],char**envp){
	printf("Content-Type: text/plain\r\n\r\n");
		//---------------------------------
		//take special note of the types!!!
		//---------------------------------
	int arr[3]={11,22,33};		// array of int of size 3
	int*x     =&arr[0];		// int*
	int*y     =arr;			// int*
	int(*z)[3]=&arr;		// int*[3], pointer to array of int of size 3
	printf("x = %p\n",(void*)x);	// verify address |
	printf("y = %p\n",(void*)y);	// verify address |- verify all addresses are equal
	printf("z = %p\n",(void*)z);	// verify address |
		//---------------------------------
		//take special note of the types!!!
		//---------------------------------
	int bar[4][3];				// type: int[4][3]
	int (*a)[3]      = &bar[0];		// type: int*[3]
	int (*b)[3]      =  bar;		// type: int*[3]
	int (*c)[4][3]   = &bar;		// type: int*[4][3]
	int*  d          =  bar[0];		// type: int*
	int   e          =  bar[0][0];		// type: int
	int*  f          = &bar[0][0];		// type: int*
	int total = sum2d(bar, 4);		// test passing array pointer to function
	    total = sum2d(b,   4);		// test passing array pointer to function
	    total = sum2d(a,   4);		// test passing array pointer to function
	return EXIT_SUCCESS;
}
/*! sample function for testing passing array pointers
 * \param parm pointer to array of int of size 3
 * \rows number of rows
 */
// int sum2d (int (*parm)[3], int rows) {
int sum2d (int parm[][3], int rows) {
   int sum = 0;
   for (int i = 0; i < rows; ++i)
      for (int j = 0; j < 3; ++j)
         sum += parm[i][j];
   return sum;
   }
