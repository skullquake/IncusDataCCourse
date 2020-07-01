/*!@file: ./src/main.c
 * @brief: description
 */
#include<iostream>
#include"mycpplib.h"
extern "C" {
#include"myclib.h"
}
int main(int argc,char**argv){
	std::cout<<"Content-Type: text/plain"<<std::endl<<std::endl;
	#ifdef __cplusplus
		std::cout<<"CPP"<<std::endl;
	#endif
	return 0;
}
