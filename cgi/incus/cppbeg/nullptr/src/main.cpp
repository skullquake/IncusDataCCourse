/*!@file: ./src/main.c
 * @brief: `nullptr` demonstration. Instead of using `0` or `NULL`,
 *         in C++ it is recommended to use `nullptr`
 */
#include<iostream>
#include"mycpplib.h"
extern "C" {
#include"myclib.h"
}
int main(int argc,char**argv){
	std::cout<<"Content-Type: text/plain"<<std::endl<<std::endl;
	int*a=nullptr;
	a=new int();
	if(a!=nullptr){
		delete a;
		a=nullptr;
	}else{
		std::cerr<<"Failed to allocate int"<<std::endl;
	}
	return 0;
}
