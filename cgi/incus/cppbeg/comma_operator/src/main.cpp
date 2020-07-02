/*!@file: ./src/main.c
 * @brief: Comma operator demonstration. The comma operator
 *         has a guaranteed left to right execution order
 */
#include<iostream>
#include"mycpplib.h"
extern "C" {
#include"myclib.h"
}
int g=10;
int f1(){
	g+=5;
	return g;
}
int f2(){
	g-=2;
	return g;
}
int main(int argc,char**argv){
	std::cout<<"Content-Type: text/plain"<<std::endl<<std::endl;
	std::cout<<(f1(),f2())<<std::endl; // f1();f2(), the result will be that of f2()
	return 0;
}
