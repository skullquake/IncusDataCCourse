/*!@file: ./src/main.c
 * @brief: external level variables
 */
#include<iostream>
#include"mycpplib.h"
extern "C" {
#include"myclib.h"
}
//external level variables
bool               eb  =true;
unsigned char      esc =0;
unsigned short     ess =0;
unsigned int       esi =0;
unsigned long      esl =0;
unsigned long long esll=0;
float              ef=0;
double             ed=0;
long double        eld=0;
signed char        euc =0;
signed short       eus =0;
signed int         eui =0;
signed long        eul =0;
signed long long   eull=0;
int main(int argc,char**argv){
	std::cout<<"Content-Type: text/plain"<<std::endl<<std::endl;
	{
		std::cout<<eb<<std::endl;
		std::cout<<esc<<std::endl;
		std::cout<<ess<<std::endl;
		std::cout<<esi<<std::endl;
		std::cout<<esl<<std::endl;
		std::cout<<esll<<std::endl;
		std::cout<<ef<<std::endl;
		std::cout<<ed<<std::endl;
		std::cout<<eld<<std::endl;
		std::cout<<euc<<std::endl;
		std::cout<<eus<<std::endl;
		std::cout<<eui<<std::endl;
		std::cout<<eul<<std::endl;
		std::cout<<eull<<std::endl;
	}
	return 0;
}
