/*!@file: ./src/main.c
 * @brief: Compound array literals demonstration.
 *         C99 has compound literals, which allows you to create array and structured types on the fly.
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
/*!brief Main driver
 *
 * The main entry point of the program
 *
 * @param argc Argument count
 * @param argv Argument vector
 * @param envp Environment pointer
 * @return 'int' used for exit code
 */
int main(int argc,char**argv,char**envp){
	argc=argc;
	argv=argv;
	envp=envp;
	printf("Content-Type: text/plain\n\n");
	{
		int*a;
		int*pos;
		int*beg;
		int*end;
		{
			a=(int[]){0,1,2,3};//compound literal
			beg=a;
			pos=a;
			end=beg+4;
			printf("a:  %p\n",(void*)a);
			printf("beg:%p\n",(void*)beg);
			printf("pos:%p\n",(void*)pos);
			printf("end:%p\n",(void*)end);
			while(pos!=end){
				printf("%d ",*pos);
				++pos;
			}printf("\n");
		}
		{
			a=(int[]){4,5,6,7,8,9};//compound literal
			beg=a;
			pos=a;
			end=beg+6;
			printf("a:  %p\n",(void*)a);
			printf("beg:%p\n",(void*)beg);
			printf("pos:%p\n",(void*)pos);
			printf("end:%p\n",(void*)end);
			while(pos!=end){
				printf("%d ",*pos);
				++pos;
			}printf("\n");
		}
		{
			a=(int[]){10,11};//compound literal
			beg=a;
			pos=a;
			end=beg+2;
			printf("a:  %p\n",(void*)a);
			printf("beg:%p\n",(void*)beg);
			printf("pos:%p\n",(void*)pos);
			printf("end:%p\n",(void*)end);
			while(pos!=end){
				printf("%d ",*pos);
				++pos;
			}printf("\n");
		}
		{
			typedef struct S{
				int a;
				int b;
			}S;
			S s;
			s=(S){1,2};
			printf("s:%p\n",(void*)&s);
			printf("s.a:%d\n",s.a);
			printf("s.b:%d\n",s.b);
			s=(S){3,4};
			printf("s:%p\n",(void*)&s);
			printf("s.a:%d\n",s.a);
			printf("s.b:%d\n",s.b);
			s=(S){5,6};
			printf("s:%p\n",(void*)&s);
			printf("s.a:%d\n",s.a);
			printf("s.b:%d\n",s.b);
		}
	}
	return EXIT_SUCCESS;
}
