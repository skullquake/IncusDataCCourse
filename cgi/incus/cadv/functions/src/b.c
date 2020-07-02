#include"b.h"
void bfevv(void){
	bfsvv();
}
void bfevi(int a){
	bfsvi(a);
}
int  bfeiv(void){
	return bfsiv();
}
int  bfeii(int a){
	return bfsii(a);
}
//static functions
void bfsvv(void){
}
void bfsvi(int a){
	a=a;//quiet
}
int  bfsiv(void){
	return 42;
}
int  bfsii(int a){
	return a;
}
