/*!@file: ./src/main.c
 * @brief: description
 */
#include<iostream>
extern "C" {
	#include"myclib.h"
}
#include"mycpplib.h"
#include"foo.h"
#include"bar.h"
#include"baz.h"
int main(int argc,char**argv){
	std::cout<<"Content-Type: text/plain"<<std::endl<<std::endl;
	foo();
	bar();
	baz();
	return 0;
}
