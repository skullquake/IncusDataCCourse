#include"foo/foo.h"
#include<stdio.h>
int myadd(int a,int b){
	return a+b;
}
int mysub(int a,int b){
	return a-b;
}
int mymul(int a,int b){
	return a*b;
}
int mydiv(int a,int b){
	return a/b;
}
#ifdef DEBUG
#include<stdlib.h>
static void testadd(void){
	printf("testing myadd()...\n");
	printf("myadd(0,1):%s\n",myadd(0,1)==1?"pass":"fail");
	printf("myadd(0,2):%s\n",myadd(0,2)==2?"pass":"fail");
	printf("myadd(0,3):%s\n",myadd(0,3)==3?"pass":"fail");
	printf("myadd(0,4):%s\n",myadd(0,4)==4?"pass":"fail");
	printf("myadd(1,1):%s\n",myadd(1,1)==2?"pass":"fail");
	printf("myadd(1,2):%s\n",myadd(1,2)==3?"pass":"fail");
	printf("myadd(1,3):%s\n",myadd(1,3)==4?"pass":"fail");
	printf("myadd(1,4):%s\n",myadd(1,4)==5?"pass":"fail");
	printf("myadd(0,-1):%s\n",myadd(0,-1)==-1?"pass":"fail");
	printf("myadd(0,-2):%s\n",myadd(0,-2)==-2?"pass":"fail");
	printf("myadd(0,-3):%s\n",myadd(0,-3)==-3?"pass":"fail");
	printf("myadd(0,-4):%s\n",myadd(0,-4)==-4?"pass":"fail");
	printf("done testing myadd()\n");

}
static void testsub(void){
	printf("testing mysub()...\n");
	printf("mysub(0,1):%s\n",mysub(0,1)==-1?"pass":"fail");
	printf("mysub(0,2):%s\n",mysub(0,2)==-2?"pass":"fail");
	printf("mysub(0,3):%s\n",mysub(0,3)==-3?"pass":"fail");
	printf("mysub(0,4):%s\n",mysub(0,4)==-4?"pass":"fail");
	printf("mysub(1,1):%s\n",mysub(1,1)==0?"pass":"fail");
	printf("mysub(1,2):%s\n",mysub(1,2)==-1?"pass":"fail");
	printf("mysub(1,3):%s\n",mysub(1,3)==-2?"pass":"fail");
	printf("mysub(1,4):%s\n",mysub(1,4)==-3?"pass":"fail");
	printf("mysub(0,-1):%s\n",mysub(0,-1)==1?"pass":"fail");
	printf("mysub(0,-2):%s\n",mysub(0,-2)==2?"pass":"fail");
	printf("mysub(0,-3):%s\n",mysub(0,-3)==3?"pass":"fail");
	printf("mysub(0,-4):%s\n",mysub(0,-4)==4?"pass":"fail");
	printf("done testing mysub()\n");


}
static void testmul(void){
	printf("testing mymul()...\n");
	printf("mymul(0,1):%s\n",mymul(0,1)==0?"pass":"fail");
	printf("mymul(0,2):%s\n",mymul(0,2)==0?"pass":"fail");
	printf("mymul(0,3):%s\n",mymul(0,3)==0?"pass":"fail");
	printf("mymul(0,4):%s\n",mymul(0,4)==0?"pass":"fail");
	printf("mymul(1,1):%s\n",mymul(1,1)==1?"pass":"fail");
	printf("mymul(1,2):%s\n",mymul(1,2)==2?"pass":"fail");
	printf("mymul(1,3):%s\n",mymul(1,3)==3?"pass":"fail");
	printf("mymul(1,4):%s\n",mymul(1,4)==4?"pass":"fail");
	printf("mymul(0,-1):%s\n",mymul(0,-1)==0?"pass":"fail");
	printf("mymul(0,-2):%s\n",mymul(0,-2)==0?"pass":"fail");
	printf("mymul(0,-3):%s\n",mymul(0,-3)==0?"pass":"fail");
	printf("mymul(0,-4):%s\n",mymul(0,-4)==0?"pass":"fail");
	printf("done testing mymul()\n");


}
static void testdiv(void){
	printf("testing mydiv()...\n");
	printf("mydiv(0,1):%s\n",mydiv(0,1)==0?"pass":"fail");
	printf("mydiv(0,2):%s\n",mydiv(0,2)==0?"pass":"fail");
	printf("mydiv(0,3):%s\n",mydiv(0,3)==0?"pass":"fail");
	printf("mydiv(0,4):%s\n",mydiv(0,4)==0?"pass":"fail");
	printf("mydiv(1,1):%s\n",mydiv(1,1)==1?"pass":"fail");
	printf("mydiv(1,2):%s\n",mydiv(1,2)==0?"pass":"fail");
	printf("mydiv(1,3):%s\n",mydiv(1,3)==0?"pass":"fail");
	printf("mydiv(1,4):%s\n",mydiv(1,4)==0?"pass":"fail");
	printf("mydiv(0,-1):%s\n",mydiv(0,-1)==0?"pass":"fail");
	printf("mydiv(0,-2):%s\n",mydiv(0,-2)==0?"pass":"fail");
	printf("mydiv(0,-3):%s\n",mydiv(0,-3)==0?"pass":"fail");
	printf("mydiv(0,-4):%s\n",mydiv(0,-4)==0?"pass":"fail");
	printf("done testing mydiv()\n");


}
int main(void){
	testadd();
	testsub();
	testmul();
	testdiv();
	return EXIT_SUCCESS;
}
#endif
