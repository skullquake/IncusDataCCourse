/*!@file: ./src/main.c
 * @brief: inspecting the addresses of
 *             external variables
 *             local variables
 *             parameters
 *         Some sample outputs:
 *         GCC LINUX x86_64
 *             ea: 0x7f594e80b070-+
 *             eb: 0x7f594e80b028 |- external level variables, order ???
 *             ec: 0x7f594e80b02c-+
 *
 *             m:x:0x7fffdade11f5-+
 *             m:y:0x7fffdade11f6 |- local variables in main, ascending
 *             m:z:0x7fffdade11f7-+
 *
 *             m:  0x7f594e608117 |- function address low
 *
 *             a:a:0x7fffdade11ac-+
 *             a:b:0x7fffdade11a8 |- parameters descending
 *             a:c:0x7fffdade11a4-+
 *
 *             a:d:0x7fffdade11b5-+
 *             a:e:0x7fffdade11b6 |- local variables descending
 *             a:f:0x7fffdade11b7-+
 *         GCC LINUX ARM64
 *             ea: 0x55940b6048-+
 *             eb: 0x55940b6018 |- externals ???
 *             ec: 0x55940b601c-+
 *
 *             m:x:0x7fe8273f07-+
 *             m:y:0x7fe8273f06 |- locals descending
 *             m:z:0x7fe8273f05-+
 *
 *             m:  0x55940b3928 |- function low
 *
 *             a:a:0x7fe8273e6f-+
 *             a:b:0x7fe8273e6e |- parameters descending
 *             a:c:0x7fe8273e6d-+
 *
 *             a:d:0x7fe8273e6c-+
 *             a:e:0x7fe8273e6b |- locals descending
 *             a:f:0x7fe8273e6a-+
 *         TCC LINUX x86_64
 *             ea: 0x60ce08-+
 *             eb: 0x60ce0c |- locals, in this case ascending addresses
 *             ec: 0x60ce10-+
 *
 *             m:x:0x7fffe40109f7
 *             m:y:0x7fffe40109f6
 *             m:z:0x7fffe40109f5
 *
 *             m:  0x40bfa5 |- function address low
 *
 *             a:a:0x7fffe40109d8-+
 *             a:b:0x7fffe40109d0 |- parameters variables descending
 *             a:c:0x7fffe40109c8-+
 *
 *             a:d:0x7fffe40109c7-+
 *             a:e:0x7fffe40109c6 |- local variables descending
 *             a:f:0x7fffe40109c5-+
 *
 *         DJGPP DOS
 *             ea:     f228-+
 *             eb:     e4d0 |- external level variables, order ???
 *             ec:     e4d4-+
 *
 *             m:x:   9280f-+
 *             m:y:   9280e |- local variables in main, descending
 *             m:z:   9280d-+
 *
 *             m:      173c |- function address low
 *
 *             a:a:   927cc-+
 *             a:b:   927c8 |- parameters descending
 *             a:c:   927c4-+
 *
 *             a:d:   927df-+
 *             a:e:   927de |- local variables descending
 *             a:f:   927dd-+

 *         BCC DOS
 *             m:x:22A2:0FCB-+
 *             m:y:22A2:0FCA |- locals, in this case descending addresses
 *             m:z:22A2:0FC9-+
 *
 *             m:  224B:0077 |- function address low
 *
 *             a:a:22A2:0FC2-+
 *             a:b:22A2:0FC4 |- parameters ascending
 *             a:c:22A2:0FC6-+
 *
 *             a:d:22A2:0FBB-+
 *             a:e:22A2:0FBA |- local variables ascending
 *             a:f:22A2:0FB9-+
 *         QC DOS
 *             ea: 0294:0042-+
 *             eb: 0294:0044 |- external level variables, ascending
 *             ec: 0294:0046-+
 *
 *             m:x:0294:0E16-+
 *             m:y:0294:0E14 |- locals descending
 *             m:z:0294:0E12-+
 *
 *             m:  0294:00D7 |- function address low
 *
 *             a:a:0294:0E08-+
 *             a:b:0294:0E0A |- parameters ascending
 *             a:c:0294:0E0C-+
 *
 *             a:d:0294:0E02-+
 *             a:e:0294:0E00 |- local variables descending
 *             a:f:0294:0DFE-+
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
char*a(char,char,char);
int ea=0;
int eb=1;
int ec=2;
int main(int argc,char**argv,char**envp){
	char x;
	char y;
	char z;
	printf("ea: %p\n",&ea);
	printf("eb: %p\n",&eb);
	printf("ec: %p\n",&ec);
	printf("m:x:%p\n",&x);
	printf("m:y:%p\n",&y);
	printf("m:z:%p\n",&z);
	printf("m:  %p\n",a);
	a(1,2,3);
	printf("Content-Type: text/plain\n\n");
	return EXIT_SUCCESS;
}
char*a(char a,char b,char c){
	char d;
	char e;
	char f;
	printf("a:a:%p\n",&a);
	printf("a:b:%p\n",&b);
	printf("a:c:%p\n",&c);
	printf("a:d:%p\n",&d);
	printf("a:e:%p\n",&e);
	printf("a:f:%p\n",&f);
	return &b;
}
