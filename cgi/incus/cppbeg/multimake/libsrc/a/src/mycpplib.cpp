#include"mycpplib.h"
#include<iostream>
Foo::Foo():ma(42){};
Foo::~Foo(){};
void Foo::test(){
	std::cout<<"Foo::test"<<std::endl;
}
Bar::Bar():ma(24){};
Bar::~Bar(){};
void Bar::test(){
	std::cout<<"Bar::test"<<std::endl;
}
extern "C"{
	void mycpplibf0(){
		std::cout<<"mycpplibf0()"<<std::endl;
	}
}
	F* mkF(std::string s){
		if(s=="Foo")
		return new Foo();
		if(s=="Bar")
		return new Bar();
		return 0;
	}
