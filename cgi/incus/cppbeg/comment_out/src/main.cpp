/*!@file: ./src/main.c
 * @brief: Various ways of commenting out statements
 */
#include<iostream>
#include"mycpplib.h"
	extern "C" {
#include"myclib.h"
}
int main(int argc,char**argv){
	std::cout<<"Content-Type: text/plain"<<std::endl<<std::endl;
#if 0
int a;
#endif
// int a;
/*
int a;
*/
	return 0;
}
