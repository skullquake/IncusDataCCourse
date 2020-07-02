/*!@file: ./src/main.c
 * @brief: `union` demonstration. `union`s have their members overlayed in memory,
 *         in other words the size of the union is the size of the largest member,
 *         and manipulating a `union`'s member will result in overwriting other member
 *         values, as the members share the same memory space for their values
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
typedef union A{
	int a;
	int b;
	long c;
	long d;
}A;
int main(int argc,char**argv,char**envp){
	argc=argc;
	argv=argv;
	envp=envp;
	printf("Content-Type: text/plain\n\n");
	{
		A a;
		a.a=32;
		printf("%d\n",a.a);
		printf("%d\n",a.b);
		a.b=64;
		printf("%d\n",a.a);
		printf("%d\n",a.b);
		a.c=128;
		printf("%ld\n",a.c);
		printf("%ld\n",a.d);
		a.d=-1;
		printf("%ld\n",a.c);
		printf("%ld\n",a.d);
		printf("%ld\n",a.a);
		printf("%ld\n",a.b);
		printf("%zu\n",sizeof(a));
		printf("%zu\n",sizeof(a.a));
		printf("%zu\n",sizeof(a.b));
		printf("%zu\n",sizeof(a.c));
		printf("%zu\n",sizeof(a.d));
	}
	return EXIT_SUCCESS;
}
