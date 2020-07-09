#ifndef H5334B178C14611EA90B643AF594230EF
#define H5334B178C14611EA90B643AF594230EF
#include"mycpplibpublic.h"
class Foo:public F{
	public:
		Foo();
		~Foo();
		void test();
	private:
		int ma;
	protected:
};
class Bar:public F{
	public:
		Bar();
		~Bar();
		void test();
	private:
		int ma;
	protected:
};

extern "C"{
	void mycpplibf0();
}
#endif
