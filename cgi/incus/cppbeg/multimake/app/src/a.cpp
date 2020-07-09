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
//#include"a/myclib.h"
//#include"a/mycpplib.h"
#include"a/mycpplibpublic.h"
int main(void){
	{
		getchar();
		void*hdl;
#ifdef _WIN32
		hdl=LoadLibrary("./lib/liba.dll");
#else
		hdl=dlopen("./lib/liba.so",RTLD_LAZY);//RTLD_NOW
		char*err=NULL;
		if((err=dlerror())!=NULL){//dont exit here,
			//there might be some unrelated errors, e.g.
			//libvendorconn under termux
			fprintf(stderr,"%s\n",err);
		}
#endif

		if(hdl!=NULL){
			printf("loaded\n");
			{//c
				void(*fn)(void);
#ifdef _WIN32
				fn=(void(*)(void))GetProcAddress((HMODULE)hdl,"myclibf0"); 
#else
				fn=(void(*)(void))dlsym(hdl,"myclibf0");
				if((err=dlerror())!=NULL){//dont exit here,
					//there might be some unrelated errors, e.g.
					//libvendorconn under termux
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
		/*
			{//cpp - function
				void(*fn)(void);
				fn=(void(*)(void))dlsym(hdl,"mycpplibf0");
				if((err=dlerror())!=NULL){//dont exit here,
					//there might be some unrelated errors, e.g.
					//libvendorconn under termux
					fprintf(stderr,"%s\n",err);
				}
				if(fn!=NULL){
					fn();
					getchar();
				}else{
					fprintf(stderr,"Failed to get function\n");
				}
			}
			{//cpp - factory
				F*(*fn)(std::string);
				fn=(F*(*)(std::string))dlsym(hdl,"mkF");
				if((err=dlerror())!=NULL){//dont exit here,
					fprintf(stderr,"%s\n",err);
				}
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

		*/
		}else{
			fprintf(stderr,"Error\n");
		}
	}
	return 0;
}
