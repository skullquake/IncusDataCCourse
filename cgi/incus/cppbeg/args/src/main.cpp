/*!@file: ./src/main.c
 * @brief: Demonstration processing command line arguments
 */
#include<iostream>
#include"mycpplib.h"
extern "C" {
#include"myclib.h"
}
int main(int argc,char**argv,char**envp){
	std::cout<<"Content-Type: text/plain"<<std::endl<<std::endl;
	for(int i=0;i<argc;++i){
		std::cout<<"["<<i<<"]:"<<std::string(argv[i])<<std::endl;
	}
	char*e=*envp;
	int eidx=0;
	while(e!=NULL){
		std::cout<<"["<<eidx++<<"]:"<<std::string(e)<<std::endl;
		++e;
	}
	/*
	*/
	return 0;
}
