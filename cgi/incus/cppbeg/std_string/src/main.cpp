/*!@file: ./src/main.c
 * @brief: `std::string` demonstration
 */
#include<iostream>
#include"mycpplib.h"
	extern "C" {
#include"myclib.h"
}
int main(int argc,char**argv){
	std::cout<<"Content-Type: text/plain"<<std::endl<<std::endl;
	std::string a;
	std::string b();
	std::string c{};
	std::string d{"lorem"};
	std::string e("lorem");
	std::string f(4,'_');
	return 0;
}
