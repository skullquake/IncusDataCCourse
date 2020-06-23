/*!@file duk/libc.c
/*!@brief native registration of various libc functions
 */
#include"duktape/libc.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<dirent.h>
#include<stdbool.h>
#include<limits.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<time.h>
#ifndef _WIN32
#include<pwd.h>
#include<grp.h>
#endif
#define PATH_MAX_STRING_SIZE 256
/*! External reference to environmental variables */
extern char **environ;
/*! Native function to get the current working directory
 *  \param ctx Duktape context to run function in
 *  \return `duk_ret_t` return type
 */
static duk_ret_t native_getcwd(duk_context*ctx){
	char cwd[PATH_MAX];
	if (getcwd(cwd, sizeof(cwd)) != NULL) {
		duk_push_string(ctx,cwd);
	} else {
		fprintf(stderr,"Error: native_getcwd: getcwd() error");
		duk_push_null(ctx);
		return 1;
	}
	return 1;
}
/*! Native function to change current working directory
 *  \param ctx Duktape context to run function in
 *  \return `duk_ret_t` return type
 */
static duk_ret_t native_chdir(duk_context*ctx){
	chdir(duk_to_string(ctx,0));
	return 0;
}
/*! Native binary write function, writs buffer to 'stdout'
 *  \param ctx Duktape context to run function in
 *  \return `duk_ret_t` return type
 */
static duk_ret_t native_write(duk_context*ctx){
	//fprintf(stderr,"Info: native_write: start\n");
	duk_size_t sz;
	void*ptr=duk_require_buffer_data(ctx,0,&sz);
	//void*ptr=duk_to_buffer(ctx,0,&sz);
	//void*ptr=duk_to_dynamic_buffer(ctx,0,&sz);
	//void*ptr=duk_to_fixed_buffer(ctx,0,&sz);
	//fprintf(stderr,"Info: native_write: buf: length: %d\n",sz);
	//fprintf(stderr,"Info: writing %zu bytes..\n",sz);
	fwrite(ptr,1,sz,stdout);
	//fprintf(stderr,"Info: native_write: end\n");
	return 0;/*no return value(=undefined)*/
}
//todo: fopen
//      fwrite
//      fread
//      fclose
static duk_ret_t native_fopen(duk_context*ctx){
	//fprintf(stderr,"Info: native_fopen: start\n");
	const char*fnam=duk_to_string(ctx,0);
	const char*fmod=duk_to_string(ctx,1);
	fprintf(stderr,"Info: native_fopen: Opening %s [%s]\n",fnam,fmod);
	FILE*fp=fopen(fnam,fmod);
	if(fp==NULL){
		duk_push_null(ctx);
	}else{
		duk_push_pointer(ctx,(void*)fp);
	}
	//fprintf(stderr,"Info: native_fopen: end\n");
	return 1;
}
static duk_ret_t native_fclose(duk_context*ctx){
	duk_push_int(ctx,fclose((FILE*)duk_to_pointer(ctx,0)));
	return 1;
}
//size_t fwrite( const void *buffer, size_t size, size_t count,FILE *stream );
static duk_ret_t native_fwrite(duk_context*ctx){
	void*buffer;
	duk_size_t sz;
	//buffer=duk_to_buffer(ctx,0,&sz);
	buffer=duk_require_buffer_data/*duk_to_buffer*/(ctx,0,&sz);
	size_t size=duk_to_int(ctx,1);
	size_t count=duk_to_int(ctx,2);
	FILE*stream=(FILE*)duk_to_pointer(ctx,3);
	size_t read=fwrite(buffer,size,count,stream);
	duk_push_int(ctx,read);
	return 1;
}
//size_t fread ( void * ptr, size_t size, size_t count, FILE * stream );
//In the javascript it takes an object as argument
//https://github.com/svaarala/duktape/issues/416
static duk_ret_t native_fread(duk_context*ctx){
	//duk_push_uint(ctx, 123);                   /* -> stack: [ obj 123 ] */
	//duk_put_prop_string(ctx, 4, "new_param");  /* -> stack: [ obj ] */
	//duk_push_uint(ctx, 456);
	//duk_put_prop_string(ctx, 0, "existing_param2");
	if(
		duk_has_prop_string(ctx,0,"buf")&&
		duk_has_prop_string(ctx,0,"size")&&
		duk_has_prop_string(ctx,0,"count")&&
		duk_has_prop_string(ctx,0,"stream")
	) {
		(void*)duk_get_prop_string(ctx, 0, "buf");
		void*ptr;
		duk_size_t sz;
		ptr=duk_require_buffer_data/*duk_to_buffer*/(ctx,-1,&sz);

		(void*)duk_get_prop_string(ctx, 0, "size");
		size_t size=duk_to_int(ctx,-1);
		(void*)duk_get_prop_string(ctx, 0, "count");
		size_t count=duk_to_int(ctx,-1);
		(void*)duk_get_prop_string(ctx, 0, "stream");
		FILE*stream=(FILE*)duk_to_pointer(ctx,-1);
		size_t read=fread(ptr,size,count,stream);
		duk_push_int(ctx,read);
	}else{
		fprintf(stderr,"Info: native_fread: foo: %s\n","Property not found");
		duk_push_int(ctx,0);
	}
	/*
	void*ptr;
	duk_size_t sz;
	ptr=duk_to_buffer(ctx,0,&sz);
	size_t size=duk_to_int(ctx,1);
	size_t count=duk_to_int(ctx,2);
	FILE*stream=(FILE*)duk_to_pointer(ctx,3);
	size_t read=fread(ptr,size,count,stream);
	duk_push_int(ctx,read);
	*/
	return 1;
}
/*! Native function fseek
 *  In the javascript it takes an object as argument
 *  \param ctx Duktape context to run function in
 *  \return `duk_ret_t` return type
 */
