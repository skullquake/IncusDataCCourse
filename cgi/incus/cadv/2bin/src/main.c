/*!@file: ./src/main.c
 * @brief: prints out binary representation of data
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdlib.h>
#include"cJSON/cJSON.h"
void tobinstream(void*data,size_t sz,FILE*);
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
	printf("uc: ");tobinstream(&uc,sizeof(uc),stdout);
	printf("sc: ");tobinstream(&uc,sizeof(uc),stdout);
	printf("us: ");tobinstream(&ss,sizeof(ss),stdout);
	printf("ss: ");tobinstream(&us,sizeof(us),stdout);
	printf("ui: ");tobinstream(&si,sizeof(si),stdout);
	printf("si: ");tobinstream(&ui,sizeof(ui),stdout);
	printf("sl: ");tobinstream(&sl,sizeof(sl),stdout);
	printf("ul: ");tobinstream(&ul,sizeof(ul),stdout);
	printf(" f: ");tobinstream(&f,sizeof(f),stdout);
	printf(" d: ");tobinstream(&d,sizeof(d),stdout);
	printf("ld: ");tobinstream(&ld,sizeof(ld),stdout);
	return EXIT_SUCCESS;
}
void tobinstream(void*data,size_t sz,FILE*fp){
	for(size_t i=0;i<sz;++i){
		//todo: improve
		fprintf(fp,"%d",((*(((unsigned char*)data)+i))&0x80)>0);
		fprintf(fp,"%d",((*(((unsigned char*)data)+i))&0x40)>0);
		fprintf(fp,"%d",((*(((unsigned char*)data)+i))&0x20)>0);
		fprintf(fp,"%d",((*(((unsigned char*)data)+i))&0x10)>0);
		fprintf(fp,"%d",((*(((unsigned char*)data)+i))&0x08)>0);
		fprintf(fp,"%d",((*(((unsigned char*)data)+i))&0x04)>0);
		fprintf(fp,"%d",((*(((unsigned char*)data)+i))&0x02)>0);
		fprintf(fp,"%d",((*(((unsigned char*)data)+i))&0x01)>0);
		fprintf(fp," ");
	}fprintf(fp,"\n");
}
