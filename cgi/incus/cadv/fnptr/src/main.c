/*!@file: ./src/main.c
 * @brief: function pointers as arguments to function
 */
#include<stdio.h>
#ifdef __BORLANDC__
	#define EXIT_SUCCESS 0
	#define EXIT_FAILURE 1
#else
	#include<stdlib.h>
	#include<stdbool.h>
#endif
void foo(void){
	printf("void foo(void)\n");
}
void bar(void){
	printf("void bar(void)\n");
}
void baz(void){
	printf("void baz(void)\n");
}
void  fnvv(void){printf("fnvv()\n");}
void  fnvi(int a){printf("fnvi():%d\n",a);}
void  fnvii(int a,int b){printf("fnvii():%d,%d\n",a,b);}
void  fnviii(int a,int b,int c){printf("fnviii():%d,%d,%d\n",a,b,c);}
int   fniv(void){printf("fniv()\n");return 42;}
int   fnii(int a){printf("fnii():%d\n",a);return a;}
int   fniii(int a,int b){printf("fniii():%d,%d\n",a,b);return a+b;}
int   fniiii(int a,int b,int c){printf("fniiii():%d,%d,%d\n",a,b,c);return a+b+c;}
void  fnvf(float a){printf("fnvf():%f\n",a);}
void  fnvff(float a,float b){printf("fnvff():%f,%f\n",a,b);}
void  fnvfff(float a,float b,float c){printf("fnvfff():%f,%f,%f\n",a,b,c);}
float fnfv(void){printf("fnfv()\n");return 4.2;}
float fnff(float a){printf("fnff():%f\n",a);return a;}
float fnfff(float a,float b){printf("fnfff():%f,%f\n",a,b);return a+b;}
float fnffff(float a,float b,float c){printf("fnffff():%f,%f,%f\n",a,b,c);return a+b+c;}
void dowork(int*beg,int*end,void(*cb)(int)){
	while(beg!=end){
		cb(*beg);
		++beg;
	}
}
void f0(int i){
	printf("%d\n",i);
}
void f1(int i){
	printf("%d\n",i*2);
}

int  main(int argc,char**argv,char**envp){
	argc=argc;
	argv=argv;
	envp=envp;//shutup
	printf("Content-Type: text/plain\n\n");

	{
		int buf[]={0,1,2,3};
		dowork(buf,buf+4,f0);
		dowork(buf,buf+4,f1);
	}
	//single function pointer
	{
		void (*fp)(void);
		fp=&foo;
		(*fp)();
	}
	//array of function pointers
	{
		void (*fp[3])(void)={&foo,&bar,&baz};
		int i;
		for(i=0;i<(sizeof(fp)/sizeof(fp[0]));i++){
			(*fp[i])();
		}
	}
	//function pointer types
	//note the peculiar declaration syntax where the type encapsulates
	//the identifier, here ar some example of definining and
	//and initializing function pointer variables
	{
		void(*a)(void)=fnvv;
		void(*b)(int)=fnvi;
		void(*c)(int,int)=fnvii;
		void(*d)(int,int,int)=fnviii;
		int(*e)(void)=fniv;
		int(*f)(int)=fnii;
		int(*g)(int,int)=fniii;
		int(*h)(int,int,int)=fniiii;
		void(*i)(float)=fnvf;
		void(*j)(float,float)=fnvff;
		void(*k)(float,float,float)=fnvfff;
		float(*l)(void)=fnfv;
		float(*m)(float)=fnff;
		float(*n)(float,float)=fnfff;
		float(*o)(float,float,float)=fnffff;
	}
	//function call operator
	//() is actually an operator, which can take multiple or no
	//operands
	{
		float(*a)(float)=fnff;
		printf("%d\n",a(42));
#if 0 /* the following will most likely crash the program */
      /* as we are casting a function expectgin an int    */
      /* and returning an int to one expecting a float    */
      /* and returning a float                            */
		float(*b)(float)=(float(*)(float))fnii;
		printf("%d\n",c(42));
#endif
		void(*c)(float)=(void(*)(float))fnvi;
		c(42);
		void(*d)(int)=(void(*)(int))fnvf;
		d(4.2);
	}
	{//use of typedef
		typedef void( *FVV) (void);
		typedef void( *FVI) (int);
		typedef void( *FVII )(int,int);
		typedef void( *FVIII)(int,int,int);
		typedef int(  *FIV  )(void);
		typedef int(  *FII  )(int);
		typedef int(  *FIII )(int,int);
		typedef int(  *FIIII)(int,int,int);

	}
	{//declaring array of function pointers
	 //again, note the unconventional syntax
		void(*a[5])(void)={
			fnvv,
			fnvv,
			fnvv,
			fnvv,
			NULL
		};
		{//call first function
			a[0]();
		}
		{//define pointer to pointer to function to point
		 //to the first function in the array
			void(**pos)(void)=a;
			//iterate and execute, depends on NULL delimiter
			while(*pos){
				(*pos)();
				pos=pos+1;
			}
		}
		//verify sizes
		printf("sizeof(void(*)(void)): %d\n",sizeof(void(*)(void)));
		printf("sizeof(void(*[5])(void)): %d\n",sizeof(void(*[5])(void)));
		printf("sizeof(a):%d\n",sizeof(a));
		printf("sizeof(*a):%d\n",sizeof(*a));
		printf("sizeof(a)/sizeof(*a):%d\n",sizeof(a)/sizeof(*a));
		//iterate without NULL delimiter using size computation
		//with sizeof, using pointer iterators
		{
			void(**beg)(void)=a;
			void(**end)(void)=a+(sizeof(a)/sizeof(*a));
			void(**pos)(void);
			for(pos=beg;pos!=end;++pos){
				if(*pos!=NULL){//remember to check for NULL
					(*pos)();
				}else{
				}
			}
		}
	}
	return 0;
}
