/*!@file: ./src/main.c
 * @brief: conditional inclusion based on if a symbolic preprossor symbol is defined
 */
#include<iostream>
#include"mycpplib.h"
	extern "C" {
#include"myclib.h"
}
int main(int argc,char**argv){
	std::cout<<"Content-Type: text/plain"<<std::endl<<std::endl;
#define FOO
#ifdef FOO
std::cout<<"FOO"<<std::endl;
#endif
#if defined FOO
std::cout<<"FOO"<<std::endl;
#endif
	return 0;
}
