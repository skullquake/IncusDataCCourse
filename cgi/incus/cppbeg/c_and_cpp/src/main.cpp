/*!@file: ./src/main.c
 * @brief: See README.md
 */
#include<iostream>
#include"foo.h"
#include"bar.h"
int main(int argc,char**argv){
	std::cout<<"Content-Type: text/plain"<<std::endl<<std::endl;
	foo();
	bar();
	return 0;
}