//int fseek( FILE *stream, long offset, int origin );
static duk_ret_t native_fseek(duk_context*ctx){
	if(
		duk_has_prop_string(ctx,0,"stream")&&
		duk_has_prop_string(ctx,0,"offset")&&
		duk_has_prop_string(ctx,0,"origin")
	){
		(void*)duk_get_prop_string(ctx, 0, "stream");
		FILE*stream=(FILE*)duk_to_pointer(ctx,-1);
		(void*)duk_get_prop_string(ctx, 0, "offset");
		long offset=(long)duk_to_int32(ctx,-1);
		(void*)duk_get_prop_string(ctx, 0, "origin");
		long origin=(long)duk_to_int32(ctx,-1);
		duk_push_int(
			ctx,
			fseek(
				stream,offset,origin
			)
		);
	}else{
		fprintf(stderr,"Error: native_fseek: Invalid properties\n");
		duk_push_null(ctx);//handle
	}
	return 1;
}
/*! Native function ftell
 *  In the javascript it takes an object as argument
 *  \param ctx Duktape context to run function in
 *  \return `duk_ret_t` return type
 */
//long ftell( FILE *stream );
static duk_ret_t native_ftell(duk_context*ctx){
	if(
		duk_has_prop_string(ctx,0,"stream")
	){
		(void*)duk_get_prop_string(ctx, 0, "stream");
		FILE*stream=(FILE*)duk_to_pointer(ctx,-1);
		duk_push_int(ctx,ftell(stream));
	}else{
		fprintf(stderr,"Error: native_ftell: Invalid properties\n");
		duk_push_null(ctx);//handle
	}
	return 1;
}
/*! Native function fgetpos
 *  In the javascript it takes an object as argument
 *  \param ctx Duktape context to run function in
 *  \return `duk_ret_t` return type
 */
//int fgetpos( FILE          *stream, fpos_t          *pos );
static duk_ret_t native_fgetpos(duk_context*ctx){
	if(
		duk_has_prop_string(ctx,0,"stream")
	){
		(void*)duk_get_prop_string(ctx, 0, "stream");
		FILE*stream=(FILE*)duk_to_pointer(ctx,-1);
		(void*)duk_get_prop_string(ctx, 0, "pos");
		fpos_t*pos=(fpos_t*)duk_to_pointer(ctx,-1);
		duk_push_int(ctx,fgetpos(stream,pos));
	}else{
		fprintf(stderr,"Error: native_fgetpos: Invalid properties\n");
		duk_push_null(ctx);//handle
	}
	return 1;
}
/*! Native function rewind
 *  In the javascript it takes an object as argument
 *  \param ctx Duktape context to run function in
 *  \return `duk_ret_t` return type
 */
