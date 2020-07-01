/*!@file: ./src/main.c
 * @brief: `decltype` can be used to perform type determination at compile time.
 *         So if you have <ident> of <type> you can declare a new variable using
 *         decltype(<ident>) <newident>
 *         `decltype` can also be used on expressions, as illustrated below
 */
#include<iostream>
#include"mycpplib.h"
	extern "C" {
#include"myclib.h"
}
namespace mynamespace{
	typedef struct Foo{
		int ma;
		int mb;
		Foo(int pa,int pb):ma{pa},mb{pb}{
			std::cout<<"Foo::Foo()"<<std::endl;
		};
		~Foo(){
			std::cout<<"Foo::~Foo()"<<std::endl;
		};
		void test(){std::cout<<"Foo::test()"<<std::endl;};
	}Foo;
	typedef struct Bar{
		int ma;
		int mb;
		Bar(int pa,int pb):ma{pa},mb{pb}{
			std::cout<<"Bar::~Bar()"<<std::endl;
		};
		~Bar(){
			std::cout<<"Bar::~Bar()"<<std::endl;
		};
		void test(){std::cout<<"Bar::test()"<<std::endl;};
	}Bar;
}
int main(int argc,char**argv){
	std::cout<<"Content-Type: text/plain"<<std::endl<<std::endl;
	{//basic example
		int a=42;
		decltype(a) b=24;
		double c=4.2;
		decltype(a+c) d=a+c;;
		std::cout<<"a:"<<a<<std::endl;
		std::cout<<"b:"<<b<<std::endl;
		std::cout<<"c:"<<c<<std::endl;
		std::cout<<"d:"<<d<<std::endl;
	}
	{//with user defined types
		using mynamespace::Foo;
		using mynamespace::Bar;
		Foo a(1,2);
		decltype(a)b(1,2);
		Bar c(1,2);
		decltype(c)d(1,2);
		a.test();
		b.test();
		c.test();
		d.test();
	}
	{//raw pointers
		using mynamespace::Foo;
		Foo*a=new Foo(1,2);
		if(a!=NULL){
			decltype(a)b=a;
			free(b);
		}else{
			std::cerr<<"Failed to allocate Foo"<<std::endl;
		}
	}
	return 0;
}
