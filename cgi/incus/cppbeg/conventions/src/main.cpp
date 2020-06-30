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
	std::cout<<R"(      = "equivalent/identical to")"<<std::endl;
	std::cout<<R"(   -t-> "has the type")"<<std::endl;
	std::cout<<R"(   -r-> "is read as")"<<std::endl;
	std::cout<<R"(   -m-> "means" or "has this meaning")"<<std::endl;
	std::cout<<R"(     => "expands to" or "is defined in terms of" *)"<<std::endl;
	std::cout<<R"( <type> any legal built-in or user-defined type)"<<std::endl;
	std::cout<<R"( <expr> any legal expression in a context)"<<std::endl;
	std::cout<<R"(<ident> any legal identifier (name))"<<std::endl;
	std::cout<<std::endl;
	std::cout<<R"( * In comments, we use '//=>...' to show the output of a statement)"<<std::endl;
	return 0;
}
