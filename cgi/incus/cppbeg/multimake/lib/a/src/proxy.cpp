#include"proxy.h"
#include<iostream>
extern "C"{
extern std::string publicstring;
}
Proxy::Proxy(){
	std::cout<<"Proxy::Proxy()"<<std::endl;
	std::cout<<publicstring<<std::endl;
}
Proxy::~Proxy(){
	std::cout<<"Proxy::~Proxy()"<<std::endl;
}
static Proxy p;
