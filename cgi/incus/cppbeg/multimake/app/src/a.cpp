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

#include<stdio.h>
#include<stdlib.h>
#include<string>
#ifdef _WIN32
	#include<windows.h>
#else
	#include"dlfcn.h"
#endif
#include"a/mycpplibpublic.h"


//requires -rdynamic
//allows shared libraries to access this
std::string publicstring="Lorem ipsum sit consecutar";


int main(void){
	{
		getchar();
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
					getchar();
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
					getchar();
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
					getchar();
				}else{
					fprintf(stderr,"Failed to get function\n");
				}
			}
		}else{
			fprintf(stderr,"Error\n");
		}
	}
	return 0;
}
