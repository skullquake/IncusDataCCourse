/*!@file: ./src/main.c
 * @brief: Before we begin with classes, we can look at structs.
 */
#include<iostream>
#include<cstdlib>
#include"mycpplib.h"
	extern "C" {
#include"myclib.h"
}
namespace mynamespace{
	typedef struct Foo{
		//notice that in a struct, in c++, all members are `public`
		//there is no differentiation between `public`, `private`, and `protected`
		int a;
		int b{42};
		int c{24};
		//constructor in a struct
		Foo():a{42},b{24},c{33}{
			std::cout<<"Foo::Foo()"<<std::endl;
		};
		//destructor in a struct
		~Foo(){
			std::cout<<"Foo::~Foo()"<<std::endl;
		};
		//member functions
		void fvv(void){
			std::cout<<"fvv()"<<std::endl;
		};
		void fvi(int pa){
			std::cout<<"fvi()"<<std::endl;
		};
		int fiv(void){
			std::cout<<"fiv()"<<std::endl;
		};
		int fii(int pa){
			std::cout<<"fi()"<<std::endl;
		};
	}Foo;
}
int main(int argc,char**argv){
	std::cout<<"Content-Type: text/plain"<<std::endl<<std::endl;
	{//basic demonstration
		using mynamespace::Foo;
		Foo f;
		f.fvv();
		f.fvi(42);
		f.fiv();
		f.fii(42);
	}
	{//demonstration using pointers
		using mynamespace::Foo;
		Foo*f=new Foo();
		f->fvv();
		f->fvi(42);
		f->fiv();
		f->fii(42);
	}
	{//inappropriate use of malloc ???
	 //here notice that no constructor or destructor is automatically called
	 //and you cannot call them manually
		using mynamespace::Foo;
		Foo*f=(Foo*)malloc(sizeof(Foo));
		if(f!=NULL){
			//f->Foo();//manually call constructor: compile time error
			//f->~Foo();//manually call destructor: compile time error
			free(f);
		}else{
			std::cerr<<"Failed to allocate foo"<<std::endl;
		}		
	}
	return 0;
}
