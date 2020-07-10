//https://www.ibm.com/developerworks/aix/library/au-aix-symbol-visibility-part2/index.html
//http://blog.fesnel.com/blog/2009/08/19/hiding-whats-exposed-in-a-shared-library/
//https://blogs.kde.org/2018/01/19/fun-symbol-visibility
//https://labjack.com/news/simple-cpp-symbol-visibility-demo
//https://stackoverflow.com/questions/15560892/symbol-visibility-and-namespace
//http://mingw.5.n7.nabble.com/ignoring-unresolved-symbols-in-shared-libraries-td14076.html
//https://stackoverflow.com/questions/39477163/can-you-compile-a-shared-object-to-prefer-local-symbols-even-if-its-being-loaded
//https://stackoverflow.com/questions/36692315/what-exactly-does-rdynamic-do-and-when-exactly-is-it-needed
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
//  https://www.codeproject.com/Articles/16598/Get-Your-DLL-s-Path-Name
//  https://stackoverflow.com/questions/6924195/get-dll-path-at-runtime
// linux
//  https://stackoverflow.com/questions/1681060/library-path-when-dynamically-loaded
// sharing globals (used here for registration)
//  https://stackoverflow.com/questions/3004318/dynamic-loaded-libraries-and-shared-global-symbols 
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
static Proxy p;

