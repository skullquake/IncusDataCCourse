//https://www.tldp.org/HOWTO/html_single/C++-dlopen/
//https://github.com/alainfrisch/flexdll
//https://tldp.org/HOWTO/Program-Library-HOWTO/dl-libraries.html
//https://cygwin.com/cygwin-ug-net/dll.html
//mingw issue loading symbols from client
//https://stackoverflow.com/questions/39759060/compile-to-dll-with-some-undefined-references-with-mingw
//https://atomheartother.github.io/c++/2018/07/12/CPPDynLib.html
//https://developer.ibm.com/technologies/systems/articles/au-aix-symbol-visibility/
//get module path from this module:
// windows
//  GetModuleFilename
#include"proxy.h"
#include"mycpplib.h"
#include<iostream>
#include<map>
#ifdef _WIN32
#else
#include<dlfcn.h>
#endif
#ifdef _WIN32
__declspec(dllimport) std::string publicstring;
//extern std::string publicstring;
#else
extern std::string publicstring;
extern std::map<std::string,F*(*)(void)>factorymap;
#endif

void dummy(){}
static std::string getFileName(const std::string& s){
	char sep = '/';
#ifdef _WIN32
	sep = '\\';
#endif
	size_t i=s.rfind(sep,s.length());
	if(i!=std::string::npos){
		return(s.substr(i+1, s.length()-i));
	}
	return("");
}
Proxy::Proxy(){
	std::cout<<"Proxy::Proxy()"<<std::endl;
#ifdef _WIN32
#else
	std::cout<<publicstring<<std::endl;
#endif
//test get path of this shared object
#ifdef _WIN32
#else
	Dl_info info;
	if(dladdr((const void*)dummy,&info)){//find better way
		//std::cout<<"Path:   "<<info.dli_fname<<std::endl;
		//std::cout<<"Symbol: "<<info.dli_sname<<std::endl;
		factorymap[(
			//std::string(info.dli_sname)+
			getFileName(std::string(info.dli_fname))+
			std::string(":")+
			std::string("Foo")
		)]=[]()->F*{return new Foo();};
		factorymap[(
			//std::string(info.dli_sname)+
			getFileName(std::string(info.dli_fname))+
			std::string(":")+
			std::string("Bar")
		)]=[]()->F*{return new Bar();};
	}else{
	}
#endif
}
Proxy::~Proxy(){
	std::cout<<"Proxy::~Proxy()"<<std::endl;
	//todo: unload and clean from global hashmap
}
static Proxy p;

