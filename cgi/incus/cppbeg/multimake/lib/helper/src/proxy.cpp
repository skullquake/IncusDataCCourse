#include"proxy.h"
#include"../../a/include/mycpplibpublic.h"
#include<iostream>
#include<map>
#ifdef _WIN32
#include<windows.h>
#else
#include<dlfcn.h>
#endif
std::map<std::string,F*(*)(void)>factorymap;
std::string helper_version="0.01";
static void dummy(){}
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
static std::string getmpath(void){
	std::string ret="";
	int err=0;
#ifdef _WIN32
	char path[MAX_PATH];
	HMODULE hm=NULL;
	if(GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS|GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,(LPCSTR)&dummy,&hm)!=0){
		if(GetModuleFileName(hm,path,sizeof(path))==0){
			err=GetLastError();
		}else{
			ret=std::string(path);
		}
	}else{
		err=GetLastError();
	}
#else
	Dl_info info;
	if(dladdr((const void*)dummy,&info)){//find better way
		ret=std::string(info.dli_fname);
	}else{
	}
#endif
	return ret;
}
__attribute__((visibility("hidden"))) Proxy::Proxy(){
	std::cout<<"Proxy::Proxy()"<<std::endl;
	std::string mpath=getmpath();
	std::cout<<"mpath:"<<mpath<<std::endl;
	std::cout<<"mname:"<<getFileName(mpath)<<std::endl;
}
__attribute__((visibility("hidden"))) Proxy::~Proxy(){
	std::cout<<"Proxy::~Proxy()"<<std::endl;
	std::string mpath=getmpath();
	std::cout<<"mpath:"<<mpath<<std::endl;
	std::cout<<"mname:"<<getFileName(mpath)<<std::endl;
}
static Proxy p;

