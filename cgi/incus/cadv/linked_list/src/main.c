/*!@file: ./src/main.c
 * @brief: Linked list example. This includes the use of a `struct`, pointers,
 *         `malloc`, and `free`
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#define SZ_NAM 16
#define SZ_DSC 64
typedef struct DICT_ENTRY{
	char nam[SZ_NAM];
	char dsc[SZ_DSC];
	struct DICT_ENTRY*nxt;
}DICT_ENTRY;
int main(int argc,char**argv,char**envp){
	argc=argc;
	argv=argv;
	envp=envp;
	printf("Content-Type: text/plain\n\n");

	//pointers
	DICT_ENTRY*root;
	DICT_ENTRY*nod;

	//populate
	nod=root=(DICT_ENTRY*)malloc(sizeof(DICT_ENTRY));
	snprintf(nod->nam,SZ_NAM-1,"aardvark");
	snprintf(nod->dsc,SZ_DSC-1,"a burrowing African mammal");

	
	nod=nod->nxt=(DICT_ENTRY*)malloc(sizeof(DICT_ENTRY));
	snprintf(nod->nam,SZ_NAM-1,"abyss");
	snprintf(nod->dsc,SZ_DSC-1,"a large, dark, bottomless pit");

	nod=nod->nxt=(DICT_ENTRY*)malloc(sizeof(DICT_ENTRY));
	snprintf(nod->nam,SZ_NAM-1,"acument");
	snprintf(nod->dsc,SZ_DSC-1,"mentally very bright; keen");

	nod=nod->nxt=(DICT_ENTRY*)malloc(sizeof(DICT_ENTRY));
	snprintf(nod->nam,SZ_NAM-1,"addle");
	snprintf(nod->dsc,SZ_DSC-1,"to become very confused");

	nod=nod->nxt=(DICT_ENTRY*)malloc(sizeof(DICT_ENTRY));
	snprintf(nod->nam,SZ_NAM-1,"aerie");
	snprintf(nod->dsc,SZ_DSC-1,"a high nest used by eagles");
	nod->nxt=NULL;

	//traverse and print
	for(int i=0;i<2;++i){
		nod=root;
		while(nod!=NULL){
			printf("adr: %p\n",(void*)nod);
			printf("nam: %s\n",nod->nam);
			printf("dsc: %s\n",nod->dsc);
			nod=nod->nxt;
		}
	}

	//free
	nod=root;
	while(nod!=NULL){
		root=nod;
		nod=nod->nxt;
		free(root);
	}
	root=nod=NULL;
	
	
	return EXIT_SUCCESS;
}
