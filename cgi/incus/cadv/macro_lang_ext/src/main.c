/*!@file: ./src/main.c
 * @brief: You can use preprocessor directives to create your own keywords and constructs, as illustrated
 *         in the following example with repeat and until
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define repeat do
#define until(x) while((!x))
int main(int argc,char**argv,char**envp){
	argc=argc;
	argv=argv;
	envp=envp;
	unsigned int i=8;
	printf("Content-Type: text/plain\n\n");
	repeat
	{
		printf("%d\n",i);
		--i;
	}
	until(i==0);
	return EXIT_SUCCESS;
}
