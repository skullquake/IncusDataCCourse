/*!@file duk/dukgluetest.c
 * @brief Various dukglue tests
 */
#ifdef DUK_USE_DUKGLUE
#include"duktape/dukglue.h"
#include"dukglue/dukglue.h"
#include<iostream>
#include<cmath>
#ifdef __cplusplus
extern "C"{
#endif
void f0(){
	std::cout<<"f0()"<<std::endl;
}
void f1(std::string p0){
	std::cout<<"f1():"<<p0<<std::endl;
}
int f2(std::vector<int> p0){
	std::cout<<"f2():"<<std::endl;
	int ret=0;
	for(auto a:p0){
		ret+=a;
	}
	return ret;
}
std::string f3(){
	return "foo";
}
class C0{
	public:
		C0(){
			std::cout<<"C0::C0()"<<std::endl;
		};
		~C0(){
			std::cout<<"C0::~C0()"<<std::endl;
		};
		void f0(){
			std::cout<<"C0::f0()"<<std::endl;
		};
		void f1(){
			std::cout<<"C0::f1()"<<std::endl;
		};
	private:
	protected:
};
C0*mkC0(){
	return new C0();
}
typedef struct Point{
	Point(double px,double py):x(px),y(py){};
	double x;
	double y;
}Point;
double calcDistance(Point*p0,Point*p1){
	double x=(p1->x-p0->x);
	double y=(p1->y-p0->y);
	return sqrt(x*x+y*y);
}
class Shape{
	public:
		Shape(double px,double py):mx(px),my(py){
			std::cout<<"Shape::Shape()"<<std::endl;
		};
		virtual ~Shape(){
			std::cout<<"Shape::~Shape()"<<std::endl;
		};
	protected:
	private:
		double mx;
		double my;
};
class Circle:public Shape{
	public:
		Circle(double px,double py,double pr):Shape(px,py),mr(pr){
			std::cout<<"Circle::Circle"<<std::endl;
		};
		~Circle(){
			std::cout<<"Circle::~Circle"<<std::endl;
		};
	protected:
	private:
		double mr;
};
class Ellipse:public Circle{
	public:
		Ellipse(double px,double py, double pr, double pr2):Circle(px,py,pr),mr2(pr2){
			std::cout<<"Ellipse::Ellipse"<<std::endl;
		};
		~Ellipse(){
			std::cout<<"Ellipse::~Ellipse"<<std::endl;
		};
	private:
		double mr2;
	protected:
};
class Square:public Shape{
	public:
		Square(double px,double py,double ps):Shape(px,py),ms(ps){
			std::cout<<"Square::Square"<<std::endl;
		};
		~Square(){
			std::cout<<"Square::~Square"<<std::endl;
		};
	private:
		double ms;
	protected:
};
class Rectangle:public Square{
	public:
		Rectangle(double px,double py,double ps,double ps2):Square(px,py,ps),ms2(ps2){
			std::cout<<"Rectangle::Rectangle"<<std::endl;
		};
		~Rectangle(){
			std::cout<<"Rectangle::Rectangle"<<std::endl;
		};
	private:
		double ms2;
	protected:
};
void duk_register_dukgluetest(duk_context*ctx){
	dukglue_register_function(ctx,f0,"f0");
	dukglue_register_function(ctx,f1,"f1");
	dukglue_register_function(ctx,f2,"f2");
	dukglue_register_function(ctx,f3,"f3");
	dukglue_register_constructor<C0/*,args*/>(ctx,"C0");
	dukglue_register_method(ctx,&C0::f0,"f0");
	dukglue_register_method(ctx,&C0::f1,"f1");
	dukglue_register_delete<C0>(ctx);
	dukglue_register_method(ctx,&C0::f0,"f0");
	dukglue_register_function(ctx,mkC0,"mkC0");
	dukglue_register_constructor<Point,double,double>(ctx,"Point");
	dukglue_register_function(ctx,calcDistance,"calcDistance");
	dukglue_register_constructor<Shape,double,double>(ctx,"Shape");
	dukglue_register_delete<Shape>(ctx);
	dukglue_register_constructor<Circle,double,double,double>(ctx,"Circle");
	dukglue_register_delete<Circle>(ctx);
	dukglue_register_constructor<Ellipse,double,double,double,double>(ctx,"Ellipse");
	dukglue_register_delete<Ellipse>(ctx);
	dukglue_register_constructor<Square,double,double,double>(ctx,"Square");
	dukglue_register_delete<Square>(ctx);
	dukglue_register_constructor<Rectangle,double,double,double,double>(ctx,"Rectangle");
	dukglue_register_delete<Rectangle>(ctx);
}
#ifdef __cplusplus
}
#endif
#endif


