/*!@file duk/sqlite.c
 * @brief Various sqlite native functions to expose to Duktape
 */
#include"duktape/sqlite.h"
#include<sqlite.h>
//---------------------------
/*! Native sqlite open
 *  *Has to be reworked to take an object and modify obj.db and set it to a pointer
 *  reference: https://github.com/svaarala/duktape/issues/219
 *  reference: https://stackoverflow.com/questions/38686495/how-to-add-modify-or-delete-a-property-of-an-object-in-duktape
 *  Will return an integer, which you can compare to SQLITE_ERROR and so on
 *  Since we cannot pass in variables by reference, for now we pass in a `String`
 *  that will be populated in the caller context with the `sqlite3`
 *  \return `duk_ret_t` return type
 */

static duk_ret_t native_sqlite3_open(duk_context*ctx){
	char*dbpath=duk_to_string(ctx,0);
	fprintf(stderr,"Info: opening %s...\n",dbpath);
	sqlite3*db;
	int rc=sqlite3_open(dbpath,&db);
	char*dbkey=duk_to_string(ctx,1);
	//push db pointer onto caller context
	duk_push_pointer(ctx,(void*)db);
	duk_put_global_string(ctx,dbkey);
	duk_push_int(ctx,rc);
	//push db pointer onto caller context
	/*
	duk_push_global_object(ctx);
	duk_dup(ctx, 0); 
	duk_push_pointer(ctx, 2); 
	duk_put_prop(ctx, -3); 
	*/
	return 1;
}

/*! Native function
 *  \param ctx Duktape context to run function in
 *  \return `duk_ret_t` return type
 */
static duk_ret_t native_sqlite3_close(duk_context*ctx){
	sqlite3_close(duk_to_string(ctx,0));
	return 0;
}
/*
int sqlite3_prepare_v2(
  sqlite3 *db,            // Database handle 
  const char *zSql,       // SQL statement, UTF-8 encoded 
  int nByte,              // Maximum length of zSql in bytes. 
  sqlite3_stmt **ppStmt,  // OUT: Statement handle 
  const char **pzTail     // OUT: Pointer to unused portion of zSql 
);
*/
/*! Native function
 *  \param ctx Duktape context to run function in
 *  \return `duk_ret_t` return type
 */
static duk_ret_t native_sqlite3_prepare_v2(duk_context*ctx){
	sqlite3_stmt*res;
	int rc=sqlite3_prepare_v2(
		duk_to_pointer(ctx,0),
		duk_to_string(ctx,1),
		-1,//duk_to_int(ctx,2),
		&res,
		0
	);
	char*dbkey=duk_to_string(ctx,2);
	duk_push_pointer(ctx,(void*)res);
	duk_put_global_string(ctx,dbkey);
	duk_push_int(ctx,rc);
	return 1;
}
/*! Native function
 *  \param ctx Duktape context to run function in
 *  \return `duk_ret_t` return type
 */
static duk_ret_t native_sqlite3_step(duk_context*ctx){
	//fprintf(stderr,"Info: native_sqlite3_step: start\n");
	duk_push_int(ctx,sqlite3_step((sqlite3_stmt*)duk_to_pointer(ctx,0)));
	//fprintf(stderr,"Info: native_sqlite3_step: end\n");
	return 1;
}
/*! Native function
 *  \param ctx Duktape context to run function in
 *  \return `duk_ret_t` return type
 */
static duk_ret_t native_sqlite3_errmsg(duk_context*ctx){
	duk_push_string(ctx,sqlite3_errmsg(duk_to_pointer(ctx,0)));
	return 1;
}
//int sqlite3_finalize(sqlite3_stmt *pStmt);
/*! Native function
 *  \param ctx Duktape context to run function in
 *  \return `duk_ret_t` return type
 */
static duk_ret_t native_sqlite3_finalize(duk_context*ctx){
	duk_push_int(ctx,sqlite3_finalize((sqlite3_stmt*)duk_to_pointer(ctx,0)));
	return 1;
}
//int sqlite3_reset(sqlite3_stmt *pStmt);
/*! Native function
 *  \param ctx Duktape context to run function in
 *  \return `duk_ret_t` return type
 */
static duk_ret_t native_sqlite3_reset(duk_context*ctx){
	duk_push_int(ctx,sqlite3_reset((sqlite3_stmt*)duk_to_pointer(ctx,0)));
	return 1;
}
/*! Native function
 *  \param ctx Duktape context to run function in
 *  \return `duk_ret_t` return type
 */
static duk_ret_t native_sqlite3_column_count(duk_context*ctx){
	//fprintf(stderr,"Info: native_sqlite3_column_count: start\n");
	duk_push_int(ctx,sqlite3_column_count((sqlite3_stmt*)duk_to_pointer(ctx,0)));
	//fprintf(stderr,"Info: native_sqlite3_column_count: end\n");
	return 1;
}
/*! Native function
 *  \param ctx Duktape context to run function in
 *  \return `duk_ret_t` return type
 */
static duk_ret_t native_sqlite3_column_text(duk_context*ctx){
	//fprintf(stderr,"Info: native_sqlite3_column_text: start\n");
	duk_push_string(
		ctx,sqlite3_column_text(
			(sqlite3_stmt*)duk_to_pointer(ctx,0),
			duk_to_int(ctx,1)
		)
	);
	//fprintf(stderr,"Info: native_sqlite3_column_text: end\n");
	return 1;
}
/*
static duk_ret_t native_sqlite3_column_blob(duk_context*ctx){
	//fprintf(stderr,"Info: native_sqlite3_column_blob: start\n");
	duk_push_(
		ctx,sqlite3_column_blob(
			(sqlite3_stmt*)duk_to_pointer(ctx,0),
			duk_to_int(ctx,1)
		)
	);
	//fprintf(stderr,"Info: native_sqlite3_column_blob: end\n");
	return 1;
}
*/
/*! Native function
 *  \param ctx Duktape context to run function in
 *  \return `duk_ret_t` return type
 */
static duk_ret_t native_sqlite3_column_double(duk_context*ctx){
	//fprintf(stderr,"Info: native_sqlite3_column_double: start\n");
	duk_push_number(
		ctx,sqlite3_column_double(
			(sqlite3_stmt*)duk_to_pointer(ctx,0),
			duk_to_int(ctx,1)
		)
	);
	//fprintf(stderr,"Info: native_sqlite3_column_double: end\n");
	return 1;
}
/*! Native function
 *  \param ctx Duktape context to run function in
 *  \return `duk_ret_t` return type
 */
static duk_ret_t native_sqlite3_column_int(duk_context*ctx){
	//fprintf(stderr,"Info: native_sqlite3_column_int: start\n");
	duk_push_number(
		ctx,sqlite3_column_int(
			(sqlite3_stmt*)duk_to_pointer(ctx,0),
			duk_to_int(ctx,1)
		)
	);
	//fprintf(stderr,"Info: native_sqlite3_column_int: end\n");
	return 1;
}
/*! Native function
 *  \param ctx Duktape context to run function in
 *  \return `duk_ret_t` return type
 */
static duk_ret_t native_sqlite3_column_int64(duk_context*ctx){
	//fprintf(stderr,"Info: native_sqlite3_column_int64: start\n");
	duk_push_int(
		ctx,sqlite3_column_int64(
			(sqlite3_stmt*)duk_to_pointer(ctx,0),
			duk_to_int(ctx,1)
		)
	);
	//fprintf(stderr,"Info: native_sqlite3_column_int64: end\n");
	return 1;
}
/*! Native function
 *  \param ctx Duktape context to run function in
 *  \return `duk_ret_t` return type
 */
static duk_ret_t native_sqlite3_column_text16(duk_context*ctx){
	//fprintf(stderr,"Info: native_sqlite3_column_text16: start\n");
	duk_push_string(
		ctx,sqlite3_column_text16(
			(sqlite3_stmt*)duk_to_pointer(ctx,0),
			duk_to_int(ctx,1)
		)
	);
	//fprintf(stderr,"Info: native_sqlite3_column_text16: end\n");
	return 1;
}
/*
static duk_ret_t native_sqlite3_column_value(duk_context*ctx){
	//fprintf(stderr,"Info: native_sqlite3_column_value: start\n");
	duk_push_(
		ctx,sqlite3_column_value(
			(sqlite3_stmt*)duk_to_pointer(ctx,0),
			duk_to_int(ctx,1)
		)
	);
	//fprintf(stderr,"Info: native_sqlite3_column_value: end\n");
	return 1;
}
static duk_ret_t native_sqlite3_column_bytes(duk_context*ctx){
	//fprintf(stderr,"Info: native_sqlite3_column_bytes: start\n");
	duk_push_(
		ctx,sqlite3_column_bytes(
			(sqlite3_stmt*)duk_to_pointer(ctx,0),
			duk_to_int(ctx,1)
		)
	);
	//fprintf(stderr,"Info: native_sqlite3_column_bytes: end\n");
	return 1;
}
static duk_ret_t native_sqlite3_column_bytes16(duk_context*ctx){
	//fprintf(stderr,"Info: native_sqlite3_column_bytes16: start\n");
	duk_push_(
		ctx,sqlite3_column_bytes16(
			(sqlite3_stmt*)duk_to_pointer(ctx,0),
			duk_to_int(ctx,1)
		)
	);
	//fprintf(stderr,"Info: native_sqlite3_column_bytes16: end\n");
	return 1;
}
*/
//sqlite3_column_type() â€” Get the datatype of a result column
//SQLITE_INTEGER, SQLITE_FLOAT, SQLITE_TEXT, SQLITE_BLOB, or SQLITE_NULL
/*! Native function
 *  \param ctx Duktape context to run function in
 *  \return `duk_ret_t` return type
 */
static duk_ret_t native_sqlite3_column_type(duk_context*ctx){
	//fprintf(stderr,"Info: native_sqlite3_column_type: start\n");
	duk_push_int(
		ctx,sqlite3_column_type(
			(sqlite3_stmt*)duk_to_pointer(ctx,0),
			duk_to_int(ctx,1)
		)
	);
	//fprintf(stderr,"Info: native_sqlite3_column_type: end\n");
	return 1;
}
//https://www.sqlite.org/c3ref/column_name.html
//const char *sqlite3_column_name(sqlite3_stmt*, int N);
/*! Native function
 *  \param ctx Duktape context to run function in
 *  \return `duk_ret_t` return type
 */
static duk_ret_t native_sqlite3_column_name(duk_context*ctx){
	//fprintf(stderr,"Info: native_sqlite3_column_name: start\n");
	duk_push_string(
		ctx,sqlite3_column_name(
			(sqlite3_stmt*)duk_to_pointer(ctx,0),
			duk_to_int(ctx,1)
		)
	);
	//fprintf(stderr,"Info: native_sqlite3_column_name: end\n");
	return 1;
}
//https://www.sqlite.org/c3ref/value_blob.html
/*! Native function
 *  \param ctx Duktape context to run function in
 *  \return `duk_ret_t` return type
 */
static duk_ret_t native_sqlite3_value_bytes(duk_context*ctx){
	//fprintf(stderr,"Info: native_sqlite3_value_bytes: start\n");
	duk_push_int(
		ctx,sqlite3_value_bytes(
			(sqlite3_value*)duk_to_pointer(ctx,0)
		)
	);
	//fprintf(stderr,"Info: native_sqlite3_value_bytes: end\n");
	return 1;
}
/*! Native function
 *  \param ctx Duktape context to run function in
 *  \return `duk_ret_t` return type
 */
static duk_ret_t native_sqlite3_value_bytes16(duk_context*ctx){
	//fprintf(stderr,"Info: native_sqlite3_value_bytes16: start\n");
	duk_push_int(
		ctx,sqlite3_value_bytes16(
			(sqlite3_value*)duk_to_pointer(ctx,0)
		)
	);
	//fprintf(stderr,"Info: native_sqlite3_value_bytes16: end\n");
	return 1;
}
/*! Native function
 *  \param ctx Duktape context to run function in
 *  \return `duk_ret_t` return type
 */
static duk_ret_t native_sqlite3_value_type(duk_context*ctx){
	//fprintf(stderr,"Info: native_sqlite3_value_type: start\n");
	duk_push_int(
		ctx,sqlite3_value_type(
			(sqlite3_value*)duk_to_pointer(ctx,0)
		)
	);
	//fprintf(stderr,"Info: native_sqlite3_value_type: end\n");
	return 1;
}
/*! Native function
 *  \param ctx Duktape context to run function in
 *  \return `duk_ret_t` return type
 */
static duk_ret_t native_sqlite3_value_numeric_type(duk_context*ctx){
	//fprintf(stderr,"Info: native_: start\n");
	duk_push_int(
		ctx,sqlite3_value_numeric_type(
			(sqlite3_value*)duk_to_pointer(ctx,0)
		)
	);
	//fprintf(stderr,"Info: native_sqlite3_value_numeric_type: end\n");
	return 1;
}
/*! Native function
 *  \param ctx Duktape context to run function in
 *  \return `duk_ret_t` return type
 */
