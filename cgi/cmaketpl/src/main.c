/*!@file  main.c
*  @brief template cgi
*/
#include "main.h"
int main(int argc,char* argv[],char**envp){
	printf("Content-Type: text/plain\r\n\r\n");
	printf("Hello");
	return EXIT_SUCCESS;
}
