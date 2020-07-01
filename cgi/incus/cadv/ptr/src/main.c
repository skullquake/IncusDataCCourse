/*!@file: ./src/main.c
 * @brief: array to arrays iteration with pointers
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdlib.h>
#include"cJSON/cJSON.h"
int main(int argc,char**argv,char**envp){
	argc=argc;
	argv=argv;
	envp=envp;//shutup
	printf("Content-Type: text/plain\n\n");
	{
		int a;
		int*b;
		char*c;
		void*d;
		b=&a;
		printf("b: %p\n",b++);
		printf("b: %p\n",b++);
		printf("b: %p\n",b++);
		printf("b: %p\n",b++);
		c=(char*)&a;
		printf("c: %p\n",c++);
		printf("c: %p\n",c++);
		printf("c: %p\n",c++);
		printf("c: %p\n",c++);
		c=(char*)&a;
		printf("c: %p\n",c);c+=sizeof(a);
		printf("c: %p\n",c);c+=sizeof(a);
		printf("c: %p\n",c);c+=sizeof(a);
		printf("c: %p\n",c);c+=sizeof(a);
		d=(void*)&a;
		printf("d: %p\n",d++);
		printf("d: %p\n",d++);
		printf("d: %p\n",d++);
		printf("d: %p\n",d++);
		d=(void*)&a;
		printf("d: %p\n",d);d+=sizeof(a);
		printf("d: %p\n",d);d+=sizeof(a);
		printf("d: %p\n",d);d+=sizeof(a);
		printf("d: %p\n",d);d+=sizeof(a);
	}
	{//pointer to pointer
		int a=42;
		int*b=&a;
		int**c=&b;
		int d=24;
		printf("  a:%d\n",  a);
		printf(" &a:%p\n", &a);
		printf("  b:%p\n",  b);
		printf(" *b:%d\n", *b);
		printf("  c:%p\n",  c);
		printf(" *c:%p\n", *c);
		printf("**c:%d\n",**c);
		printf("*c=&d;/*d is another integer variable different from a*/\n");
		*c=&d;
		printf("  b:%p\n",  b);
		printf(" *b:%d\n", *b);
	}
	{//pointer to pointer
		void**a;
		void**b;
		a=&b;
		b=&a;
		printf("  a: pointer to pointer of type void initialized to address of b\n");
		printf("  b: pointer to pointer of type void initialized to address of a\n");
		printf("  Various tests confirming value and address, with multiple 'back indirections'\n");
		printf("  a:.........................%p\n",a);
		printf(" *a:.........................%p\n",*a);
		printf("  b:.........................%p\n",b);
		printf(" *b:.........................%p\n",*b);
		printf(" *a==b:......................%s\n",*a==b?"true":"false");
		printf(" *b==a:......................%s\n",*b==a?"true":"false");
		printf(" *(void**)a:.................%p\n",*(void**)a);
		printf(" *(void**)b:.................%p\n",*(void**)b);
		printf(" *(void**)*a==a:.............%s\n",*(void**)*a==a?"true":"false");
		printf(" *(void**)*b==b:.............%s\n",*(void**)*b==b?"true":"false");
		printf(" *(void**)*(void**)a:........%p\n",*(void**)*(void**)a);
		printf(" *(void**)*(void**)b:........%p\n",*(void**)*(void**)b);
		printf(" *(void**)*(void**)*a==*a:...%s\n",*(void**)*(void**)*a==*a?"true":"false");
		printf(" *(void**)*(void**)*b==*b:...%s\n",*(void**)*(void**)*b==*b?"true":"false");
		/*
		*/
	}
	{
		char buf[4][4]={
			{'a','b','c','d'},
			{'e','f','g','h'},
			{'i','j','k','l'},
			{'m','n','o','p'}
		};
		char*beg=(char*)buf;
		char*end=(char*)buf+(sizeof(buf));
		for(char*pos=beg;pos!=end;++pos){
			putchar(*pos);
			if((pos-beg)!=0&&(pos-beg)%4==0)putchar('\n');
		}printf("\n");
	}
	{//size of pointers
	 //note the sizes are all the same
		printf("sizeof(unsigned char*):        %zu\n",sizeof(unsigned char*));
		printf("sizeof(signed char*):          %zu\n",sizeof(signed char*));
		printf("sizeof(unsigned short*):       %zu\n",sizeof(unsigned short*));
		printf("sizeof(signed short*):         %zu\n",sizeof(signed short*));
		printf("sizeof(unsigned int*):         %zu\n",sizeof(unsigned int*));
		printf("sizeof(signed int*):           %zu\n",sizeof(signed int*));
		printf("sizeof(unsigned long*):        %zu\n",sizeof(unsigned long*));
		printf("sizeof(signed long*):          %zu\n",sizeof(signed long*));
		printf("sizeof(unsigned long long*):   %zu\n",sizeof(unsigned long long*));
		printf("sizeof(signed long long*):     %zu\n",sizeof(signed long long*));
		printf("sizeof(signed float*):         %zu\n",sizeof(float*));
		printf("sizeof(signed double*):        %zu\n",sizeof(double*));
		printf("sizeof(struct{int a;int b;}*): %zu\n",sizeof(struct{int a;int b;}*));
		printf("sizeof(void(*)(void)):         %zu\n",sizeof(void(*)(void)));
		printf("sizeof((*)[8]):                %zu\n",sizeof(int(*)[8]));
	}

	return EXIT_SUCCESS;
}
