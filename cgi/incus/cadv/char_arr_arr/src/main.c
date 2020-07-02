/*!@file: ./src/main.c
 * @brief: array of array of characters
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
int main(int argc,char**argv,char**envp){
	argc=argc;
	argv=argv;
	envp=envp;
	printf("Content-Type: text/plain\n\n");
	char buf[4][4]={
		"foo",
		"bar",
		"baz",
		""//only consists of \0, so first character is a \0
	};
	char(*p)[4/* try 2 */]=buf;//note specifying the size of the array affects the increment operator
	while(**p){//until first character is \0
		printf("%s\n",*p++);
	}
	return EXIT_SUCCESS;
}
