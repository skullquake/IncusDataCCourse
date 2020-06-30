/*!@file: ./src/main.c
 * @brief: pointer pointing to itself
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
int main(void){
	void*a;
	a=(void*)&a;
	printf("Content-Type: text/plain\n\n");
	printf("%p\n",&a);
	printf("%p\n",a);
	return EXIT_SUCCESS;
}
