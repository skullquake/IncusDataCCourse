/*!@file: ./src/main.c
 * @brief: functions
 */
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include"b.h"
//extern functions - defined in this compilation unit
extern void afevv(void);
extern void afevi(int);
extern int  afeiv(void);
extern int  afeii(int);
//static functions - defined in this compilation unit
static void afsvv(void);
static void afsvi(int);
static int  afsiv(void);
static int  afsii(int);
int main(int argc,char**argv,char**envp){
	argc=argc;
	argv=argv;
	envp=envp;
	printf("Content-Type: text/plain\n\n");
	//call extern from this compilation unit
	afevv();
	afevi(42);
	afeiv();
	afeii(42);
	//call extern from other compilation unit
	bfevv();
	bfevi(42);
	bfeiv();
	bfeii(42);
	return EXIT_SUCCESS;
}
void afevv(void){
	afsvv();
}
void afevi(int a){
	afsvi(a);
}
int  afeiv(void){
	return afsiv();
}
int  afeii(int a){
	return afsii(a);
}
//static functions
static void afsvv(void){
}
static void afsvi(int a){
	a=a;//quiet
}
static int  afsiv(void){
	return 42;
}
static int  afsii(int a){
	return a;
}
