/*!@file: ./src/main.c
 * @brief: Using namespaces with one identifer, not entire namespace.
 *         Often we do not want to use the entire namespace, just
 *         some variables, functions, or classes from that namespace.
 *         We can do this with the using keyword as illustrated in 
 *         the following.
 */
#include<iostream>
#include"mycpplib.h"
	extern "C" {
#include"myclib.h"
}
namespace foo{
	int a=42;
	int b=24;
}
int main(int argc,char**argv){
	std::cout<<"Content-Type: text/plain"<<std::endl<<std::endl;
	std::cout<<foo::a<<std::endl;
	std::cout<<foo::b<<std::endl;
	{
		using namespace foo;
		std::cout<<a<<std::endl;
		std::cout<<b<<std::endl;
	}
	{
		using foo::a;
		std::cout<<a<<std::endl;
		std::cout<<foo::b<<std::endl;
	}
	{
		using foo::b;
		std::cout<<foo::a<<std::endl;
		std::cout<<b<<std::endl;
	}
	{
		using foo::a;
		using foo::b;
		std::cout<<a<<std::endl;
		std::cout<<b<<std::endl;
	}
	return 0;
}
