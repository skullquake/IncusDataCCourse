/*!@file: ./src/main.c
 * @brief: print out the value of the stack pointer
 *         you can print out the address of the first local, that would be pretty close
 *         otherwise you can use inline assembler
 *         reference:
 *             http://blogs.umb.edu/michaelbazzinott001/2014/09/24/x86_64-get-stack-pointer-rsp/
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<inttypes.h>
unsigned long long getrsp(void){
#if defined(__clang__)
	fprintf(stderr,"getrsp:clang:unimplemented\n");
	return 0;
#elif defined(__GNUC__) || defined(__GNUG__)
	__asm__ ("movq %rsp, %rax");
#elif defined(_MSC_VER)
	fprintf(stderr,"getrsp:msvc:unimplemented\n");
	return 0;
#endif
}
void a(char p0,char p1){
#if defined(__clang__)
	printf("clang\n");
#elif defined(__GNUC__) || defined(__GNUG__)
	//register uintptr_t sp __asm__ ("sp");
	//printf("SP: 0x%016" PRIxPTR "\n", sp);
	printf("&p0:%p\n",&p0);
	printf("&p1:%p\n",&p1);
	void*b;
	printf("&b: %p\n",b);
	printf("sp: %p\n",getrsp());
	int c;
	printf("&c: %p\n",&c);
	printf("sp: %p\n",getrsp());
	int d;
	printf("&d: %p\n",&d);
	printf("sp: %p\n",getrsp());
#elif defined(_MSC_VER)
	printf("msvc\n");
#endif
}
int main(int argc,char**argv,char**envp){
	argc=argc;
	argv=argv;
	envp=envp;
	printf("Content-Type: text/plain\n\n");
	printf("%p\n",getrsp());
	a(0,0);
	printf("%p\n",getrsp());
	return EXIT_SUCCESS;
}
