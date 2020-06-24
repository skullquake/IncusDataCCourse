/*!@file a.c
 * @brief http utilities
 */
#include"util/http.h"
#include<string.h>
#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
/*! Searches URL query string for key value
 * 
 *  Given query string `input` this function attempts to
 *  find `find` key and populates `**dst`, a pointer to
 *  a pointer. Memory will be allocated to dest if found
 *  and it will be populated with the value
 *
 *  If the key was not found, `dest` is set to `NULL`
 * 
 *  Remember to free `dest` it was not found
 *
    \param dest destination buffer
    \param input input streag to search
    \param find needle to search for
 */
void httpString(char**dest,char*input,const char*find){
	char* found=strstr(input, find);
	if(!found){
		*dest=NULL;//not found
		return;
	}
	char* assign=found+strlen(find);
	if(*assign!='='){
		*dest=NULL;//ill formed
		return;
	}
	char* value=assign+1;
	char* end_value=strchr(value,'&');
	if(!end_value){
		//end_value=strchr(value,0)-1;//-1!
		end_value=strchr(value,0);//-1!
	}
	int length=end_value-value;
	*dest=(char*)malloc(length+1);
	if(!*dest) {
		*dest=NULL;//not enough memory
		return;
	}
	memcpy(*dest,value,length);
	(*dest)[length]=0;
	//decode
	char*decoded=(char*)malloc(strlen(*dest)+1);
	if(decoded!=NULL){
		if(urldecode(*dest,decoded)<0){
			fprintf(stderr,"Failed to decode\n");
		}else{
			sprintf(*dest,"%s",decoded);
			free(decoded);
		}
	}else{
		fprintf(stderr,"Failed to allocate decode buffer\n");
	}
}
/*! Reads request body from `stdin` given
 *  \param len Number of bytes to read
 *  \param fp stream to read from
 *  \return `string` populated from stream with `len` bytes
 */

char* stream2buf(unsigned long len,FILE*fp){
	char*buf=NULL;
	buf=(char*)malloc(len+2);			//allocate buffer
	size_t brd=fread(buf,1,len,fp);			//bytes read
	buf[brd]='\0';					//add terminator
	/*
	//memset(buf+brd+1,(int)'\0',(len+2)-(size_t)(brd+1));	//terminator
	fprintf(stderr,"2\n");
	fprintf("brd: %zu\n",brd);
	fprintf("BUF: %s\n",buf);
	*/
	return buf;
}
/*! Checks if a character is a hexadecimal character (ripped from rosetta)
    \param x character to check
    \return `1` if hex, else `0`
 */
int ishex(int x){
	return	(x>='0'&&x<='9')||
		(x>='a'&&x<='f')||
		(x>='A'&&x<='F');
}
/*! Decodes a URL string (ripped from rosetta)
    \param s string to decode
    \param dec preallocated buffer to store decoded result in
    \return <0 on failure
 */
int urldecode(const char*s,char*dec){
	char *o;
	const char*end=s+strlen(s);
	int c;
	for(o=dec;s<=end;o++){
		c=*s++;
		if(c=='+')c=' ';
		else if(c=='%'&&(
			!ishex(*s++)||
			!ishex(*s++)||
			!sscanf(s-2,"%2x",&c)
			)
		)
			return -1;
		if(dec)*o=c;
	}
	return o-dec;
}


