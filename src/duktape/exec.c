#include"duktape/exec.h"
#include"duktape/duktape.h"
#include"duktape/register.h"
#include<stdio.h>
char*actionDukEval(char*s){
	duk_context *ctx=duk_create_heap_default();
	duk_register(ctx);
#if 0
	char*fmt="try{%s}catch(e){print(e.toString());}";
	size_t bufsz=snprintf(0,0,fmt,s);
	char*swrapped=(char*)malloc(bufsz+1);
	if(swrapped!=NULL){
		snprintf(swrapped,bufsz,fmt,s);
		duk_eval_string_noresult(ctx,swrapped);
		free(swrapped);
	}else{
		fprintf(stderr,"actionDuk:Failed to allocate try{}catch{} wrapper");
	}
#endif
	duk_eval_string_noresult(ctx,s);
	duk_destroy_heap(ctx);
	return NULL;
}
void duk_exec(const char*path){
	char*buffer=0;
	long length;
	FILE*f=fopen(path,"rb");
	if(f){
		fseek(f,0,SEEK_END);
		length=ftell(f);
		fseek(f,0,SEEK_SET);
		buffer=malloc(length+1);
		if(buffer){
			fread(buffer,1,length,f);
			buffer[length]='\0';
		}
		fclose(f);
	}
	if(buffer){
		actionDukEval(buffer);
		free(buffer);
	}else{
		fprintf(stderr,"Error:duk_exec:Failed to open file\n");
	}
}