/*!@file src/srv/hdl/duk.c
 * @brief scripting event handler
 */
#include"srv/hdl/duk.h"
#include"macros/logging.h"
#include"duktape/duktape.h"
#include"duktape/register.h"
#include<stdio.h>
#include<stdint.h>
#include<string.h>
#define NUM_SESSIONS 32
#define SESSION_COOKIE_NAME "mgs"
/*! struct describing session
 */
typedef struct session{
	uint64_t id;
	double created;
	double last_used;
	char*user;
	int userdata;
}session;
session s_sessions[NUM_SESSIONS];

extern struct mg_serve_http_opts s_http_server_opts;
static void dukexec(char*path,struct mg_connection*nc,int ev,void *ev_data);
/*! Extract session from cookie
 *  @param hm `struct http_message`
 *  @return `struct session`
 */
static struct session *get_session(struct http_message*hm);
/*! Event handler for js execution. Exepcts url argument scr with value of path
 *  to script to execute
 */
void hdl_duk(struct mg_connection*c,int ev,void *p){
	DBGVAR(hdl_duk,p);
	if(ev==MG_EV_HTTP_REQUEST){
		struct http_message*hm=(struct http_message*)p;
		struct mg_str buf=hm->query_string;
		char*scrkey="scr";
		char scrval[64];
		int ret = mg_get_http_var(&buf,scrkey,scrval, sizeof(scrval));
		session*s=get_session(hm);
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
/*! native function to register on js context */
static duk_ret_t native_mg_printf(duk_context*ctx){//todo: varargs
	struct mg_connection*nc=(struct mg_connection*)duk_to_pointer(ctx,0);
	char*val=duk_to_string(ctx,1);
	mg_printf(nc,val);
	return 0;
}
/*! open file, get contents, create js context, register and execute */
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
		//register request parameters (pointers)
		duk_push_pointer(ctx,nc);
		duk_put_global_string(ctx,"nc");
		duk_push_int(ctx,ev);
		duk_put_global_string(ctx,"ev");
		duk_push_pointer(ctx,ev_data);
		duk_put_global_string(ctx,"ev_data");
		//register mongoose functions - todo: refactor
		duk_push_c_function(ctx,native_mg_printf,2);
		duk_put_global_string(ctx,"mg_printf");//todo: varargs
		duk_eval_string_noresult(ctx,buffer);
		duk_destroy_heap(ctx);
		free(buffer);
	}else{
		fprintf(stderr,"Error:duk_exec:Failed to open file\n");
	}
}
static struct session *get_session(struct http_message*hm){
	printf("info:get_session:start\n");
	session*ret=NULL;
	char ssid_buf[64];
	char*ssid=ssid_buf;
	struct mg_str*cookie_header=mg_get_http_header(hm,"cookie");
	if(cookie_header==NULL){
		printf("info:get_session:no cookie header found\n");
		goto clean;
	}
	if(!mg_http_parse_header2(cookie_header,SESSION_COOKIE_NAME,&ssid,sizeof(ssid_buf))){
		printf("warning:get_session:failed to obtain session cookie\n");
		goto clean;
	}
	uint64_t sid=strtoull(ssid,NULL,16);
	int i;
	for(i=0;i<NUM_SESSIONS;++i){
		if(s_sessions[i].id==sid){
			printf("info:get_session:session found\n");
			s_sessions[i].last_used=mg_time();
			ret=&s_sessions[i];
			goto clean;
		}
	}
	printf("info:get_session:session not found\n");
	clean:
		if(ssid!=ssid_buf)free(ssid);
	printf("info:get_session:end\n");
	return ret;
}
