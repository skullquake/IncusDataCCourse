//mingw issue loading symbols from client
//https://stackoverflow.com/questions/39759060/compile-to-dll-with-some-undefined-references-with-mingw
//https://atomheartother.github.io/c++/2018/07/12/CPPDynLib.html
//https://developer.ibm.com/technologies/systems/articles/au-aix-symbol-visibility/
#include"proxy.h"
#include<iostream>
#ifdef _WIN32
__declspec(dllimport) std::string publicstring;
//extern std::string publicstring;
#else
extern std::string publicstring;
#endif
Proxy::Proxy(){
	std::cout<<"Proxy::Proxy()"<<std::endl;
#ifndef _WIN32
	std::cout<<publicstring<<std::endl;
#endif
}
Proxy::~Proxy(){
	std::cout<<"Proxy::~Proxy()"<<std::endl;
}
static Proxy p;