static duk_ret_t native_sqlite3_value_nochange(duk_context*ctx){
	//fprintf(stderr,"Info: native_sqlite3_value_nochange: start\n");
	duk_push_int(
		ctx,sqlite3_value_nochange(
			(sqlite3_value*)duk_to_pointer(ctx,0)
		)
	);
	//fprintf(stderr,"Info: native_sqlite3_value_nochange: end\n");
	return 1;
}
/*! Native function
 *  \param ctx Duktape context to run function in
 *  \return `duk_ret_t` return type
 */
static duk_ret_t native_sqlite3_value_frombind(duk_context*ctx){
	//fprintf(stderr,"Info: native_sqlite3_value_frombind: start\n");
	duk_push_int(
		ctx,sqlite3_value_frombind(
			(sqlite3_value*)duk_to_pointer(ctx,0)
		)
	);
	//fprintf(stderr,"Info: native_sqlite3_column_type: end\n");
	return 1;
}
//--------------------------------------------------------------------------------
//prepared statement binding functions
//--------------------------------------------------------------------------------
//https://stackoverflow.com/questions/31745465/how-to-prepare-sql-statements-and-bind-parameters

//int sqlite3_bind_blob(sqlite3_stmt*, int, const void*, int n, void(*)(void*));
/*! Native function
 *  \param ctx Duktape context to run function in
 *  \return `duk_ret_t` return type
 */
static duk_ret_t native_sqlite3_bind_blob(duk_context*ctx){
	//fprintf(stderr,"Info: native_sqlite3_bind_blob: start\n");
	duk_push_int(
		ctx,
		sqlite3_bind_blob(
			(sqlite3_stmt*)duk_to_pointer(ctx,0),
			duk_to_int(ctx,1),
			0,//duk_to_buffer(ctx,0),//buffer
			0,//buffer length
			0//callback?
		)
	);
	//fprintf(stderr,"Info: native_sqlite3_bind_blob: end\n");
	return 1;
}
//int sqlite3_bind_blob64(sqlite3_stmt*, int, const void*, sqlite3_uint64,void(*)(void*));
/*! Native function
 *  \param ctx Duktape context to run function in
 *  \return `duk_ret_t` return type
 */
static duk_ret_t native_sqlite3_bind_blob64(duk_context*ctx){
	//fprintf(stderr,"Info: native_: start\n");
	duk_push_int(
		ctx,
		sqlite3_bind_blob64(
			(sqlite3_stmt*)duk_to_pointer(ctx,0),
			duk_to_int(ctx,1),
			0,//buffer
			duk_to_uint32(ctx,2),
			0//callback?
		)
	);
	//fprintf(stderr,"Info: native_: end\n");
	return 1;
}
//int sqlite3_bind_double(sqlite3_stmt*, int, double);
/*! Native function
 *  \param ctx Duktape context to run function in
 *  \return `duk_ret_t` return type
 */
static duk_ret_t native_sqlite3_bind_double(duk_context*ctx){
	//fprintf(stderr,"Info: native_sqlite3_bind_double: start\n");
	duk_push_number(
		ctx,
		(
			(sqlite3_stmt*)duk_to_pointer(ctx,0),
			duk_to_int(ctx,1),
			duk_to_number(ctx,2)
		)
	);
	//fprintf(stderr,"Info: native_sqlite3_bind_double: end\n");
	return 1;
}
//int sqlite3_bind_int(sqlite3_stmt*, int, int);
/*! Native function
 *  \param ctx Duktape context to run function in
 *  \return `duk_ret_t` return type
 */
static duk_ret_t native_sqlite3_bind_int(duk_context*ctx){
	//fprintf(stderr,"Info: native_sqlite3_bind_int: start\n");
	duk_push_int(
		ctx,
		sqlite3_bind_int(
			(sqlite3_stmt*)duk_to_pointer(ctx,0),
			duk_to_int(ctx,1),
			duk_to_int(ctx,2)
		)
	);
	//fprintf(stderr,"Info: native_sqlite3_bind_int: end\n");
	return 1;
}
//int sqlite3_bind_int64(sqlite3_stmt*, int, sqlite3_int64);
/*! Native function
 *  \param ctx Duktape context to run function in
 *  \return `duk_ret_t` return type
 */
static duk_ret_t native_sqlite3_bind_int64(duk_context*ctx){
	//fprintf(stderr,"Info: native_sqlite3_bind_int64: start\n");
	duk_push_int(
		ctx,
		sqlite3_bind_int64(
			(sqlite3_stmt*)duk_to_pointer(ctx,0),
			duk_to_int(ctx,1),//64??
			duk_to_int32(ctx,2)//64??
		)
	);
	//fprintf(stderr,"Info: native_sqlite3_bind_int64: end\n");
	return 1;
}
//int sqlite3_bind_null(sqlite3_stmt*, int);
/*! Native function
 *  \param ctx Duktape context to run function in
 *  \return `duk_ret_t` return type
 */
static duk_ret_t native_sqlite3_bind_null(duk_context*ctx){
	//fprintf(stderr,"Info: native_sqlite3_bind_null: start\n");
	duk_push_int(
		ctx,
		sqlite3_bind_null(
			(sqlite3_stmt*)duk_to_pointer(ctx,0),
			duk_to_int(ctx,1)
		)
	);
	//fprintf(stderr,"Info: native_sqlite3_bind_null: end\n");
	return 1;
}
//int sqlite3_bind_text(sqlite3_stmt*,int,const char*,int,void(*)(void*));
/*! Native function
 *  \param ctx Duktape context to run function in
 *  \return `duk_ret_t` return type
 */
static duk_ret_t native_sqlite3_bind_text(duk_context*ctx){
	//fprintf(stderr,"Info: native_sqlite3_bind_text: start\n");
	duk_push_int(
		ctx,
		sqlite3_bind_text(
			(sqlite3_stmt*)duk_to_pointer(ctx,0),
			duk_to_int(ctx,1),
			duk_to_string(ctx,2),
			duk_to_int(ctx,3),
			0//callback???
		)
	);
	//fprintf(stderr,"Info: native_sqlite3_bind_text: end\n");
	return 1;
}
//int sqlite3_bind_text16(sqlite3_stmt*, int, const void*, int, void(*)(void*));
/*! Native function
 *  \param ctx Duktape context to run function in
 *  \return `duk_ret_t` return type
 */
static duk_ret_t native_sqlite3_bind_text16(duk_context*ctx){
	//fprintf(stderr,"Info: native_sqlite3_bind_text16: start\n");
	duk_push_int(
		ctx,
		sqlite3_bind_text16(
			(sqlite3_stmt*)duk_to_pointer(ctx,0),
			duk_to_int(ctx,1),
			0,//userdata???
			0,//???
			0//callback???
		)
	);
	//fprintf(stderr,"Info: native_sqlite3_bind_text16: end\n");
	return 1;
}
//int sqlite3_bind_text64(sqlite3_stmt*, int, const char*, sqlite3_uint64,void(*)(void*), unsigned char encoding);
/*! Native function
 *  \param ctx Duktape context to run function in
 *  \return `duk_ret_t` return type
 */
static duk_ret_t native_sqlite3_bind_text64(duk_context*ctx){
	//fprintf(stderr,"Info: native_sqlite3_bind_text64: start\n");
	duk_push_int(
		ctx,
		sqlite3_bind_text64(
			(sqlite3_stmt*)duk_to_pointer(ctx,0),
			duk_to_int(ctx,1),
			(const char*)duk_to_pointer(ctx,2),
			duk_to_int32(ctx,3),//64?
			0,//callback?
			duk_to_uint(ctx,4)//unsigned char???
		)
	);
	//fprintf(stderr,"Info: native_sqlite3_bind_text64: end\n");
	return 1;
}
/*
//int sqlite3_bind_value(sqlite3_stmt*, int, const sqlite3_value*);
static duk_ret_t native_sqlite3_bind_value(duk_context*ctx){
	//fprintf(stderr,"Info: native_sqlite3_bind_value: start\n");
	duk_push_int(
		ctx,
		sqlite3_bind_value(
			(sqlite3_stmt*)duk_to_pointer(ctx,0),
			duk_to_int(ctx,0),
			???
		)
	);
	//fprintf(stderr,"Info: native_sqlite3_bind_value: end\n");
	return 1;
}
*/
//int sqlite3_bind_pointer(sqlite3_stmt*, int, void*, const char*,void(*)(void*));
/*! Native function
 *  \param ctx Duktape context to run function in
 *  \return `duk_ret_t` return type
 */
static duk_ret_t native_sqlite3_bind_pointer(duk_context*ctx){
	//fprintf(stderr,"Info: native_sqlite3_bind_pointer: start\n");
	duk_push_int(
		ctx,
		(
			(sqlite3_stmt*)duk_to_pointer(ctx,0),
			duk_to_int(ctx,1),
			(void*)duk_to_pointer(ctx,2)
		)
	);
	//fprintf(stderr,"Info: native_sqlite3_bind_pointer: end\n");
	return 1;
}
//int sqlite3_bind_zeroblob(sqlite3_stmt*, int, int n);
/*! Native function
 *  \param ctx Duktape context to run function in
 *  \return `duk_ret_t` return type
 */
static duk_ret_t native_sqlite3_bind_zeroblob(duk_context*ctx){
	//fprintf(stderr,"Info: native_sqlite3_bind_zeroblob: start\n");
	duk_push_int(
		ctx,
		sqlite3_bind_zeroblob(
			(sqlite3_stmt*)duk_to_pointer(ctx,0),
			duk_to_int(ctx,1),
			duk_to_int(ctx,2)
		)
	);
	//fprintf(stderr,"Info: native_sqlite3_bind_zeroblob: end\n");
	return 1;
}
//int sqlite3_bind_zeroblob64(sqlite3_stmt*, int, sqlite3_uint64);
/*! Native function
 *  \param ctx Duktape context to run function in
 *  \return `duk_ret_t` return type
 */
static duk_ret_t native_sqlite3_bind_zeroblob64(duk_context*ctx){
	//fprintf(stderr,"Info: native_sqlite3_bind_zeroblob64: start\n");
	duk_push_int(
		ctx,
		sqlite3_bind_zeroblob64(
			(sqlite3_stmt*)duk_to_pointer(ctx,0),
			duk_to_int(ctx,1),
			duk_to_int32(ctx,2)//64???
		)
	);
	//fprintf(stderr,"Info: native_sqlite3_bind_zeroblob64: end\n");
	return 1;
}
//-------------
/*
https://www.sqlite.org/c3ref/exec.html
int sqlite3_exec(
  sqlite3*,                                  // An open database 
  const char *sql,                           // SQL to be evaluated 
  int (*callback)(void*,int,char**,char**),  // Callback function 
  void *,                                    // 1st argument to callback 
  char **errmsg                              // Error msg written here 
);
*/
/*! Native function
 *  \param ctx Duktape context to run function in
 *  \return `duk_ret_t` return type
 */
static duk_ret_t native_sqlite3_exec(duk_context*ctx){
	fprintf(stderr,"Info: native_sqlite3_exec: start\n");
	int rc=sqlite3_exec(
		(sqlite3*)duk_to_pointer(ctx,0),
		duk_to_string(ctx,1),
		0,//callback
		0,//callback userdata
		0//errors
	);
	duk_push_int(ctx,rc);
	fprintf(stderr,"Info: native_sqlite3_exec: end\n");
	return 1;
}
/*! Register native function on context
 *  \return `duk_ret_t` return type
 */
