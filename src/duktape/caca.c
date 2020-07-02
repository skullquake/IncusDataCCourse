/*!@file duk/caca.c
 * @brief Various libcaca native functions to expose to Duktape
 */
#ifdef DUK_USE_CACA
#include"duktape/caca.h"
#include<caca.h>
//#include<zlib.h>
static duk_ret_t native_caca_create_display(duk_context*ctx){
	duk_push_pointer(ctx,(void*)caca_create_display(NULL));
	return 1;
}
static duk_ret_t native_caca_get_canvas(duk_context*ctx){
	duk_push_pointer(ctx,(void*)caca_get_canvas((caca_display_t*)duk_get_pointer(ctx,0)));
	return 1;
}
static duk_ret_t native_caca_set_display_title(duk_context*ctx){
	caca_set_display_title((caca_display_t*)duk_get_pointer(ctx,0),duk_get_string(ctx,1));
	return 0;
}
static duk_ret_t native_caca_set_color_ansi(duk_context*ctx){
	caca_set_color_ansi((caca_canvas_t*)duk_get_pointer(ctx,0),duk_get_int(ctx,1),duk_get_int(ctx,2));
	return 0;
}
static duk_ret_t native_caca_put_str(duk_context*ctx){
	//caca_put_str(cv, 0, 0, "This is a message");
	caca_put_str((caca_canvas_t*)duk_get_pointer(ctx,0),duk_get_int(ctx,1),duk_get_int(ctx,2),duk_get_string(ctx,3));
	return 0;
}
static duk_ret_t native_caca_caca_refresh_display(duk_context*ctx){
	caca_refresh_display((caca_display_t*)duk_get_pointer(ctx,0));
	return 0;
}
static duk_ret_t native_caca_get_event(duk_context*ctx){
	caca_event_t ev;
	caca_get_event((caca_display_t*)duk_get_pointer(ctx,0),duk_get_int(ctx,1), &ev, -1);
	return 0;
}
static duk_ret_t native_caca_free_display(duk_context*ctx){
	caca_free_display((caca_display_t*)duk_get_pointer(ctx,0));
	return 0;
}
/*! Native function
 *  \param ctx Duktape context to run function in
 *  \return `duk_ret_t` return type
 */
static duk_ret_t native_caca_test(duk_context*ctx){
	caca_canvas_t *cv;
	caca_display_t *dp;
	caca_event_t ev;
	dp = caca_create_display(NULL);
	if(!dp) return 1;
	cv = caca_get_canvas(dp);
	caca_set_display_title(dp, "Hello!");
	caca_set_color_ansi(cv, CACA_BLACK, CACA_WHITE);
	caca_put_str(cv, 0, 0, "This is a message");
	caca_refresh_display(dp);
	caca_get_event(dp, CACA_EVENT_KEY_PRESS, &ev, -1);
	caca_free_display(dp);
#if 0
	int rc=sqlite3_exec(
		(sqlite3*)duk_to_pointer(ctx,0),
		duk_to_string(ctx,1),
		0,//callback
		0,//callback userdata
		0//errors
	);
	duk_push_int(ctx,rc);
#endif
	return 1;
}
/*! Register native function on context
 *  \return `duk_ret_t` return type
 */
void duk_register_caca(duk_context*ctx){
#if 0
	duk_push_int(ctx,SQLITE_WIN32_TEMP_DIRECTORY_TYPE);
	duk_put_global_string(ctx,"SQLITE_WIN32_TEMP_DIRECTORY_TYPE");
	duk_push_c_function(ctx,native_sqlite3_bind_zeroblob64,3);
	duk_put_global_string(ctx,"bind_zeroblob64");
#endif

	duk_push_int(ctx,CACA_BLACK);
	duk_put_global_string(ctx,"CACA_BLACK");
	duk_push_int(ctx,CACA_WHITE);
	duk_put_global_string(ctx,"CACA_WHITE");
	duk_push_int(ctx,CACA_EVENT_KEY_PRESS);
	duk_put_global_string(ctx,"CACA_EVENT_KEY_PRESS");

	duk_push_c_function(ctx,native_caca_test,0);
	duk_put_global_string(ctx,"caca_test");

	duk_push_c_function(ctx,native_caca_create_display,0);
	duk_put_global_string(ctx,"caca_create_display");
	duk_push_c_function(ctx,native_caca_get_canvas,1);
	duk_put_global_string(ctx,"caca_get_canvas");
	duk_push_c_function(ctx,native_caca_set_display_title,2);
	duk_put_global_string(ctx,"caca_set_display_title");
	duk_push_c_function(ctx,native_caca_set_color_ansi,3);
	duk_put_global_string(ctx,"caca_set_color_ansi");
	duk_push_c_function(ctx,native_caca_put_str,4);
	duk_put_global_string(ctx,"caca_put_str");
	duk_push_c_function(ctx,native_caca_caca_refresh_display,1);
	duk_put_global_string(ctx,"caca_refresh_display");
	duk_push_c_function(ctx,native_caca_get_event,2);//for now
	duk_put_global_string(ctx,"caca_get_event");
	duk_push_c_function(ctx,native_caca_free_display,1);
	duk_put_global_string(ctx,"caca_free_display");
}
#endif