//void rewind( FILE          *stream)
static duk_ret_t native_rewind(duk_context*ctx){
	if(
		duk_has_prop_string(ctx,0,"stream")
	){
		(void*)duk_get_prop_string(ctx, 0, "stream");
		FILE*stream=(FILE*)duk_to_pointer(ctx,-1);
		rewind(stream);
	}else{
		fprintf(stderr,"Error: native_rewind: Invalid properties\n");
	}
	return 0;
}
/*! Native function fstat
 *  In the javascript it takes an object `{fildes:Pointer}` as argument, and will return an object with the parsed stat
 *  \param ctx Duktape context to run function in
 *  \return `duk_ret_t` return type
 */
//int fstat (int filedes, struct stat *buf)
//https://pubs.opengroup.org/onlinepubs/009695399/functions/fstat.html
static duk_ret_t native_fstat(duk_context*ctx){
	struct stat buf;
	if(
		duk_has_prop_string(ctx,0,"fildes")
	){
		(void*)duk_get_prop_string(ctx,0,"fildes");
		int fildes=duk_to_int(ctx,-1);
		struct stat buf;
		if(fstat(fildes,&buf)==0){
			duk_idx_t obj_idx=duk_push_object(ctx);
			duk_push_int(ctx,buf.st_ino);duk_put_prop_string(ctx,obj_idx,"st_ino");
			duk_push_int(ctx,buf.st_uid);duk_put_prop_string(ctx,obj_idx,"st_uid");
#ifndef _WIN32
			struct passwd *pwuser;
			struct group *grpnam;
			if((pwuser=getpwuid(buf.st_uid))!=NULL){
				duk_push_string(ctx,pwuser->pw_name);duk_put_prop_string(ctx,obj_idx,"pwuser_pw_name");
			}
			duk_push_int(ctx,buf.st_gid);duk_put_prop_string(ctx,obj_idx,"gid");
			if((grpnam=getgrgid(buf.st_gid))!=NULL){
				duk_push_string(ctx,grpnam->gr_name);duk_put_prop_string(ctx,obj_idx,"grpnam_gr_name");
			}
#endif
			duk_push_int(ctx,buf.st_size);duk_put_prop_string(ctx,obj_idx,"st_size");
			duk_push_int(ctx,buf.st_nlink);duk_put_prop_string(ctx,obj_idx,"st_nlink");

			duk_push_boolean(ctx,buf.st_mode&R_OK);duk_put_prop_string(ctx,obj_idx,"read");
			duk_push_boolean(ctx,buf.st_mode&W_OK);duk_put_prop_string(ctx,obj_idx,"write");
			duk_push_boolean(ctx,buf.st_mode&X_OK);duk_put_prop_string(ctx,obj_idx,"execute");

			duk_push_string(ctx,ctime(&buf.st_atime));duk_put_prop_string(ctx,obj_idx,"st_atim");//get rid of newlines....
			duk_push_string(ctx,ctime(&buf.st_mtime));duk_put_prop_string(ctx,obj_idx,"st_mtim");//"
			duk_push_string(ctx,ctime(&buf.st_ctime));duk_put_prop_string(ctx,obj_idx,"st_ctim");//"

			duk_push_boolean(ctx,S_ISREG(buf.st_mode));duk_put_prop_string(ctx,obj_idx,"file");
			duk_push_boolean(ctx,S_ISDIR(buf.st_mode));duk_put_prop_string(ctx,obj_idx,"directory");

		}else{
			duk_push_null(ctx);
		}
	}else{
		fprintf(stderr,"Error: native_fstat: Invalid properties\n");
		duk_push_null(ctx);
	}
	return 1;
}
/*! Native function stat
 *  In the javascript it takes an object `{path:String}` as argument, and will return an object with the parsed stat
 *  \param ctx Duktape context to run function in
 *  \return `duk_ret_t` return type
 */
