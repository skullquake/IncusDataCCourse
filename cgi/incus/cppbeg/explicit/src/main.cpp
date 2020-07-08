/*!@file: ./src/main.c
 * @brief: `explicit` demonstration.
 *         In C++ a constructor with only one required argument is considered a
 *         conversion constructor. It converts the paramter type to a class type.
 *         `explicit` can be applied to constructors and conversion functions.
 *         When you have a class with a constructor that takes a single
 *         parameter of some type, the compiler can convert other types
 *         to that type in some situations, for example if you have a class
 *         that has a constructor that takes an `int`, and you have another
 *         function with a parameter of that class, you can call that function
 *         with an `int` value as argument and the compiler will call the
 *         constructor for you
 *
 *         `explicit` inhibits the compiler from automatically choosing
 *         a given constructor for you
 */
#include<iostream>
#include"mycpplib.h"
extern "C" {
#include"myclib.h"
}
namespace{
	class C0{
		public:
			C0(int pa):ma(pa){};
			friend std::ostream&operator<<(std::ostream&os,const C0&c0);
		protected:
		private:
			int ma;
	};
	void f0(C0 c0);
	class C1{
		public:
			explicit C1(int pa):ma(pa){};
			friend std::ostream&operator<<(std::ostream&os,const C1&c1);
		protected:
		private:
			int ma;
	};
	void f1(C1 c1);
}
int main(int argc,char**argv){
	std::cout<<"Content-Type: text/plain"<<std::endl<<std::endl;
	{
		f0(42);
		//f1(42);
		f1(static_cast<C1>(42));//we have to explicitly cast
		f1((C1)42);//we have to explicitly cast
	}
	return 0;
}
namespace{
	std::ostream&operator<<(std::ostream&os,const C0&c0){
		os<<c0.ma;
		return os;
	}
	void f0(C0 c0){
		std::cout<<c0<<std::endl;
	}
	std::ostream&operator<<(std::ostream&os,const C1&c1){
		os<<c1.ma;
		return os;
	}
	void f1(C1 c1){
		std::cout<<c1<<std::endl;
	}
}
