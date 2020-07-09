/*
 * prelimnirary dlopen work
 * this can later be modified to be
 * included in duktape
 * or as a request handler
 * pointing to dll/so files, with a fixed
 * function called from that dll/so, though
 * the dll/so is dynamically loaded in
 * the dll/so can then act much as a cgi
 * endpoint, but running inside the 
 * main server process
 *
 *  https://www.linuxjournal.com/article/3687
 *  take a look at this for overcoming some of the limitations
 *  around the mangling in c++, some of it implemented here
 *  
 *  dealing with windows:
 *  https://www.codeproject.com/Articles/13501/Platform-Independent-Coding-DLLs-and-SOs
 */
#include<iostream>
#include<vector>
#include<cstdlib>
#include<cstdio>
#include<string>
#include<dirent.h>
#include<cstring>
#include<map>
#ifdef _WIN32
	#include<windows.h>
#else
	#include"dlfcn.h"
#endif
#include"a/mycpplibpublic.h"


//requires -rdynamic
//allows shared libraries to access this
std::string publicstring="Lorem ipsum sit consecutar";
std::map<std::string,F*(*)(void)>factorymap;
int main(void){
	{
		std::string path="./lib";
		DIR*dp=nullptr;
		dp=opendir(path.c_str());
		struct dirent*entry=nullptr;
		std::vector<void*> vhdl;
		if(dp!=nullptr){
			while((entry=readdir(dp))){
				//if(entry->d_type==DT_REG){
#ifdef _WIN32
					if(strstr(entry->d_name,".dll")){
#else
					if(strstr(entry->d_name,".so")){
#endif
						void*hdl;
						char sopath[1024];
						strcpy(sopath,path.c_str());
						strcat(sopath,"/");
						strcat(sopath,entry->d_name);
						std::cout<<"Loading "<<sopath<<std::endl;
#ifdef _WIN32
						hdl=LoadLibrary(sopath);
#else
						hdl=dlopen(sopath,RTLD_LAZY);
#endif
						if(hdl!=NULL)vhdl.push_back(hdl);
					}
				//}
			}
			closedir(dp);
			/*
			while(!vhdl.empty()){
#ifdef _WIN32
				FreeLibrary((HMODULE)vhdl.back());
#else
				dlclose(vhdl.back());
#endif
				vhdl.pop_back();
			}
			*/
		}
	}
	{
		void*hdl;
#ifdef _WIN32
		const char*libnam="./lib/liba.dll";
#else
		const char*libnam="./lib/liba.so";
#endif
#ifdef _WIN32
		hdl=LoadLibrary(libnam);
#else
		//hdl=dlopen(libnam,RTLD_NOW);
		hdl=dlopen(libnam,RTLD_LAZY);
		char*err=NULL;
		if((err=dlerror())!=NULL){//dont exit here!
			fprintf(stderr,"%s\n",err);
		}
#endif
		if(hdl!=NULL){
			printf("loaded\n");
			{//c
				void(*fn)(void);
				const char*fnnam="myclibf0";
#ifdef _WIN32
				fn=(void(*)(void))GetProcAddress((HMODULE)hdl,fnnam); 
#else
				fn=(void(*)(void))dlsym(hdl,fnnam);
				if((err=dlerror())!=NULL){
					fprintf(stderr,"%s\n",err);
				}
#endif
				if(fn!=NULL){
					fn();
				}else{
					fprintf(stderr,"Failed to get function\n");
				}
			}
			{//cpp - function
				void(*fn)(void);
				const char*fnnam="mycpplibf0";
#ifdef _WIN32
				fn=(void(*)(void))GetProcAddress((HMODULE)hdl,fnnam); 
#else
				fn=(void(*)(void))dlsym(hdl,fnnam);
				if((err=dlerror())!=NULL){
					fprintf(stderr,"%s\n",err);
				}
#endif
				if(fn!=NULL){
					fn();
				}else{
					fprintf(stderr,"Failed to get function\n");
				}
			}
			{//cpp - factory
				F*(*fn)(std::string);
				const char*fnnam="mkF";
#ifdef _WIN32
				fn=(F*(*)(std::string))GetProcAddress((HMODULE)hdl,fnnam); 
#else
				fn=(F*(*)(std::string))dlsym(hdl,fnnam);
				if((err=dlerror())!=NULL){
					fprintf(stderr,"%s\n",err);
				}
#endif
				if(fn!=NULL){
					F*f;
					f=fn("Foo");
					f->test();
					f=fn("Bar");
					f->test();
				}else{
					fprintf(stderr,"Failed to get function\n");
				}
			}
		}else{
			fprintf(stderr,"Error\n");
		}
	}
	{//global hashmap factory - test
		//factorymap["Foo"]();
		/*
		factorymap["asdf"]=[]()->F*{
			return nullptr;
		};
		*/
		std::cout<<"----------------------------------------"<<std::endl;
		for(auto itr=factorymap.begin();itr!=factorymap.end();++itr){
			auto k=itr->first;
			std::cout<<k<<std::endl;
			F*f=itr->second();
			if(f!=nullptr){
				f->test();
			}else{
				std::cerr<<"Failed to get object"<<std::endl;
			}
		}
		std::cout<<"----------------------------------------"<<std::endl;
	}
	return 0;
}
