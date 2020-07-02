/*!@file: ./src/main.c
 * @brief: `constexpr` demonstration
 *         'constexpr' was intruduced in c++ 11, and allows compile time evaluation
 *         of expressions, so you can't use something like a cout or non-`constexpr`
 *         function call,
 *         its mainly to increase performance
 *         `constexrp` should also be used instead of symbolic constants defined using
 *         the prepcossor in C++
 *         `constexpr` can be used for variables, functions, and objects
 *         references:
 *             https://www.educative.io/edpresso/what-is-the-constexpr-keyword-in-cpp
 */
#include<iostream>
#include"mycpplib.h"
	extern "C" {
#include"myclib.h"
}
//regular preprocessor defined symbolic constant
#define FOO 12345678
#define BAR(P0) (P0*2)
#define BAZ BAR(42)
//constexpr, evaluated at compile time
constexpr long foo=87654321;
//constexpr function
// return type cannot be void
// can only call other constexpr functions
// can only refer to its parameters and other global const variables
constexpr long bar(long p0){
	return p0*2;
};
constexpr long baz=bar(42);
//constexpr objects
//all non-static members must be initialized
//members must have constexpr constructors, e.g. basic data types
class Coord{
	public:
		//constexpr constructor
		//constructor must be defined as default or delete, otherwise its body must be empty
		constexpr Coord(int px,int py):mx(px),my(py){}
		//constexpr methods, follows normal constexpr function rules
		constexpr int getx(){return this->mx;}
		constexpr int gety(){return this->my;}
	private:
		int mx;
		int my;
};
int main(int argc,char**argv){
	std::cout<<"Content-Type: text/plain"<<std::endl<<std::endl;
	std::cout<<FOO<<std::endl;
	std::cout<<BAR(42)<<std::endl;
	std::cout<<BAZ<<std::endl;
	std::cout<<foo<<std::endl;
	std::cout<<bar(42)<<std::endl;//arguments must be literal/const
	std::cout<<baz<<std::endl;
	{
		Coord c(4,2);
		std::cout<<"["<<c.getx()<<":"<<c.gety()<<"]"<<std::endl;
	}
	{
		Coord c(2,4);
		std::cout<<"["<<c.getx()<<":"<<c.gety()<<"]"<<std::endl;
	}
	
	return 0;
}
