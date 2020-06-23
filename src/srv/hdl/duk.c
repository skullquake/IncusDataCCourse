/*!@file src/srv/hdl/duk.c
 * @brief scripting event handler
 */
#include"srv/hdl/duk.h"
#include"macros/logging.h"
extern struct mg_serve_http_opts s_http_server_opts;
void hdl_duk(struct mg_connection*c,int ev,void *p){
	DBGVAR(hdl_duk,p);
	if(ev==MG_EV_HTTP_REQUEST){
		struct http_message*hm=(struct http_message *) p;
		mg_printf(c,"HTTP/1.0 200 OK\r\n\r\n[Home]");
		c->flags|=MG_F_SEND_AND_CLOSE;
		//mg_send_head(c,200,hm->message.len,"Content-Type: text/plain");
		//mg_printf(c,"%.*s",(int)hm->message.len,hm->message.p);
	}
}
