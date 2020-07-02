/*!@file: ./src/main.c
 * @brief: `malloc` demonstration
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<time.h>
int main(int argc,char**argv,char**envp){
	argc=argc;
	argv=argv;
	envp=envp;
	printf("Content-Type: text/plain\n\n");
	{
		int slen=4;
		int bufsz=slen*sizeof(char);
		char*buf=(char*)malloc(bufsz);
		if(buf!=NULL){
			snprintf(buf,bufsz,"lorem ipsum");
			printf("%s\n",buf);
			free(buf);
		}else{
			fprintf(stderr,"error:failed to allocate buf\n");
		}
	}
	{//dynamically allocating, populating, printing, and freeing char**
		srand(time(0));
		int nelem=4;
		int bufsz=nelem*sizeof(char*);
		char**buf=(char**)malloc(bufsz);
		if(buf!=NULL){
			bool err=false;
			int slen=8;
			int strsz=slen*sizeof(char);
			for(int i=0;i<nelem;++i){
				buf[i]=(char*)malloc(strsz);
				if(buf[i]==NULL){
					fprintf(stderr,"error:failed to allocate string\n");
					err=true;
					break;
				}
			}
			if(!err){
				for(int i=0;i<nelem;++i){
					snprintf(buf[i],slen-1,"val:%d",rand());
				}
				for(int i=0;i<nelem;++i){
					printf("%s\n",buf[i]);
				}
			}
			for(int i=0;i<nelem;++i){
				if(buf[i]!=NULL)free(buf[i]);
			}
			free(buf);
		}else{
			fprintf(stderr,"error:failed to allocate buf\n");
		}
	}
	{//malloc in an array, here we have an array, which has a compile time size,
	 //populated with character pointers, pointing to runtime allocated arrays of char
	 //iteration ensues via char**, and the array contains a NULL terminator element
	 //to indicate the end of the array
		int bufellen=8;
		int bufelsz=bufellen*sizeof(char*);
		char*buf[]={
			(char*)malloc(bufelsz),
			(char*)malloc(bufelsz),
			(char*)malloc(bufelsz),
			(char*)malloc(bufelsz),
			NULL
		};
		char**pos=buf;
		while(*pos!=NULL){
			snprintf(*pos,bufellen-1,"val: %d",rand());
			++pos;
		}
		pos=buf;
		while(*pos!=NULL){
			printf("%s\n",*pos);
			++pos;
		}
		pos=buf;
		while(*pos!=NULL){
			free(*pos);
			pos++;
		}
	}

	return EXIT_SUCCESS;
}
