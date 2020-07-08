/**
 * @file scr/dukglue/dukglue.js
 * @author Ockert van Schalkwyk
 * @brief dukglue tests
 * @version 0.1
 */
function dukglue_test(){
	log("info:dukgluetest:start");
	{//function test
		f0();
		f1("foo");
		log(f2([0,1,2,3]));
		log(f3());
	}
	{//class test
		var c0=new C0();
		c0.f0();
		c0.f1();
		c0.delete();
	}
	{//struct test, passing to function
		var p0=new Point(0,0);
		var p1=new Point(1,1);
		log(calcDistance(p0,p1));
	}
	{//function returning object test
		var c1=mkC0();
		c1.f0();
		c1.f1();
		delete c1;
	}
	{//inheritance test
		s=new Shape(0,0);
		s.delete();
		c=new Circle(0,0,1);
		c.delete();
		e=new Ellipse(0,0,1,2);
		e.delete();
		sq=new Square(0,0,1);
		r=new Rectangle(0,0,1,2);
		r.delete();
	}
	log("info:dukgluetest:end");
}