void duk_register_sqlite(duk_context*ctx){
	//--------------------------------------------------------------------------------
	//constants - https://www.sqlite.org/c3ref/constlist.html
	duk_push_int(ctx,SQLITE_ABORT);
	duk_put_global_string(ctx,"SQLITE_ABORT");
	duk_push_int(ctx,SQLITE_ABORT_ROLLBACK);
	duk_put_global_string(ctx,"SQLITE_ABORT_ROLLBACK");
	duk_push_int(ctx,SQLITE_ACCESS_EXISTS);
	duk_put_global_string(ctx,"SQLITE_ACCESS_EXISTS");
	duk_push_int(ctx,SQLITE_ACCESS_READ);
	duk_put_global_string(ctx,"SQLITE_ACCESS_READ");
	duk_push_int(ctx,SQLITE_ACCESS_READWRITE);
	duk_put_global_string(ctx,"SQLITE_ACCESS_READWRITE");
	duk_push_int(ctx,SQLITE_ALTER_TABLE);
	duk_put_global_string(ctx,"SQLITE_ALTER_TABLE");
	duk_push_int(ctx,SQLITE_ANALYZE);
	duk_put_global_string(ctx,"SQLITE_ANALYZE");
	duk_push_int(ctx,SQLITE_ANY);
	duk_put_global_string(ctx,"SQLITE_ANY");
	duk_push_int(ctx,SQLITE_ATTACH);
	duk_put_global_string(ctx,"SQLITE_ATTACH");
	duk_push_int(ctx,SQLITE_AUTH);
	duk_put_global_string(ctx,"SQLITE_AUTH");
	duk_push_int(ctx,SQLITE_AUTH_USER);
	duk_put_global_string(ctx,"SQLITE_AUTH_USER");
	duk_push_int(ctx,SQLITE_BLOB);
	duk_put_global_string(ctx,"SQLITE_BLOB");
	duk_push_int(ctx,SQLITE_BUSY);
	duk_put_global_string(ctx,"SQLITE_BUSY");
	duk_push_int(ctx,SQLITE_BUSY_RECOVERY);
	duk_put_global_string(ctx,"SQLITE_BUSY_RECOVERY");
	duk_push_int(ctx,SQLITE_BUSY_SNAPSHOT);
	duk_put_global_string(ctx,"SQLITE_BUSY_SNAPSHOT");
	duk_push_int(ctx,SQLITE_BUSY_TIMEOUT);
	duk_put_global_string(ctx,"SQLITE_BUSY_TIMEOUT");
	duk_push_int(ctx,SQLITE_CANTOPEN);
	duk_put_global_string(ctx,"SQLITE_CANTOPEN");
	duk_push_int(ctx,SQLITE_CANTOPEN_CONVPATH);
	duk_put_global_string(ctx,"SQLITE_CANTOPEN_CONVPATH");
	duk_push_int(ctx,SQLITE_CANTOPEN_DIRTYWAL);
	duk_put_global_string(ctx,"SQLITE_CANTOPEN_DIRTYWAL");
	duk_push_int(ctx,SQLITE_CANTOPEN_FULLPATH);
	duk_put_global_string(ctx,"SQLITE_CANTOPEN_FULLPATH");
	duk_push_int(ctx,SQLITE_CANTOPEN_ISDIR);
	duk_put_global_string(ctx,"SQLITE_CANTOPEN_ISDIR");
	duk_push_int(ctx,SQLITE_CANTOPEN_NOTEMPDIR);
	duk_put_global_string(ctx,"SQLITE_CANTOPEN_NOTEMPDIR");
	duk_push_int(ctx,SQLITE_CANTOPEN_SYMLINK);
	duk_put_global_string(ctx,"SQLITE_CANTOPEN_SYMLINK");
	duk_push_int(ctx,SQLITE_CHECKPOINT_FULL);
	duk_put_global_string(ctx,"SQLITE_CHECKPOINT_FULL");
	duk_push_int(ctx,SQLITE_CHECKPOINT_PASSIVE);
	duk_put_global_string(ctx,"SQLITE_CHECKPOINT_PASSIVE");
	duk_push_int(ctx,SQLITE_CHECKPOINT_RESTART);
	duk_put_global_string(ctx,"SQLITE_CHECKPOINT_RESTART");
	duk_push_int(ctx,SQLITE_CHECKPOINT_TRUNCATE);
	duk_put_global_string(ctx,"SQLITE_CHECKPOINT_TRUNCATE");
	duk_push_int(ctx,SQLITE_CONFIG_COVERING_INDEX_SCAN);
	duk_put_global_string(ctx,"SQLITE_CONFIG_COVERING_INDEX_SCAN");
	duk_push_int(ctx,SQLITE_CONFIG_GETMALLOC);
	duk_put_global_string(ctx,"SQLITE_CONFIG_GETMALLOC");
	duk_push_int(ctx,SQLITE_CONFIG_GETMUTEX);
	duk_put_global_string(ctx,"SQLITE_CONFIG_GETMUTEX");
	duk_push_int(ctx,SQLITE_CONFIG_GETPCACHE);
	duk_put_global_string(ctx,"SQLITE_CONFIG_GETPCACHE");
	duk_push_int(ctx,SQLITE_CONFIG_GETPCACHE2);
	duk_put_global_string(ctx,"SQLITE_CONFIG_GETPCACHE2");
	duk_push_int(ctx,SQLITE_CONFIG_HEAP);
	duk_put_global_string(ctx,"SQLITE_CONFIG_HEAP");
	duk_push_int(ctx,SQLITE_CONFIG_LOG);
	duk_put_global_string(ctx,"SQLITE_CONFIG_LOG");
	duk_push_int(ctx,SQLITE_CONFIG_LOOKASIDE);
	duk_put_global_string(ctx,"SQLITE_CONFIG_LOOKASIDE");
	duk_push_int(ctx,SQLITE_CONFIG_MALLOC);
	duk_put_global_string(ctx,"SQLITE_CONFIG_MALLOC");
	duk_push_int(ctx,SQLITE_CONFIG_MEMDB_MAXSIZE);
	duk_put_global_string(ctx,"SQLITE_CONFIG_MEMDB_MAXSIZE");
	duk_push_int(ctx,SQLITE_CONFIG_MEMSTATUS);
	duk_put_global_string(ctx,"SQLITE_CONFIG_MEMSTATUS");
	duk_push_int(ctx,SQLITE_CONFIG_MMAP_SIZE);
	duk_put_global_string(ctx,"SQLITE_CONFIG_MMAP_SIZE");
	duk_push_int(ctx,SQLITE_CONFIG_MULTITHREAD);
	duk_put_global_string(ctx,"SQLITE_CONFIG_MULTITHREAD");
	duk_push_int(ctx,SQLITE_CONFIG_MUTEX);
	duk_put_global_string(ctx,"SQLITE_CONFIG_MUTEX");
	duk_push_int(ctx,SQLITE_CONFIG_PAGECACHE);
	duk_put_global_string(ctx,"SQLITE_CONFIG_PAGECACHE");
	duk_push_int(ctx,SQLITE_CONFIG_PCACHE);
	duk_put_global_string(ctx,"SQLITE_CONFIG_PCACHE");
	duk_push_int(ctx,SQLITE_CONFIG_PCACHE2);
	duk_put_global_string(ctx,"SQLITE_CONFIG_PCACHE2");
	duk_push_int(ctx,SQLITE_CONFIG_PCACHE_HDRSZ);
	duk_put_global_string(ctx,"SQLITE_CONFIG_PCACHE_HDRSZ");
	duk_push_int(ctx,SQLITE_CONFIG_PMASZ);
	duk_put_global_string(ctx,"SQLITE_CONFIG_PMASZ");
	duk_push_int(ctx,SQLITE_CONFIG_SCRATCH);
	duk_put_global_string(ctx,"SQLITE_CONFIG_SCRATCH");
	duk_push_int(ctx,SQLITE_CONFIG_SERIALIZED);
	duk_put_global_string(ctx,"SQLITE_CONFIG_SERIALIZED");
	duk_push_int(ctx,SQLITE_CONFIG_SINGLETHREAD);
	duk_put_global_string(ctx,"SQLITE_CONFIG_SINGLETHREAD");
	duk_push_int(ctx,SQLITE_CONFIG_SMALL_MALLOC);
	duk_put_global_string(ctx,"SQLITE_CONFIG_SMALL_MALLOC");
	duk_push_int(ctx,SQLITE_CONFIG_SORTERREF_SIZE);
	duk_put_global_string(ctx,"SQLITE_CONFIG_SORTERREF_SIZE");
	duk_push_int(ctx,SQLITE_CONFIG_SQLLOG);
	duk_put_global_string(ctx,"SQLITE_CONFIG_SQLLOG");
	duk_push_int(ctx,SQLITE_CONFIG_STMTJRNL_SPILL);
	duk_put_global_string(ctx,"SQLITE_CONFIG_STMTJRNL_SPILL");
	duk_push_int(ctx,SQLITE_CONFIG_URI);
	duk_put_global_string(ctx,"SQLITE_CONFIG_URI");
	duk_push_int(ctx,SQLITE_CONFIG_WIN32_HEAPSIZE);
	duk_put_global_string(ctx,"SQLITE_CONFIG_WIN32_HEAPSIZE");
	duk_push_int(ctx,SQLITE_CONSTRAINT);
	duk_put_global_string(ctx,"SQLITE_CONSTRAINT");
	duk_push_int(ctx,SQLITE_CONSTRAINT_CHECK);
	duk_put_global_string(ctx,"SQLITE_CONSTRAINT_CHECK");
	duk_push_int(ctx,SQLITE_CONSTRAINT_COMMITHOOK);
	duk_put_global_string(ctx,"SQLITE_CONSTRAINT_COMMITHOOK");
	duk_push_int(ctx,SQLITE_CONSTRAINT_FOREIGNKEY);
	duk_put_global_string(ctx,"SQLITE_CONSTRAINT_FOREIGNKEY");
	duk_push_int(ctx,SQLITE_CONSTRAINT_FUNCTION);
	duk_put_global_string(ctx,"SQLITE_CONSTRAINT_FUNCTION");
	duk_push_int(ctx,SQLITE_CONSTRAINT_NOTNULL);
	duk_put_global_string(ctx,"SQLITE_CONSTRAINT_NOTNULL");
	duk_push_int(ctx,SQLITE_CONSTRAINT_PINNED);
	duk_put_global_string(ctx,"SQLITE_CONSTRAINT_PINNED");
	duk_push_int(ctx,SQLITE_CONSTRAINT_PRIMARYKEY);
	duk_put_global_string(ctx,"SQLITE_CONSTRAINT_PRIMARYKEY");
	duk_push_int(ctx,SQLITE_CONSTRAINT_ROWID);
	duk_put_global_string(ctx,"SQLITE_CONSTRAINT_ROWID");
	duk_push_int(ctx,SQLITE_CONSTRAINT_TRIGGER);
	duk_put_global_string(ctx,"SQLITE_CONSTRAINT_TRIGGER");
	duk_push_int(ctx,SQLITE_CONSTRAINT_UNIQUE);
	duk_put_global_string(ctx,"SQLITE_CONSTRAINT_UNIQUE");
	duk_push_int(ctx,SQLITE_CONSTRAINT_VTAB);
	duk_put_global_string(ctx,"SQLITE_CONSTRAINT_VTAB");
	duk_push_int(ctx,SQLITE_COPY);
	duk_put_global_string(ctx,"SQLITE_COPY");
	duk_push_int(ctx,SQLITE_CORRUPT);
	duk_put_global_string(ctx,"SQLITE_CORRUPT");
	duk_push_int(ctx,SQLITE_CORRUPT_INDEX);
	duk_put_global_string(ctx,"SQLITE_CORRUPT_INDEX");
	duk_push_int(ctx,SQLITE_CORRUPT_SEQUENCE);
	duk_put_global_string(ctx,"SQLITE_CORRUPT_SEQUENCE");
	duk_push_int(ctx,SQLITE_CORRUPT_VTAB);
	duk_put_global_string(ctx,"SQLITE_CORRUPT_VTAB");
	duk_push_int(ctx,SQLITE_CREATE_INDEX);
	duk_put_global_string(ctx,"SQLITE_CREATE_INDEX");
	duk_push_int(ctx,SQLITE_CREATE_TABLE);
	duk_put_global_string(ctx,"SQLITE_CREATE_TABLE");
	duk_push_int(ctx,SQLITE_CREATE_TEMP_INDEX);
	duk_put_global_string(ctx,"SQLITE_CREATE_TEMP_INDEX");
	duk_push_int(ctx,SQLITE_CREATE_TEMP_TABLE);
	duk_put_global_string(ctx,"SQLITE_CREATE_TEMP_TABLE");
	duk_push_int(ctx,SQLITE_CREATE_TEMP_TRIGGER);
	duk_put_global_string(ctx,"SQLITE_CREATE_TEMP_TRIGGER");
	duk_push_int(ctx,SQLITE_CREATE_TEMP_VIEW);
	duk_put_global_string(ctx,"SQLITE_CREATE_TEMP_VIEW");
	duk_push_int(ctx,SQLITE_CREATE_TRIGGER);
	duk_put_global_string(ctx,"SQLITE_CREATE_TRIGGER");
	duk_push_int(ctx,SQLITE_CREATE_VIEW);
	duk_put_global_string(ctx,"SQLITE_CREATE_VIEW");
	duk_push_int(ctx,SQLITE_CREATE_VTABLE);
	duk_put_global_string(ctx,"SQLITE_CREATE_VTABLE");
	duk_push_int(ctx,SQLITE_DBCONFIG_DEFENSIVE);
	duk_put_global_string(ctx,"SQLITE_DBCONFIG_DEFENSIVE");
	duk_push_int(ctx,SQLITE_DBCONFIG_DQS_DDL);
	duk_put_global_string(ctx,"SQLITE_DBCONFIG_DQS_DDL");
	duk_push_int(ctx,SQLITE_DBCONFIG_DQS_DML);
	duk_put_global_string(ctx,"SQLITE_DBCONFIG_DQS_DML");
	duk_push_int(ctx,SQLITE_DBCONFIG_ENABLE_FKEY);
	duk_put_global_string(ctx,"SQLITE_DBCONFIG_ENABLE_FKEY");
	duk_push_int(ctx,SQLITE_DBCONFIG_ENABLE_FTS3_TOKENIZER);
	duk_put_global_string(ctx,"SQLITE_DBCONFIG_ENABLE_FTS3_TOKENIZER");
	duk_push_int(ctx,SQLITE_DBCONFIG_ENABLE_LOAD_EXTENSION);
	duk_put_global_string(ctx,"SQLITE_DBCONFIG_ENABLE_LOAD_EXTENSION");
	duk_push_int(ctx,SQLITE_DBCONFIG_ENABLE_QPSG);
	duk_put_global_string(ctx,"SQLITE_DBCONFIG_ENABLE_QPSG");
	duk_push_int(ctx,SQLITE_DBCONFIG_ENABLE_TRIGGER);
	duk_put_global_string(ctx,"SQLITE_DBCONFIG_ENABLE_TRIGGER");
	duk_push_int(ctx,SQLITE_DBCONFIG_ENABLE_VIEW);
	duk_put_global_string(ctx,"SQLITE_DBCONFIG_ENABLE_VIEW");
	duk_push_int(ctx,SQLITE_DBCONFIG_LEGACY_ALTER_TABLE);
	duk_put_global_string(ctx,"SQLITE_DBCONFIG_LEGACY_ALTER_TABLE");
	duk_push_int(ctx,SQLITE_DBCONFIG_LEGACY_FILE_FORMAT);
	duk_put_global_string(ctx,"SQLITE_DBCONFIG_LEGACY_FILE_FORMAT");
	duk_push_int(ctx,SQLITE_DBCONFIG_LOOKASIDE);
	duk_put_global_string(ctx,"SQLITE_DBCONFIG_LOOKASIDE");
	duk_push_int(ctx,SQLITE_DBCONFIG_MAINDBNAME);
	duk_put_global_string(ctx,"SQLITE_DBCONFIG_MAINDBNAME");
	duk_push_int(ctx,SQLITE_DBCONFIG_MAX);
	duk_put_global_string(ctx,"SQLITE_DBCONFIG_MAX");
	duk_push_int(ctx,SQLITE_DBCONFIG_NO_CKPT_ON_CLOSE);
	duk_put_global_string(ctx,"SQLITE_DBCONFIG_NO_CKPT_ON_CLOSE");
	duk_push_int(ctx,SQLITE_DBCONFIG_RESET_DATABASE);
	duk_put_global_string(ctx,"SQLITE_DBCONFIG_RESET_DATABASE");
	duk_push_int(ctx,SQLITE_DBCONFIG_TRIGGER_EQP);
	duk_put_global_string(ctx,"SQLITE_DBCONFIG_TRIGGER_EQP");
	duk_push_int(ctx,SQLITE_DBCONFIG_TRUSTED_SCHEMA);
	duk_put_global_string(ctx,"SQLITE_DBCONFIG_TRUSTED_SCHEMA");
	duk_push_int(ctx,SQLITE_DBCONFIG_WRITABLE_SCHEMA);
	duk_put_global_string(ctx,"SQLITE_DBCONFIG_WRITABLE_SCHEMA");
	duk_push_int(ctx,SQLITE_DBSTATUS_CACHE_HIT);
	duk_put_global_string(ctx,"SQLITE_DBSTATUS_CACHE_HIT");
	duk_push_int(ctx,SQLITE_DBSTATUS_CACHE_MISS);
	duk_put_global_string(ctx,"SQLITE_DBSTATUS_CACHE_MISS");
	duk_push_int(ctx,SQLITE_DBSTATUS_CACHE_SPILL);
	duk_put_global_string(ctx,"SQLITE_DBSTATUS_CACHE_SPILL");
	duk_push_int(ctx,SQLITE_DBSTATUS_CACHE_USED);
	duk_put_global_string(ctx,"SQLITE_DBSTATUS_CACHE_USED");
	duk_push_int(ctx,SQLITE_DBSTATUS_CACHE_USED_SHARED);
	duk_put_global_string(ctx,"SQLITE_DBSTATUS_CACHE_USED_SHARED");
	duk_push_int(ctx,SQLITE_DBSTATUS_CACHE_WRITE);
	duk_put_global_string(ctx,"SQLITE_DBSTATUS_CACHE_WRITE");
	duk_push_int(ctx,SQLITE_DBSTATUS_DEFERRED_FKS);
	duk_put_global_string(ctx,"SQLITE_DBSTATUS_DEFERRED_FKS");
	duk_push_int(ctx,SQLITE_DBSTATUS_LOOKASIDE_HIT);
	duk_put_global_string(ctx,"SQLITE_DBSTATUS_LOOKASIDE_HIT");
	duk_push_int(ctx,SQLITE_DBSTATUS_LOOKASIDE_MISS_FULL);
	duk_put_global_string(ctx,"SQLITE_DBSTATUS_LOOKASIDE_MISS_FULL");
	duk_push_int(ctx,SQLITE_DBSTATUS_LOOKASIDE_MISS_SIZE);
	duk_put_global_string(ctx,"SQLITE_DBSTATUS_LOOKASIDE_MISS_SIZE");
	duk_push_int(ctx,SQLITE_DBSTATUS_LOOKASIDE_USED);
	duk_put_global_string(ctx,"SQLITE_DBSTATUS_LOOKASIDE_USED");
	duk_push_int(ctx,SQLITE_DBSTATUS_MAX);
	duk_put_global_string(ctx,"SQLITE_DBSTATUS_MAX");
	duk_push_int(ctx,SQLITE_DBSTATUS_SCHEMA_USED);
	duk_put_global_string(ctx,"SQLITE_DBSTATUS_SCHEMA_USED");
	duk_push_int(ctx,SQLITE_DBSTATUS_STMT_USED);
	duk_put_global_string(ctx,"SQLITE_DBSTATUS_STMT_USED");
	duk_push_int(ctx,SQLITE_DELETE);
	duk_put_global_string(ctx,"SQLITE_DELETE");
	duk_push_int(ctx,SQLITE_DENY);
	duk_put_global_string(ctx,"SQLITE_DENY");
	duk_push_int(ctx,SQLITE_DESERIALIZE_FREEONCLOSE);
	duk_put_global_string(ctx,"SQLITE_DESERIALIZE_FREEONCLOSE");
	duk_push_int(ctx,SQLITE_DESERIALIZE_READONLY);
	duk_put_global_string(ctx,"SQLITE_DESERIALIZE_READONLY");
	duk_push_int(ctx,SQLITE_DESERIALIZE_RESIZEABLE);
	duk_put_global_string(ctx,"SQLITE_DESERIALIZE_RESIZEABLE");
	duk_push_int(ctx,SQLITE_DETACH);
	duk_put_global_string(ctx,"SQLITE_DETACH");
	duk_push_int(ctx,SQLITE_DETERMINISTIC);
	duk_put_global_string(ctx,"SQLITE_DETERMINISTIC");
	duk_push_int(ctx,SQLITE_DIRECTONLY);
	duk_put_global_string(ctx,"SQLITE_DIRECTONLY");
	duk_push_int(ctx,SQLITE_DONE);
	duk_put_global_string(ctx,"SQLITE_DONE");
	duk_push_int(ctx,SQLITE_DROP_INDEX);
	duk_put_global_string(ctx,"SQLITE_DROP_INDEX");
	duk_push_int(ctx,SQLITE_DROP_TABLE);
	duk_put_global_string(ctx,"SQLITE_DROP_TABLE");
	duk_push_int(ctx,SQLITE_DROP_TEMP_INDEX);
	duk_put_global_string(ctx,"SQLITE_DROP_TEMP_INDEX");
	duk_push_int(ctx,SQLITE_DROP_TEMP_TABLE);
	duk_put_global_string(ctx,"SQLITE_DROP_TEMP_TABLE");
	duk_push_int(ctx,SQLITE_DROP_TEMP_TRIGGER);
	duk_put_global_string(ctx,"SQLITE_DROP_TEMP_TRIGGER");
	duk_push_int(ctx,SQLITE_DROP_TEMP_VIEW);
	duk_put_global_string(ctx,"SQLITE_DROP_TEMP_VIEW");
	duk_push_int(ctx,SQLITE_DROP_TRIGGER);
	duk_put_global_string(ctx,"SQLITE_DROP_TRIGGER");
	duk_push_int(ctx,SQLITE_DROP_VIEW);
	duk_put_global_string(ctx,"SQLITE_DROP_VIEW");
	duk_push_int(ctx,SQLITE_DROP_VTABLE);
	duk_put_global_string(ctx,"SQLITE_DROP_VTABLE");
	duk_push_int(ctx,SQLITE_EMPTY);
	duk_put_global_string(ctx,"SQLITE_EMPTY");
	duk_push_int(ctx,SQLITE_ERROR);
	duk_put_global_string(ctx,"SQLITE_ERROR");
	duk_push_int(ctx,SQLITE_ERROR_MISSING_COLLSEQ);
	duk_put_global_string(ctx,"SQLITE_ERROR_MISSING_COLLSEQ");
	duk_push_int(ctx,SQLITE_ERROR_RETRY);
	duk_put_global_string(ctx,"SQLITE_ERROR_RETRY");
	duk_push_int(ctx,SQLITE_ERROR_SNAPSHOT);
	duk_put_global_string(ctx,"SQLITE_ERROR_SNAPSHOT");
	duk_push_int(ctx,SQLITE_FAIL);
	duk_put_global_string(ctx,"SQLITE_FAIL");
	duk_push_int(ctx,SQLITE_FCNTL_BEGIN_ATOMIC_WRITE);
	duk_put_global_string(ctx,"SQLITE_FCNTL_BEGIN_ATOMIC_WRITE");
	duk_push_int(ctx,SQLITE_FCNTL_BUSYHANDLER);
	duk_put_global_string(ctx,"SQLITE_FCNTL_BUSYHANDLER");
	duk_push_int(ctx,SQLITE_FCNTL_CHUNK_SIZE);
	duk_put_global_string(ctx,"SQLITE_FCNTL_CHUNK_SIZE");
	duk_push_int(ctx,SQLITE_FCNTL_CKPT_DONE);
	duk_put_global_string(ctx,"SQLITE_FCNTL_CKPT_DONE");
	duk_push_int(ctx,SQLITE_FCNTL_CKPT_START);
	duk_put_global_string(ctx,"SQLITE_FCNTL_CKPT_START");
	duk_push_int(ctx,SQLITE_FCNTL_COMMIT_ATOMIC_WRITE);
	duk_put_global_string(ctx,"SQLITE_FCNTL_COMMIT_ATOMIC_WRITE");
	duk_push_int(ctx,SQLITE_FCNTL_COMMIT_PHASETWO);
	duk_put_global_string(ctx,"SQLITE_FCNTL_COMMIT_PHASETWO");
	duk_push_int(ctx,SQLITE_FCNTL_DATA_VERSION);
	duk_put_global_string(ctx,"SQLITE_FCNTL_DATA_VERSION");
	duk_push_int(ctx,SQLITE_FCNTL_FILE_POINTER);
	duk_put_global_string(ctx,"SQLITE_FCNTL_FILE_POINTER");
	duk_push_int(ctx,SQLITE_FCNTL_GET_LOCKPROXYFILE);
	duk_put_global_string(ctx,"SQLITE_FCNTL_GET_LOCKPROXYFILE");
	duk_push_int(ctx,SQLITE_FCNTL_HAS_MOVED);
	duk_put_global_string(ctx,"SQLITE_FCNTL_HAS_MOVED");
	duk_push_int(ctx,SQLITE_FCNTL_JOURNAL_POINTER);
	duk_put_global_string(ctx,"SQLITE_FCNTL_JOURNAL_POINTER");
	duk_push_int(ctx,SQLITE_FCNTL_LAST_ERRNO);
	duk_put_global_string(ctx,"SQLITE_FCNTL_LAST_ERRNO");
	duk_push_int(ctx,SQLITE_FCNTL_LOCKSTATE);
	duk_put_global_string(ctx,"SQLITE_FCNTL_LOCKSTATE");
	duk_push_int(ctx,SQLITE_FCNTL_LOCK_TIMEOUT);
	duk_put_global_string(ctx,"SQLITE_FCNTL_LOCK_TIMEOUT");
	duk_push_int(ctx,SQLITE_FCNTL_MMAP_SIZE);
	duk_put_global_string(ctx,"SQLITE_FCNTL_MMAP_SIZE");
	duk_push_int(ctx,SQLITE_FCNTL_OVERWRITE);
	duk_put_global_string(ctx,"SQLITE_FCNTL_OVERWRITE");
	duk_push_int(ctx,SQLITE_FCNTL_PDB);
	duk_put_global_string(ctx,"SQLITE_FCNTL_PDB");
	duk_push_int(ctx,SQLITE_FCNTL_PERSIST_WAL);
	duk_put_global_string(ctx,"SQLITE_FCNTL_PERSIST_WAL");
	duk_push_int(ctx,SQLITE_FCNTL_POWERSAFE_OVERWRITE);
	duk_put_global_string(ctx,"SQLITE_FCNTL_POWERSAFE_OVERWRITE");
	duk_push_int(ctx,SQLITE_FCNTL_PRAGMA);
	duk_put_global_string(ctx,"SQLITE_FCNTL_PRAGMA");
	duk_push_int(ctx,SQLITE_FCNTL_RBU);
	duk_put_global_string(ctx,"SQLITE_FCNTL_RBU");
	duk_push_int(ctx,SQLITE_FCNTL_RESERVE_BYTES);
	duk_put_global_string(ctx,"SQLITE_FCNTL_RESERVE_BYTES");
	duk_push_int(ctx,SQLITE_FCNTL_ROLLBACK_ATOMIC_WRITE);
	duk_put_global_string(ctx,"SQLITE_FCNTL_ROLLBACK_ATOMIC_WRITE");
	duk_push_int(ctx,SQLITE_FCNTL_SET_LOCKPROXYFILE);
	duk_put_global_string(ctx,"SQLITE_FCNTL_SET_LOCKPROXYFILE");
	duk_push_int(ctx,SQLITE_FCNTL_SIZE_HINT);
	duk_put_global_string(ctx,"SQLITE_FCNTL_SIZE_HINT");
	duk_push_int(ctx,SQLITE_FCNTL_SIZE_LIMIT);
	duk_put_global_string(ctx,"SQLITE_FCNTL_SIZE_LIMIT");
	duk_push_int(ctx,SQLITE_FCNTL_SYNC);
	duk_put_global_string(ctx,"SQLITE_FCNTL_SYNC");
	duk_push_int(ctx,SQLITE_FCNTL_SYNC_OMITTED);
	duk_put_global_string(ctx,"SQLITE_FCNTL_SYNC_OMITTED");
	duk_push_int(ctx,SQLITE_FCNTL_TEMPFILENAME);
	duk_put_global_string(ctx,"SQLITE_FCNTL_TEMPFILENAME");
	duk_push_int(ctx,SQLITE_FCNTL_TRACE);
	duk_put_global_string(ctx,"SQLITE_FCNTL_TRACE");
	duk_push_int(ctx,SQLITE_FCNTL_VFSNAME);
	duk_put_global_string(ctx,"SQLITE_FCNTL_VFSNAME");
	duk_push_int(ctx,SQLITE_FCNTL_VFS_POINTER);
	duk_put_global_string(ctx,"SQLITE_FCNTL_VFS_POINTER");
	duk_push_int(ctx,SQLITE_FCNTL_WAL_BLOCK);
	duk_put_global_string(ctx,"SQLITE_FCNTL_WAL_BLOCK");
	duk_push_int(ctx,SQLITE_FCNTL_WIN32_AV_RETRY);
	duk_put_global_string(ctx,"SQLITE_FCNTL_WIN32_AV_RETRY");
	duk_push_int(ctx,SQLITE_FCNTL_WIN32_GET_HANDLE);
	duk_put_global_string(ctx,"SQLITE_FCNTL_WIN32_GET_HANDLE");
	duk_push_int(ctx,SQLITE_FCNTL_WIN32_SET_HANDLE);
	duk_put_global_string(ctx,"SQLITE_FCNTL_WIN32_SET_HANDLE");
	duk_push_int(ctx,SQLITE_FCNTL_ZIPVFS);
	duk_put_global_string(ctx,"SQLITE_FCNTL_ZIPVFS");
	duk_push_int(ctx,SQLITE_FLOAT);
	duk_put_global_string(ctx,"SQLITE_FLOAT");
	duk_push_int(ctx,SQLITE_FORMAT);
	duk_put_global_string(ctx,"SQLITE_FORMAT");
	duk_push_int(ctx,SQLITE_FULL);
	duk_put_global_string(ctx,"SQLITE_FULL");
	duk_push_int(ctx,SQLITE_FUNCTION);
	duk_put_global_string(ctx,"SQLITE_FUNCTION");
	duk_push_int(ctx,SQLITE_IGNORE);
	duk_put_global_string(ctx,"SQLITE_IGNORE");
	duk_push_int(ctx,SQLITE_INDEX_CONSTRAINT_EQ);
	duk_put_global_string(ctx,"SQLITE_INDEX_CONSTRAINT_EQ");
	duk_push_int(ctx,SQLITE_INDEX_CONSTRAINT_FUNCTION);
	duk_put_global_string(ctx,"SQLITE_INDEX_CONSTRAINT_FUNCTION");
	duk_push_int(ctx,SQLITE_INDEX_CONSTRAINT_GE);
	duk_put_global_string(ctx,"SQLITE_INDEX_CONSTRAINT_GE");
	duk_push_int(ctx,SQLITE_INDEX_CONSTRAINT_GLOB);
	duk_put_global_string(ctx,"SQLITE_INDEX_CONSTRAINT_GLOB");
	duk_push_int(ctx,SQLITE_INDEX_CONSTRAINT_GT);
	duk_put_global_string(ctx,"SQLITE_INDEX_CONSTRAINT_GT");
	duk_push_int(ctx,SQLITE_INDEX_CONSTRAINT_IS);
	duk_put_global_string(ctx,"SQLITE_INDEX_CONSTRAINT_IS");
	duk_push_int(ctx,SQLITE_INDEX_CONSTRAINT_ISNOT);
	duk_put_global_string(ctx,"SQLITE_INDEX_CONSTRAINT_ISNOT");
	duk_push_int(ctx,SQLITE_INDEX_CONSTRAINT_ISNOTNULL);
	duk_put_global_string(ctx,"SQLITE_INDEX_CONSTRAINT_ISNOTNULL");
	duk_push_int(ctx,SQLITE_INDEX_CONSTRAINT_ISNULL);
	duk_put_global_string(ctx,"SQLITE_INDEX_CONSTRAINT_ISNULL");
	duk_push_int(ctx,SQLITE_INDEX_CONSTRAINT_LE);
	duk_put_global_string(ctx,"SQLITE_INDEX_CONSTRAINT_LE");
	duk_push_int(ctx,SQLITE_INDEX_CONSTRAINT_LIKE);
	duk_put_global_string(ctx,"SQLITE_INDEX_CONSTRAINT_LIKE");
	duk_push_int(ctx,SQLITE_INDEX_CONSTRAINT_LT);
	duk_put_global_string(ctx,"SQLITE_INDEX_CONSTRAINT_LT");
	duk_push_int(ctx,SQLITE_INDEX_CONSTRAINT_MATCH);
	duk_put_global_string(ctx,"SQLITE_INDEX_CONSTRAINT_MATCH");
	duk_push_int(ctx,SQLITE_INDEX_CONSTRAINT_NE);
	duk_put_global_string(ctx,"SQLITE_INDEX_CONSTRAINT_NE");
	duk_push_int(ctx,SQLITE_INDEX_CONSTRAINT_REGEXP);
	duk_put_global_string(ctx,"SQLITE_INDEX_CONSTRAINT_REGEXP");
	duk_push_int(ctx,SQLITE_INDEX_SCAN_UNIQUE);
	duk_put_global_string(ctx,"SQLITE_INDEX_SCAN_UNIQUE");
	duk_push_int(ctx,SQLITE_INNOCUOUS);
	duk_put_global_string(ctx,"SQLITE_INNOCUOUS");
	duk_push_int(ctx,SQLITE_INSERT);
	duk_put_global_string(ctx,"SQLITE_INSERT");
	duk_push_int(ctx,SQLITE_INTEGER);
	duk_put_global_string(ctx,"SQLITE_INTEGER");
	duk_push_int(ctx,SQLITE_INTERNAL);
	duk_put_global_string(ctx,"SQLITE_INTERNAL");
	duk_push_int(ctx,SQLITE_INTERRUPT);
	duk_put_global_string(ctx,"SQLITE_INTERRUPT");
	duk_push_int(ctx,SQLITE_IOCAP_ATOMIC);
	duk_put_global_string(ctx,"SQLITE_IOCAP_ATOMIC");
	duk_push_int(ctx,SQLITE_IOCAP_ATOMIC16K);
	duk_put_global_string(ctx,"SQLITE_IOCAP_ATOMIC16K");
	duk_push_int(ctx,SQLITE_IOCAP_ATOMIC1K);
	duk_put_global_string(ctx,"SQLITE_IOCAP_ATOMIC1K");
	duk_push_int(ctx,SQLITE_IOCAP_ATOMIC2K);
	duk_put_global_string(ctx,"SQLITE_IOCAP_ATOMIC2K");
	duk_push_int(ctx,SQLITE_IOCAP_ATOMIC32K);
	duk_put_global_string(ctx,"SQLITE_IOCAP_ATOMIC32K");
	duk_push_int(ctx,SQLITE_IOCAP_ATOMIC4K);
	duk_put_global_string(ctx,"SQLITE_IOCAP_ATOMIC4K");
	duk_push_int(ctx,SQLITE_IOCAP_ATOMIC512);
	duk_put_global_string(ctx,"SQLITE_IOCAP_ATOMIC512");
	duk_push_int(ctx,SQLITE_IOCAP_ATOMIC64K);
	duk_put_global_string(ctx,"SQLITE_IOCAP_ATOMIC64K");
	duk_push_int(ctx,SQLITE_IOCAP_ATOMIC8K);
	duk_put_global_string(ctx,"SQLITE_IOCAP_ATOMIC8K");
	duk_push_int(ctx,SQLITE_IOCAP_BATCH_ATOMIC);
	duk_put_global_string(ctx,"SQLITE_IOCAP_BATCH_ATOMIC");
	duk_push_int(ctx,SQLITE_IOCAP_IMMUTABLE);
	duk_put_global_string(ctx,"SQLITE_IOCAP_IMMUTABLE");
	duk_push_int(ctx,SQLITE_IOCAP_POWERSAFE_OVERWRITE);
	duk_put_global_string(ctx,"SQLITE_IOCAP_POWERSAFE_OVERWRITE");
	duk_push_int(ctx,SQLITE_IOCAP_SAFE_APPEND);
	duk_put_global_string(ctx,"SQLITE_IOCAP_SAFE_APPEND");
	duk_push_int(ctx,SQLITE_IOCAP_SEQUENTIAL);
	duk_put_global_string(ctx,"SQLITE_IOCAP_SEQUENTIAL");
	duk_push_int(ctx,SQLITE_IOCAP_UNDELETABLE_WHEN_OPEN);
	duk_put_global_string(ctx,"SQLITE_IOCAP_UNDELETABLE_WHEN_OPEN");
	duk_push_int(ctx,SQLITE_IOERR);
	duk_put_global_string(ctx,"SQLITE_IOERR");
	duk_push_int(ctx,SQLITE_IOERR_ACCESS);
	duk_put_global_string(ctx,"SQLITE_IOERR_ACCESS");
	duk_push_int(ctx,SQLITE_IOERR_AUTH);
	duk_put_global_string(ctx,"SQLITE_IOERR_AUTH");
	duk_push_int(ctx,SQLITE_IOERR_BEGIN_ATOMIC);
	duk_put_global_string(ctx,"SQLITE_IOERR_BEGIN_ATOMIC");
	duk_push_int(ctx,SQLITE_IOERR_BLOCKED);
	duk_put_global_string(ctx,"SQLITE_IOERR_BLOCKED");
	duk_push_int(ctx,SQLITE_IOERR_CHECKRESERVEDLOCK);
	duk_put_global_string(ctx,"SQLITE_IOERR_CHECKRESERVEDLOCK");
	duk_push_int(ctx,SQLITE_IOERR_CLOSE);
	duk_put_global_string(ctx,"SQLITE_IOERR_CLOSE");
	duk_push_int(ctx,SQLITE_IOERR_COMMIT_ATOMIC);
	duk_put_global_string(ctx,"SQLITE_IOERR_COMMIT_ATOMIC");
	duk_push_int(ctx,SQLITE_IOERR_CONVPATH);
	duk_put_global_string(ctx,"SQLITE_IOERR_CONVPATH");
	duk_push_int(ctx,SQLITE_IOERR_DATA);
	duk_put_global_string(ctx,"SQLITE_IOERR_DATA");
	duk_push_int(ctx,SQLITE_IOERR_DELETE);
	duk_put_global_string(ctx,"SQLITE_IOERR_DELETE");
	duk_push_int(ctx,SQLITE_IOERR_DELETE_NOENT);
	duk_put_global_string(ctx,"SQLITE_IOERR_DELETE_NOENT");
	duk_push_int(ctx,SQLITE_IOERR_DIR_CLOSE);
	duk_put_global_string(ctx,"SQLITE_IOERR_DIR_CLOSE");
	duk_push_int(ctx,SQLITE_IOERR_DIR_FSYNC);
	duk_put_global_string(ctx,"SQLITE_IOERR_DIR_FSYNC");
	duk_push_int(ctx,SQLITE_IOERR_FSTAT);
	duk_put_global_string(ctx,"SQLITE_IOERR_FSTAT");
	duk_push_int(ctx,SQLITE_IOERR_FSYNC);
	duk_put_global_string(ctx,"SQLITE_IOERR_FSYNC");
	duk_push_int(ctx,SQLITE_IOERR_GETTEMPPATH);
	duk_put_global_string(ctx,"SQLITE_IOERR_GETTEMPPATH");
	duk_push_int(ctx,SQLITE_IOERR_LOCK);
	duk_put_global_string(ctx,"SQLITE_IOERR_LOCK");
	duk_push_int(ctx,SQLITE_IOERR_MMAP);
	duk_put_global_string(ctx,"SQLITE_IOERR_MMAP");
	duk_push_int(ctx,SQLITE_IOERR_NOMEM);
	duk_put_global_string(ctx,"SQLITE_IOERR_NOMEM");
	duk_push_int(ctx,SQLITE_IOERR_RDLOCK);
	duk_put_global_string(ctx,"SQLITE_IOERR_RDLOCK");
	duk_push_int(ctx,SQLITE_IOERR_READ);
	duk_put_global_string(ctx,"SQLITE_IOERR_READ");
	duk_push_int(ctx,SQLITE_IOERR_ROLLBACK_ATOMIC);
	duk_put_global_string(ctx,"SQLITE_IOERR_ROLLBACK_ATOMIC");
	duk_push_int(ctx,SQLITE_IOERR_SEEK);
	duk_put_global_string(ctx,"SQLITE_IOERR_SEEK");
	duk_push_int(ctx,SQLITE_IOERR_SHMLOCK);
	duk_put_global_string(ctx,"SQLITE_IOERR_SHMLOCK");
	duk_push_int(ctx,SQLITE_IOERR_SHMMAP);
	duk_put_global_string(ctx,"SQLITE_IOERR_SHMMAP");
	duk_push_int(ctx,SQLITE_IOERR_SHMOPEN);
	duk_put_global_string(ctx,"SQLITE_IOERR_SHMOPEN");
	duk_push_int(ctx,SQLITE_IOERR_SHMSIZE);
	duk_put_global_string(ctx,"SQLITE_IOERR_SHMSIZE");
	duk_push_int(ctx,SQLITE_IOERR_SHORT_READ);
	duk_put_global_string(ctx,"SQLITE_IOERR_SHORT_READ");
	duk_push_int(ctx,SQLITE_IOERR_TRUNCATE);
	duk_put_global_string(ctx,"SQLITE_IOERR_TRUNCATE");
	duk_push_int(ctx,SQLITE_IOERR_UNLOCK);
	duk_put_global_string(ctx,"SQLITE_IOERR_UNLOCK");
	duk_push_int(ctx,SQLITE_IOERR_VNODE);
	duk_put_global_string(ctx,"SQLITE_IOERR_VNODE");
	duk_push_int(ctx,SQLITE_IOERR_WRITE);
	duk_put_global_string(ctx,"SQLITE_IOERR_WRITE");
	duk_push_int(ctx,SQLITE_LIMIT_ATTACHED);
	duk_put_global_string(ctx,"SQLITE_LIMIT_ATTACHED");
	duk_push_int(ctx,SQLITE_LIMIT_COLUMN);
	duk_put_global_string(ctx,"SQLITE_LIMIT_COLUMN");
	duk_push_int(ctx,SQLITE_LIMIT_COMPOUND_SELECT);
	duk_put_global_string(ctx,"SQLITE_LIMIT_COMPOUND_SELECT");
	duk_push_int(ctx,SQLITE_LIMIT_EXPR_DEPTH);
	duk_put_global_string(ctx,"SQLITE_LIMIT_EXPR_DEPTH");
	duk_push_int(ctx,SQLITE_LIMIT_FUNCTION_ARG);
	duk_put_global_string(ctx,"SQLITE_LIMIT_FUNCTION_ARG");
	duk_push_int(ctx,SQLITE_LIMIT_LENGTH);
	duk_put_global_string(ctx,"SQLITE_LIMIT_LENGTH");
	duk_push_int(ctx,SQLITE_LIMIT_LIKE_PATTERN_LENGTH);
	duk_put_global_string(ctx,"SQLITE_LIMIT_LIKE_PATTERN_LENGTH");
	duk_push_int(ctx,SQLITE_LIMIT_SQL_LENGTH);
	duk_put_global_string(ctx,"SQLITE_LIMIT_SQL_LENGTH");
	duk_push_int(ctx,SQLITE_LIMIT_TRIGGER_DEPTH);
	duk_put_global_string(ctx,"SQLITE_LIMIT_TRIGGER_DEPTH");
	duk_push_int(ctx,SQLITE_LIMIT_VARIABLE_NUMBER);
	duk_put_global_string(ctx,"SQLITE_LIMIT_VARIABLE_NUMBER");
	duk_push_int(ctx,SQLITE_LIMIT_VDBE_OP);
	duk_put_global_string(ctx,"SQLITE_LIMIT_VDBE_OP");
	duk_push_int(ctx,SQLITE_LIMIT_WORKER_THREADS);
	duk_put_global_string(ctx,"SQLITE_LIMIT_WORKER_THREADS");
	duk_push_int(ctx,SQLITE_LOCKED);
	duk_put_global_string(ctx,"SQLITE_LOCKED");
	duk_push_int(ctx,SQLITE_LOCKED_SHAREDCACHE);
	duk_put_global_string(ctx,"SQLITE_LOCKED_SHAREDCACHE");
	duk_push_int(ctx,SQLITE_LOCKED_VTAB);
	duk_put_global_string(ctx,"SQLITE_LOCKED_VTAB");
	duk_push_int(ctx,SQLITE_LOCK_EXCLUSIVE);
	duk_put_global_string(ctx,"SQLITE_LOCK_EXCLUSIVE");
	duk_push_int(ctx,SQLITE_LOCK_NONE);
	duk_put_global_string(ctx,"SQLITE_LOCK_NONE");
	duk_push_int(ctx,SQLITE_LOCK_PENDING);
	duk_put_global_string(ctx,"SQLITE_LOCK_PENDING");
	duk_push_int(ctx,SQLITE_LOCK_RESERVED);
	duk_put_global_string(ctx,"SQLITE_LOCK_RESERVED");
	duk_push_int(ctx,SQLITE_LOCK_SHARED);
	duk_put_global_string(ctx,"SQLITE_LOCK_SHARED");
	duk_push_int(ctx,SQLITE_MISMATCH);
	duk_put_global_string(ctx,"SQLITE_MISMATCH");
	duk_push_int(ctx,SQLITE_MISUSE);
	duk_put_global_string(ctx,"SQLITE_MISUSE");
	duk_push_int(ctx,SQLITE_MUTEX_FAST);
	duk_put_global_string(ctx,"SQLITE_MUTEX_FAST");
	duk_push_int(ctx,SQLITE_MUTEX_RECURSIVE);
	duk_put_global_string(ctx,"SQLITE_MUTEX_RECURSIVE");
	duk_push_int(ctx,SQLITE_MUTEX_STATIC_APP1);
	duk_put_global_string(ctx,"SQLITE_MUTEX_STATIC_APP1");
	duk_push_int(ctx,SQLITE_MUTEX_STATIC_APP2);
	duk_put_global_string(ctx,"SQLITE_MUTEX_STATIC_APP2");
	duk_push_int(ctx,SQLITE_MUTEX_STATIC_APP3);
	duk_put_global_string(ctx,"SQLITE_MUTEX_STATIC_APP3");
	duk_push_int(ctx,SQLITE_MUTEX_STATIC_LRU);
	duk_put_global_string(ctx,"SQLITE_MUTEX_STATIC_LRU");
	duk_push_int(ctx,SQLITE_MUTEX_STATIC_LRU2);
	duk_put_global_string(ctx,"SQLITE_MUTEX_STATIC_LRU2");
	duk_push_int(ctx,SQLITE_MUTEX_STATIC_MASTER);
	duk_put_global_string(ctx,"SQLITE_MUTEX_STATIC_MASTER");
	duk_push_int(ctx,SQLITE_MUTEX_STATIC_MEM);
	duk_put_global_string(ctx,"SQLITE_MUTEX_STATIC_MEM");
	duk_push_int(ctx,SQLITE_MUTEX_STATIC_MEM2);
	duk_put_global_string(ctx,"SQLITE_MUTEX_STATIC_MEM2");
	duk_push_int(ctx,SQLITE_MUTEX_STATIC_OPEN);
	duk_put_global_string(ctx,"SQLITE_MUTEX_STATIC_OPEN");
	duk_push_int(ctx,SQLITE_MUTEX_STATIC_PMEM);
	duk_put_global_string(ctx,"SQLITE_MUTEX_STATIC_PMEM");
	duk_push_int(ctx,SQLITE_MUTEX_STATIC_PRNG);
	duk_put_global_string(ctx,"SQLITE_MUTEX_STATIC_PRNG");
	duk_push_int(ctx,SQLITE_MUTEX_STATIC_VFS1);
	duk_put_global_string(ctx,"SQLITE_MUTEX_STATIC_VFS1");
	duk_push_int(ctx,SQLITE_MUTEX_STATIC_VFS2);
	duk_put_global_string(ctx,"SQLITE_MUTEX_STATIC_VFS2");
	duk_push_int(ctx,SQLITE_MUTEX_STATIC_VFS3);
	duk_put_global_string(ctx,"SQLITE_MUTEX_STATIC_VFS3");
	duk_push_int(ctx,SQLITE_NOLFS);
	duk_put_global_string(ctx,"SQLITE_NOLFS");
	duk_push_int(ctx,SQLITE_NOMEM);
	duk_put_global_string(ctx,"SQLITE_NOMEM");
	duk_push_int(ctx,SQLITE_NOTADB);
	duk_put_global_string(ctx,"SQLITE_NOTADB");
	duk_push_int(ctx,SQLITE_NOTFOUND);
	duk_put_global_string(ctx,"SQLITE_NOTFOUND");
	duk_push_int(ctx,SQLITE_NOTICE);
	duk_put_global_string(ctx,"SQLITE_NOTICE");
	duk_push_int(ctx,SQLITE_NOTICE_RECOVER_ROLLBACK);
	duk_put_global_string(ctx,"SQLITE_NOTICE_RECOVER_ROLLBACK");
	duk_push_int(ctx,SQLITE_NOTICE_RECOVER_WAL);
	duk_put_global_string(ctx,"SQLITE_NOTICE_RECOVER_WAL");
	duk_push_int(ctx,SQLITE_NULL);
	duk_put_global_string(ctx,"SQLITE_NULL");
	duk_push_int(ctx,SQLITE_OK);
	duk_put_global_string(ctx,"SQLITE_OK");
	duk_push_int(ctx,SQLITE_OK_LOAD_PERMANENTLY);
	duk_put_global_string(ctx,"SQLITE_OK_LOAD_PERMANENTLY");
	duk_push_int(ctx,SQLITE_OK_SYMLINK);
	duk_put_global_string(ctx,"SQLITE_OK_SYMLINK");
	duk_push_int(ctx,SQLITE_OPEN_AUTOPROXY);
	duk_put_global_string(ctx,"SQLITE_OPEN_AUTOPROXY");
	duk_push_int(ctx,SQLITE_OPEN_CREATE);
	duk_put_global_string(ctx,"SQLITE_OPEN_CREATE");
	duk_push_int(ctx,SQLITE_OPEN_DELETEONCLOSE);
	duk_put_global_string(ctx,"SQLITE_OPEN_DELETEONCLOSE");
	duk_push_int(ctx,SQLITE_OPEN_EXCLUSIVE);
	duk_put_global_string(ctx,"SQLITE_OPEN_EXCLUSIVE");
	duk_push_int(ctx,SQLITE_OPEN_FULLMUTEX);
	duk_put_global_string(ctx,"SQLITE_OPEN_FULLMUTEX");
	duk_push_int(ctx,SQLITE_OPEN_MAIN_DB);
	duk_put_global_string(ctx,"SQLITE_OPEN_MAIN_DB");
	duk_push_int(ctx,SQLITE_OPEN_MAIN_JOURNAL);
	duk_put_global_string(ctx,"SQLITE_OPEN_MAIN_JOURNAL");
	duk_push_int(ctx,SQLITE_OPEN_MASTER_JOURNAL);
	duk_put_global_string(ctx,"SQLITE_OPEN_MASTER_JOURNAL");
	duk_push_int(ctx,SQLITE_OPEN_MEMORY);
	duk_put_global_string(ctx,"SQLITE_OPEN_MEMORY");
	duk_push_int(ctx,SQLITE_OPEN_NOFOLLOW);
	duk_put_global_string(ctx,"SQLITE_OPEN_NOFOLLOW");
	duk_push_int(ctx,SQLITE_OPEN_NOMUTEX);
	duk_put_global_string(ctx,"SQLITE_OPEN_NOMUTEX");
	duk_push_int(ctx,SQLITE_OPEN_PRIVATECACHE);
	duk_put_global_string(ctx,"SQLITE_OPEN_PRIVATECACHE");
	duk_push_int(ctx,SQLITE_OPEN_READONLY);
	duk_put_global_string(ctx,"SQLITE_OPEN_READONLY");
	duk_push_int(ctx,SQLITE_OPEN_READWRITE);
	duk_put_global_string(ctx,"SQLITE_OPEN_READWRITE");
	duk_push_int(ctx,SQLITE_OPEN_SHAREDCACHE);
	duk_put_global_string(ctx,"SQLITE_OPEN_SHAREDCACHE");
	duk_push_int(ctx,SQLITE_OPEN_SUBJOURNAL);
	duk_put_global_string(ctx,"SQLITE_OPEN_SUBJOURNAL");
	duk_push_int(ctx,SQLITE_OPEN_TEMP_DB);
	duk_put_global_string(ctx,"SQLITE_OPEN_TEMP_DB");
	duk_push_int(ctx,SQLITE_OPEN_TEMP_JOURNAL);
	duk_put_global_string(ctx,"SQLITE_OPEN_TEMP_JOURNAL");
	duk_push_int(ctx,SQLITE_OPEN_TRANSIENT_DB);
	duk_put_global_string(ctx,"SQLITE_OPEN_TRANSIENT_DB");
	duk_push_int(ctx,SQLITE_OPEN_URI);
	duk_put_global_string(ctx,"SQLITE_OPEN_URI");
	duk_push_int(ctx,SQLITE_OPEN_WAL);
	duk_put_global_string(ctx,"SQLITE_OPEN_WAL");
	duk_push_int(ctx,SQLITE_PERM);
	duk_put_global_string(ctx,"SQLITE_PERM");
	duk_push_int(ctx,SQLITE_PRAGMA);
	duk_put_global_string(ctx,"SQLITE_PRAGMA");
	duk_push_int(ctx,SQLITE_PREPARE_NORMALIZE);
	duk_put_global_string(ctx,"SQLITE_PREPARE_NORMALIZE");
	duk_push_int(ctx,SQLITE_PREPARE_NO_VTAB);
	duk_put_global_string(ctx,"SQLITE_PREPARE_NO_VTAB");
	duk_push_int(ctx,SQLITE_PREPARE_PERSISTENT);
	duk_put_global_string(ctx,"SQLITE_PREPARE_PERSISTENT");
	duk_push_int(ctx,SQLITE_PROTOCOL);
	duk_put_global_string(ctx,"SQLITE_PROTOCOL");
	duk_push_int(ctx,SQLITE_RANGE);
	duk_put_global_string(ctx,"SQLITE_RANGE");
	duk_push_int(ctx,SQLITE_READ);
	duk_put_global_string(ctx,"SQLITE_READ");
	duk_push_int(ctx,SQLITE_READONLY);
	duk_put_global_string(ctx,"SQLITE_READONLY");
	duk_push_int(ctx,SQLITE_READONLY_CANTINIT);
	duk_put_global_string(ctx,"SQLITE_READONLY_CANTINIT");
	duk_push_int(ctx,SQLITE_READONLY_CANTLOCK);
	duk_put_global_string(ctx,"SQLITE_READONLY_CANTLOCK");
	duk_push_int(ctx,SQLITE_READONLY_DBMOVED);
	duk_put_global_string(ctx,"SQLITE_READONLY_DBMOVED");
	duk_push_int(ctx,SQLITE_READONLY_DIRECTORY);
	duk_put_global_string(ctx,"SQLITE_READONLY_DIRECTORY");
	duk_push_int(ctx,SQLITE_READONLY_RECOVERY);
	duk_put_global_string(ctx,"SQLITE_READONLY_RECOVERY");
	duk_push_int(ctx,SQLITE_READONLY_ROLLBACK);
	duk_put_global_string(ctx,"SQLITE_READONLY_ROLLBACK");
	duk_push_int(ctx,SQLITE_RECURSIVE);
	duk_put_global_string(ctx,"SQLITE_RECURSIVE");
	duk_push_int(ctx,SQLITE_REINDEX);
	duk_put_global_string(ctx,"SQLITE_REINDEX");
	duk_push_int(ctx,SQLITE_REPLACE);
	duk_put_global_string(ctx,"SQLITE_REPLACE");
	duk_push_int(ctx,SQLITE_ROLLBACK);
	duk_put_global_string(ctx,"SQLITE_ROLLBACK");
	duk_push_int(ctx,SQLITE_ROW);
	duk_put_global_string(ctx,"SQLITE_ROW");
	duk_push_int(ctx,SQLITE_SAVEPOINT);
	duk_put_global_string(ctx,"SQLITE_SAVEPOINT");
	duk_push_int(ctx,SQLITE_SCANSTAT_EST);
	duk_put_global_string(ctx,"SQLITE_SCANSTAT_EST");
	duk_push_int(ctx,SQLITE_SCANSTAT_EXPLAIN);
	duk_put_global_string(ctx,"SQLITE_SCANSTAT_EXPLAIN");
	duk_push_int(ctx,SQLITE_SCANSTAT_NAME);
	duk_put_global_string(ctx,"SQLITE_SCANSTAT_NAME");
	duk_push_int(ctx,SQLITE_SCANSTAT_NLOOP);
	duk_put_global_string(ctx,"SQLITE_SCANSTAT_NLOOP");
	duk_push_int(ctx,SQLITE_SCANSTAT_NVISIT);
	duk_put_global_string(ctx,"SQLITE_SCANSTAT_NVISIT");
	duk_push_int(ctx,SQLITE_SCANSTAT_SELECTID);
	duk_put_global_string(ctx,"SQLITE_SCANSTAT_SELECTID");
	duk_push_int(ctx,SQLITE_SCHEMA);
	duk_put_global_string(ctx,"SQLITE_SCHEMA");
	duk_push_int(ctx,SQLITE_SELECT);
	duk_put_global_string(ctx,"SQLITE_SELECT");
	duk_push_int(ctx,SQLITE_SERIALIZE_NOCOPY);
	duk_put_global_string(ctx,"SQLITE_SERIALIZE_NOCOPY");
	duk_push_int(ctx,SQLITE_SHM_EXCLUSIVE);
	duk_put_global_string(ctx,"SQLITE_SHM_EXCLUSIVE");
	duk_push_int(ctx,SQLITE_SHM_LOCK);
	duk_put_global_string(ctx,"SQLITE_SHM_LOCK");
	duk_push_int(ctx,SQLITE_SHM_NLOCK);
	duk_put_global_string(ctx,"SQLITE_SHM_NLOCK");
	duk_push_int(ctx,SQLITE_SHM_SHARED);
	duk_put_global_string(ctx,"SQLITE_SHM_SHARED");
	duk_push_int(ctx,SQLITE_SHM_UNLOCK);
	duk_put_global_string(ctx,"SQLITE_SHM_UNLOCK");
	duk_push_int(ctx,SQLITE_SOURCE_ID);
	duk_put_global_string(ctx,"SQLITE_SOURCE_ID");
	duk_push_int(ctx,SQLITE_STATIC);
	duk_put_global_string(ctx,"SQLITE_STATIC");
	duk_push_int(ctx,SQLITE_STATUS_MALLOC_COUNT);
	duk_put_global_string(ctx,"SQLITE_STATUS_MALLOC_COUNT");
	duk_push_int(ctx,SQLITE_STATUS_MALLOC_SIZE);
	duk_put_global_string(ctx,"SQLITE_STATUS_MALLOC_SIZE");
	duk_push_int(ctx,SQLITE_STATUS_MEMORY_USED);
	duk_put_global_string(ctx,"SQLITE_STATUS_MEMORY_USED");
	duk_push_int(ctx,SQLITE_STATUS_PAGECACHE_OVERFLOW);
	duk_put_global_string(ctx,"SQLITE_STATUS_PAGECACHE_OVERFLOW");
	duk_push_int(ctx,SQLITE_STATUS_PAGECACHE_SIZE);
	duk_put_global_string(ctx,"SQLITE_STATUS_PAGECACHE_SIZE");
	duk_push_int(ctx,SQLITE_STATUS_PAGECACHE_USED);
	duk_put_global_string(ctx,"SQLITE_STATUS_PAGECACHE_USED");
	duk_push_int(ctx,SQLITE_STATUS_PARSER_STACK);
	duk_put_global_string(ctx,"SQLITE_STATUS_PARSER_STACK");
	duk_push_int(ctx,SQLITE_STATUS_SCRATCH_OVERFLOW);
	duk_put_global_string(ctx,"SQLITE_STATUS_SCRATCH_OVERFLOW");
	duk_push_int(ctx,SQLITE_STATUS_SCRATCH_SIZE);
	duk_put_global_string(ctx,"SQLITE_STATUS_SCRATCH_SIZE");
	duk_push_int(ctx,SQLITE_STATUS_SCRATCH_USED);
	duk_put_global_string(ctx,"SQLITE_STATUS_SCRATCH_USED");
	duk_push_int(ctx,SQLITE_STMTSTATUS_AUTOINDEX);
	duk_put_global_string(ctx,"SQLITE_STMTSTATUS_AUTOINDEX");
	duk_push_int(ctx,SQLITE_STMTSTATUS_FULLSCAN_STEP);
	duk_put_global_string(ctx,"SQLITE_STMTSTATUS_FULLSCAN_STEP");
	duk_push_int(ctx,SQLITE_STMTSTATUS_MEMUSED);
	duk_put_global_string(ctx,"SQLITE_STMTSTATUS_MEMUSED");
	duk_push_int(ctx,SQLITE_STMTSTATUS_REPREPARE);
	duk_put_global_string(ctx,"SQLITE_STMTSTATUS_REPREPARE");
	duk_push_int(ctx,SQLITE_STMTSTATUS_RUN);
	duk_put_global_string(ctx,"SQLITE_STMTSTATUS_RUN");
	duk_push_int(ctx,SQLITE_STMTSTATUS_SORT);
	duk_put_global_string(ctx,"SQLITE_STMTSTATUS_SORT");
	duk_push_int(ctx,SQLITE_STMTSTATUS_VM_STEP);
	duk_put_global_string(ctx,"SQLITE_STMTSTATUS_VM_STEP");
	duk_push_int(ctx,SQLITE_SUBTYPE);
	duk_put_global_string(ctx,"SQLITE_SUBTYPE");
	duk_push_int(ctx,SQLITE_SYNC_DATAONLY);
	duk_put_global_string(ctx,"SQLITE_SYNC_DATAONLY");
	duk_push_int(ctx,SQLITE_SYNC_FULL);
	duk_put_global_string(ctx,"SQLITE_SYNC_FULL");
	duk_push_int(ctx,SQLITE_SYNC_NORMAL);
	duk_put_global_string(ctx,"SQLITE_SYNC_NORMAL");
	duk_push_int(ctx,SQLITE_TESTCTRL_ALWAYS);
	duk_put_global_string(ctx,"SQLITE_TESTCTRL_ALWAYS");
	duk_push_int(ctx,SQLITE_TESTCTRL_ASSERT);
	duk_put_global_string(ctx,"SQLITE_TESTCTRL_ASSERT");
	duk_push_int(ctx,SQLITE_TESTCTRL_BENIGN_MALLOC_HOOKS);
	duk_put_global_string(ctx,"SQLITE_TESTCTRL_BENIGN_MALLOC_HOOKS");
	duk_push_int(ctx,SQLITE_TESTCTRL_BITVEC_TEST);
	duk_put_global_string(ctx,"SQLITE_TESTCTRL_BITVEC_TEST");
	duk_push_int(ctx,SQLITE_TESTCTRL_BYTEORDER);
	duk_put_global_string(ctx,"SQLITE_TESTCTRL_BYTEORDER");
	duk_push_int(ctx,SQLITE_TESTCTRL_EXPLAIN_STMT);
	duk_put_global_string(ctx,"SQLITE_TESTCTRL_EXPLAIN_STMT");
	duk_push_int(ctx,SQLITE_TESTCTRL_EXTRA_SCHEMA_CHECKS);
	duk_put_global_string(ctx,"SQLITE_TESTCTRL_EXTRA_SCHEMA_CHECKS");
	duk_push_int(ctx,SQLITE_TESTCTRL_FAULT_INSTALL);
	duk_put_global_string(ctx,"SQLITE_TESTCTRL_FAULT_INSTALL");
	duk_push_int(ctx,SQLITE_TESTCTRL_FIRST);
	duk_put_global_string(ctx,"SQLITE_TESTCTRL_FIRST");
	duk_push_int(ctx,SQLITE_TESTCTRL_IMPOSTER);
	duk_put_global_string(ctx,"SQLITE_TESTCTRL_IMPOSTER");
	duk_push_int(ctx,SQLITE_TESTCTRL_INTERNAL_FUNCTIONS);
	duk_put_global_string(ctx,"SQLITE_TESTCTRL_INTERNAL_FUNCTIONS");
	duk_push_int(ctx,SQLITE_TESTCTRL_ISINIT);
	duk_put_global_string(ctx,"SQLITE_TESTCTRL_ISINIT");
	duk_push_int(ctx,SQLITE_TESTCTRL_ISKEYWORD);
	duk_put_global_string(ctx,"SQLITE_TESTCTRL_ISKEYWORD");
	duk_push_int(ctx,SQLITE_TESTCTRL_LAST);
	duk_put_global_string(ctx,"SQLITE_TESTCTRL_LAST");
	duk_push_int(ctx,SQLITE_TESTCTRL_LOCALTIME_FAULT);
	duk_put_global_string(ctx,"SQLITE_TESTCTRL_LOCALTIME_FAULT");
	duk_push_int(ctx,SQLITE_TESTCTRL_NEVER_CORRUPT);
	duk_put_global_string(ctx,"SQLITE_TESTCTRL_NEVER_CORRUPT");
	duk_push_int(ctx,SQLITE_TESTCTRL_ONCE_RESET_THRESHOLD);
	duk_put_global_string(ctx,"SQLITE_TESTCTRL_ONCE_RESET_THRESHOLD");
	duk_push_int(ctx,SQLITE_TESTCTRL_OPTIMIZATIONS);
	duk_put_global_string(ctx,"SQLITE_TESTCTRL_OPTIMIZATIONS");
	duk_push_int(ctx,SQLITE_TESTCTRL_PARSER_COVERAGE);
	duk_put_global_string(ctx,"SQLITE_TESTCTRL_PARSER_COVERAGE");
	duk_push_int(ctx,SQLITE_TESTCTRL_PENDING_BYTE);
	duk_put_global_string(ctx,"SQLITE_TESTCTRL_PENDING_BYTE");
	duk_push_int(ctx,SQLITE_TESTCTRL_PRNG_RESET);
	duk_put_global_string(ctx,"SQLITE_TESTCTRL_PRNG_RESET");
	duk_push_int(ctx,SQLITE_TESTCTRL_PRNG_RESTORE);
	duk_put_global_string(ctx,"SQLITE_TESTCTRL_PRNG_RESTORE");
	duk_push_int(ctx,SQLITE_TESTCTRL_PRNG_SAVE);
	duk_put_global_string(ctx,"SQLITE_TESTCTRL_PRNG_SAVE");
	duk_push_int(ctx,SQLITE_TESTCTRL_PRNG_SEED);
	duk_put_global_string(ctx,"SQLITE_TESTCTRL_PRNG_SEED");
	duk_push_int(ctx,SQLITE_TESTCTRL_RESERVE);
	duk_put_global_string(ctx,"SQLITE_TESTCTRL_RESERVE");
	duk_push_int(ctx,SQLITE_TESTCTRL_RESULT_INTREAL);
	duk_put_global_string(ctx,"SQLITE_TESTCTRL_RESULT_INTREAL");
	duk_push_int(ctx,SQLITE_TESTCTRL_SCRATCHMALLOC);
	duk_put_global_string(ctx,"SQLITE_TESTCTRL_SCRATCHMALLOC");
	duk_push_int(ctx,SQLITE_TESTCTRL_SORTER_MMAP);
	duk_put_global_string(ctx,"SQLITE_TESTCTRL_SORTER_MMAP");
	duk_push_int(ctx,SQLITE_TESTCTRL_VDBE_COVERAGE);
	duk_put_global_string(ctx,"SQLITE_TESTCTRL_VDBE_COVERAGE");
	duk_push_int(ctx,SQLITE_TEXT);
	duk_put_global_string(ctx,"SQLITE_TEXT");
	duk_push_int(ctx,SQLITE_TOOBIG);
	duk_put_global_string(ctx,"SQLITE_TOOBIG");
	//duk_push_int(ctx,SQLITE_TRACE);		//???
	//duk_put_global_string(ctx,"SQLITE_TRACE");	//???
	duk_push_int(ctx,SQLITE_TRACE_CLOSE);
	duk_put_global_string(ctx,"SQLITE_TRACE_CLOSE");
	duk_push_int(ctx,SQLITE_TRACE_PROFILE);
	duk_put_global_string(ctx,"SQLITE_TRACE_PROFILE");
	duk_push_int(ctx,SQLITE_TRACE_ROW);
	duk_put_global_string(ctx,"SQLITE_TRACE_ROW");
	duk_push_int(ctx,SQLITE_TRACE_STMT);
	duk_put_global_string(ctx,"SQLITE_TRACE_STMT");
	duk_push_int(ctx,SQLITE_TRANSACTION);
	duk_put_global_string(ctx,"SQLITE_TRANSACTION");
	duk_push_int(ctx,SQLITE_TRANSIENT);
	duk_put_global_string(ctx,"SQLITE_TRANSIENT");
	duk_push_int(ctx,SQLITE_UPDATE);
	duk_put_global_string(ctx,"SQLITE_UPDATE");
	duk_push_int(ctx,SQLITE_UTF16);
	duk_put_global_string(ctx,"SQLITE_UTF16");
	duk_push_int(ctx,SQLITE_UTF16BE);
	duk_put_global_string(ctx,"SQLITE_UTF16BE");
	duk_push_int(ctx,SQLITE_UTF16LE);
	duk_put_global_string(ctx,"SQLITE_UTF16LE");
	duk_push_int(ctx,SQLITE_UTF16_ALIGNED);
	duk_put_global_string(ctx,"SQLITE_UTF16_ALIGNED");
	duk_push_int(ctx,SQLITE_UTF8);
	duk_put_global_string(ctx,"SQLITE_UTF8");
	duk_push_int(ctx,SQLITE_VERSION);
	duk_put_global_string(ctx,"SQLITE_VERSION");
	duk_push_int(ctx,SQLITE_VERSION_NUMBER);
	duk_put_global_string(ctx,"SQLITE_VERSION_NUMBER");
	duk_push_int(ctx,SQLITE_VTAB_CONSTRAINT_SUPPORT);
	duk_put_global_string(ctx,"SQLITE_VTAB_CONSTRAINT_SUPPORT");
	duk_push_int(ctx,SQLITE_VTAB_DIRECTONLY);
	duk_put_global_string(ctx,"SQLITE_VTAB_DIRECTONLY");
	duk_push_int(ctx,SQLITE_VTAB_INNOCUOUS);
	duk_put_global_string(ctx,"SQLITE_VTAB_INNOCUOUS");
	duk_push_int(ctx,SQLITE_WARNING);
	duk_put_global_string(ctx,"SQLITE_WARNING");
	duk_push_int(ctx,SQLITE_WARNING_AUTOINDEX);
	duk_put_global_string(ctx,"SQLITE_WARNING_AUTOINDEX");
	duk_push_int(ctx,SQLITE_WIN32_DATA_DIRECTORY_TYPE);
	duk_put_global_string(ctx,"SQLITE_WIN32_DATA_DIRECTORY_TYPE");
	duk_push_int(ctx,SQLITE_WIN32_TEMP_DIRECTORY_TYPE);
	duk_put_global_string(ctx,"SQLITE_WIN32_TEMP_DIRECTORY_TYPE");
	//--constants
	//----------------------------------------
	duk_push_c_function(ctx,native_sqlite3_open,2);
	duk_put_global_string(ctx,"sqlite3_open");
	duk_push_c_function(ctx,native_sqlite3_close,1);
	duk_put_global_string(ctx,"sqlite3_close");
	duk_push_c_function(ctx,native_sqlite3_errmsg,1);
	duk_put_global_string(ctx,"sqlite3_errmsg");
	duk_push_c_function(ctx,native_sqlite3_prepare_v2,3);
	duk_put_global_string(ctx,"sqlite3_prepare_v2");
	duk_push_c_function(ctx,native_sqlite3_exec,2);
	duk_put_global_string(ctx,"sqlite3_exec");
	duk_push_c_function(ctx,native_sqlite3_step,1);
	duk_put_global_string(ctx,"sqlite3_step");
	duk_push_c_function(ctx,native_sqlite3_finalize,1);
	duk_put_global_string(ctx,"sqlite3_finalize");
	duk_push_c_function(ctx,native_sqlite3_reset,1);
	duk_put_global_string(ctx,"sqlite3_reset");
	duk_push_c_function(ctx,native_sqlite3_column_count,1);
	duk_put_global_string(ctx,"sqlite3_column_count");
	//----------------------------------------
	duk_push_c_function(ctx,native_sqlite3_column_text,2);
	duk_put_global_string(ctx,"sqlite3_column_text");
	duk_push_c_function(ctx,native_sqlite3_column_double,2);
	duk_put_global_string(ctx,"sqlite3_column_double");
	duk_push_c_function(ctx,native_sqlite3_column_int,2);
	duk_put_global_string(ctx,"sqlite3_column_int");
	duk_push_c_function(ctx,native_sqlite3_column_int64,2);
	duk_put_global_string(ctx,"sqlite3_column_int64");
	duk_push_c_function(ctx,native_sqlite3_column_text16,2);
	duk_put_global_string(ctx,"sqlite3_column_text16");
/* todo: expose more functions
	duk_push_c_function(ctx,native_sqlite3_column_blob,2);
	duk_put_global_string(ctx,"sqlite3_column_blob");
	duk_push_c_function(ctx,native_sqlite3_column_value,2);
	duk_put_global_string(ctx,"sqlite3_column_value");
	duk_push_c_function(ctx,native_sqlite3_column_bytes,2);
	duk_put_global_string(ctx,"sqlite3_column_bytes");
	duk_push_c_function(ctx,nativesqlite3_column_bytes16_,2);
	duk_put_global_string(ctx,"sqlite3_column_bytes16");
*/
	duk_push_c_function(ctx,native_sqlite3_column_type,2);
	duk_put_global_string(ctx,"sqlite3_column_type");
	duk_push_c_function(ctx,native_sqlite3_column_name,2);
	duk_put_global_string(ctx,"sqlite3_column_name");
	//----------------------------------------
	//parameter binding
	//----------------------------------------
	duk_push_c_function(ctx,native_sqlite3_bind_blob,2);
	duk_put_global_string(ctx,"native_sqlite3_bind_blob");
	duk_push_c_function(ctx,native_sqlite3_bind_blob64,3);
	duk_put_global_string(ctx,"sqlite3_bind_blob64");
	duk_push_c_function(ctx,native_sqlite3_bind_double,2);
	duk_put_global_string(ctx,"sqlite3_bind_double");
	duk_push_c_function(ctx,native_sqlite3_bind_int,3);
	duk_put_global_string(ctx,"sqlite3_bind_int");
	duk_push_c_function(ctx,native_sqlite3_bind_int64,3);
	duk_put_global_string(ctx,"sqlite3_bind_int64");
	duk_push_c_function(ctx,native_sqlite3_bind_null,2);
	duk_put_global_string(ctx,"sqlite3_bind_null");
	duk_push_c_function(ctx,native_sqlite3_bind_text,4);
	duk_put_global_string(ctx,"sqlite3_bind_text");
	duk_push_c_function(ctx,native_sqlite3_bind_text16,2);
	duk_put_global_string(ctx,"sqlite3_bind_text16");
	duk_push_c_function(ctx,native_sqlite3_bind_text64,5);
	duk_put_global_string(ctx,"sqlite3_bind_text64");
	//duk_push_c_function(ctx,native_sqlite3_bind_value,2);
	//duk_put_global_string(ctx,"sqlite3_bind_value");
	duk_push_c_function(ctx,native_sqlite3_bind_pointer,3);
	duk_put_global_string(ctx,"sqlite3_bind_pointer");
	duk_push_c_function(ctx,native_sqlite3_bind_zeroblob,3);
	duk_put_global_string(ctx,"sqlite3_bind_zeroblob");
	duk_push_c_function(ctx,native_sqlite3_bind_zeroblob64,3);
	duk_put_global_string(ctx,"bind_zeroblob64");
	//----------------------------------------
	//duk_pop(ctx);
}