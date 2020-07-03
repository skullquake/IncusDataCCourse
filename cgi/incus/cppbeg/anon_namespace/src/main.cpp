/*!@file: ./src/main.c
 * @brief: anonymous `namespace` demonstration
 *         the following will limit the scope of variables, functions
 *         and types to this compilation unit
 *         Even though its anonyomous, the compiler will choose
 *         a unique name for you for your anonymous namespace
 *         If multiple anonymous namespaces appear in the same compilation
 *         unit, they will all get the same unique identifier
 */
#include<iostream>
#include"mycpplib.h"
extern "C" {
#include"myclib.h"
}
//anonymous namespace
namespace{
	//function declarations
	extern void foo(void);
	extern void bar(void);
	extern void baz(void);
}
int main(int argc,char**argv){
	std::cout<<"Content-Type: text/plain"<<std::endl<<std::endl;
	{
		foo();
		bar();
		baz();
	}
	return 0;
}
//anonymous namespace
namespace{
	//function definitions
	void foo(void){std::cout<<"foo()"<<std::endl;}
	void bar(void){std::cout<<"bar()"<<std::endl;}
	void baz(void){std::cout<<"baz()"<<std::endl;}
}

