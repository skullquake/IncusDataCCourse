/*!@file: ./src/main.c
 * @brief: Here we observe the precedence of the * dereferencing operator
 */
#include<iostream>
#include"mycpplib.h"
extern "C" {
#include"myclib.h"
}
int main(int argc,char**argv){
	std::cout<<"Content-Type: text/plain"<<std::endl<<std::endl;
	int a[4]={0,1,2,3};
	for(int i=0;i<4;++i){
		std::cout<<a[i]<<std::endl;
	}std::cout<<"----------------------------------------"<<std::endl;
	++*a; // ++(*a)
	for(int i=0;i<4;++i){
		std::cout<<a[i]<<std::endl;
	}std::cout<<"----------------------------------------"<<std::endl;
#if 0 // wont compile
	std::cout<<(*++a)<<std::endl;
#endif
	return 0;
}
