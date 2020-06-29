/*!@file: ./src/main.c
 * @brief: Demonstrating can array of pointers
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
int main(int argc,char**argv,char**envp){
	argc=argc;
	argv=argv;
	envp=envp;
	printf("Content-Type: text/plain\n\n");
	{
		char*buf[]={
			"a",
			"ab",
			"abc",
			"abcd",
			NULL//delimiter, for iteration
		};
		char**pos=buf;//remember, buf yields a pointer to a pointer
		while(*pos!=NULL){
			printf("%s\n",*pos);
			pos++;
		}
	}
	return EXIT_SUCCESS;
}
