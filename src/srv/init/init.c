#include"srv/init/init.h"
#include"duktape/duktape.h"
#include"duktape/register.h"
#include"macros/logging.h"
void srv_init(char* path){
	if(path!=NULL){
		//scripted initialization
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
			duk_context *ctx=duk_create_heap_default();
			duk_register(ctx);
			duk_eval_string_noresult(ctx,buffer);
			duk_destroy_heap(ctx);
			free(buffer);
		}else{
			fprintf(stderr,"Error:duk_exec:Failed to open file\n");
		}
	}else{
		//native c initialization
	}
}

