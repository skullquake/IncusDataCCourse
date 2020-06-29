/*!@file: ./src/main.c
 * @brief: Various ways of iterating through an array of arrays. Addresses are printed for verification
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define D0 2
#define D1 2
int main(int argc,char**argv,char**envp){
	argc=argc;
	argv=argv;
	envp=envp;
	printf("Content-Type: text/plain\n\n");
	{
		int buf[D0][D1];
		int idx=0;
		for(int i=0;i<D0;++i){
			for(int j=0;j<D0;++j){
				buf[i][j]=idx++;
			}
		}
		for(int i=0;i<D0;++i){
			for(int j=0;j<D0;++j){
				printf("%p: %d\n",&buf[i][j],buf[i][j]);
			}
		}
	}
	{
		int buf[D0][D1];
		for(int i=0;i<D0*D1;++i){
			*((int*)(buf)+i)=i;
		}
		for(int i=0;i<D0*D1;++i){
			printf("%p: %d\n",((int*)(buf)+i),*((int*)(buf)+i));
		}
	}
	{
		int buf[D0][D1];
		int*pos=(int*)buf;
		for(int i=0;i<D0*D1;++i,++pos){
			*pos=i;
		}
		pos=(int*)buf;
		for(int i=0;i<D0*D1;++i,++pos){
			printf("%p: %d\n",pos,*pos);
		}
	}
	{
		int buf[D0][D1];
		int*beg=(int*)buf;
		int*end=beg+(D0*D1);
		for(int idx=0,*pos=beg;pos!=end;++pos,++idx){
			*pos=idx;
		}
		for(int*pos=beg;pos!=end;++pos){
			printf("%p: %d\n",pos,*pos);
		}
	}
	return EXIT_SUCCESS;
}