//int stat(const char *restrict path, struct stat *restrict buf);
//https://pubs.opengroup.org/onlinepubs/009695399/functions/stat.html
static duk_ret_t native_stat(duk_context*ctx){
	struct stat buf;
	if(
		duk_has_prop_string(ctx,0,"path")
	){
		(void*)duk_get_prop_string(ctx,0,"path");
		const char*path=(const char*)duk_to_string(ctx,-1);
		struct stat buf;
		if(stat(path,&buf)==0){
			duk_idx_t obj_idx=duk_push_object(ctx);
			duk_push_int(ctx,buf.st_ino);duk_put_prop_string(ctx,obj_idx,"st_ino");
			duk_push_int(ctx,buf.st_uid);duk_put_prop_string(ctx,obj_idx,"st_uid");
#ifndef _WIN32
			struct passwd *pwuser;
			struct group *grpnam;
			if((pwuser=getpwuid(buf.st_uid))!=NULL){
				duk_push_string(ctx,pwuser->pw_name);duk_put_prop_string(ctx,obj_idx,"pwuser_pw_name");
			}
			duk_push_int(ctx,buf.st_gid);duk_put_prop_string(ctx,obj_idx,"gid");
			if((grpnam=getgrgid(buf.st_gid))!=NULL){
				duk_push_string(ctx,grpnam->gr_name);duk_put_prop_string(ctx,obj_idx,"grpnam_gr_name");
			}
#endif
			duk_push_int(ctx,buf.st_size);duk_put_prop_string(ctx,obj_idx,"st_size");
			duk_push_int(ctx,buf.st_nlink);duk_put_prop_string(ctx,obj_idx,"st_nlink");

			duk_push_boolean(ctx,buf.st_mode&R_OK);duk_put_prop_string(ctx,obj_idx,"read");
			duk_push_boolean(ctx,buf.st_mode&W_OK);duk_put_prop_string(ctx,obj_idx,"write");
			duk_push_boolean(ctx,buf.st_mode&X_OK);duk_put_prop_string(ctx,obj_idx,"execute");

			duk_push_string(ctx,ctime(&buf.st_atime));duk_put_prop_string(ctx,obj_idx,"st_atim");//get rid of newlines....
			duk_push_string(ctx,ctime(&buf.st_mtime));duk_put_prop_string(ctx,obj_idx,"st_mtim");//"
			duk_push_string(ctx,ctime(&buf.st_ctime));duk_put_prop_string(ctx,obj_idx,"st_ctim");//"

			duk_push_boolean(ctx,S_ISREG(buf.st_mode));duk_put_prop_string(ctx,obj_idx,"file");
			duk_push_boolean(ctx,S_ISDIR(buf.st_mode));duk_put_prop_string(ctx,obj_idx,"directory");
/*
	mode_t			st_mode;
	ino_t			st_ino;
	dev_t			st_dev;
	dev_t			st_rdev;
	nlink_t			st_nlink;
	uid_t			st_uid;
	gid_t			st_gid;
	off_t			st_size;
	struct timespec	st_atim;
	struct timespec	st_mtim;
	struct timespec st_ctim;
	blksize_t		st_blksize;
	blkcnt_t		st_blocks;
*/
		}else{
			duk_push_null(ctx);
		}
	}else{
		fprintf(stderr,"Error: native_fstat: Invalid properties\n");
		duk_push_null(ctx);
	}
	return 1;
}
/*! Native function fileno
 *  In the javascript it takes an object `{stream:Pointer}`as argument, and will return an integer with the fileno
 *  \param ctx Duktape context to run function in
 *  \return `duk_ret_t` return type
 */
//int fileno(FILE *stream);
//https://pubs.opengroup.org/onlinepubs/009695399/functions/fileno.html
static duk_ret_t native_fileno(duk_context*ctx){
	if(
		duk_has_prop_string(ctx,0,"stream")
	){
		(void*)duk_get_prop_string(ctx,0,"stream");
		FILE*stream=(FILE*)duk_to_pointer(ctx,-1);
		duk_push_int(ctx,fileno(stream));
	}else{
		fprintf(stderr,"Error: native_fstat: Invalid properties\n");
		duk_push_null(ctx);
	}
	return 1;
}
#ifndef _WIN32
/*! Native function fopendir
 *  In the javascript it takes an object `{fd:int}`as argument, and will return an Pointer to DIR
 *  \param ctx Duktape context to run function in
 *  \return `duk_ret_t` return type
 */
//DIR *fdopendir(int fd);
static duk_ret_t native_fdopendir(duk_context*ctx){
	if(
		duk_has_prop_string(ctx,0,"fd")
	){
		(void*)duk_get_prop_string(ctx,0,"fd");
		int fd=duk_to_int(ctx,-1);
		duk_push_pointer(ctx,(void*)fdopendir(fd));
	}else{
		fprintf(stderr,"Error: native_fdopendir: Invalid properties\n");
		duk_push_null(ctx);
	}
	return 1;
}
#endif
/*! Native function opendir
 *  In the javascript it takes an object `{dirname:String}`as argument, and will return an Pointer to DIR
 *  \param ctx Duktape context to run function in
 *  \return `duk_ret_t` return type
 */
