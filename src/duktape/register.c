/*!@file duk/native.c
 * @brief Various native functions to expose to Duktape
 * references : creating/returning object:
 *              https://stackoverflow.com/questions/36281265/using-json-objects-in-duktape
 *              differentiating between windows and linux:
 *              https://stackoverflow.com/questions/6649936/c-compiling-on-windows-and-linux-ifdef-switch
 *              [f]stat:
 *              https://en.wikipedia.org/wiki/Stat_(system_call)
 */
#include"duktape.h"
#include"duktape/register.h"
#include"duktape/duk_module_duktape.h"
#include"duktape/sqlite.h"
#include"duktape/libc.h"
#ifdef DUK_USE_CURL
#include"duktape/curl.h"
#endif
#ifdef DUK_USE_CACA
#include"duktape/caca.h"
#endif
#ifdef DUK_USE_NCURSES
#include"duktape/ncurses.h"
#endif
#include<dirent.h>
#include<sys/stat.h>
#define PATH_MAX_STRING_SIZE 256
/*! External reference to environmental variables */
extern char **environ;
/*! Native function make directory recursive
 *  \param ctx Duktape context to run function in
 *  \return `duk_ret_t` return type
 */
static duk_ret_t native_mkdir_p(duk_context*ctx){
	int ret=0;
	char*dir=duk_to_string(ctx,0);
	int mode=duk_to_int(ctx,1);
	char tmp[PATH_MAX_STRING_SIZE];
	char *p = NULL;
	struct stat sb;
	size_t len;
	
	/* copy path */
	len = strnlen (dir, PATH_MAX_STRING_SIZE);
	if (len == 0 || len == PATH_MAX_STRING_SIZE) {
		duk_push_int(ctx,-1);
		return 1;
	}
	memcpy (tmp, dir, len);
	tmp[len] = '\0';

	/* remove trailing slash */
	if(tmp[len - 1] == '/') {
		tmp[len - 1] = '\0';
	}

	/* check if path exists and is a directory */
	if (stat (tmp, &sb) == 0) {
		if (S_ISDIR (sb.st_mode)) {
			duk_push_int(ctx,0);
			return 1;
		}
	}
	
	/* recursive mkdir */
	for(p = tmp + 1; *p; p++) {
		if(*p == '/') {
			*p = 0;
			/* test path */
			if (stat(tmp, &sb) != 0) {
				/* path does not exist - create directory */
#ifdef _WIN32
				if (mkdir(tmp) < 0) {
#else
				if (mkdir(tmp, mode) < 0) {
#endif
					duk_push_int(ctx,-1);
					return 0;
				}
			} else if (!S_ISDIR(sb.st_mode)) {
				/* not a directory */
				duk_push_int(ctx,-1);
				return 1;
			}
			*p = '/';
		}
	}
	/* test path */
	if (stat(tmp, &sb) != 0) {
		/* path does not exist - create directory */
#ifdef _WIN32
		if (mkdir(tmp) < 0) {
#else
		if (mkdir(tmp, mode) < 0) {
#endif
			duk_push_int(ctx,-1);
			return 1;
		}
	} else if (!S_ISDIR(sb.st_mode)) {
		/* not a directory */
		duk_push_int(ctx,-1);
		return 1;
	}
}
/*! Native print function, prints value to `stdout`
 *  \param ctx Duktape context to run function in
 *  \return `duk_ret_t` return type
 */
static duk_ret_t native_print(duk_context*ctx){
	//fprintf(stderr,"%s",duk_to_string(ctx,0));
	fprintf(stdout,"%s",duk_to_string(ctx,0));
	return 0;/*no return value(=undefined)*/
}
/*! Native print function, prints value to `stdout`. Appends newline character
 *  \param ctx Duktape context to run function in
 *  \return `duk_ret_t` return type
 */
static duk_ret_t native_println(duk_context*ctx){
	//fprintf(stderr,"%s",duk_to_string(ctx,0));
	fprintf(stdout,"%s\n",duk_to_string(ctx,0));
	return 0;/*no return value(=undefined)*/
}
/*! Native get environment function. Returns an `Object` of the environmental variables
 *  \param ctx Duktape context to run function in
 *  \return `duk_ret_t` return type
 */
static duk_ret_t native_env(duk_context*ctx){
	//duk_push_array(ctx);
	int i=0;
	char *s=*environ;
	int idx=0;
	//set up object to be returned
	duk_idx_t obj_idx;
	obj_idx = duk_push_object(ctx);
	for (;s;i++){
		s=*(environ+1+i);
		if(s!=NULL){
			//add key values to object
			//todo: fix up code
			size_t len=strlen(s)+1;
			char*scopy=(char*)malloc(len);
			memcpy(scopy,s,strlen(s));
			scopy[len-1]='\0';
			char*eqpos=strchr(scopy,'=');
			if(eqpos!=NULL){
				*eqpos='\0';
				duk_push_string(ctx,eqpos+1);//"my_name");
				duk_put_prop_string(ctx,obj_idx,scopy);
			}else{
			}
			free(scopy);
			//duk_push_string(ctx,s);
			//duk_put_prop_index(ctx,-2,i);
		}
	}
	return 1;
}
/*! Push file as buffer
 *  \return `duk_ret_t` return type
 */
void fileio_push_file_buffer(duk_context *ctx, const char *filename) {
	FILE *f = NULL;
	long len;
	void *buf;
	size_t got;

	if (!filename) {
		goto error;
	}

	f = fopen(filename, "rb");
	if (!f) {
		goto error;
	}

	if (fseek(f, 0, SEEK_END) != 0) {
		goto error;
	}

	len = ftell(f);

	if (fseek(f, 0, SEEK_SET) != 0) {
		goto error;
	}

	buf = duk_push_fixed_buffer(ctx, (size_t) len);

	got = fread(buf, 1, len, f);
	if (got != (size_t) len) {
		duk_pop(ctx);
		goto error;
	}

	fclose(f);
	return;

 error:
	if (f) {
		fclose(f);
	}
	duk_push_undefined(ctx);
}

/*! Push file as string
 *  \return `duk_ret_t` return type
 */
void fileio_push_file_string(duk_context *ctx, const char *filename) {
	fileio_push_file_buffer(ctx, filename);
	if (duk_is_buffer_data(ctx, -1)) {
		duk_buffer_to_string(ctx, -1);
	}
}
/*! Native read file function to expose
 *  \return `duk_ret_t` return type
 */
static int fileio_readfile(duk_context *ctx) {
	const char *filename = duk_to_string(ctx, 0);
	fileio_push_file_buffer(ctx, filename);
	if (!duk_is_buffer_data(ctx, -1)) {
		return DUK_RET_ERROR;
	}
	return 1;
}
/*! List fileio functions
 *  \return `duk_ret_t` return type
 */
static duk_function_list_entry fileio_funcs[] = {
	{ "readfile", fileio_readfile, 1 },
	{ NULL, NULL, 0 }
};
/*! Native list directory
 *  \return `duk_ret_t` return type
 */
static duk_ret_t native_ls(duk_context*ctx){
	const char*path=duk_to_string(ctx,0);
	DIR *dp;
	struct dirent *ep;     
	dp=opendir(path);
	duk_push_array(ctx);
	int i=0;
	if(dp!=NULL){
		while(ep=readdir(dp)){
			duk_push_string(ctx,ep->d_name);
			duk_put_prop_index(ctx,-2,i++);
			//puts(ep->d_name);
		}
		(void) closedir (dp);
	}else{
		//could not open directory
	}
	return 1;
}


/*! Native load and evalute in context
 *  \return `duk_ret_t` return type
 */
static duk_ret_t native_load(duk_context*ctx){
	const char*filename=duk_to_string(ctx,0);
	//fprintf(stderr,"Info: native_load: opening %s\n",filename);
	char*buffer=0;
	long length;
	FILE*f=fopen(filename,"rb");
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
		duk_eval_string_noresult(ctx,buffer);
		free(buffer);
		//fprintf(stderr,"Info: native_load: done loading %s\n",filename);
	}else{
		fprintf(stderr,"Error: native_load: Failed to open %s\n",filename);
	}
	return 0;
}
/*! Native reftest function. From javascript you cannot pass an object by reference
 *  and then modify it in C. The closest for now is to pass in a `String`, which is 
 *  a variable name, and then modify the caller context to push a variable onto
 *  that context with the name specified
 *  \return `duk_ret_t` return type
 */
static duk_ret_t native_reftest(duk_context*ctx){
//https://stackoverflow.com/questions/38686495/how-to-add-modify-or-delete-a-property-of-an-object-in-duktape
    /* argument object is at index 0 */
    duk_push_uint(ctx, 123);                   /* -> stack: [ obj 123 ] */
    duk_put_prop_string(ctx, 0, "new_param");  /* -> stack: [ obj ] */
    duk_push_uint(ctx, 456);
    duk_put_prop_string(ctx, 0, "existing_param2");
    //del_prop_string(ctx, 0, "existing_param3");
    return 0;  /* no return value (same as 'return undefined' in Ecmascript) */
	/*
	// Value stack index 0: key. 
	duk_push_global_object(ctx);
	duk_dup(ctx, 0);  // key 
	duk_push_uint(ctx, 2);  // value 
	duk_put_prop(ctx, -3);  // global[key] = value 
	*/
}
//---------------------------
/*! Register native function on context
 *  \return `duk_ret_t` return type
 */
void duk_register(duk_context*ctx){
	duk_module_duktape_init(ctx);
	duk_register_sqlite(ctx);
	duk_register_log(ctx);
	duk_register_libc(ctx);
#ifdef DUK_USE_CURL
	duk_register_curl(ctx);
#endif
#ifdef DUK_USE_CACA
	duk_register_caca(ctx);
#endif
#ifdef DUK_USE_CACA
	duk_register_ncurses(ctx);
#endif
	//----------------------------------------
	duk_push_c_function(ctx,native_mkdir_p,2);
	duk_put_global_string(ctx,"mkdir_p");
	duk_push_c_function(ctx,native_env,DUK_VARARGS);
	duk_put_global_string(ctx,"getEnv");
	duk_push_c_function(ctx,native_ls,DUK_VARARGS);
	duk_put_global_string(ctx,"ls");
	duk_push_c_function(ctx,native_load,1);
	duk_put_global_string(ctx,"load");
	//open file from extras
	//----------------------------------------
	duk_push_global_object(ctx);
	duk_push_object(ctx);
	duk_put_function_list(ctx, -1, fileio_funcs);
	duk_put_prop_string(ctx, -2, "FileIo");
	//----------------------------------------
	//printing functions
	//----------------------------------------
	duk_push_c_function(ctx,native_print,1/*nargs*/);
	duk_put_global_string(ctx,"print");
	duk_push_c_function(ctx,native_println,1/*nargs*/);
	duk_put_global_string(ctx,"println");
	duk_pop(ctx);
}
