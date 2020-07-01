/*!@file duktape/curl.c
 * @brief Register various curl functions
 */
#ifdef DUK_USE_CURL
#include"duktape/sqlite.h"
#include<curl/curl.h>
/* @brief curl test
 * @param ctx script context
 * @return number of return values
 */
static duk_ret_t native_curl_test(duk_context*ctx){
	curl_global_init(CURL_GLOBAL_ALL);
	CURL*myHandle;
	CURLcode result;
	myHandle=curl_easy_init();
	curl_easy_setopt(myHandle,CURLOPT_URL,"http://127.0.0.1:1234/duk?scr=./scr/ep/main.js");
	result=curl_easy_perform(myHandle);
	curl_easy_cleanup(myHandle);
	return 0;
}
/* ---------------------------------------- */
/* curl.h                                   */
/* ---------------------------------------- */

/* @brief native CURL_EXTERN CURLcode curl_global_init(long flags);
 * @param ctx script context
 * @return number of return values
 */
static duk_ret_t native_curl_global_init(duk_context*ctx){
	//note typedef CURLcode (*curl_conv_callback)(char *buffer, size_t length);
	//for now, CURLcode will be made int
	duk_push_int(ctx,curl_global_init(duk_get_int(ctx,0)));
	return 1;
}
/* ---------------------------------------- */
/* easy.h                                   */
/* ---------------------------------------- */
/* @brief native CURL_EXTERN CURL *curl_easy_init(void);
 * @param ctx script context
 * @return number of return values
 */
static duk_ret_t native_curl_easy_init(duk_context*ctx){
	duk_push_pointer(ctx,(void*)curl_easy_init());
	return 1;
}
/* @brief native CURL_EXTERN CURLcode curl_easy_setopt(CURL *curl, CURLoption option, ...);
 * @param ctx script context
 * @return number of return values
 */
static duk_ret_t native_curl_easy_setopt(duk_context*ctx){
	//unable to handle varargs at this point, assuming option>=3 char*, might be void*
	duk_ret_t ret=0;
	if(duk_is_undefined(ctx,2)){
		fprintf(stderr,"error:native_curl_easy_setopt:unsupported type\n");
	}else if(duk_is_null(ctx,2)){
		fprintf(stderr,"error:native_curl_easy_setopt:unsupported type\n");
	}else if(duk_is_boolean(ctx,2)){
		fprintf(stderr,"error:native_curl_easy_setopt:unsupported type\n");
	}else if(duk_is_number(ctx,2)){
		duk_push_int(ctx,curl_easy_setopt((CURL*)duk_get_pointer(ctx,0),duk_get_int(ctx,1),(long)duk_get_number(ctx,2)));
		ret=1;
	}else if(duk_is_number(ctx,2)){
		fprintf(stderr,"error:native_curl_easy_setopt:unsupported type\n");
	}else if(duk_is_nan(ctx,2)){
		fprintf(stderr,"error:native_curl_easy_setopt:unsupported type\n");
	}else if(duk_is_string(ctx,2)){
		duk_push_int(ctx,curl_easy_setopt((CURL*)duk_get_pointer(ctx,0),duk_get_int(ctx,1),duk_get_string(ctx,2)));
		ret=1;
	}else if(duk_is_object(ctx,2)){
		fprintf(stderr,"error:native_curl_easy_setopt:unsupported type\n");
	}else if(duk_is_buffer(ctx,2)){
		fprintf(stderr,"error:native_curl_easy_setopt:unsupported type\n");
	}else if(duk_is_buffer_data(ctx,2)){
		fprintf(stderr,"error:native_curl_easy_setopt:unsupported type\n");
	}else if(duk_is_pointer(ctx,2)){
		duk_push_int(ctx,curl_easy_setopt((CURL*)duk_get_pointer(ctx,0),duk_get_int(ctx,1),(void*)duk_get_pointer(ctx,2)));
		ret=1;
	}else if(duk_is_lightfunc(ctx,2)){
		fprintf(stderr,"error:native_curl_easy_setopt:unsupported type\n");
	}else if(duk_is_symbol(ctx,2)){
		fprintf(stderr,"error:native_curl_easy_setopt:unsupported type\n");
	}else if(duk_is_array(ctx,2)){
		fprintf(stderr,"error:native_curl_easy_setopt:unsupported type\n");
	}else if(duk_is_function(ctx,2)){
		fprintf(stderr,"error:native_curl_easy_setopt:unsupported type\n");
	}else if(duk_is_c_function(ctx,2)){
		fprintf(stderr,"error:native_curl_easy_setopt:unsupported type\n");
	}else if(duk_is_ecmascript_function(ctx,2)){
		fprintf(stderr,"error:native_curl_easy_setopt:unsupported type\n");
	}else if(duk_is_bound_function(ctx,2)){
		fprintf(stderr,"error:native_curl_easy_setopt:unsupported type\n");
	}else if(duk_is_thread(ctx,2)){
		fprintf(stderr,"error:native_curl_easy_setopt:unsupported type\n");
	}else if(duk_is_callable(ctx,2)){
		fprintf(stderr,"error:native_curl_easy_setopt:unsupported type\n");
	}else if(duk_is_constructable(ctx,2)){
		fprintf(stderr,"error:native_curl_easy_setopt:unsupported type\n");
	}else if(duk_is_dynamic_buffer(ctx,2)){
		fprintf(stderr,"error:native_curl_easy_setopt:unsupported type\n");
	}else if(duk_is_fixed_buffer(ctx,2)){
		fprintf(stderr,"error:native_curl_easy_setopt:unsupported type\n");
	}else if(duk_is_external_buffer(ctx,2)){
		fprintf(stderr,"error:native_curl_easy_setopt:unsupported type\n");
	}else if(duk_is_primitive(ctx,2)){
		fprintf(stderr,"error:native_curl_easy_setopt:unsupported type\n");
	}else if(duk_is_object_coercible(ctx,2)){
		fprintf(stderr,"error:native_curl_easy_setopt:unsupported type\n");
	}else if(duk_is_error(ctx,2)){
		fprintf(stderr,"error:native_curl_easy_setopt:unsupported type\n");
	}else if(duk_is_eval_error(ctx,2)){
		fprintf(stderr,"error:native_curl_easy_setopt:unsupported type\n");
	}else if(duk_is_range_error(ctx,2)){
		fprintf(stderr,"error:native_curl_easy_setopt:unsupported type\n");
	}else if(duk_is_reference_error(ctx,2)){
		fprintf(stderr,"error:native_curl_easy_setopt:unsupported type\n");
	}else if(duk_is_syntax_error(ctx,2)){
		fprintf(stderr,"error:native_curl_easy_setopt:unsupported type\n");
	}else if(duk_is_type_error(ctx,2)){
		fprintf(stderr,"error:native_curl_easy_setopt:unsupported type\n");
	}else if(duk_is_uri_error(ctx,2)){
		fprintf(stderr,"error:native_curl_easy_setopt:unsupported type\n");
	}else{
		fprintf(stderr,"error:native_curl_easy_setopt:unsupported type\n");
	}
	return ret;
}
/* @brief native CURL_EXTERN CURLcode curl_easy_perform(CURL *curl);
 * @param ctx script context
 * @return number of return values
 */
static duk_ret_t native_curl_easy_perform(duk_context*ctx){
	duk_push_int(ctx,curl_easy_perform((CURL*)duk_get_pointer(ctx,0)));
	return 1;
}
/* @brief native CURL_EXTERN void curl_easy_cleanup(CURL *curl);
 * @param ctx script context
 * @return number of return values
 */
static duk_ret_t native_curl_easy_cleanup(duk_context*ctx){
	curl_easy_cleanup((CURL*)duk_to_pointer(ctx,0));
	return 0;
}
/* @brief native CURL_EXTERN CURLcode curl_easy_getinfo(CURL *curl, CURLINFO info, ...);
 * @param ctx script context
 * @return number of return values
 */
static duk_ret_t native_curl_easy_getinfo(duk_context*ctx){
	return 0;
}
/* @brief native CURL_EXTERN CURL *curl_easy_duphandle(CURL *curl);
 * @param ctx script context
 * @return number of return values
 */
static duk_ret_t native_curl_easy_duphandle(duk_context*ctx){
	return 0;
}
/* @brief native CURL_EXTERN void curl_easy_reset(CURL *curl);
 * @param ctx script context
 * @return number of return values
 */
static duk_ret_t native_curl_easy_reset(duk_context*ctx){
	curl_easy_reset((CURL*)duk_to_pointer(ctx,0));
	return 0;
}
/* @brief native CURL_EXTERN CURLcode curl_easy_recv(CURL *curl, void *buffer, size_t buflen,size_t *n);
 * @param ctx script context
 * @return number of return values
 */
static duk_ret_t native_curl_easy_recv(duk_context*ctx){
	size_t n=(size_t)duk_to_int(ctx,3);
	duk_push_int(ctx,curl_easy_recv(
		(CURL*)duk_to_pointer(ctx,0),
		(void*)duk_to_pointer(ctx,1),
		(size_t)duk_to_int(ctx,2),
		&n
	));
	return 1;
}
/* @brief native CURL_EXTERN CURLcode curl_easy_send(CURL *curl, const void *buffer,size_t buflen, size_t *n);
 * @param ctx script context
 * @return number of return values
 */