//DIR *opendir(const char *dirname);
static duk_ret_t native_opendir(duk_context*ctx){
	if(
		duk_has_prop_string(ctx,0,"dirname")
	){
		(void*)duk_get_prop_string(ctx,0,"dirname");
		char*dirname=(char*)duk_to_string(ctx,-1);
		DIR *dp=opendir(dirname);
		if(dp==NULL){
			//fprintf(stderr,"Warning: native_opendir: dp NULL\n");
			duk_push_null(ctx);
		}else{
			duk_push_pointer(ctx,dp);
		}
	}else{
		fprintf(stderr,"Error: native_opendir: Invalid properties\n");
		duk_push_null(ctx);
	}
	return 1;
}
/*! Native function readdir
 *  In the javascript it takes an object `{dirp:Pointer}`as argument, and will return an struct dirent
 *  \param ctx Duktape context to run function in
 *  \return `duk_ret_t` return type
 */
//struct dirent *readdir(DIR *dirp);
static duk_ret_t native_readdir(duk_context*ctx){
	if(
		duk_has_prop_string(ctx,0,"dirp")
	){
		(void*)duk_get_prop_string(ctx,0,"dirp");
		DIR*dirp=(DIR*)duk_to_pointer(ctx,-1);
		struct dirent*ep;
		ep=readdir(dirp);
		if(ep==NULL){
			//fprintf(stderr,"Warning: native_readdir: dirent NULL\n");
			duk_push_null(ctx);
		}else{
			duk_push_pointer(ctx,ep);
		}
	}else{
		fprintf(stderr,"Error: native_readdir: Invalid properties\n");
		duk_push_null(ctx);
	}
	return 1;
}
/*! Native function closedir
 *  In the javascript it takes an object `{dirp:Pointer}`as argument, and will return Number
 *  \param ctx Duktape context to run function in
 *  \return `duk_ret_t` return type
 */
//int closedir(DIR *dirp);
static duk_ret_t native_closedir(duk_context*ctx){
	if(
		duk_has_prop_string(ctx,0,"dirp")
	){
		(void*)duk_get_prop_string(ctx,0,"dirp");
		DIR*dirp=(DIR*)duk_to_pointer(ctx,-1);
		duk_push_int(ctx,readdir(dirp));
	}else{
		fprintf(stderr,"Error: native_closedir: Invalid properties\n");
		duk_push_null(ctx);
	}
	return 1;
}
/*! Native function dirent2json
 *  In the javascript it takes an object `{dirp:Pointer}` as argument, and will return the JSON representation of `dirent
 *  \param ctx Duktape context to run function in
 *  \return `duk_ret_t` return type
 */
static duk_ret_t native_dirent2json(duk_context*ctx){
	if(
		duk_has_prop_string(ctx,0,"dirp")
	){
		(void*)duk_get_prop_string(ctx,0,"dirp");
		struct dirent*dirp=(struct dirent*)duk_to_pointer(ctx,-1);
		duk_idx_t obj_idx=duk_push_object(ctx);
		duk_push_int(ctx,dirp->d_ino);
		duk_put_prop_string(ctx,obj_idx,"d_ino");
		duk_push_string(ctx,dirp->d_name);
		duk_put_prop_string(ctx,obj_idx,"d_name");
	}else{
		fprintf(stderr,"Error: native_readdir: Invalid properties\n");
		duk_push_null(ctx);
	}
	return 1;
}
/*
int stat (const char *filename, struct stat *buf)
*/
//---------------------------
/*! Register native function on context
 *  \return `duk_ret_t` return type
 */
