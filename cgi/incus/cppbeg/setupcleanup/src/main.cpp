/*!@file: ./src/main.c
 * @brief: Program startup and termination using C++ constructors and destructors
 *         Note the order of the calls. Also note the relative call position of the
 *         destructors to the registered atexit functions cleanup0 and cleanup1
 */
#include<iostream>
#include<cstdlib>//atexit()???
#include<ctime>//atexit()???
#include"mycpplib.h"
	extern "C" {
#include"myclib.h"
}
namespace mynamespace{
	static void cleanup1();
	static void cleanup2();
	static struct init_and_clean{
		int instance_;
		init_and_clean(int instance=1):instance_(instance){
			std::cerr<<"Setup code ("<<instance_<<") called"<<std::endl;
		};
		~init_and_clean(){
			std::cerr<<"Cleanup code ("<<instance_<<") called"<<std::endl;
		};
	}start_exit{};
	void cleanup0(){
		std::cerr<<"cleanup0()"<<std::endl;
	};
	void cleanup1(){
		std::cerr<<"cleanup1()"<<std::endl;
	};
	int rnd(){
		srand(time(0));
		return rand();
	}
};
//c++ allows you to initialize objects with a global lifetime
//as illustrated in the following two statements
mynamespace::init_and_clean iac0{0};
int foo=mynamespace::rnd();
int main(int argc,char**argv){
	using mynamespace::init_and_clean;
	using mynamespace::cleanup0;
	using mynamespace::cleanup1;
	std::cout<<"Content-Type: text/plain"<<std::endl<<std::endl;
	if(true){
		//local, will get constructed and destroyed within
		//this statement block
		init_and_clean nested{6};
		static init_and_clean static_nested{7};
	}
	atexit(cleanup0);
	atexit(cleanup1);
	return 0;
}
//if a external level object is initialized after main, it will still be
//initialized before the main function statements get executed
mynamespace::init_and_clean iac1{1};
