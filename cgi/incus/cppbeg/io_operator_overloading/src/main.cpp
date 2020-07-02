/*!@file: ./src/main.c
 * @brief: description
 */
#include<iostream>
#include<sstream>
#include"mycpplib.h"
extern "C" {
#include"myclib.h"
}
namespace myspace{
	typedef struct Foo{
		int ma;
		int mb;
		Foo(int pa,int pb):ma{pa},mb{pb}{
		};
		~Foo(){};
	}Foo;
	std::ostream&operator<<(std::ostream&os,const Foo&foo){
		os<<foo.ma<<" "<<foo.mb;
		return os;
	}
	std::istream&operator>>(std::istream&is,Foo&foo){
		is>>foo.ma;
		is>>foo.mb;
		return is;
	}
}
int main(int argc,char**argv){
	std::cout<<"Content-Type: text/plain"<<std::endl<<std::endl;
	{
		using namespace myspace;
		Foo f0(0,1);
		Foo f1(2,3);
		std::cout<<f0<<std::endl;
		std::cout<<f1<<std::endl;
		std::stringstream ss("4 2");
		ss>>f1;
		std::cout<<f1<<std::endl;
	}
	return 0;
}
