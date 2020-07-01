/*!@file: ./src/main.c
 * @brief: 'const' variables and pointers demonstration.
 *         
 *         
 */
#include<iostream>
#include"mycpplib.h"
extern "C" {
	#include"myclib.h"
}
int main(int argc,char**argv){
	std::cout<<"Content-Type: text/plain"<<std::endl<<std::endl;
	{
		int a=123;		//nonconst var
		const int b=321;	//const var
		int*c=&a;		//pointer nonconst, var pointed to nonconst
		const int*d=&b;		//pointer nonconst, var pointed to const
		int*const e=&a;		//pointer const, var pointed to nonconst
		const int*const f=&b;	//pointer const, var pointed to const
		
	}
	{
		//there is some flexibility as illustrated here
		//const <type>&<param>
		//<type> const&<param>
		const int a=42;	//these have...
		int const b=24;	//...the same type
		//same applies to pointers
		const int*ap=&a;
		int const*bp=&b;
		const int*const ccp=&a;
		int const*const cdp=&b;
	}
	return 0;
}
