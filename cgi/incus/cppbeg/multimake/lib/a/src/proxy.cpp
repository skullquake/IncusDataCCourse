#include"proxy.h"
#include"mycpplib.h"
#include<iostream>
#include<map>
#ifdef _WIN32
#include<windows.h>
#else
#include<dlfcn.h>
#endif
extern std::string helper_version;
void clienttest(void);
extern std::map<std::string,F*(*)(void)>factorymap;
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
			//handle error
			err=GetLastError();
			//fprintf(stderr, "GetModuleFileName failed, error = %d\n", ret);
			//Return or however you want to handle an error.
		}else{
			ret=std::string(path);
		}
	}else{
		err=GetLastError();
		//fprintf(stderr, "GetModuleHandle failed, error = %d\n", ret);
		// Return or however you want to handle an error.
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
	std::cout<<"liba:Proxy::Proxy()"<<std::endl;
	std::cout<<"helper_version: "<<helper_version<<std::endl;
//test get path of this shared object
	std::string mpath=getmpath();
	std::cout<<"mpath:"<<mpath<<std::endl;
	std::cout<<"mname:"<<getFileName(mpath)<<std::endl;
	//add functions
	factorymap[(
		getFileName(mpath)+
		std::string(":")+
		std::string("Foo")
	)]=[]()->F*{return new Foo();};
	factorymap[(
		getFileName(mpath)+
		std::string(":")+
		std::string("Bar")
	)]=[]()->F*{return new Bar();};
}
__attribute__((visibility("hidden"))) Proxy::~Proxy(){
	std::cout<<"Proxy::~Proxy()"<<std::endl;
	//todo: unload and clean from global hashmap
}
__attribute__((visibility("hidden"))) static Proxy p;
