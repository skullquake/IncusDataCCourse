/*!@file srv/srv.c
 * @brief server module
 */
#include"srv/srv.h"
#include"srv/hdl/main.h"
#include"srv/hdl/duk.h"
#include"macros/logging.h"
#include"mongoose/mongoose.h"
#define POLLTIME 100
/*! Server port */
const char*s_http_port="8999";
/*! Global server options */
struct mg_serve_http_opts s_http_server_opts;
/*! starts server (todo: parameterize)
    \return nothing
*/
void srv_start(char*port){
	DBGVAR(srv_start,p);
	port=port==NULL?s_http_port:port;
	struct mg_mgr mgr;
	struct mg_connection*c;
	mg_mgr_init(&mgr,NULL);
	printf("Starting web server on port %s\n",port);
	c=mg_bind(&mgr,port,ev_handler);
	mg_register_http_endpoint(c,"/duk",hdl_duk);
	mg_set_protocol_http_websocket(c);
	s_http_server_opts.document_root=".";
	s_http_server_opts.cgi_file_pattern="**.ps1|**.py|**.cgi|**.bat|**.sh|**.exe$|**.out$";

	//set cgi interpreter based on host
	printf("--------------------------\n");
#ifdef WIN32
	char cgi_host[]="WIN32";
	char cgi_interpreter[]="C:\\Windows\\System32\\cmd.exe /s ";
		//C:\\Windows\\System32\\WindowsPowerShell\\v1.0\\powershell.exe -File "
#else
	char cgi_host[]="LINUX";
	char cgi_interpreter[]="";
#endif
	if(*cgi_host!='\0'){
		printf("HOST: %s\n",cgi_host);
	}else{
		printf("HOST: NONE\n");
	}
	if(*cgi_interpreter!='\0'){
		printf("SHELL: %s\n",cgi_interpreter);
	}else{
		printf("SHELL: NONE\n");
	}
	printf("--------------------------\n");

	s_http_server_opts.enable_directory_listing="yes";
	for(;;){
		mg_mgr_poll(&mgr,POLLTIME);
	}
	mg_mgr_free(&mgr);
}
