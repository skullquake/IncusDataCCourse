/*!@file src/srv/hdl/main.c
 * @brief main event handler
 */
#include"srv/hdl/main.h"
#include"macros/logging.h"
extern struct mg_serve_http_opts s_http_server_opts;
void ev_handler(struct mg_connection*c,int ev,void *p){
	if(ev==MG_EV_HTTP_REQUEST){
		DBGVAR(ev_handler,p);
		DBGVAR("MG_EV_HTTP_REQUEST",s);
		mg_serve_http(c,(struct http_message*)p,s_http_server_opts);
	}
#if 0 /*skip*/
	struct http_message*hm=(struct http_message *) p;
	mg_printf(c,"HTTP/1.0 200 OK\r\n\r\n[Home]");
	c->flags|=MG_F_SEND_AND_CLOSE;
#endif

}