static duk_ret_t native_curl_easy_send(duk_context*ctx){
	return 0;
}
void duk_register_curl(duk_context*ctx){
	//----------------------------------------
	//curl.h
	//----------------------------------------
	//CONSTANTS
	// enum curl_sslbackend
	duk_push_int(ctx,CURLSSLBACKEND_NONE);
	duk_put_global_string(ctx,"CURLSSLBACKEND_NONE");
	duk_push_int(ctx,CURLSSLBACKEND_OPENSSL);
	duk_put_global_string(ctx,"CURLSSLBACKEND_OPENSSL");
	duk_push_int(ctx,CURLSSLBACKEND_GNUTLS);
	duk_put_global_string(ctx,"CURLSSLBACKEND_GNUTLS");
	duk_push_int(ctx,CURLSSLBACKEND_NSS);
	duk_put_global_string(ctx,"CURLSSLBACKEND_NSS");
	duk_push_int(ctx,CURLSSLBACKEND_OBSOLETE4);
	duk_put_global_string(ctx,"CURLSSLBACKEND_OBSOLETE4");
	duk_push_int(ctx,CURLSSLBACKEND_GSKIT);
	duk_put_global_string(ctx,"CURLSSLBACKEND_GSKIT");
	duk_push_int(ctx,CURLSSLBACKEND_POLARSSL );
	duk_put_global_string(ctx,"CURLSSLBACKEND_POLARSSL");
	duk_push_int(ctx,CURLSSLBACKEND_WOLFSSL);
	duk_put_global_string(ctx,"CURLSSLBACKEND_WOLFSSL");
	duk_push_int(ctx,CURLSSLBACKEND_SCHANNEL);
	duk_put_global_string(ctx,"CURLSSLBACKEND_SCHANNEL");
	duk_push_int(ctx,CURLSSLBACKEND_DARWINSSL);
	duk_put_global_string(ctx,"CURLSSLBACKEND_DARWINSSL");
	duk_push_int(ctx,CURLSSLBACKEND_AXTLS);
	duk_put_global_string(ctx,"CURLSSLBACKEND_AXTLS");
	duk_push_int(ctx,CURLSSLBACKEND_MBEDTLS);
	duk_put_global_string(ctx,"CURLSSLBACKEND_MBEDTLS");
	// enum curl_sslbackend - end
	duk_push_int(ctx,CURL_HTTPPOST_FILENAME);
	duk_put_global_string(ctx,"CURL_HTTPPOST_FILENAME");
	duk_push_int(ctx,CURL_HTTPPOST_READFILE);
	duk_put_global_string(ctx,"CURL_HTTPPOST_READFILE");
	duk_push_int(ctx,CURL_HTTPPOST_PTRNAME);
	duk_put_global_string(ctx,"CURL_HTTPPOST_PTRNAME");
	duk_push_int(ctx,CURL_HTTPPOST_PTRCONTENTS);
	duk_put_global_string(ctx,"CURL_HTTPPOST_PTRCONTENTS");
	duk_push_int(ctx,CURL_HTTPPOST_BUFFER);
	duk_put_global_string(ctx,"CURL_HTTPPOST_BUFFER");
	duk_push_int(ctx,CURL_HTTPPOST_PTRBUFFER);
	duk_put_global_string(ctx,"CURL_HTTPPOST_PTRBUFFER");
	duk_push_int(ctx,CURL_HTTPPOST_CALLBACK);
	duk_put_global_string(ctx,"CURL_HTTPPOST_CALLBACK");
	duk_push_int(ctx,CURL_HTTPPOST_LARGE);
	duk_put_global_string(ctx,"CURL_HTTPPOST_LARGE");
	duk_push_int(ctx,CURL_MAX_READ_SIZE);
	duk_put_global_string(ctx,"CURL_MAX_READ_SIZE");
	duk_push_int(ctx,CURL_MAX_WRITE_SIZE);
	duk_put_global_string(ctx,"CURL_MAX_WRITE_SIZE");
	duk_push_int(ctx,CURL_MAX_HTTP_HEADER);
	duk_put_global_string(ctx,"CURL_MAX_HTTP_HEADER");
	duk_push_int(ctx,CURL_WRITEFUNC_PAUSE);
	duk_put_global_string(ctx,"CURL_WRITEFUNC_PAUSE");
	// enum curlfiletype
	duk_push_int(ctx,CURLFILETYPE_FILE );
	duk_put_global_string(ctx,"CURLFILETYPE_FILE");
	duk_push_int(ctx,CURLFILETYPE_DIRECTORY);
	duk_put_global_string(ctx,"CURLFILETYPE_DIRECTORY");
	duk_push_int(ctx,CURLFILETYPE_SYMLINK);
	duk_put_global_string(ctx,"CURLFILETYPE_SYMLINK");
	duk_push_int(ctx,CURLFILETYPE_DEVICE_BLOCK);
	duk_put_global_string(ctx,"CURLFILETYPE_DEVICE_BLOCK");
	duk_push_int(ctx,CURLFILETYPE_DEVICE_CHAR);
	duk_put_global_string(ctx,"CURLFILETYPE_DEVICE_CHAR");
	duk_push_int(ctx,CURLFILETYPE_NAMEDPIPE);
	duk_put_global_string(ctx,"CURLFILETYPE_NAMEDPIPE");
	duk_push_int(ctx,CURLFILETYPE_SOCKET);
	duk_put_global_string(ctx,"CURLFILETYPE_SOCKET");
	duk_push_int(ctx,CURLFILETYPE_DOOR);
	duk_put_global_string(ctx,"CURLFILETYPE_DOOR");
	duk_push_int(ctx,CURLFILETYPE_UNKNOWN);
	duk_put_global_string(ctx,"CURLFILETYPE_UNKNOWN");
	// enum curlfiletype - end
	duk_push_int(ctx,CURLFINFOFLAG_KNOWN_FILENAME);
	duk_put_global_string(ctx,"CURLFINFOFLAG_KNOWN_FILENAME");
	duk_push_int(ctx,CURLFINFOFLAG_KNOWN_FILETYPE);
	duk_put_global_string(ctx,"CURLFINFOFLAG_KNOWN_FILETYPE");
	duk_push_int(ctx,CURLFINFOFLAG_KNOWN_TIME);
	duk_put_global_string(ctx,"CURLFINFOFLAG_KNOWN_TIME");
	duk_push_int(ctx,CURLFINFOFLAG_KNOWN_PERM);
	duk_put_global_string(ctx,"CURLFINFOFLAG_KNOWN_PERM");
	duk_push_int(ctx,CURLFINFOFLAG_KNOWN_UID);
	duk_put_global_string(ctx,"CURLFINFOFLAG_KNOWN_UID");
	duk_push_int(ctx,CURLFINFOFLAG_KNOWN_GID);
	duk_put_global_string(ctx,"CURLFINFOFLAG_KNOWN_GID");
	duk_push_int(ctx,CURLFINFOFLAG_KNOWN_SIZE);
	duk_put_global_string(ctx,"CURLFINFOFLAG_KNOWN_SIZE");
	duk_push_int(ctx,CURLFINFOFLAG_KNOWN_HLINKCOUNT);
	duk_put_global_string(ctx,"CURLFINFOFLAG_KNOWN_HLINKCOUNT");
	duk_push_int(ctx,CURL_CHUNK_BGN_FUNC_OK);
	duk_put_global_string(ctx,"CURL_CHUNK_BGN_FUNC_OK");
	duk_push_int(ctx,CURL_CHUNK_BGN_FUNC_FAIL);
	duk_put_global_string(ctx,"CURL_CHUNK_BGN_FUNC_FAIL");
	duk_push_int(ctx,CURL_CHUNK_BGN_FUNC_SKIP);
	duk_put_global_string(ctx,"CURL_CHUNK_BGN_FUNC_SKIP");
	duk_push_int(ctx,CURL_CHUNK_END_FUNC_OK);
	duk_put_global_string(ctx,"CURL_CHUNK_END_FUNC_OK");
	duk_push_int(ctx,CURL_CHUNK_END_FUNC_FAIL);
	duk_put_global_string(ctx,"CURL_CHUNK_END_FUNC_FAIL");
	duk_push_int(ctx,CURL_FNMATCHFUNC_MATCH);
	duk_put_global_string(ctx,"CURL_FNMATCHFUNC_MATCH");
	duk_push_int(ctx,CURL_FNMATCHFUNC_NOMATCH);
	duk_put_global_string(ctx,"CURL_FNMATCHFUNC_NOMATCH");
	duk_push_int(ctx,CURL_FNMATCHFUNC_FAIL);
	duk_put_global_string(ctx,"CURL_FNMATCHFUNC_FAIL");
	duk_push_int(ctx,CURL_SEEKFUNC_OK);
	duk_put_global_string(ctx,"CURL_SEEKFUNC_OK");
	duk_push_int(ctx,CURL_SEEKFUNC_FAIL);
	duk_put_global_string(ctx,"CURL_SEEKFUNC_FAIL");
	duk_push_int(ctx,CURL_SEEKFUNC_CANTSEEK);
	duk_put_global_string(ctx,"CURL_SEEKFUNC_CANTSEEK");
	duk_push_int(ctx,CURL_READFUNC_ABORT);
	duk_put_global_string(ctx,"CURL_READFUNC_ABORT");
	duk_push_int(ctx,CURL_READFUNC_PAUSE);
	duk_put_global_string(ctx,"CURL_READFUNC_PAUSE");
	// enum curlsocktype
	duk_push_int(ctx,CURLSOCKTYPE_IPCXN);
	duk_put_global_string(ctx,"CURLSOCKTYPE_IPCXN");
	duk_push_int(ctx,CURLSOCKTYPE_ACCEPT);
	duk_put_global_string(ctx,"CURLSOCKTYPE_ACCEPT");
	duk_push_int(ctx,CURLSOCKTYPE_LAST);
	duk_put_global_string(ctx,"CURLSOCKTYPE_LAST");
	// enum curlsocktype - end
	duk_push_int(ctx,CURL_SOCKOPT_OK);
	duk_put_global_string(ctx,"CURL_SOCKOPT_OK");
	duk_push_int(ctx,CURL_SOCKOPT_ERROR);
	duk_put_global_string(ctx,"CURL_SOCKOPT_ERROR");
	duk_push_int(ctx,CURL_SOCKOPT_ALREADY_CONNECTED);
	duk_put_global_string(ctx,"CURL_SOCKOPT_ALREADY_CONNECTED");
	//enum curlioerr
	duk_push_int(ctx,CURLIOE_OK);
	duk_put_global_string(ctx,"CURLIOE_OK");
	duk_push_int(ctx,CURLIOE_UNKNOWNCMD);
	duk_put_global_string(ctx,"CURLIOE_UNKNOWNCMD");
	duk_push_int(ctx,CURLIOE_FAILRESTART);
	duk_put_global_string(ctx,"CURLIOE_FAILRESTART");
	duk_push_int(ctx,CURLIOE_LAST);
	duk_put_global_string(ctx,"CURLIOE_LAST");
	//enum curlioerr - end
	//enum - curliocmd 
	duk_push_int(ctx,CURLIOCMD_NOP);
	duk_put_global_string(ctx,"CURLIOCMD_NOP");
	duk_push_int(ctx,CURLIOCMD_RESTARTREAD);
	duk_put_global_string(ctx,"CURLIOCMD_RESTARTREAD");
	duk_push_int(ctx,CURLIOCMD_LAST);
	duk_put_global_string(ctx,"CURLIOCMD_LAST");
	//enum - curliocmd - end
	//enum curl_infotype
	duk_push_int(ctx,CURLINFO_TEXT);
	duk_put_global_string(ctx,"CURLINFO_TEXT");
	duk_push_int(ctx,CURLINFO_HEADER_IN);
	duk_put_global_string(ctx,"CURLINFO_HEADER_IN");
	duk_push_int(ctx,CURLINFO_HEADER_OUT);
	duk_put_global_string(ctx,"CURLINFO_HEADER_OUT");
	duk_push_int(ctx,CURLINFO_DATA_IN);
	duk_put_global_string(ctx,"CURLINFO_DATA_IN");
	duk_push_int(ctx,CURLINFO_DATA_OUT);
	duk_put_global_string(ctx,"CURLINFO_DATA_OUT");
	duk_push_int(ctx,CURLINFO_SSL_DATA_IN);
	duk_put_global_string(ctx,"CURLINFO_SSL_DATA_IN");
	duk_push_int(ctx,CURLINFO_SSL_DATA_OUT);
	duk_put_global_string(ctx,"CURLINFO_SSL_DATA_OUT");
	duk_push_int(ctx,CURLINFO_END);
	duk_put_global_string(ctx,"CURLINFO_END");
	//enum curl_infotype - end
	//enum CURLcode
	duk_push_int(ctx,CURLE_OK);
	duk_put_global_string(ctx,"CURLE_OK");
	duk_push_int(ctx,CURLE_UNSUPPORTED_PROTOCOL);
	duk_put_global_string(ctx,"CURLE_UNSUPPORTED_PROTOCOL");
	duk_push_int(ctx,CURLE_FAILED_INIT);
	duk_put_global_string(ctx,"CURLE_FAILED_INIT");
	duk_push_int(ctx,CURLE_URL_MALFORMAT);
	duk_put_global_string(ctx,"CURLE_URL_MALFORMAT");
	duk_push_int(ctx,CURLE_NOT_BUILT_IN);
	duk_put_global_string(ctx,"CURLE_NOT_BUILT_IN");
	duk_push_int(ctx,CURLE_COULDNT_RESOLVE_PROXY);
	duk_put_global_string(ctx,"CURLE_COULDNT_RESOLVE_PROXY");
	duk_push_int(ctx,CURLE_COULDNT_RESOLVE_HOST);
	duk_put_global_string(ctx,"CURLE_COULDNT_RESOLVE_HOST");
	duk_push_int(ctx,CURLE_COULDNT_CONNECT);
	duk_put_global_string(ctx,"CURLE_COULDNT_CONNECT");
	duk_push_int(ctx,CURLE_WEIRD_SERVER_REPLY);
	duk_put_global_string(ctx,"CURLE_WEIRD_SERVER_REPLY");
	duk_push_int(ctx,CURLE_REMOTE_ACCESS_DENIED);
	duk_put_global_string(ctx,"CURLE_REMOTE_ACCESS_DENIED");
	duk_push_int(ctx,CURLE_FTP_ACCEPT_FAILED);
	duk_put_global_string(ctx,"CURLE_FTP_ACCEPT_FAILED");
	duk_push_int(ctx,CURLE_FTP_WEIRD_PASS_REPLY);
	duk_put_global_string(ctx,"CURLE_FTP_WEIRD_PASS_REPLY");
	duk_push_int(ctx,CURLE_FTP_ACCEPT_TIMEOUT);
	duk_put_global_string(ctx,"CURLE_FTP_ACCEPT_TIMEOUT");
	duk_push_int(ctx,CURLE_FTP_WEIRD_PASV_REPLY);
	duk_put_global_string(ctx,"CURLE_FTP_WEIRD_PASV_REPLY");
	duk_push_int(ctx,CURLE_FTP_WEIRD_227_FORMAT);
	duk_put_global_string(ctx,"CURLE_FTP_WEIRD_227_FORMAT");
	duk_push_int(ctx,CURLE_FTP_CANT_GET_HOST);
	duk_put_global_string(ctx,"CURLE_FTP_CANT_GET_HOST");
	duk_push_int(ctx,CURLE_HTTP2);
	duk_put_global_string(ctx,"CURLE_HTTP2");
	duk_push_int(ctx,CURLE_FTP_COULDNT_SET_TYPE);
	duk_put_global_string(ctx,"CURLE_FTP_COULDNT_SET_TYPE");
	duk_push_int(ctx,CURLE_PARTIAL_FILE);
	duk_put_global_string(ctx,"CURLE_PARTIAL_FILE");
	duk_push_int(ctx,CURLE_FTP_COULDNT_RETR_FILE);
	duk_put_global_string(ctx,"CURLE_FTP_COULDNT_RETR_FILE");
	duk_push_int(ctx,CURLE_OBSOLETE20);
	duk_put_global_string(ctx,"CURLE_OBSOLETE20");
	duk_push_int(ctx,CURLE_QUOTE_ERROR);
	duk_put_global_string(ctx,"CURLE_QUOTE_ERROR");
	duk_push_int(ctx,CURLE_HTTP_RETURNED_ERROR);
	duk_put_global_string(ctx,"CURLE_HTTP_RETURNED_ERROR");
	duk_push_int(ctx,CURLE_WRITE_ERROR);
	duk_put_global_string(ctx,"CURLE_WRITE_ERROR");
	duk_push_int(ctx,CURLE_OBSOLETE24);
	duk_put_global_string(ctx,"CURLE_OBSOLETE24");
	duk_push_int(ctx,CURLE_UPLOAD_FAILED);
	duk_put_global_string(ctx,"CURLE_UPLOAD_FAILED");
	duk_push_int(ctx,CURLE_READ_ERROR);
	duk_put_global_string(ctx,"CURLE_READ_ERROR");
	duk_push_int(ctx,CURLE_OUT_OF_MEMORY);
	duk_put_global_string(ctx,"CURLE_OUT_OF_MEMORY");
	duk_push_int(ctx,CURLE_OPERATION_TIMEDOUT);
	duk_put_global_string(ctx,"CURLE_OPERATION_TIMEDOUT");
	duk_push_int(ctx,CURLE_OBSOLETE29);
	duk_put_global_string(ctx,"CURLE_OBSOLETE29");
	duk_push_int(ctx,CURLE_FTP_PORT_FAILED);
	duk_put_global_string(ctx,"CURLE_FTP_PORT_FAILED");
	duk_push_int(ctx,CURLE_FTP_COULDNT_USE_REST);
	duk_put_global_string(ctx,"CURLE_FTP_COULDNT_USE_REST");
	duk_push_int(ctx,CURLE_OBSOLETE32);
	duk_put_global_string(ctx,"CURLE_OBSOLETE32");
	duk_push_int(ctx,CURLE_RANGE_ERROR);
	duk_put_global_string(ctx,"CURLE_RANGE_ERROR");
	duk_push_int(ctx,CURLE_HTTP_POST_ERROR);
	duk_put_global_string(ctx,"CURLE_HTTP_POST_ERROR");
	duk_push_int(ctx,CURLE_SSL_CONNECT_ERROR);
	duk_put_global_string(ctx,"CURLE_SSL_CONNECT_ERROR");
	duk_push_int(ctx,CURLE_BAD_DOWNLOAD_RESUME);
	duk_put_global_string(ctx,"CURLE_BAD_DOWNLOAD_RESUME");
	duk_push_int(ctx,CURLE_FILE_COULDNT_READ_FILE);
	duk_put_global_string(ctx,"CURLE_FILE_COULDNT_READ_FILE");
	duk_push_int(ctx,CURLE_LDAP_CANNOT_BIND);
	duk_put_global_string(ctx,"CURLE_LDAP_CANNOT_BIND");
	duk_push_int(ctx,CURLE_LDAP_SEARCH_FAILED);
	duk_put_global_string(ctx,"CURLE_LDAP_SEARCH_FAILED");
	duk_push_int(ctx,CURLE_OBSOLETE40);
	duk_put_global_string(ctx,"CURLE_OBSOLETE40");
	duk_push_int(ctx,CURLE_FUNCTION_NOT_FOUND);
	duk_put_global_string(ctx,"CURLE_FUNCTION_NOT_FOUND");
	duk_push_int(ctx,CURLE_ABORTED_BY_CALLBACK);
	duk_put_global_string(ctx,"CURLE_ABORTED_BY_CALLBACK");
	duk_push_int(ctx,CURLE_BAD_FUNCTION_ARGUMENT);
	duk_put_global_string(ctx,"CURLE_BAD_FUNCTION_ARGUMENT");
	duk_push_int(ctx,CURLE_OBSOLETE44);
	duk_put_global_string(ctx,"CURLE_OBSOLETE44");
	duk_push_int(ctx,CURLE_INTERFACE_FAILED);
	duk_put_global_string(ctx,"CURLE_INTERFACE_FAILED");
	duk_push_int(ctx,CURLE_OBSOLETE46);
	duk_put_global_string(ctx,"CURLE_OBSOLETE46");
	duk_push_int(ctx,CURLE_TOO_MANY_REDIRECTS);
	duk_put_global_string(ctx,"CURLE_TOO_MANY_REDIRECTS");
	duk_push_int(ctx,CURLE_UNKNOWN_OPTION);
	duk_put_global_string(ctx,"CURLE_UNKNOWN_OPTION");
	duk_push_int(ctx,CURLE_TELNET_OPTION_SYNTAX);
	duk_put_global_string(ctx,"CURLE_TELNET_OPTION_SYNTAX");
	duk_push_int(ctx,CURLE_OBSOLETE50);
	duk_put_global_string(ctx,"CURLE_OBSOLETE50");
	duk_push_int(ctx,CURLE_PEER_FAILED_VERIFICATION);
	duk_put_global_string(ctx,"CURLE_PEER_FAILED_VERIFICATION");
	duk_push_int(ctx,CURLE_GOT_NOTHING);
	duk_put_global_string(ctx,"CURLE_GOT_NOTHING");
	duk_push_int(ctx,CURLE_SSL_ENGINE_NOTFOUND);
	duk_put_global_string(ctx,"CURLE_SSL_ENGINE_NOTFOUND");
	duk_push_int(ctx,CURLE_SSL_ENGINE_SETFAILED);
	duk_put_global_string(ctx,"CURLE_SSL_ENGINE_SETFAILED");
	duk_push_int(ctx,CURLE_SEND_ERROR);
	duk_put_global_string(ctx,"CURLE_SEND_ERROR");
	duk_push_int(ctx,CURLE_RECV_ERROR);
	duk_put_global_string(ctx,"CURLE_RECV_ERROR");
	duk_push_int(ctx,CURLE_OBSOLETE57);
	duk_put_global_string(ctx,"CURLE_OBSOLETE57");
	duk_push_int(ctx,CURLE_SSL_CERTPROBLEM);
	duk_put_global_string(ctx,"CURLE_SSL_CERTPROBLEM");
	duk_push_int(ctx,CURLE_SSL_CIPHER);
	duk_put_global_string(ctx,"CURLE_SSL_CIPHER");
	duk_push_int(ctx,CURLE_SSL_CACERT);
	duk_put_global_string(ctx,"CURLE_SSL_CACERT");
	duk_push_int(ctx,CURLE_BAD_CONTENT_ENCODING);
	duk_put_global_string(ctx,"CURLE_BAD_CONTENT_ENCODING");
	duk_push_int(ctx,CURLE_LDAP_INVALID_URL);
	duk_put_global_string(ctx,"CURLE_LDAP_INVALID_URL");
	duk_push_int(ctx,CURLE_FILESIZE_EXCEEDED);
	duk_put_global_string(ctx,"CURLE_FILESIZE_EXCEEDED");
	duk_push_int(ctx,CURLE_USE_SSL_FAILED);
	duk_put_global_string(ctx,"CURLE_USE_SSL_FAILED");
	duk_push_int(ctx,CURLE_SEND_FAIL_REWIND);
	duk_put_global_string(ctx,"CURLE_SEND_FAIL_REWIND");
	duk_push_int(ctx,CURLE_SSL_ENGINE_INITFAILED);
	duk_put_global_string(ctx,"CURLE_SSL_ENGINE_INITFAILED");
	duk_push_int(ctx,CURLE_LOGIN_DENIED);
	duk_put_global_string(ctx,"CURLE_LOGIN_DENIED");
	duk_push_int(ctx,CURLE_TFTP_NOTFOUND);
	duk_put_global_string(ctx,"CURLE_TFTP_NOTFOUND");
	duk_push_int(ctx,CURLE_TFTP_PERM);
	duk_put_global_string(ctx,"CURLE_TFTP_PERM");
	duk_push_int(ctx,CURLE_REMOTE_DISK_FULL);
	duk_put_global_string(ctx,"CURLE_REMOTE_DISK_FULL");
	duk_push_int(ctx,CURLE_TFTP_ILLEGAL);
	duk_put_global_string(ctx,"CURLE_TFTP_ILLEGAL");
	duk_push_int(ctx,CURLE_TFTP_UNKNOWNID);
	duk_put_global_string(ctx,"CURLE_TFTP_UNKNOWNID");
	duk_push_int(ctx,CURLE_REMOTE_FILE_EXISTS);
	duk_put_global_string(ctx,"CURLE_REMOTE_FILE_EXISTS");
	duk_push_int(ctx,CURLE_TFTP_NOSUCHUSER);
	duk_put_global_string(ctx,"CURLE_TFTP_NOSUCHUSER");
	duk_push_int(ctx,CURLE_CONV_FAILED);
	duk_put_global_string(ctx,"CURLE_CONV_FAILED");
	duk_push_int(ctx,CURLE_CONV_REQD);
	duk_put_global_string(ctx,"CURLE_CONV_REQD");
	duk_push_int(ctx,CURLE_SSL_CACERT_BADFILE);
	duk_put_global_string(ctx,"CURLE_SSL_CACERT_BADFILE");
	duk_push_int(ctx,CURLE_REMOTE_FILE_NOT_FOUND);
	duk_put_global_string(ctx,"CURLE_REMOTE_FILE_NOT_FOUND");
	duk_push_int(ctx,CURLE_SSH);
	duk_put_global_string(ctx,"CURLE_SSH");
	duk_push_int(ctx,CURLE_SSL_SHUTDOWN_FAILED);
	duk_put_global_string(ctx,"CURLE_SSL_SHUTDOWN_FAILED");
	duk_push_int(ctx,CURLE_AGAIN);
	duk_put_global_string(ctx,"CURLE_AGAIN");
	duk_push_int(ctx,CURLE_SSL_CRL_BADFILE);
	duk_put_global_string(ctx,"CURLE_SSL_CRL_BADFILE");
	duk_push_int(ctx,CURLE_SSL_ISSUER_ERROR);
	duk_put_global_string(ctx,"CURLE_SSL_ISSUER_ERROR");
	duk_push_int(ctx,CURLE_FTP_PRET_FAILED);
	duk_put_global_string(ctx,"CURLE_FTP_PRET_FAILED");
	duk_push_int(ctx,CURLE_RTSP_CSEQ_ERROR);
	duk_put_global_string(ctx,"CURLE_RTSP_CSEQ_ERROR");
	duk_push_int(ctx,CURLE_RTSP_SESSION_ERROR);
	duk_put_global_string(ctx,"CURLE_RTSP_SESSION_ERROR");
	duk_push_int(ctx,CURLE_FTP_BAD_FILE_LIST);
	duk_put_global_string(ctx,"CURLE_FTP_BAD_FILE_LIST");
	duk_push_int(ctx,CURLE_CHUNK_FAILED);
	duk_put_global_string(ctx,"CURLE_CHUNK_FAILED");
	duk_push_int(ctx,CURLE_NO_CONNECTION_AVAILABLE);
	duk_put_global_string(ctx,"CURLE_NO_CONNECTION_AVAILABLE");
	duk_push_int(ctx,CURLE_SSL_PINNEDPUBKEYNOTMATCH);
	duk_put_global_string(ctx,"CURLE_SSL_PINNEDPUBKEYNOTMATCH");
	duk_push_int(ctx,CURLE_SSL_INVALIDCERTSTATUS);
	duk_put_global_string(ctx,"CURLE_SSL_INVALIDCERTSTATUS");
	duk_push_int(ctx,CURLE_HTTP2_STREAM);
	duk_put_global_string(ctx,"CURLE_HTTP2_STREAM");
	duk_push_int(ctx,CURL_LAST);
	duk_put_global_string(ctx,"CURL_LAST");
	//enum CURLcode - end
	duk_push_int(ctx,CURLE_ALREADY_COMPLETE);
	duk_put_global_string(ctx,"CURLE_ALREADY_COMPLETE");
	//enum curl_proxytype
	duk_push_int(ctx,CURLPROXY_HTTP);
	duk_put_global_string(ctx,"CURLPROXY_HTTP");
	duk_push_int(ctx,CURLPROXY_HTTP_1_0);
	duk_put_global_string(ctx,"CURLPROXY_HTTP_1_0");
	duk_push_int(ctx,CURLPROXY_HTTPS);
	duk_put_global_string(ctx,"CURLPROXY_HTTPS");
	duk_push_int(ctx,CURLPROXY_SOCKS4);
	duk_put_global_string(ctx,"CURLPROXY_SOCKS4");
	duk_push_int(ctx,CURLPROXY_SOCKS5);
	duk_put_global_string(ctx,"CURLPROXY_SOCKS5");
	duk_push_int(ctx,CURLPROXY_SOCKS4A);
	duk_put_global_string(ctx,"CURLPROXY_SOCKS4A");
	duk_push_int(ctx,CURLPROXY_SOCKS5_HOSTNAME);
	duk_put_global_string(ctx,"CURLPROXY_SOCKS5_HOSTNAME");
	//enum curl_proxytype - end
	duk_push_int(ctx,CURLAUTH_NONE);
	duk_put_global_string(ctx,"CURLAUTH_NONE");
	duk_push_int(ctx,CURLAUTH_BASIC);
	duk_put_global_string(ctx,"CURLAUTH_BASIC");
	duk_push_int(ctx,CURLAUTH_DIGEST);
	duk_put_global_string(ctx,"CURLAUTH_DIGEST");
	duk_push_int(ctx,CURLAUTH_NEGOTIATE);
	duk_put_global_string(ctx,"CURLAUTH_NEGOTIATE");
	duk_push_int(ctx,CURLAUTH_GSSNEGOTIATE);
	duk_put_global_string(ctx,"CURLAUTH_GSSNEGOTIATE");
	duk_push_int(ctx,CURLAUTH_GSSAPI);
	duk_put_global_string(ctx,"CURLAUTH_GSSAPI");
	duk_push_int(ctx,CURLAUTH_NTLM);
	duk_put_global_string(ctx,"CURLAUTH_NTLM");
	duk_push_int(ctx,CURLAUTH_DIGEST_IE);
	duk_put_global_string(ctx,"CURLAUTH_DIGEST_IE");
	duk_push_int(ctx,CURLAUTH_NTLM_WB);
	duk_put_global_string(ctx,"CURLAUTH_NTLM_WB");
	duk_push_int(ctx,CURLAUTH_ONLY);
	duk_put_global_string(ctx,"CURLAUTH_ONLY");
	duk_push_int(ctx,CURLAUTH_ANY);
	duk_put_global_string(ctx,"CURLAUTH_ANY");
	duk_push_int(ctx,CURLAUTH_ANYSAFE);
	duk_put_global_string(ctx,"CURLAUTH_ANYSAFE");
	duk_push_int(ctx,CURLSSH_AUTH_ANY);
	duk_put_global_string(ctx,"CURLSSH_AUTH_ANY");
	duk_push_int(ctx,CURLSSH_AUTH_NONE);
	duk_put_global_string(ctx,"CURLSSH_AUTH_NONE");
	duk_push_int(ctx,CURLSSH_AUTH_PUBLICKEY);
	duk_put_global_string(ctx,"CURLSSH_AUTH_PUBLICKEY");
	duk_push_int(ctx,CURLSSH_AUTH_PASSWORD);
	duk_put_global_string(ctx,"CURLSSH_AUTH_PASSWORD");
	duk_push_int(ctx,CURLSSH_AUTH_HOST);
	duk_put_global_string(ctx,"CURLSSH_AUTH_HOST");
	duk_push_int(ctx,CURLSSH_AUTH_KEYBOARD);
	duk_put_global_string(ctx,"CURLSSH_AUTH_KEYBOARD");
	duk_push_int(ctx,CURLSSH_AUTH_AGENT);
	duk_put_global_string(ctx,"CURLSSH_AUTH_AGENT");
	duk_push_int(ctx,CURLSSH_AUTH_GSSAPI);
	duk_put_global_string(ctx,"CURLSSH_AUTH_GSSAPI");
	duk_push_int(ctx,CURLSSH_AUTH_DEFAULT);
	duk_put_global_string(ctx,"CURLSSH_AUTH_DEFAULT");
	duk_push_int(ctx,CURLGSSAPI_DELEGATION_NONE);
	duk_put_global_string(ctx,"CURLGSSAPI_DELEGATION_NONE");
	duk_push_int(ctx,CURLGSSAPI_DELEGATION_POLICY_FLAG);
	duk_put_global_string(ctx,"CURLGSSAPI_DELEGATION_POLICY_FLAG");
	duk_push_int(ctx,CURLGSSAPI_DELEGATION_FLAG);
	duk_put_global_string(ctx,"CURLGSSAPI_DELEGATION_FLAG");
	duk_push_int(ctx,CURL_ERROR_SIZE);
	duk_put_global_string(ctx,"CURL_ERROR_SIZE");
	//enum curl_khtype
	duk_push_int(ctx,CURLKHTYPE_UNKNOWN);
	duk_put_global_string(ctx,"CURLKHTYPE_UNKNOWN");
	duk_push_int(ctx,CURLKHTYPE_RSA1);
	duk_put_global_string(ctx,"CURLKHTYPE_RSA1");
	duk_push_int(ctx,CURLKHTYPE_RSA);
	duk_put_global_string(ctx,"CURLKHTYPE_RSA");
	duk_push_int(ctx,CURLKHTYPE_DSS);
	duk_put_global_string(ctx,"CURLKHTYPE_DSS");
	duk_push_int(ctx,CURLKHTYPE_ECDSA);
	duk_put_global_string(ctx,"CURLKHTYPE_ECDSA");
	duk_push_int(ctx,CURLKHTYPE_ED25519);
	duk_put_global_string(ctx,"CURLKHTYPE_ED25519");
	//enum curl_khtype - end
	//enum curl_khstat
	duk_push_int(ctx,CURLKHSTAT_FINE_ADD_TO_FILE);
	duk_put_global_string(ctx,"CURLKHSTAT_FINE_ADD_TO_FILE");
	duk_push_int(ctx,CURLKHSTAT_FINE);
	duk_put_global_string(ctx,"CURLKHSTAT_FINE");
	duk_push_int(ctx,CURLKHSTAT_REJECT);
	duk_put_global_string(ctx,"CURLKHSTAT_REJECT");
	duk_push_int(ctx,CURLKHSTAT_DEFER);
	duk_put_global_string(ctx,"CURLKHSTAT_DEFER");
	duk_push_int(ctx,CURLKHSTAT_LAST);
	duk_put_global_string(ctx,"CURLKHSTAT_LAST");
	//enum curl_khstat - end
	//enum curl_khmatch
	duk_push_int(ctx,CURLKHMATCH_OK);
	duk_put_global_string(ctx,"CURLKHMATCH_OK");
	duk_push_int(ctx,CURLKHMATCH_MISMATCH);
	duk_put_global_string(ctx,"CURLKHMATCH_MISMATCH");
	duk_push_int(ctx,CURLKHMATCH_MISSING);
	duk_put_global_string(ctx,"CURLKHMATCH_MISSING");
	duk_push_int(ctx,CURLKHMATCH_LAST);
	duk_put_global_string(ctx,"CURLKHMATCH_LAST");
	//enum curl_khmatch - end
	//enum curl_usessl
	duk_push_int(ctx,CURLUSESSL_NONE);
	duk_put_global_string(ctx,"CURLUSESSL_NONE");
	duk_push_int(ctx,CURLUSESSL_TRY);
	duk_put_global_string(ctx,"CURLUSESSL_TRY");
	duk_push_int(ctx,CURLUSESSL_CONTROL);
	duk_put_global_string(ctx,"CURLUSESSL_CONTROL");
	duk_push_int(ctx,CURLUSESSL_ALL);
	duk_put_global_string(ctx,"CURLUSESSL_ALL");
	duk_push_int(ctx,CURLUSESSL_LAST);
	duk_put_global_string(ctx,"CURLUSESSL_LAST");
	//enum curl_usessl - end
	duk_push_int(ctx,CURLSSLOPT_ALLOW_BEAST );
	duk_put_global_string(ctx,"CURLSSLOPT_ALLOW_BEAST");
	duk_push_int(ctx,CURLSSLOPT_NO_REVOKE );
	duk_put_global_string(ctx,"CURLSSLOPT_NO_REVOKE");
/*
typedef enum {
  CURLFTPSSL_CCC_NONE,
  CURLFTPSSL_CCC_PASSIVE,
  CURLFTPSSL_CCC_ACTIVE,
  CURLFTPSSL_CCC_LAST
} curl_ftpccc;
typedef enum {
  CURLFTPAUTH_DEFAULT,
  CURLFTPAUTH_SSL,
  CURLFTPAUTH_TLS,
  CURLFTPAUTH_LAST
} curl_ftpauth;
typedef enum {
  CURLFTP_CREATE_DIR_NONE,
  CURLFTP_CREATE_DIR,
  CURLFTP_CREATE_DIR_RETRY,
  CURLFTP_CREATE_DIR_LAST
} curl_ftpcreatedir;
typedef enum {
  CURLFTPMETHOD_DEFAULT,
  CURLFTPMETHOD_MULTICWD,
  CURLFTPMETHOD_NOCWD,
  CURLFTPMETHOD_SINGLECWD,
  CURLFTPMETHOD_LAST
} curl_ftpmethod;
#define CURLHEADER_UNIFIED  0
#define CURLHEADER_SEPARATE (1<<0)
#define CURLPROTO_HTTP   (1<<0)
#define CURLPROTO_HTTPS  (1<<1)
#define CURLPROTO_FTP    (1<<2)
#define CURLPROTO_FTPS   (1<<3)
#define CURLPROTO_SCP    (1<<4)
#define CURLPROTO_SFTP   (1<<5)
#define CURLPROTO_TELNET (1<<6)
#define CURLPROTO_LDAP   (1<<7)
#define CURLPROTO_LDAPS  (1<<8)
#define CURLPROTO_DICT   (1<<9)
#define CURLPROTO_FILE   (1<<10)
#define CURLPROTO_TFTP   (1<<11)
#define CURLPROTO_IMAP   (1<<12)
#define CURLPROTO_IMAPS  (1<<13)
#define CURLPROTO_POP3   (1<<14)
#define CURLPROTO_POP3S  (1<<15)
#define CURLPROTO_SMTP   (1<<16)
#define CURLPROTO_SMTPS  (1<<17)
#define CURLPROTO_RTSP   (1<<18)
#define CURLPROTO_RTMP   (1<<19)
#define CURLPROTO_RTMPT  (1<<20)
#define CURLPROTO_RTMPE  (1<<21)
#define CURLPROTO_RTMPTE (1<<22)
#define CURLPROTO_RTMPS  (1<<23)
#define CURLPROTO_RTMPTS (1<<24)
#define CURLPROTO_GOPHER (1<<25)
#define CURLPROTO_SMB    (1<<26)
#define CURLPROTO_SMBS   (1<<27)
#define CURLPROTO_ALL    (~0)
#define CURLOPTTYPE_LONG          0
#define CURLOPTTYPE_OBJECTPOINT   10000
#define CURLOPTTYPE_STRINGPOINT   10000
#define CURLOPTTYPE_FUNCTIONPOINT 20000
#define CURLOPTTYPE_OFF_T         30000
enum {
  CURL_HTTP_VERSION_NONE,
  CURL_HTTP_VERSION_1_0,
  CURL_HTTP_VERSION_1_1,
  CURL_HTTP_VERSION_2_0,
  CURL_HTTP_VERSION_2TLS,
  CURL_HTTP_VERSION_2_PRIOR_KNOWLEDGE,
  CURL_HTTP_VERSION_LAST 
};
enum {
    CURL_RTSPREQ_NONE,
    CURL_RTSPREQ_OPTIONS,
    CURL_RTSPREQ_DESCRIBE,
    CURL_RTSPREQ_ANNOUNCE,
    CURL_RTSPREQ_SETUP,
    CURL_RTSPREQ_PLAY,
    CURL_RTSPREQ_PAUSE,
    CURL_RTSPREQ_TEARDOWN,
    CURL_RTSPREQ_GET_PARAMETER,
    CURL_RTSPREQ_SET_PARAMETER,
    CURL_RTSPREQ_RECORD,
    CURL_RTSPREQ_RECEIVE,
    CURL_RTSPREQ_LAST
};
enum CURL_NETRC_OPTION {
  CURL_NETRC_IGNORED,
  CURL_NETRC_OPTIONAL,
  CURL_NETRC_REQUIRED,
  CURL_NETRC_LAST
};

enum {
  CURL_SSLVERSION_DEFAULT,
  CURL_SSLVERSION_TLSv1,
  CURL_SSLVERSION_SSLv2,
  CURL_SSLVERSION_SSLv3,
  CURL_SSLVERSION_TLSv1_0,
  CURL_SSLVERSION_TLSv1_1,
  CURL_SSLVERSION_TLSv1_2,
  CURL_SSLVERSION_TLSv1_3,

  CURL_SSLVERSION_LAST 
};
enum {
  CURL_SSLVERSION_MAX_NONE =     0,
  CURL_SSLVERSION_MAX_DEFAULT =  (CURL_SSLVERSION_TLSv1   << 16),
  CURL_SSLVERSION_MAX_TLSv1_0 =  (CURL_SSLVERSION_TLSv1_0 << 16),
  CURL_SSLVERSION_MAX_TLSv1_1 =  (CURL_SSLVERSION_TLSv1_1 << 16),
  CURL_SSLVERSION_MAX_TLSv1_2 =  (CURL_SSLVERSION_TLSv1_2 << 16),
  CURL_SSLVERSION_MAX_TLSv1_3 =  (CURL_SSLVERSION_TLSv1_3 << 16),
  CURL_SSLVERSION_MAX_LAST =     (CURL_SSLVERSION_LAST    << 16)
};
enum CURL_TLSAUTH {
  CURL_TLSAUTH_NONE,
  CURL_TLSAUTH_SRP,
  CURL_TLSAUTH_LAST
};
#define CURL_REDIR_GET_ALL  0
#define CURL_REDIR_POST_301 1
#define CURL_REDIR_POST_302 2
#define CURL_REDIR_POST_303 4
#define CURL_REDIR_POST_ALL (CURL_REDIR_POST_301|CURL_REDIR_POST_302|CURL_REDIR_POST_303)
typedef enum {
  CURL_TIMECOND_NONE,
  CURL_TIMECOND_IFMODSINCE,
  CURL_TIMECOND_IFUNMODSINCE,
  CURL_TIMECOND_LASTMOD,
  CURL_TIMECOND_LAST
} curl_TimeCond;
#define CURL_ZERO_TERMINATED ((size_t) -1)

typedef enum {
  CFINIT(NOTHING),
  CFINIT(COPYNAME),
  CFINIT(PTRNAME),
  CFINIT(NAMELENGTH),
  CFINIT(COPYCONTENTS),
  CFINIT(PTRCONTENTS),
  CFINIT(CONTENTSLENGTH),
  CFINIT(FILECONTENT),
  CFINIT(ARRAY),
  CFINIT(OBSOLETE),
  CFINIT(FILE),
  CFINIT(BUFFER),
  CFINIT(BUFFERPTR),
  CFINIT(BUFFERLENGTH),
  CFINIT(CONTENTTYPE),
  CFINIT(CONTENTHEADER),
  CFINIT(FILENAME),
  CFINIT(END),
  CFINIT(OBSOLETE2),
  CFINIT(STREAM),
  CFINIT(CONTENTLEN),
  CURLFORM_LASTENTRY
} CURLformoption;

typedef enum {
  CURL_FORMADD_OK,
  CURL_FORMADD_MEMORY,
  CURL_FORMADD_OPTION_TWICE,
  CURL_FORMADD_NULL,
  CURL_FORMADD_UNKNOWN_OPTION,
  CURL_FORMADD_INCOMPLETE,
  CURL_FORMADD_ILLEGAL_ARRAY,
  CURL_FORMADD_DISABLED,
  CURL_FORMADD_LAST
} CURLFORMcode;

typedef enum {
  CURLSSLSET_OK = 0,
  CURLSSLSET_UNKNOWN_BACKEND,
  CURLSSLSET_TOO_LATE,
  CURLSSLSET_NO_BACKENDS
} CURLsslset;

#define CURLINFO_STRING   0x100000
#define CURLINFO_LONG     0x200000
#define CURLINFO_DOUBLE   0x300000
#define CURLINFO_SLIST    0x400000
#define CURLINFO_PTR      0x400000
#define CURLINFO_SOCKET   0x500000
#define CURLINFO_OFF_T    0x600000
#define CURLINFO_MASK     0x0fffff
#define CURLINFO_TYPEMASK 0xf00000
typedef enum {
  CURLINFO_NONE,
  CURLINFO_EFFECTIVE_URL    = CURLINFO_STRING + 1,
  CURLINFO_RESPONSE_CODE    = CURLINFO_LONG   + 2,
  CURLINFO_TOTAL_TIME       = CURLINFO_DOUBLE + 3,
  CURLINFO_NAMELOOKUP_TIME  = CURLINFO_DOUBLE + 4,
  CURLINFO_CONNECT_TIME     = CURLINFO_DOUBLE + 5,
  CURLINFO_PRETRANSFER_TIME = CURLINFO_DOUBLE + 6,
  CURLINFO_SIZE_UPLOAD      = CURLINFO_DOUBLE + 7,
  CURLINFO_SIZE_UPLOAD_T    = CURLINFO_OFF_T  + 7,
  CURLINFO_SIZE_DOWNLOAD    = CURLINFO_DOUBLE + 8,
  CURLINFO_SIZE_DOWNLOAD_T  = CURLINFO_OFF_T  + 8,
  CURLINFO_SPEED_DOWNLOAD   = CURLINFO_DOUBLE + 9,
  CURLINFO_SPEED_DOWNLOAD_T = CURLINFO_OFF_T  + 9,
  CURLINFO_SPEED_UPLOAD     = CURLINFO_DOUBLE + 10,
  CURLINFO_SPEED_UPLOAD_T   = CURLINFO_OFF_T  + 10,
  CURLINFO_HEADER_SIZE      = CURLINFO_LONG   + 11,
  CURLINFO_REQUEST_SIZE     = CURLINFO_LONG   + 12,
  CURLINFO_SSL_VERIFYRESULT = CURLINFO_LONG   + 13,
  CURLINFO_FILETIME         = CURLINFO_LONG   + 14,
  CURLINFO_CONTENT_LENGTH_DOWNLOAD   = CURLINFO_DOUBLE + 15,
  CURLINFO_CONTENT_LENGTH_DOWNLOAD_T = CURLINFO_OFF_T  + 15,
  CURLINFO_CONTENT_LENGTH_UPLOAD     = CURLINFO_DOUBLE + 16,
  CURLINFO_CONTENT_LENGTH_UPLOAD_T   = CURLINFO_OFF_T  + 16,
  CURLINFO_STARTTRANSFER_TIME = CURLINFO_DOUBLE + 17,
  CURLINFO_CONTENT_TYPE     = CURLINFO_STRING + 18,
  CURLINFO_REDIRECT_TIME    = CURLINFO_DOUBLE + 19,
  CURLINFO_REDIRECT_COUNT   = CURLINFO_LONG   + 20,
  CURLINFO_PRIVATE          = CURLINFO_STRING + 21,
  CURLINFO_HTTP_CONNECTCODE = CURLINFO_LONG   + 22,
  CURLINFO_HTTPAUTH_AVAIL   = CURLINFO_LONG   + 23,
  CURLINFO_PROXYAUTH_AVAIL  = CURLINFO_LONG   + 24,
  CURLINFO_OS_ERRNO         = CURLINFO_LONG   + 25,
  CURLINFO_NUM_CONNECTS     = CURLINFO_LONG   + 26,
  CURLINFO_SSL_ENGINES      = CURLINFO_SLIST  + 27,
  CURLINFO_COOKIELIST       = CURLINFO_SLIST  + 28,
  CURLINFO_LASTSOCKET       = CURLINFO_LONG   + 29,
  CURLINFO_FTP_ENTRY_PATH   = CURLINFO_STRING + 30,
  CURLINFO_REDIRECT_URL     = CURLINFO_STRING + 31,
  CURLINFO_PRIMARY_IP       = CURLINFO_STRING + 32,
  CURLINFO_APPCONNECT_TIME  = CURLINFO_DOUBLE + 33,
  CURLINFO_CERTINFO         = CURLINFO_PTR    + 34,
  CURLINFO_CONDITION_UNMET  = CURLINFO_LONG   + 35,
  CURLINFO_RTSP_SESSION_ID  = CURLINFO_STRING + 36,
  CURLINFO_RTSP_CLIENT_CSEQ = CURLINFO_LONG   + 37,
  CURLINFO_RTSP_SERVER_CSEQ = CURLINFO_LONG   + 38,
  CURLINFO_RTSP_CSEQ_RECV   = CURLINFO_LONG   + 39,
  CURLINFO_PRIMARY_PORT     = CURLINFO_LONG   + 40,
  CURLINFO_LOCAL_IP         = CURLINFO_STRING + 41,
  CURLINFO_LOCAL_PORT       = CURLINFO_LONG   + 42,
  CURLINFO_TLS_SESSION      = CURLINFO_PTR    + 43,
  CURLINFO_ACTIVESOCKET     = CURLINFO_SOCKET + 44,
  CURLINFO_TLS_SSL_PTR      = CURLINFO_PTR    + 45,
  CURLINFO_HTTP_VERSION     = CURLINFO_LONG   + 46,
  CURLINFO_PROXY_SSL_VERIFYRESULT = CURLINFO_LONG + 47,
  CURLINFO_PROTOCOL         = CURLINFO_LONG   + 48,
  CURLINFO_SCHEME           = CURLINFO_STRING + 49,
  CURLINFO_LASTONE          = 49
} CURLINFO;
typedef enum {
  CURLCLOSEPOLICY_NONE,

  CURLCLOSEPOLICY_OLDEST,
  CURLCLOSEPOLICY_LEAST_RECENTLY_USED,
  CURLCLOSEPOLICY_LEAST_TRAFFIC,
  CURLCLOSEPOLICY_SLOWEST,
  CURLCLOSEPOLICY_CALLBACK,

  CURLCLOSEPOLICY_LAST
} curl_closepolicy;
*/
	duk_push_int(ctx,CURL_GLOBAL_SSL);
	duk_put_global_string(ctx,"CURL_GLOBAL_SSL");
	duk_push_int(ctx,CURL_GLOBAL_WIN32);
	duk_put_global_string(ctx,"CURL_GLOBAL_WIN32");
	duk_push_int(ctx,CURL_GLOBAL_ALL);
	duk_put_global_string(ctx,"CURL_GLOBAL_ALL");
	duk_push_int(ctx,CURL_GLOBAL_NOTHING);
	duk_put_global_string(ctx,"CURL_GLOBAL_NOTHING");
	duk_push_int(ctx,CURL_GLOBAL_DEFAULT);
	duk_put_global_string(ctx,"CURL_GLOBAL_DEFAULT");
	duk_push_int(ctx,CURL_GLOBAL_ACK_EINTR);
	duk_put_global_string(ctx,"CURL_GLOBAL_ACK_EINTR");
	//CONSTANTS END
	//FUNCTIONS
	duk_push_c_function(ctx,native_curl_global_init,1);
	duk_put_global_string(ctx,"curl_global_init");
	//FUNCTIONS - END
	//----------------------------------------
	// usr/include/x86_64-linux-gnu/curl/typecheck-gcc.h
	//----------------------------------------
	duk_push_int(ctx,CURLINFO_CERTINFO);
	duk_put_global_string(ctx,"CURLINFO_CERTINFO");
	duk_push_int(ctx,CURLINFO_COOKIELIST);
	duk_put_global_string(ctx,"CURLINFO_COOKIELIST");
	duk_push_int(ctx,CURLINFO_DOUBLE);
	duk_put_global_string(ctx,"CURLINFO_DOUBLE");
	duk_push_int(ctx,CURLINFO_LONG);
	duk_put_global_string(ctx,"CURLINFO_LONG");
	duk_push_int(ctx,CURLINFO_OFF_T);
	duk_put_global_string(ctx,"CURLINFO_OFF_T");
	duk_push_int(ctx,CURLINFO_SLIST);
	duk_put_global_string(ctx,"CURLINFO_SLIST");
	duk_push_int(ctx,CURLINFO_SOCKET);
	duk_put_global_string(ctx,"CURLINFO_SOCKET");
	duk_push_int(ctx,CURLINFO_SSL_ENGINES);
	duk_put_global_string(ctx,"CURLINFO_SSL_ENGINES");
	duk_push_int(ctx,CURLINFO_STRING);
	duk_put_global_string(ctx,"CURLINFO_STRING");
	duk_push_int(ctx,CURLINFO_TLS_SESSION);
	duk_put_global_string(ctx,"CURLINFO_TLS_SESSION");
	duk_push_int(ctx,CURLINFO_TLS_SSL_PTR);
	duk_put_global_string(ctx,"CURLINFO_TLS_SSL_PTR");
	duk_push_int(ctx,CURLOPTTYPE_OBJECTPOINT);
	duk_put_global_string(ctx,"CURLOPTTYPE_OBJECTPOINT");
	duk_push_int(ctx,CURLOPTTYPE_OFF_T);
	duk_put_global_string(ctx,"CURLOPTTYPE_OFF_T");
	duk_push_int(ctx,CURLOPT_ABSTRACT_UNIX_SOCKET);
	duk_put_global_string(ctx,"CURLOPT_ABSTRACT_UNIX_SOCKET");
	duk_push_int(ctx,CURLOPT_ACCEPT_ENCODING);
	duk_put_global_string(ctx,"CURLOPT_ACCEPT_ENCODING");
	duk_push_int(ctx,CURLOPT_CAINFO);
	duk_put_global_string(ctx,"CURLOPT_CAINFO");
	duk_push_int(ctx,CURLOPT_CAPATH);
	duk_put_global_string(ctx,"CURLOPT_CAPATH");
	duk_push_int(ctx,CURLOPT_CHUNK_DATA);
	duk_put_global_string(ctx,"CURLOPT_CHUNK_DATA");
	duk_push_int(ctx,CURLOPT_CLOSESOCKETDATA);
	duk_put_global_string(ctx,"CURLOPT_CLOSESOCKETDATA");
	duk_push_int(ctx,CURLOPT_CONV_FROM_NETWORK_FUNCTION);
	duk_put_global_string(ctx,"CURLOPT_CONV_FROM_NETWORK_FUNCTION");
	duk_push_int(ctx,CURLOPT_CONV_FROM_UTF8_FUNCTION);
	duk_put_global_string(ctx,"CURLOPT_CONV_FROM_UTF8_FUNCTION");
	duk_push_int(ctx,CURLOPT_CONV_TO_NETWORK_FUNCTION);
	duk_put_global_string(ctx,"CURLOPT_CONV_TO_NETWORK_FUNCTION");
	duk_push_int(ctx,CURLOPT_COOKIE);
	duk_put_global_string(ctx,"CURLOPT_COOKIE");
	duk_push_int(ctx,CURLOPT_COOKIEFILE);
	duk_put_global_string(ctx,"CURLOPT_COOKIEFILE");
	duk_push_int(ctx,CURLOPT_COOKIEJAR);
	duk_put_global_string(ctx,"CURLOPT_COOKIEJAR");
	duk_push_int(ctx,CURLOPT_COOKIELIST);
	duk_put_global_string(ctx,"CURLOPT_COOKIELIST");
	duk_push_int(ctx,CURLOPT_COPYPOSTFIELDS);
	duk_put_global_string(ctx,"CURLOPT_COPYPOSTFIELDS");
	duk_push_int(ctx,CURLOPT_CRLFILE);
	duk_put_global_string(ctx,"CURLOPT_CRLFILE");
	duk_push_int(ctx,CURLOPT_CUSTOMREQUEST);
	duk_put_global_string(ctx,"CURLOPT_CUSTOMREQUEST");
	duk_push_int(ctx,CURLOPT_DEBUGDATA);
	duk_put_global_string(ctx,"CURLOPT_DEBUGDATA");
	duk_push_int(ctx,CURLOPT_DEBUGFUNCTION);
	duk_put_global_string(ctx,"CURLOPT_DEBUGFUNCTION");
	duk_push_int(ctx,CURLOPT_DEFAULT_PROTOCOL);
	duk_put_global_string(ctx,"CURLOPT_DEFAULT_PROTOCOL");
	duk_push_int(ctx,CURLOPT_DNS_INTERFACE);
	duk_put_global_string(ctx,"CURLOPT_DNS_INTERFACE");
	duk_push_int(ctx,CURLOPT_DNS_LOCAL_IP4);
	duk_put_global_string(ctx,"CURLOPT_DNS_LOCAL_IP4");
	duk_push_int(ctx,CURLOPT_DNS_LOCAL_IP6);
	duk_put_global_string(ctx,"CURLOPT_DNS_LOCAL_IP6");
	duk_push_int(ctx,CURLOPT_DNS_SERVERS);
	duk_put_global_string(ctx,"CURLOPT_DNS_SERVERS");
	duk_push_int(ctx,CURLOPT_EGDSOCKET);
	duk_put_global_string(ctx,"CURLOPT_EGDSOCKET");
	duk_push_int(ctx,CURLOPT_ERRORBUFFER);
	duk_put_global_string(ctx,"CURLOPT_ERRORBUFFER");

	duk_push_int(ctx,CURLOPT_FOLLOWLOCATION);
	duk_put_global_string(ctx,"CURLOPT_FOLLOWLOCATION");

	duk_push_int(ctx,CURLOPT_FNMATCH_DATA);
	duk_put_global_string(ctx,"CURLOPT_FNMATCH_DATA");
	duk_push_int(ctx,CURLOPT_FTPPORT);
	duk_put_global_string(ctx,"CURLOPT_FTPPORT");
	duk_push_int(ctx,CURLOPT_FTP_ACCOUNT);
	duk_put_global_string(ctx,"CURLOPT_FTP_ACCOUNT");
	duk_push_int(ctx,CURLOPT_FTP_ALTERNATIVE_TO_USER);
	duk_put_global_string(ctx,"CURLOPT_FTP_ALTERNATIVE_TO_USER");
	duk_push_int(ctx,CURLOPT_HEADERDATA);
	duk_put_global_string(ctx,"CURLOPT_HEADERDATA");
	duk_push_int(ctx,CURLOPT_HEADERFUNCTION);
	duk_put_global_string(ctx,"CURLOPT_HEADERFUNCTION");
	duk_push_int(ctx,CURLOPT_HTTP200ALIASES);
	duk_put_global_string(ctx,"CURLOPT_HTTP200ALIASES");
	duk_push_int(ctx,CURLOPT_HTTPHEADER);
	duk_put_global_string(ctx,"CURLOPT_HTTPHEADER");
	duk_push_int(ctx,CURLOPT_HTTPPOST);
	duk_put_global_string(ctx,"CURLOPT_HTTPPOST");
	duk_push_int(ctx,CURLOPT_INTERFACE);
	duk_put_global_string(ctx,"CURLOPT_INTERFACE");
	duk_push_int(ctx,CURLOPT_INTERLEAVEDATA);
	duk_put_global_string(ctx,"CURLOPT_INTERLEAVEDATA");
	duk_push_int(ctx,CURLOPT_IOCTLDATA);
	duk_put_global_string(ctx,"CURLOPT_IOCTLDATA");
	duk_push_int(ctx,CURLOPT_IOCTLFUNCTION);
	duk_put_global_string(ctx,"CURLOPT_IOCTLFUNCTION");
	duk_push_int(ctx,CURLOPT_ISSUERCERT);
	duk_put_global_string(ctx,"CURLOPT_ISSUERCERT");
	duk_push_int(ctx,CURLOPT_KEYPASSWD);
	duk_put_global_string(ctx,"CURLOPT_KEYPASSWD");
	duk_push_int(ctx,CURLOPT_KRBLEVEL);
	duk_put_global_string(ctx,"CURLOPT_KRBLEVEL");
	duk_push_int(ctx,CURLOPT_LOGIN_OPTIONS);
	duk_put_global_string(ctx,"CURLOPT_LOGIN_OPTIONS");
	duk_push_int(ctx,CURLOPT_MAIL_AUTH);
	duk_put_global_string(ctx,"CURLOPT_MAIL_AUTH");
	duk_push_int(ctx,CURLOPT_MAIL_FROM);
	duk_put_global_string(ctx,"CURLOPT_MAIL_FROM");
	duk_push_int(ctx,CURLOPT_MAIL_RCPT);
	duk_put_global_string(ctx,"CURLOPT_MAIL_RCPT");
	duk_push_int(ctx,CURLOPT_MIMEPOST);
	duk_put_global_string(ctx,"CURLOPT_MIMEPOST");
	duk_push_int(ctx,CURLOPT_NETRC_FILE);
	duk_put_global_string(ctx,"CURLOPT_NETRC_FILE");
	duk_push_int(ctx,CURLOPT_NOPROXY);
	duk_put_global_string(ctx,"CURLOPT_NOPROXY");
	duk_push_int(ctx,CURLOPT_OPENSOCKETDATA);
	duk_put_global_string(ctx,"CURLOPT_OPENSOCKETDATA");
	duk_push_int(ctx,CURLOPT_OPENSOCKETFUNCTION);
	duk_put_global_string(ctx,"CURLOPT_OPENSOCKETFUNCTION");
	duk_push_int(ctx,CURLOPT_PASSWORD);
	duk_put_global_string(ctx,"CURLOPT_PASSWORD");
	duk_push_int(ctx,CURLOPT_PINNEDPUBLICKEY);
	duk_put_global_string(ctx,"CURLOPT_PINNEDPUBLICKEY");
	duk_push_int(ctx,CURLOPT_POSTFIELDS);
	duk_put_global_string(ctx,"CURLOPT_POSTFIELDS");
	duk_push_int(ctx,CURLOPT_POSTQUOTE);
	duk_put_global_string(ctx,"CURLOPT_POSTQUOTE");
	duk_push_int(ctx,CURLOPT_PREQUOTE);
	duk_put_global_string(ctx,"CURLOPT_PREQUOTE");
	duk_push_int(ctx,CURLOPT_PRE_PROXY);
	duk_put_global_string(ctx,"CURLOPT_PRE_PROXY");
	duk_push_int(ctx,CURLOPT_PRIVATE);
	duk_put_global_string(ctx,"CURLOPT_PRIVATE");
	duk_push_int(ctx,CURLOPT_PROGRESSDATA);
	duk_put_global_string(ctx,"CURLOPT_PROGRESSDATA");
	duk_push_int(ctx,CURLOPT_PROGRESSFUNCTION);
	duk_put_global_string(ctx,"CURLOPT_PROGRESSFUNCTION");
	duk_push_int(ctx,CURLOPT_PROXY);
	duk_put_global_string(ctx,"CURLOPT_PROXY");
	duk_push_int(ctx,CURLOPT_PROXYHEADER);
	duk_put_global_string(ctx,"CURLOPT_PROXYHEADER");
	duk_push_int(ctx,CURLOPT_PROXYPASSWORD);
	duk_put_global_string(ctx,"CURLOPT_PROXYPASSWORD");
	duk_push_int(ctx,CURLOPT_PROXYUSERNAME);
	duk_put_global_string(ctx,"CURLOPT_PROXYUSERNAME");
	duk_push_int(ctx,CURLOPT_PROXYUSERPWD);
	duk_put_global_string(ctx,"CURLOPT_PROXYUSERPWD");
	duk_push_int(ctx,CURLOPT_PROXY_CAINFO);
	duk_put_global_string(ctx,"CURLOPT_PROXY_CAINFO");
	duk_push_int(ctx,CURLOPT_PROXY_CAPATH);
	duk_put_global_string(ctx,"CURLOPT_PROXY_CAPATH");
	duk_push_int(ctx,CURLOPT_PROXY_CRLFILE);
	duk_put_global_string(ctx,"CURLOPT_PROXY_CRLFILE");
	duk_push_int(ctx,CURLOPT_PROXY_KEYPASSWD);
	duk_put_global_string(ctx,"CURLOPT_PROXY_KEYPASSWD");
	duk_push_int(ctx,CURLOPT_PROXY_PINNEDPUBLICKEY);
	duk_put_global_string(ctx,"CURLOPT_PROXY_PINNEDPUBLICKEY");
	duk_push_int(ctx,CURLOPT_PROXY_SERVICE_NAME);
	duk_put_global_string(ctx,"CURLOPT_PROXY_SERVICE_NAME");
	duk_push_int(ctx,CURLOPT_PROXY_SSLCERT);
	duk_put_global_string(ctx,"CURLOPT_PROXY_SSLCERT");
	duk_push_int(ctx,CURLOPT_PROXY_SSLCERTTYPE);
	duk_put_global_string(ctx,"CURLOPT_PROXY_SSLCERTTYPE");
	duk_push_int(ctx,CURLOPT_PROXY_SSLKEY);
	duk_put_global_string(ctx,"CURLOPT_PROXY_SSLKEY");
	duk_push_int(ctx,CURLOPT_PROXY_SSLKEYTYPE);
	duk_put_global_string(ctx,"CURLOPT_PROXY_SSLKEYTYPE");
	duk_push_int(ctx,CURLOPT_PROXY_SSL_CIPHER_LIST);
	duk_put_global_string(ctx,"CURLOPT_PROXY_SSL_CIPHER_LIST");
	duk_push_int(ctx,CURLOPT_PROXY_TLSAUTH_PASSWORD);
	duk_put_global_string(ctx,"CURLOPT_PROXY_TLSAUTH_PASSWORD");
	duk_push_int(ctx,CURLOPT_PROXY_TLSAUTH_TYPE);
	duk_put_global_string(ctx,"CURLOPT_PROXY_TLSAUTH_TYPE");
	duk_push_int(ctx,CURLOPT_PROXY_TLSAUTH_USERNAME);
	duk_put_global_string(ctx,"CURLOPT_PROXY_TLSAUTH_USERNAME");
	duk_push_int(ctx,CURLOPT_QUOTE);
	duk_put_global_string(ctx,"CURLOPT_QUOTE");
	duk_push_int(ctx,CURLOPT_RANDOM_FILE);
	duk_put_global_string(ctx,"CURLOPT_RANDOM_FILE");
	duk_push_int(ctx,CURLOPT_RANGE);
	duk_put_global_string(ctx,"CURLOPT_RANGE");
	duk_push_int(ctx,CURLOPT_READDATA);
	duk_put_global_string(ctx,"CURLOPT_READDATA");
	duk_push_int(ctx,CURLOPT_READFUNCTION);
	duk_put_global_string(ctx,"CURLOPT_READFUNCTION");
	duk_push_int(ctx,CURLOPT_REFERER);
	duk_put_global_string(ctx,"CURLOPT_REFERER");
	duk_push_int(ctx,CURLOPT_RESOLVE);
	duk_put_global_string(ctx,"CURLOPT_RESOLVE");
	duk_push_int(ctx,CURLOPT_RTSP_SESSION_ID);
	duk_put_global_string(ctx,"CURLOPT_RTSP_SESSION_ID");
	duk_push_int(ctx,CURLOPT_RTSP_STREAM_URI);
	duk_put_global_string(ctx,"CURLOPT_RTSP_STREAM_URI");
	duk_push_int(ctx,CURLOPT_RTSP_TRANSPORT);
	duk_put_global_string(ctx,"CURLOPT_RTSP_TRANSPORT");
	duk_push_int(ctx,CURLOPT_SEEKDATA);
	duk_put_global_string(ctx,"CURLOPT_SEEKDATA");
	duk_push_int(ctx,CURLOPT_SEEKFUNCTION);
	duk_put_global_string(ctx,"CURLOPT_SEEKFUNCTION");
	duk_push_int(ctx,CURLOPT_SERVICE_NAME);
	duk_put_global_string(ctx,"CURLOPT_SERVICE_NAME");
	duk_push_int(ctx,CURLOPT_SHARE);
	duk_put_global_string(ctx,"CURLOPT_SHARE");
	duk_push_int(ctx,CURLOPT_SOCKOPTDATA);
	duk_put_global_string(ctx,"CURLOPT_SOCKOPTDATA");
	duk_push_int(ctx,CURLOPT_SOCKOPTFUNCTION);
	duk_put_global_string(ctx,"CURLOPT_SOCKOPTFUNCTION");
	duk_push_int(ctx,CURLOPT_SOCKS5_GSSAPI_SERVICE);
	duk_put_global_string(ctx,"CURLOPT_SOCKS5_GSSAPI_SERVICE");
	duk_push_int(ctx,CURLOPT_SSH_HOST_PUBLIC_KEY_MD5);
	duk_put_global_string(ctx,"CURLOPT_SSH_HOST_PUBLIC_KEY_MD5");
	duk_push_int(ctx,CURLOPT_SSH_KEYDATA);
	duk_put_global_string(ctx,"CURLOPT_SSH_KEYDATA");
	duk_push_int(ctx,CURLOPT_SSH_KNOWNHOSTS);
	duk_put_global_string(ctx,"CURLOPT_SSH_KNOWNHOSTS");
	duk_push_int(ctx,CURLOPT_SSH_PRIVATE_KEYFILE);
	duk_put_global_string(ctx,"CURLOPT_SSH_PRIVATE_KEYFILE");
	duk_push_int(ctx,CURLOPT_SSH_PUBLIC_KEYFILE);
	duk_put_global_string(ctx,"CURLOPT_SSH_PUBLIC_KEYFILE");
	duk_push_int(ctx,CURLOPT_SSLCERT);
	duk_put_global_string(ctx,"CURLOPT_SSLCERT");
	duk_push_int(ctx,CURLOPT_SSLCERTTYPE);
	duk_put_global_string(ctx,"CURLOPT_SSLCERTTYPE");
	duk_push_int(ctx,CURLOPT_SSLENGINE);
	duk_put_global_string(ctx,"CURLOPT_SSLENGINE");
	duk_push_int(ctx,CURLOPT_SSLKEY);
	duk_put_global_string(ctx,"CURLOPT_SSLKEY");
	duk_push_int(ctx,CURLOPT_SSLKEYTYPE);
	duk_put_global_string(ctx,"CURLOPT_SSLKEYTYPE");
	duk_push_int(ctx,CURLOPT_SSL_CIPHER_LIST);
	duk_put_global_string(ctx,"CURLOPT_SSL_CIPHER_LIST");
	duk_push_int(ctx,CURLOPT_SSL_CTX_DATA);
	duk_put_global_string(ctx,"CURLOPT_SSL_CTX_DATA");
	duk_push_int(ctx,CURLOPT_SSL_CTX_FUNCTION);
	duk_put_global_string(ctx,"CURLOPT_SSL_CTX_FUNCTION");
	duk_push_int(ctx,CURLOPT_TELNETOPTIONS);
	duk_put_global_string(ctx,"CURLOPT_TELNETOPTIONS");
	duk_push_int(ctx,CURLOPT_TLSAUTH_PASSWORD);
	duk_put_global_string(ctx,"CURLOPT_TLSAUTH_PASSWORD");
	duk_push_int(ctx,CURLOPT_TLSAUTH_TYPE);
	duk_put_global_string(ctx,"CURLOPT_TLSAUTH_TYPE");
	duk_push_int(ctx,CURLOPT_TLSAUTH_USERNAME);
	duk_put_global_string(ctx,"CURLOPT_TLSAUTH_USERNAME");
	duk_push_int(ctx,CURLOPT_UNIX_SOCKET_PATH);
	duk_put_global_string(ctx,"CURLOPT_UNIX_SOCKET_PATH");
	duk_push_int(ctx,CURLOPT_URL);
	duk_put_global_string(ctx,"CURLOPT_URL");
	duk_push_int(ctx,CURLOPT_USERAGENT);
	duk_put_global_string(ctx,"CURLOPT_USERAGENT");
	duk_push_int(ctx,CURLOPT_USERNAME);
	duk_put_global_string(ctx,"CURLOPT_USERNAME");
	duk_push_int(ctx,CURLOPT_USERPWD);
	duk_put_global_string(ctx,"CURLOPT_USERPWD");
	duk_push_int(ctx,CURLOPT_WRITEDATA);
	duk_put_global_string(ctx,"CURLOPT_WRITEDATA");
	duk_push_int(ctx,CURLOPT_WRITEFUNCTION);
	duk_put_global_string(ctx,"CURLOPT_WRITEFUNCTION");
	duk_push_int(ctx,CURLOPT_XOAUTH2_BEARER);
	duk_put_global_string(ctx,"CURLOPT_XOAUTH2_BEARER");

	duk_push_int(ctx,CURLOPT_CONNECT_ONLY);
	duk_put_global_string(ctx,"CURLOPT_CONNECT_ONLY");
	//----------------------------------------
	//easy.h
	//----------------------------------------
	//FUNCTIONS
	duk_push_c_function(ctx,native_curl_easy_init,0);
	duk_put_global_string(ctx,"curl_easy_init");
	duk_push_c_function(ctx,native_curl_easy_reset,1);
	duk_put_global_string(ctx,"curl_easy_reset");
	duk_push_c_function(ctx,native_curl_easy_cleanup,1);
	duk_put_global_string(ctx,"curl_easy_cleanup");
	duk_push_c_function(ctx,native_curl_easy_setopt,3);//no varargs for now
	duk_put_global_string(ctx,"curl_easy_setopt");
	duk_push_c_function(ctx,native_curl_easy_perform,1);
	duk_put_global_string(ctx,"curl_easy_perform");
	duk_push_c_function(ctx,native_curl_easy_getinfo,0);
	duk_put_global_string(ctx,"curl_easy_getinfo");
	duk_push_c_function(ctx,native_curl_easy_duphandle,0);
	duk_put_global_string(ctx,"curl_easy_duphandle");
	duk_push_c_function(ctx,native_curl_easy_recv,4);
	duk_put_global_string(ctx,"curl_easy_recv");
	duk_push_c_function(ctx,native_curl_easy_send,0);
	duk_put_global_string(ctx,"curl_easy_send");
	//FUNCTIONS - END
	//----------------------------------------
	//test
	//----------------------------------------
	duk_push_c_function(ctx,native_curl_test,0);
	duk_put_global_string(ctx,"curl_test");
}
/*
//--------------------------------------------------------------------------------
//curl
//--------------------------------------------------------------------------------


struct curl_httppost {
  struct curl_httppost *next;
  char *name;
  long namelength;
  char *contents;
  long contentslength;
  char *buffer;
  long bufferlength;
  char *contenttype;
  struct curl_slist *contentheader;
  struct curl_httppost *more;
  long flags;

struct curl_fileinfo {
  char *filename;
  curlfiletype filetype;
  time_t time;
  unsigned int perm;
  int uid;
  int gid;
  curl_off_t size;
  long int hardlinks;
  struct {
    char *time;
    char *perm;
    char *user;
    char *group;
    char *target;
  } strings;
  unsigned int flags;
  char *b_data;
  size_t b_size;
  size_t b_used;
};
typedef long (*curl_chunk_bgn_callback)(const void *transfer_info,void *ptr,int remains);
typedef long (*curl_chunk_end_callback)(void *ptr);
typedef int (*curl_fnmatch_callback)(void *ptr,const char *pattern,const char *string);
typedef int (*curl_seek_callback)(void *instream,curl_off_t offset,int origin);
typedef size_t (*curl_read_callback)(char *buffer,size_t size,size_t nitems,void *instream);
typedef int (*curl_sockopt_callback)(void *clientp,curl_socket_t curlfd,curlsocktype purpose);
struct curl_sockaddr {
  int family;
  int socktype;
  int protocol;
  unsigned int addrlen;
  struct sockaddr addr;
};
typedef curl_socket_t
(*curl_opensocket_callback)(void *clientp,curlsocktype purpose,struct curl_sockaddr *address);
typedef int (*curl_closesocket_callback)(void *clientp, curl_socket_t item);
typedef curlioerr (*curl_ioctl_callback)(CURL *handle,int cmd,void *clientp);
typedef void *(*curl_malloc_callback)(size_t size);
typedef void (*curl_free_callback)(void *ptr);
typedef void *(*curl_realloc_callback)(void *ptr, size_t size);
typedef char *(*curl_strdup_callback)(const char *str);
typedef void *(*curl_calloc_callback)(size_t nmemb, size_t size);
typedef int (*curl_debug_callback)(CURL *handle,curl_infotype type,char *data,size_t size,void *userptr);
typedef CURLcode (*curl_conv_callback)(char *buffer, size_t length);
typedef CURLcode (*curl_ssl_ctx_callback)(CURL *curl,void *ssl_ctx,void *userptr);
struct curl_khkey {
  const char *key;
  size_t len;
  enum curl_khtype keytype;
};
typedef int(*curl_sshkeycallback) (CURL *easy,const struct curl_khkey *knownkey,const struct curl_khkey *foundkey,enum curl_khmatch,void *clientp);
CURL_EXTERN int curl_strequal(const char *s1, const char *s2);
CURL_EXTERN int curl_strnequal(const char *s1, const char *s2, size_t n);
typedef struct curl_mime_s      curl_mime;
typedef struct curl_mimepart_s  curl_mimepart;
CURL_EXTERN curl_mime *curl_mime_init(CURL *easy);
CURL_EXTERN void curl_mime_free(curl_mime *mime);
CURL_EXTERN curl_mimepart *curl_mime_addpart(curl_mime *mime);
CURL_EXTERN CURLcode curl_mime_name(curl_mimepart *part, const char *name);
CURL_EXTERN CURLcode curl_mime_filename(curl_mimepart *part,
                                        const char *filename);
CURL_EXTERN CURLcode curl_mime_type(curl_mimepart *part, const char *mimetype);
CURL_EXTERN CURLcode curl_mime_encoder(curl_mimepart *part,
                                       const char *encoding);
CURL_EXTERN CURLcode curl_mime_data(curl_mimepart *part,
                                    const char *data, size_t datasize);
CURL_EXTERN CURLcode curl_mime_filedata(curl_mimepart *part,
                                        const char *filename);
CURL_EXTERN CURLcode curl_mime_data_cb(curl_mimepart *part,
                                       curl_off_t datasize,
                                       curl_read_callback readfunc,
                                       curl_seek_callback seekfunc,
                                       curl_free_callback freefunc,
                                       void *arg);
CURL_EXTERN CURLcode curl_mime_subparts(curl_mimepart *part,
                                        curl_mime *subparts);
CURL_EXTERN CURLcode curl_mime_headers(curl_mimepart *part,
                                       struct curl_slist *headers,
                                       int take_ownership);
struct curl_forms {
  CURLformoption option;
  const char     *value;
};
CURL_EXTERN CURLFORMcode curl_formadd(struct curl_httppost **httppost,
                                      struct curl_httppost **last_post,
                                      ...);
typedef size_t (*curl_formget_callback)(void *arg, const char *buf,
                                        size_t len);
CURL_EXTERN int curl_formget(struct curl_httppost *form, void *arg,
                             curl_formget_callback append);
CURL_EXTERN void curl_formfree(struct curl_httppost *form);
CURL_EXTERN char *curl_getenv(const char *variable);
CURL_EXTERN char *curl_version(void);
CURL_EXTERN char *curl_easy_escape(CURL *handle,
                                   const char *string,
                                   int length);
CURL_EXTERN char *curl_escape(const char *string,
                              int length);
CURL_EXTERN char *curl_easy_unescape(CURL *handle,
                                     const char *string,
                                     int length,
                                     int *outlength);
CURL_EXTERN char *curl_unescape(const char *string,
                                int length);
CURL_EXTERN void curl_free(void *p);
CURL_EXTERN CURLcode curl_global_init_mem(long flags,
                                          curl_malloc_callback m,
                                          curl_free_callback f,
                                          curl_realloc_callback r,
                                          curl_strdup_callback s,
                                          curl_calloc_callback c);
CURL_EXTERN void curl_global_cleanup(void);
struct curl_slist {
  char *data;
  struct curl_slist *next;
};
typedef struct {
  curl_sslbackend id;
  const char *name;
} curl_ssl_backend;
CURL_EXTERN CURLsslset curl_global_sslset(curl_sslbackend id, const char *name,
                                          const curl_ssl_backend ***avail);
CURL_EXTERN struct curl_slist *curl_slist_append(struct curl_slist *,
                                                 const char *);
CURL_EXTERN void curl_slist_free_all(struct curl_slist *);
CURL_EXTERN time_t curl_getdate(const char *p, const time_t *unused);
struct curl_certinfo {
  int num_of_certs;
  struct curl_slist **certinfo;
};
struct curl_tlssessioninfo {
  curl_sslbackend backend;
  void *internals;
};
typedef enum {
  CURL_LOCK_DATA_NONE = 0,
  CURL_LOCK_DATA_SHARE,
  CURL_LOCK_DATA_COOKIE,
  CURL_LOCK_DATA_DNS,
  CURL_LOCK_DATA_SSL_SESSION,
  CURL_LOCK_DATA_CONNECT,
  CURL_LOCK_DATA_LAST
} curl_lock_data;
typedef enum {
  CURL_LOCK_ACCESS_NONE = 0,
  CURL_LOCK_ACCESS_SHARED = 1,
  CURL_LOCK_ACCESS_SINGLE = 2,
  CURL_LOCK_ACCESS_LAST
} curl_lock_access;
typedef void (*curl_lock_function)(CURL *handle,
                                   curl_lock_data data,
                                   curl_lock_access locktype,
                                   void *userptr);
typedef void (*curl_unlock_function)(CURL *handle,curl_lock_data data,void *userptr);
typedef enum {
  CURLSHE_OK,
  CURLSHE_BAD_OPTION,
  CURLSHE_IN_USE,
  CURLSHE_INVALID,
  CURLSHE_NOMEM,
  CURLSHE_NOT_BUILT_IN,
  CURLSHE_LAST
} CURLSHcode;
typedef enum {
  CURLSHOPT_NONE,
  CURLSHOPT_SHARE,
  CURLSHOPT_UNSHARE,
  CURLSHOPT_LOCKFUNC,
  CURLSHOPT_UNLOCKFUNC,
  CURLSHOPT_USERDATA,
  CURLSHOPT_LAST
} CURLSHoption;
CURL_EXTERN CURLSH *curl_share_init(void);
CURL_EXTERN CURLSHcode curl_share_setopt(CURLSH *, CURLSHoption option, ...);
CURL_EXTERN CURLSHcode curl_share_cleanup(CURLSH *);
typedef enum {
  CURLVERSION_FIRST,
  CURLVERSION_SECOND,
  CURLVERSION_THIRD,
  CURLVERSION_FOURTH,
  CURLVERSION_FIFTH,
  CURLVERSION_LAST
} CURLversion;
typedef struct {
  CURLversion age;
  const char *version;
  unsigned int version_num;
  const char *host;
  int features;
  const char *ssl_version;
  long ssl_version_num;
  const char *libz_version;
  const char * const *protocols;
  const char *ares;
  int ares_num;
  const char *libidn;
  int iconv_ver_num;
  const char *libssh_version;
  unsigned int brotli_ver_num;
  const char *brotli_version;

} curl_version_info_data;
#define CURL_VERSION_IPV6         (1<<0)
#define CURL_VERSION_KERBEROS4    (1<<1)
                                        
#define CURL_VERSION_SSL          (1<<2)
#define CURL_VERSION_LIBZ         (1<<3)
#define CURL_VERSION_NTLM         (1<<4)
#define CURL_VERSION_GSSNEGOTIATE (1<<5)
                                        
#define CURL_VERSION_DEBUG        (1<<6)
#define CURL_VERSION_ASYNCHDNS    (1<<7)
#define CURL_VERSION_SPNEGO       (1<<8)
#define CURL_VERSION_LARGEFILE    (1<<9)
#define CURL_VERSION_IDN          (1<<10
                                        
#define CURL_VERSION_SSPI         (1<<11
#define CURL_VERSION_CONV         (1<<12
#define CURL_VERSION_CURLDEBUG    (1<<13)
#define CURL_VERSION_TLSAUTH_SRP  (1<<14)
#define CURL_VERSION_NTLM_WB      (1<<15)
                                         
#define CURL_VERSION_HTTP2        (1<<16)
#define CURL_VERSION_GSSAPI       (1<<17)
#define CURL_VERSION_KERBEROS5    (1<<18)
#define CURL_VERSION_UNIX_SOCKETS (1<<19)
#define CURL_VERSION_PSL          (1<<20)
                                         
#define CURL_VERSION_HTTPS_PROXY  (1<<21)
#define CURL_VERSION_MULTI_SSL    (1<<22)
#define CURL_VERSION_BROTLI       (1<<23)
CURL_EXTERN curl_version_info_data *curl_version_info(CURLversion);
CURL_EXTERN const char *curl_easy_strerror(CURLcode);
CURL_EXTERN const char *curl_share_strerror(CURLSHcode);
CURL_EXTERN CURLcode curl_easy_pause(CURL *handle, int bitmask);
#define CURLPAUSE_RECV      (1<<0)
#define CURLPAUSE_RECV_CONT (0)
#define CURLPAUSE_SEND      (1<<2)
#define CURLPAUSE_SEND_CONT (0)
#define CURLPAUSE_ALL       (CURLPAUSE_RECV|CURLPAUSE_SEND)
#define CURLPAUSE_CONT      (CURLPAUSE_RECV_CONT|CURLPAUSE_SEND_CONT)
*/
#endif
