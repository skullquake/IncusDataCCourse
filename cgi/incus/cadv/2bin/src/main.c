/*!@file: ./src/main.c
 * @brief: description
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdlib.h>
#include"cJSON/cJSON.h"
void tobin(void*data,size_t sz,FILE*);
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
	tobin(&uc,sizeof(uc),stdout);
	tobin(&uc,sizeof(uc),stdout);
	tobin(&ss,sizeof(ss),stdout);
	tobin(&us,sizeof(us),stdout);
	tobin(&si,sizeof(si),stdout);
	tobin(&ui,sizeof(ui),stdout);
	return EXIT_SUCCESS;
}
void tobin(void*data,size_t sz,FILE*fp){
	for(size_t i=0;i<sz;++i){
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
