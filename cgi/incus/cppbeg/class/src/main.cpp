/*!@file: ./src/main.c
 * @brief: `class` demonstration
 */
#include<iostream>
#include"mycpplib.h"
extern "C" {
#include"myclib.h"
}
namespace{
	class Person{
		public:
			Person();					//default constructor
			Person(const Person&p)=default;			//default copy constructor
			Person(std::string pName,std::string mAddr);	//
			void setName(std::string pName);		//mutators
			void setAddr(std::string pAddr);		//
			std::string&getName();				//accessors
			std::string&getAddr();				//
			Person&operator=(const Person&p);		//operators
			friend std::ostream&operator<<(std::ostream&os,const Person&p);	
			~Person();					//destructor
		private:
			std::string mName;
			std::string mAddr;
		protected:
	};
}
int main(int argc,char**argv){
	std::cout<<"Content-Type: text/plain"<<std::endl<<std::endl;
	Person p0("John Doe","Kaapstad");
	Person p1{"Jane Doe","Clanwilliam"};
	std::cout<<p0<<std::endl;
	std::cout<<p1<<std::endl;
	Person p2;
	p2=p0;
	std::cout<<p2<<std::endl;;
	p2=p1;
	std::cout<<p2<<std::endl;;
	std::cout<<p0.getName()<<std::endl;
	std::cout<<p0.getAddr()<<std::endl;
	p0.setName("Piet Pompies");
	p0.setAddr("Garies");
	std::cout<<p0<<std::endl;
	Person p3(p0);
	std::cout<<p3<<std::endl;
	return 0;
}
namespace{
	Person::Person(){}
	Person::Person(std::string pName,std::string pAddr):mName(pName),mAddr(pAddr){}
	void Person::setName(std::string pName){
		mName=pName;
	}
	void Person::setAddr(std::string pAddr){
		mAddr=pAddr;
	}
	std::string& Person::getName(){
		return mName;
	}
	std::string& Person::getAddr(){
		return mAddr;
	}
	Person&Person::operator=(const Person&p){
		if(this==&p)return*this;//check self assignment
		mName=p.mName;
		mAddr=p.mAddr;
		return*this;//all operators must return something
	}
	std::ostream&operator<<(std::ostream&os,const Person&p){
		os<<p.mName<<" "<<p.mAddr;
		return os;
	}
	Person::~Person(){}
}
