/*!@file: ./src/tobin.c
 * @brief: prints out binary representation of data
 *         note that endianness influences the order of members in bitfields in terms of distribution in memory
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdlib.h>
void tobinstream(void*data,size_t sz,FILE*fp){
	if(data==NULL||sz<1||fp==NULL)return;
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
