/*!@file: ./src/main.c
 * @brief: working with arrays of pointers to TYPE
 *         the main benifit is saving on space, instead of using TYPE[][N], we use
 *         TYPE*[]
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
			"foo",
			"foobar",
			"foobarbaz",
			"foobarbazqux",
			"foobarbazquxklutz",
			""//mark end with \0, can also use NULL
		};//array of pointers of char, buf -t-> **char
		char**pos=buf;//buf -t-> char**
		while(**pos){//until \0, if we used NULL, test with *pos
			printf("%s\n",*pos++);//derefence iterator to char* and postincrement
		}
	}
	{
		char*buf[]={
			(char*)calloc(8,sizeof(char)),
			(char*)calloc(8,sizeof(char)),
			(char*)calloc(8,sizeof(char)),
			(char*)calloc(8,sizeof(char)),
			""//mark end with \0, can also use NULL
		};//array of pointers of char*, buf -t-> **char
		snprintf(buf[0],8,"0");
		snprintf(buf[1],8,"01");
		snprintf(buf[2],8,"012");
		snprintf(buf[3],8,"0123");
		char**pos=buf;//buf -t-> char**
		while(**pos){//until \0, if we used NULL, test with *pos
			printf("%s\n",*pos++);//derefence iterator to char* and post increment
		}

	}
	return EXIT_SUCCESS;
}
