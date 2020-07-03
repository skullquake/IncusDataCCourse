/*!@file: ./src/main.c
 * @brief: operator overloading demonstration
 *         Various overloads for stream insertion and extraction are
 *         provided for struct/classes for `std::istream` and `std::ostream`.
 *         For classes, two options exists, you can choose to use friend
 *         functions or not to use friend functions. If friend functions are
 *         not used, you have to implemente mutators and accessors for private
 *         members to be accessed or changed in the overloaded operation
 *
 *         Another operator you can overload is the casting operator,
 *         and we also illustrate that below
 */
#include<iostream>
#include<sstream>
#include"mycpplib.h"
extern "C" {
#include"myclib.h"
}
namespace{
	typedef struct S0{
		int a;
		int b;
	}S0;
	extern std::ostream&operator<<(std::ostream&os,const S0&s0);
	extern std::istream&operator>>(std::istream&is,S0&s0);
	//todo:cast operator overload
	class C0{
		public:
			C0()=default;
			C0(int pa,int pb);
			int getma()const;
			int getmb()const;
			void setma(int pa);
			void setmb(int pb);
			//example cast overload
			operator double(){return static_cast<double>(ma)/static_cast<double>(mb);};
		private:
			int ma;
			int mb;
	};
	extern std::ostream&operator<<(std::ostream&os,const C0&c0);
	extern std::istream&operator>>(std::istream&is,C0&c0);
	class C1{
		public:
			C1()=default;
			C1(int pa,int pb);
			friend std::ostream&operator<<(std::ostream&os,const C1&c);
			friend std::istream&operator>>(std::istream&is,C1&c1);
			//example cast overload
			operator double(){return static_cast<double>(ma)/static_cast<double>(mb);};
		private:
			int ma;
			int mb;
	};
	class C2{
		public:
			C2()=default;
			C2(int pa):ma(pa){};
			friend std::ostream&operator<<(std::ostream&os,const C2&c2);
		private:
			int ma;
	};
}
int main(int argc,char**argv){
	std::cout<<"Content-Type: text/plain"<<std::endl<<std::endl;
	{//ostream and struct
		std::cout<<"test0:"<<std::endl;
		S0 s0{4,2};
		std::cout<<s0<<std::endl;
	}
	{//istream and struct
		std::cout<<"test1:"<<std::endl;
		std::ostringstream oss;
		oss<<4<<std::endl;
		oss<<2<<std::endl;
		std::istringstream iss(oss.str());
		S0 s0;
		iss>>s0;
		std::cout<<s0<<std::endl;
	}
	{//ostream and class
		std::cout<<"test2:"<<std::endl;
		C0 c0(2,4);
		std::cout<<c0<<std::endl;
	}
	{//istream and class
		std::cout<<"test3:"<<std::endl;
		std::ostringstream oss;
		oss<<2<<std::endl;
		oss<<4<<std::endl;
		std::istringstream iss(oss.str());
		C0 c0;
		iss>>c0;
		std::cout<<c0<<std::endl;
	}
	{//friend ostream and class
		std::cout<<"test4:"<<std::endl;
		C1 c1(4,2);
		std::cout<<c1<<std::endl;
	}
	{//friend istream and class
		std::cout<<"test5:"<<std::endl;
		std::ostringstream oss;
		oss<<2<<std::endl;
		oss<<4<<std::endl;
		std::istringstream iss(oss.str());
		C1 c1;
		iss>>c1;
		std::cout<<c1<<std::endl;
	}
	{//overloaded casting operator
		std::cout<<"test6"<<std::endl;
		C1 c1;
		std::cout<<static_cast<double>(c1)<<std::endl;;
	}
	{//???
		std::cout<<"test7"<<std::endl;
		C2 c2;
		c2=(C2)42;
		std::cout<<c2<<std::endl;
	}

	return 0;
}
namespace{
	std::ostream&operator<<(std::ostream&os,const S0&s0){
		os<<s0.a<<" "<<s0.b;
		return os;
	}
	std::istream&operator>>(std::istream&is,S0&s0){
		is>>s0.a;
		is>>s0.b;
		return is;
	}
	inline C0::C0(int pa,int pb):ma(pa),mb(pb){}
	int C0::getma()const{return ma;}
	int C0::getmb()const{return mb;}
	void C0::setma(int pa){ma=pa;}
	void C0::setmb(int pb){mb=pb;}
	std::ostream&operator<<(std::ostream&os,const C0&c0){
		os<<c0.getma()<<" "<<c0.getmb();
		return os;
	}
	std::istream&operator>>(std::istream&is,C0&c0){
		int a;
		int b;
		is>>a;
		is>>b;
		c0.setma(a);
		c0.setmb(b);
		return is;
	}
	inline C1::C1(int pa,int pb):ma(pa),mb(pb){}
	std::ostream&operator<<(std::ostream&os,const C1&c1){
		os<<c1.ma<<" "<<c1.mb;
		return os;
	}
	std::istream&operator>>(std::istream&is,C1&c1){
		is>>c1.ma;
		is>>c1.mb;
		return is;
	}
	std::ostream&operator<<(std::ostream&os,const C2&c2){
		os<<c2.ma;
		return os;
	}
}
