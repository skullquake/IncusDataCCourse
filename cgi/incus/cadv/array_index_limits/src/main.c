/*!@file: ./src/main.c
 * @brief: Here we look at the effects of using invalid array indexes
 *         references:
 *             https://www.educative.io/edpresso/what-is-the-stack-smashing-detected-error
 *             https://stackoverflow.com/questions/1345670/stack-smashing-detected
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
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
void f0(char p0,char p1){
	char a=4;
	char b=2;
	char buf[8];
	char c=42;
	char d=24;
	printf("sp:  %p\n",getrsp());
	printf("&p0: %p\n",&p0);
	printf("&p1: %p\n",&p1);
	printf("&a:  %p\n",&a);
	printf("&b:  %p\n",&b);
	printf("&buf:%p\n",&buf);
	printf("&c:  %p\n",&c);
	printf("&d:  %p\n",&d);
	printf("a:   %d\n",a);
	printf("b:   %d\n",b);
	printf("c:   %d\n",c);
	printf("d:   %d\n",d);
	printf("buf[-1]=33->\n");
	buf[-1]=33;
	printf("a:   %d\n",a);
	printf("b:   %d\n",b);
	printf("c:   %d\n",c);
	printf("d:   %d\n",d);
	printf("buf[-2]=33->\n");
	buf[-2]=33;
	printf("a:   %d\n",a);
	printf("b:   %d\n",b);
	printf("c:   %d\n",c);
	printf("d:   %d\n",d);
	printf("buf[ 8]=33->\n");
	buf[ 8]=33;//stack smash detected, gcc protection for buffer overflows
	           //see -fno-stack-protector
	printf("a:   %d\n",a);
	printf("b:   %d\n",b);
	printf("c:   %d\n",c);
	printf("d:   %d\n",d);
	printf("buf[ 9]=33->\n");
	buf[ 9]=33;//stack smash detected, gcc protection for buffer overflows
	           //see -fno-stack-protector
	printf("a:   %d\n",a);
	printf("b:   %d\n",b);
	printf("c:   %d\n",c);
	printf("d:   %d\n",d);

}
int main(void){
	printf("Content-Type: text/plain\n\n");
	f0(1,2);
	return EXIT_SUCCESS;
}
