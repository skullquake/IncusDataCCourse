/*!@file src/srv/hdl/duk.c
 * @brief scripting event handler
 */
#include"srv/hdl/duk.h"
#include"macros/logging.h"
#include"duktape/duktape.h"
#include"duktape/register.h"
#include<stdio.h>
extern struct mg_serve_http_opts s_http_server_opts;
static void dukexec(char*path,struct mg_connection*nc,int ev,void *ev_data);
void hdl_duk(struct mg_connection*c,int ev,void *p){
	DBGVAR(hdl_duk,p);
	if(ev==MG_EV_HTTP_REQUEST){
			struct http_message*hm=(struct http_message*)p;
			struct mg_str buf=hm->query_string;
			char*scrkey="scr";
			char scrval[64];
			int ret = mg_get_http_var(&buf,scrkey,scrval, sizeof(scrval));
		if(ret>0){
			//mg_printf(c,"HTTP/1.0 200 OK\r\n\r\nfound");
			dukexec(scrval,c,ev,p);
			c->flags|=MG_F_SEND_AND_CLOSE;
		}else{
			mg_printf(c,"HTTP/1.0 200 OK\r\n");
			mg_printf(c,"Content-Type: application/json\r\n");
			mg_printf(c,"\r\n");
			mg_printf(c,"{\n\t\"error\":\"scr not specified\"\n\r}\n");
			c->flags|=MG_F_SEND_AND_CLOSE;
		}
	}
}
static duk_ret_t native_mg_printf(duk_context*ctx){
	struct mg_connection*nc=(struct mg_connection*)duk_to_pointer(ctx,0);
	char*val=duk_to_string(ctx,1);
	mg_printf(nc,val);
	return 0;
}
static void dukexec(char*path,struct mg_connection*nc,int ev,void *ev_data){
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


		duk_push_pointer(ctx,nc);
		duk_put_global_string(ctx,"nc");
		duk_push_int(ctx,ev);
		duk_put_global_string(ctx,"ev");
		duk_push_pointer(ctx,ev_data);
		duk_put_global_string(ctx,"ev_data");

		duk_push_c_function(ctx,native_mg_printf,2);
		duk_put_global_string(ctx,"mg_printf");//how to make varargs???

		duk_eval_string_noresult(ctx,buffer);
		duk_destroy_heap(ctx);

		free(buffer);
	}else{
		fprintf(stderr,"Error:duk_exec:Failed to open file\n");
	}
}
