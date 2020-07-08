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
 */

#include<stdio.h>
#include<stdlib.h>
#include"dlfcn.h"
//#include"a/myclib.h"
//#include"a/mycpplib.h"
int main(void){
	//dlopen("libvendorconn.so",RTLD_LAZY);
	//void*hdl=dlopen("/home/src/skullquake/IncusDataCCourse/cgi/incus/cppbeg/multimake/lib/liba.so",RTLD_NOW);
	int a;
	getchar();
	void*hdl=dlopen("./lib/liba.so",RTLD_LAZY);
	char*err=NULL;
	if(hdl!=NULL){
		printf("loaded\n");
		void(*fn)(void);
		//fn=(void(*)(void))dlsym(hdl,"myclibf0");
		fn=(void(*)(void))dlsym(hdl,"myclibf0");
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
			return EXIT_FAILURE;
		}
	}else{
		fprintf(stderr,"Error\n");
		return EXIT_FAILURE;
	}
	//myclibf0();
	//mycpplibf0();
	return 0;
}
