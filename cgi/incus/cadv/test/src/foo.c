#include"foo.h"
#include<stdio.h>
void foo(void){
	printf("foo()\n");
}
#ifdef DEBUG
#include<stdlib.h>
int main(void){
	foo();
	return EXIT_SUCCESS;
}
#endif
