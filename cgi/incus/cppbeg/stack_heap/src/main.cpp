/*!@file: ./src/main.c
 * @brief: Stack and heap demonstration. Local variables exist in
 *         an area of memory called the stack. Dynamic variables, allocated
 *         using the `new` keyword or `malloc`, exists in an area of
 *         memory called the heap.
 */
#include<iostream>
#include"mycpplib.h"
extern "C" {
#include"myclib.h"
}
int main(int argc,char**argv){
	std::cout<<"Content-Type: text/plain"<<std::endl<<std::endl;
	{//normal local variables exist on the stack
		int a=42;//on stack
	}
	{//dynamic variables, and int on the heap. Its pointer is on the stack
		int*a=new int(42);//a on stack, points to int on heap
		if(a!=nullptr){delete a;a=nullptr;}
	}
	{//pointers to pointers
	 //pointers can themselves exist on the heap, i.e. dynamically allocated
		int**a=new int*(nullptr);//a on stack, points to int** on heap
		if(a!=nullptr){
			*a=new int(42);//*a on heap, assigned new int on heap
			if(*a!=nullptr){delete *a;*a=nullptr;}
			delete a;
			a=nullptr;
		}
	}
	return 0;
}
