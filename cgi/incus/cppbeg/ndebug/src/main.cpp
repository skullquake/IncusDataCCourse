/*!@file: ./src/main.c
 * @brief: `NDEBUG`, for statements that should compile when doing debug compile
 */
#include<iostream>
#include"mycpplib.h"
	extern "C" {
#include"myclib.h"
}
int main(int argc,char**argv){
	std::cout<<"Content-Type: text/plain"<<std::endl<<std::endl;
//for this to execute, compile without -DNDEBUG, you can edit the makefile for
//this, and should in fact have a release and debug target in your makefile
#ifndef NDEBUG
	std::cerr<<"Only when debugging"<<std::endl;
#endif
	return 0;
}
