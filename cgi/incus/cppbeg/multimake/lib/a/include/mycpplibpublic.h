#ifndef H67BAC622C16011EAEC663A8910475A
#define H67BAC622C16011EAEC663A8910475A
#include<string>
class F{
	public:
		//virtual ~F()=0;
		virtual void test()=0;
};
extern "C"{
	F* mkF(std::string s);
}
#endif
