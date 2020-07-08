
/*!@file duktape/pthread.c
 * @brief Various pthread native functions to expose to Duktape
 */
#ifdef DUK_USE_PTHREAD
#include"duktape/pthread.h"
#include<pthread.h>
#include<unistd.h>
#if 0
int pthread_mutex_destroy(pthread_mutex_t* __mutex);
int pthread_mutex_init(pthread_mutex_t* __mutex, const pthread_mutexattr_t* __attr);
int pthread_mutex_lock(pthread_mutex_t* __mutex);
int pthread_mutex_trylock(pthread_mutex_t* __mutex);
int pthread_mutex_unlock(pthread_mutex_t* __mutex);
int pthread_key_create(pthread_key_t* __key_ptr, void (*__key_destructor)(void*));
int pthread_key_delete(pthread_key_t __key);
int pthread_mutexattr_destroy(pthread_mutexattr_t* __attr);
int pthread_mutexattr_getpshared(const pthread_mutexattr_t* __attr, int* __shared);
int pthread_mutexattr_gettype(const pthread_mutexattr_t* __attr, int* __type);
//--------------------------------------------------------------------------------
//js prototype code
//--------------------------------------------------------------------------------
//	function pth_fn_0(arg){};//thread callback
//	var pth_data_0={foo:42};//data object
//	var pth_obj_0=mkpthobj();//pointer pthread_t
//	if(pthread_create(pth_obj_0,0,pth_fn_0,pth_data_0)){
//		printf(stderr,"Could not create thread\n");
//	}
//	if(pthread_join(pth_obj_0){
//		printf(stderr,"Failed to join thread\n");
//	}
//	free(pth_obj_0);//general libc free
//--------------------------------------------------------------------------------
#endif
static duk_ret_t native_mk_pthread_t(duk_context*ctx){
	duk_push_pointer(ctx,(pthread_t*)malloc(sizeof(pthread_t)));
	return 1;
}
typedef struct duk_pthread_data{
	void*ctx;
	void*fn;
	char*fnnam;
	void*data;
	int test;
}duk_pthread_data;
void pthread_callback(void*arg){
	fprintf(stderr,"pthread_callback:begin\n");
	if(arg!=NULL){
		duk_pthread_data*dpd=(duk_pthread_data*)arg;
		duk_context*ctx=(duk_context*)(dpd->ctx);
		//duk_call(ctx,1);// /*works?*/1);  // TypeError if not callable / undefined
		fprintf(stderr,"pthread_callback:data:%d\n",dpd->test);
		free(arg);
	}else{
		fprintf(stderr,"pthread_callback:data:NULL\n");
	}
	fprintf(stderr,"pthread_callback:end\n");
}
//int pthread_create(pthread_t* __pthread_ptr, pthread_attr_t const* __attr, void* (*__start_routine)(void*), void*);
static duk_ret_t native_pthread_create(duk_context*ctx){
	//    (void) duk_require_function(ctx, -1);
	//(void) duk_require_function(ctx, -1);
	if(!duk_is_function(ctx,2)){
		fprintf(stderr,"info:native_pthread_create:is not function");
		duk_error(ctx, DUK_ERR_TYPE_ERROR, "not a function");
	}else{
		fprintf(stderr,"info:native_pthread_create:is function");
		duk_call(ctx,1);// /*works?*/1);  // TypeError if not callable / undefined
	}
	duk_pthread_data*dpd=(duk_pthread_data*)malloc(sizeof(duk_pthread_data));;
	dpd->ctx=(void*)ctx;
	dpd->test=42;
	/*
	 *     // Equivalent to Ecmascript code: globalObject._my_callback = arg; 
	 *     duk_dup(ctx, 0);
	 *     duk_put_global_string(ctx, "_my_callback");
	 */
	duk_push_int(ctx,pthread_create(
		duk_get_pointer(ctx,0),
		duk_get_int(ctx,1),
		pthread_callback,
		dpd
	));
	return 1;
	/*
	return 0;
	*/
}

//int pthread_join(pthread_t __pthread, void** __return_value_ptr);
static duk_ret_t native_pthread_join(duk_context*ctx){
	duk_push_int(ctx,pthread_join(
		duk_get_pointer(ctx,0),
		duk_get_int(ctx,1)//void** - fix later
	));
	return 1;
}
//int usleep(useconds_t usec);
static duk_ret_t native_usleep(duk_context*ctx){
	duk_push_int(ctx,usleep(duk_get_int(ctx,0)));
	return 1;
}
void duk_register_pthread(duk_context*ctx){
#if 0
	//normal arguments
static duk_ret_t native_(duk_context*ctx){
	return 0;
}
	//object arguments - for reference
	//e.g. var objref={p0:p0,p1,p1};
	//     fnref(objref);//effect: p0...pN passed in by reference
static duk_ret_t native_fnref(duk_context*ctx){
	if(
		duk_has_prop_string(ctx,0,"p0")
	){
		(void*)duk_get_prop_string(ctx,0,"p0");
		struct dirent*dirp=(struct dirent*)duk_to_pointer(ctx,-1);
		//todo: manipulate obj arg
	}else{
		fprintf(stderr,"Error: native_readdir: Invalid properties\n");
		duk_push_null(ctx);
	}
	return 1;
}

	duk_push_int(ctx,SYMBOL);
	duk_put_global_string(ctx,"SYMBOL");
	duk_push_c_function(ctx,native_name,1);
	duk_put_global_string(ctx,"name");
#endif
	duk_push_c_function(ctx,native_mk_pthread_t,0);
	duk_put_global_string(ctx,"mk_pthread_t");
	duk_push_c_function(ctx,native_pthread_create,4);
	duk_put_global_string(ctx,"pthread_create");
	duk_push_c_function(ctx,native_pthread_join,2);
	duk_put_global_string(ctx,"pthread_join");
	duk_push_c_function(ctx,native_usleep,1);
	duk_put_global_string(ctx,"usleep");
}
#endif
