/*!@file: ./src/main.c
 * @brief: The `nothrow` keyword can be used with `new` to ensure
 *         no exception is thrown if memeory could not be allocated.
 *         This is a bit difficult to test, but the following serves
 *         as illustration on how to make the `new` operator not throw
 *         an exception.
 */
#include<iostream>
#include"mycpplib.h"
extern "C" {
#include"myclib.h"
}
int main(int argc,char**argv){
	std::cout<<"Content-Type: text/plain"<<std::endl<<std::endl;
	{//normal new
	}
	{//nothrow new
	}
	return 0;
}