void duk_register_libc(duk_context*ctx){
	//----------------------------------------
	duk_push_c_function(ctx,native_getcwd,0);
	duk_put_global_string(ctx,"getcwd");
	duk_push_c_function(ctx,native_chdir,1);
	duk_put_global_string(ctx,"chdir");
	//----------------------------------------
	//fwrite utility function
	//----------------------------------------
	duk_push_c_function(ctx,native_write,1/*nargs*/);
	duk_put_global_string(ctx,"write");
	//----------------------------------------
	//file pointers
	duk_push_pointer(ctx,stdin);
	duk_put_global_string(ctx,"stdin");
	duk_push_pointer(ctx,stdout);
	duk_put_global_string(ctx,"stdout");
	duk_push_pointer(ctx,stderr);
	duk_put_global_string(ctx,"stderr");
	//EOF etc
	duk_push_int(ctx,EOF);
	duk_put_global_string(ctx,"EOF");
	//file positioning
	duk_push_int(ctx,SEEK_SET);
	duk_put_global_string(ctx,"SEEK_SET");
	duk_push_int(ctx,SEEK_CUR);
	duk_put_global_string(ctx,"SEEK_CUR");
	duk_push_int(ctx,SEEK_END);
	duk_put_global_string(ctx,"SEEK_END");
	//constants - sys/stat.h
	duk_push_int(ctx,S_IRWXU);
	duk_put_global_string(ctx,"S_IRWXU");
	duk_push_int(ctx,S_IRUSR);
	duk_put_global_string(ctx,"S_IRUSR");
	duk_push_int(ctx,S_IWUSR);
	duk_put_global_string(ctx,"S_IWUSR");
	duk_push_int(ctx,S_IXUSR);
	duk_put_global_string(ctx,"S_IXUSR");
	duk_push_int(ctx,S_IRWXG);
	duk_put_global_string(ctx,"S_IRWXG");
	duk_push_int(ctx,S_IRGRP);
	duk_put_global_string(ctx,"S_IRGRP");
	duk_push_int(ctx,S_IWGRP);
	duk_put_global_string(ctx,"S_IWGRP");
	duk_push_int(ctx,S_IXGRP);
	duk_put_global_string(ctx,"S_IXGRP");
	duk_push_int(ctx,S_IRWXO);
	duk_put_global_string(ctx,"S_IRWXO");
	duk_push_int(ctx,S_IROTH);
	duk_put_global_string(ctx,"S_IROTH");
	duk_push_int(ctx,S_IWOTH);
	duk_put_global_string(ctx,"S_IWOTH");
	duk_push_int(ctx,S_IXOTH);
	duk_put_global_string(ctx,"S_IXOTH");
	//duk_push_int(ctx,S_ISUID);		// not in windows???
	//duk_put_global_string(ctx,"S_ISUID");	// not in windows???
	//duk_push_int(ctx,S_ISGID);		// not in windows???
	//duk_put_global_string(ctx,"S_ISGID");	// not in windows???
	//----------------------------------------
	duk_push_c_function(ctx,native_fopen,2);
	duk_put_global_string(ctx,"fopen");
	duk_push_c_function(ctx,native_fclose,2);
	duk_put_global_string(ctx,"fclose");
	duk_push_c_function(ctx,native_fread,4);
	duk_put_global_string(ctx,"fread");
	duk_push_c_function(ctx,native_fwrite,4);
	duk_put_global_string(ctx,"fwrite");
	//----------------------------------------
	duk_push_c_function(ctx,native_ftell,1);
	duk_put_global_string(ctx,"ftell");
	duk_push_c_function(ctx,native_fseek,1);
	duk_put_global_string(ctx,"fseek");
	duk_push_c_function(ctx,native_fgetpos,1);
	duk_put_global_string(ctx,"fgetpos");
	duk_push_c_function(ctx,native_rewind,1);
	duk_put_global_string(ctx,"rewind");
	duk_push_c_function(ctx,native_stat,1);
	duk_put_global_string(ctx,"stat");
	duk_push_c_function(ctx,native_fstat,1);
	duk_put_global_string(ctx,"fstat");
	duk_push_c_function(ctx,native_fileno,1);
	duk_put_global_string(ctx,"fileno");
	//----------------------------------------
#ifndef _WIN32
	duk_push_c_function(ctx,native_fdopendir,1);
	duk_put_global_string(ctx,"fdopendir");
#endif
	duk_push_c_function(ctx,native_opendir,1);
	duk_put_global_string(ctx,"opendir");
	duk_push_c_function(ctx,native_readdir,1);
	duk_put_global_string(ctx,"readdir");
	duk_push_c_function(ctx,native_closedir,1);
	duk_put_global_string(ctx,"closedir");
	duk_push_c_function(ctx,native_dirent2json,1);
	duk_put_global_string(ctx,"dirent2json");
	//----------------------------------------
}