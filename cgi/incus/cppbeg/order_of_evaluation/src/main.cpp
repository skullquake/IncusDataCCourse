/*!@file: ./src/main.c
 * @brief: Demonstrating danger of depending on order of evaluation
 */
#include<iostream>
#include"mycpplib.h"
extern "C" {
#include"myclib.h"
}
int global=12;
int f1(){
	global+=5;
	return global;
}
int f2(){
	global-=2;
	return global;
}
int main(int argc,char**argv){
	std::cout<<"Content-Type: text/plain"<<std::endl<<std::endl;
	int result=f1()+f2();	//L->R 17+15=32
				//R->L 15+10=25
	std::cout<<result<<std::endl;
	return 0;
}
