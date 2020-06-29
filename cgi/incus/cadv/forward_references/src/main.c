/*!@file: ./src/main.c
 * @brief: Forward references demonstration
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

//you can create pointers, declarations of pointers, functions taking pointers to, 
//and declarations of functions taking pointers to a struct type prior to the
//definition of a struct, but just pointers, not variables
extern struct MYSTRUCT*a;
struct MYSTRUCT*a;
extern void b(struct MYSTRUCT*a);
void b(struct MYSTRUCT*a){}
/* in fact you dont even have to define the struct
typedef struct MYSTRUCT{
	int a;
	int b;
}MYSTRUCT;
*/
 
//you can create pointers, declarations of pointers, functions taking pointers to, 
//and declarations of functions taking pointers to a union type prior to the
//definition of a union but just pointers, not variables
extern union MYUNION*c;
union MYUNION*c;
extern void d(union MYUNION*a);
void d(union MYUNION*a){}
/* in fact you dont even have to define the union
typedef union MYUNION{
	int a;
	int b;
}MYUNION;
*/

//you can create pointers, declarations of pointers, functions taking pointers to, 
//and declarations of functions taking pointers to a enum type prior to the
//definition of a enum but just pointers, not variables
extern enum MYENUM*e;
enum MYENUM*e;
extern void f(enum MYENUM*a);
void f(enum MYENUM*a){}
/* in fact you dont even have to define the enum
typedef enum MYENUM{
	myenum_a=0,
	myenum_b=1,
	myenum_c=2,
	myenum_d=3
}MYENUM;
*/

//the above behavior allows you to use references to structs in other structs
typedef struct STRUCTA{
	int foo;
	int bar;
	struct STRUCTB* baz;//references STRUCTA, which is not yet defined
}STRUCTA;
typedef struct STRUCTB{
	int qux;
	struct STRUCTA* klutz;//references STRUCTB, which is already defined
}STRUCTB;

int main(int argc,char**argv,char**envp){
	argc=argc;
	argv=argv;
	envp=envp;
	printf("Content-Type: text/plain\n\n");
	return EXIT_SUCCESS;
}
