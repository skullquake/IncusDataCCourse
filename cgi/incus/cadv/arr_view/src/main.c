/*!@file: ./src/main.c
 * @brief: You can define an array, then define a pointer to a specific element in that array.
 *         This pointer does not need to pointer to the first element. If it points
 *         To the second element, you can indeed use <ident>[-1] or *(<ident>-1)
 *         to reference the first element. 
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
int main(int argc,char**argv,char**envp){
	argc=argc;
	argv=argv;
	envp=envp;
	printf("Content-Type: text/plain\n\n");
	{
		int buf[10];
		int bufsz=sizeof(buf)/sizeof(*buf);
		int*beg=buf;
		int*end=buf+bufsz;
		int*pos=buf;
		int idx=0;
		//populate
		while(pos!=end){
			*pos=idx++;
			pos+=1;
		}
		pos=buf;
		idx=0;
		//iterate and print out
		while(pos!=end){
			printf("buf[%2d]: %d\n",idx,*pos);
			pos+=1;
			++idx;
		}
		//create pointer pointing to second element
		int*buf2=buf+1;
		printf("buf2[ 0]: %d\n",buf2[0]);
		printf("buf2[-1]: %d\n",buf2[-1]);
		//create pointer pointing to last element and iterate in reverse
		int*buf3=end-1;
		for(int i=0;i<bufsz;i++){
			printf("buf3[%2d]: %d\n",-i,buf3[-i]);
		}
		
	}
	return EXIT_SUCCESS;
}
