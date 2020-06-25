/*!@file: ./src/main.c
 * @brief: prints out binary representation of data
 *         note that endianness influences the order of members in bitfields in terms of distribution in memory
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdlib.h>
#include"tobin.h"
int main(int argc,char**argv,char**envp){
	argc=argc;
	argv=argv;
	envp=envp;
	printf("Content-Type: text/plain\r\n\r\n");
	signed char    sc= 0;
	unsigned char  uc= 1;
	signed short   ss=-1;
	unsigned short us=-1;
	signed int     si=-1;
	unsigned int   ui=-1;
	signed long    sl=-1;
	unsigned long  ul=-1;
	float           f=1.23;
	double          d=1.23;
	long double    ld=1.23;
	struct{
		unsigned char uc0;
		unsigned char uc1;
		unsigned char uc2;
		unsigned char uc3;
	}              as={0,1,2,3};
	union{
		unsigned char      uc;
		unsigned long long ull;
	}              au0={0x00,0x00};
	union{
		unsigned char      uc;
		unsigned long long ull;
	}              au1={0x00,0x00};
	au0.uc=1;
	au1.ull=2;
	struct{//bitfield
		unsigned flda:4;//field a
		unsigned fldb:4;//field b
		unsigned     :2;//junk
		signed   fldc:6;//field c
	}              bf={flda:0x1,fldb:0x01,fldc:0x01};
	printf("uc:  ");tobinstream(&uc,sizeof(uc),stdout);
	printf("sc:  ");tobinstream(&uc,sizeof(uc),stdout);
	printf("us:  ");tobinstream(&ss,sizeof(ss),stdout);
	printf("ss:  ");tobinstream(&us,sizeof(us),stdout);
	printf("ui:  ");tobinstream(&si,sizeof(si),stdout);
	printf("si:  ");tobinstream(&ui,sizeof(ui),stdout);
	printf("sl:  ");tobinstream(&sl,sizeof(sl),stdout);
	printf("ul:  ");tobinstream(&ul,sizeof(ul),stdout);
	printf(" f:  ");tobinstream(&f,sizeof(f),stdout);
	printf(" d:  ");tobinstream(&d,sizeof(d),stdout);
	printf("ld:  ");tobinstream(&ld,sizeof(ld),stdout);
	printf("as:  ");tobinstream(&as,sizeof(as),stdout);
	printf("au0: ");tobinstream(&au0,sizeof(au0),stdout);
	printf("au1: ");tobinstream(&au1,sizeof(au1),stdout);
	printf("bf:  ");tobinstream(&bf,sizeof(bf),stdout);
	return EXIT_SUCCESS;
}
