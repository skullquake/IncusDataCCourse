/*!@file: ./src/main.c
 * @brief: description
 */
#include<iostream>
#include"mycpplib.h"
extern "C" {
#include"myclib.h"
}
int a=42;
int main(int argc,char**argv){
	std::cout<<"Content-Type: text/plain"<<std::endl<<std::endl;
	std::cout<<::a<<std::endl;
	return 0;
}
