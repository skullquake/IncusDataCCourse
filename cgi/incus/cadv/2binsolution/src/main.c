/*!@file  main.c
*  @brief to binary test program
*/
#include"main.h"
#include"tobin.h"
int main(int argc,char* argv[],char**envp){
	printf("Content-Type: text/plain\r\n\r\n");
	printf("Hello");
	char buf[sizeof(uint64_t) * 8 + 1] = {0};
	printf("123 in binary: %s\n", tobin(buf, 123ULL, 16));
	printf("-1 in binary: %s\n", tobin(buf, -1, sizeof(uint64_t) * 8));
	return EXIT_SUCCESS;
}
