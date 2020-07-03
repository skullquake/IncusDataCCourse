/*!@file: ./src/main.c
 * @brief: `inline` is a keyword used with function definitions.
 *         The compile will replace the function call with the definition
 *         of the inline function instead of referring to the function
 *         definition at runtime, i.e. performing a function call with
 *         jumps, argument copying, etc. `inline` serves as a hint to the
 *         compiler, if the function is too big, the compiler will not
 *         perform the inline.
 *
 *         We usually use inline on small functions that are called often.
 *
 *         references:
 *             http://www.cplusplus.com/articles/2LywvCM9/
 */
#include<iostream>
#include"mycpplib.h"
extern "C" {
#include"myclib.h"
}
namespace{
	class Foo{
		public:
			inline int add(int a,int b){
				return a+b;
			}
			int mul(int a,int b);
	};
}
int main(int argc,char**argv){
	std::cout<<"Content-Type: text/plain"<<std::endl<<std::endl;
	Foo f;
	std::cout<<f.add(1,2)<<std::endl;
	std::cout<<f.mul(3,4)<<std::endl;
	return 0;
}
namespace{
	inline int Foo::mul(int a,int b){
		return a*b;
	}
}
