/*!@file: ./src/main.c
 * @brief: Here we abuse the rules by making `main` do nothing
 */
#include<iostream>
#include"mycpplib.h"
	extern "C" {
#include"myclib.h"
}
namespace myspace{
	int mymain(){
		std::cout<<"My main"<<std::endl;
		return EXIT_SUCCESS;
	}
	decltype(mymain())_=mymain();
	
}
int main(){return myspace::_;}
