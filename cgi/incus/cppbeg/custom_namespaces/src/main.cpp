/*!@file: ./src/main.c
 * @brief: You can create your own custom namespace and namespace
 *         existing functions and variables in them as follows
 */
#include<iostream>
#include"mycpplib.h"
extern "C" {
#include"myclib.h"
}
namespace _9ee81f92_bc4b_11ea_b805_afe0d3c108f0{
	using std::cout;
	using std::cin;
	using std::cerr;
	using std::endl;

}
int main(int argc,char**argv){
	std::cout<<"Content-Type: text/plain"<<std::endl<<std::endl;
	{
		using namespace _9ee81f92_bc4b_11ea_b805_afe0d3c108f0;
		cout<<"hello"<<endl;
	}
	return 0;
}
