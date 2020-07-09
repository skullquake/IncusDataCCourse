#include"proxy.h"
#include<iostream>
Proxy::Proxy(){
	std::cout<<"Proxy::Proxy()"<<std::endl;
}
Proxy::~Proxy(){
	std::cout<<"Proxy::~Proxy()"<<std::endl;
}
static Proxy p;
