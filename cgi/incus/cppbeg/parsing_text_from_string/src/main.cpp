/*!@file: ./src/main.c
 * @brief: the stream extraction operator `>>` can be used to
 *         parse text from a string
 *         `std::cin` has type `std::ostream`, which is logically
 *         a text file you read from
 *         Note that when `std::cin` is used to parse a `boolean`,
 *         you have to take into account that extracting a `boolean`
 *         or any value from `std::cin` using the stream extraction
 *         operator is an expression that yields a `boolean`, which indicates
 *         if the extraction was successful
 *         
 *         if we want to parse from string values, for example the
 *         argument vector, we can use a `std::stringstream`
 */
#include<iostream>
#include<sstream>
#include"mycpplib.h"
extern "C" {
#include"myclib.h"
}
int main(int argc,char**argv){
	std::cout<<"Content-Type: text/plain"<<std::endl<<std::endl;
	{//std::cin
		using std::cin;
		using std::cout;
		using std::cerr;
		using std::endl;
		int a;
		if(!(cin>>a)){
			cerr<<"failed to read"<<endl;
			//return EXIT_FAILURE
		}
		bool b;
		if(!(cin>>b)){
			cerr<<"failed to read"<<endl;
			//return EXIT_FAILURE
		}
	}
	{//std::stringstream
		for(int i=0;i<argc;++i){
			std::stringstream ss(argv[i]);
			int val;
			if(!(ss>>val)){
				std::cerr<<"Failed to parse"<<std::endl;
			}else{
				std::cout<<"Parsed"<<std::endl;
			}
		}
	}
	return 0;
}
