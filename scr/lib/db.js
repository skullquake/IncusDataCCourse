/**
 * @file scr/db.js
 * @author Ockert van Schalkwyk
 * @brief Preliminary SQLITE database JavaScript utility function and test functions
 *
 * Todo: Turn into class, where database object is reused, and destructor closes database
 *       and frees resources
 *
 * @version 0.1
 */

/*! Javascript utility functions test
 *  \return nothing
 */
function sqlitetest(){
	NROWS=32;
	NFIELDS=32;
	log('Info: sqlitetest(): start')
	//database operations
	var results=[];
	//exec test
	log("Info: Dropping table...");
	var r=dbexec('./db/a.db',"drop table if exists FOO");
	results.push(r);

	log("Info: Creating table...");
	//create create table query...
	var tablename="FOO";
	var fields={};
	for(var i=0;i<NFIELDS;i++){
		fields['field'+i]={
			type:"text"
		};
	}
	var q="create table if not exists $TABLENAME($FIELDS)";
	q=q
		.replace(
			"$TABLENAME",
			tablename
		)
		.replace(
			"$FIELDS",
			(function(){
				var ret=[];
				Object.keys(fields).forEach(function(fieldname,fieldidx){
					ret.push([fieldname,fields[fieldname].type].join(' '));
				});
				return ret.join(',');
			})()
		)
	var r=dbexec('./db/a.db',q);
	results.push(r);
	log("Info: Generating data...");
	//create data for prepared statement, a two dimensional array
	var pdata=[];
	for(var i=0;i<NROWS;i++){
		var pdatarow=[];
		Object.keys(fields).forEach(function(fieldname,fieldidx){
			switch(fields[fieldname].type){
				case 'text':
					pdatarow.push(""+Math.floor(8*Math.random()));
					break;
				case 'number':
					pdatarow.push(Math.floor(8*Math.random()));
					break;
				case 'default':
					pdatarow.push(null)
					break;
			}
		});
		pdata.push(pdatarow);

	}
	log("Info: Creating insert statement SQL...");
	q="INSERT INTO FOO($FIELDS) VALUES($PARAMS)"
	q=q
		.replace(
			"$FIELDS",
			(function(){
				var ret=[];
				Object.keys(fields).forEach(function(fieldname,fieldidx){
					ret.push(fieldname);
				});
				return ret.join(',');
			})()
		).replace(
			"$PARAMS",
			(function(){
				var ret=[];
				Object.keys(fields).forEach(function(fieldname,fieldidx){
					ret.push("?");
				});
				return ret.join(',');
			})()
		)
	log(q);
	log(pdata);
	log("Info: Executing SQL...");
	dbexecprepared("./db/a.db",q,pdata);
	//query test
	var r=dbquery("./db/a.db","SELECT * from FOO","res",function(){});
	results.push(r);
	//respond
	print("Content-Type: application/json\n\n")
	println(JSON.stringify(results,0,'\t'));
	log('Info: sqlitetest(): end')
}

/*! Development test
 *  \return nothing
 */
function sqlitetestNative(){
	log('Info: sqlitetest(): start')
	try{
		var dbpath="./db/a.db";
		var dbvarnam="db";
		var rc=sqlite3_open(dbpath,dbvarnam);
		db=eval(dbvarnam);//workaround for now, use object arg later
		if(rc!=SQLITE_OK){
			log("Error: Failed to open database "+dbpath);
			log(sqlite3_errmsg(db));
		}else{
			log("Info: Database "+dbpath+" opened");
			//----------------------------------------
			//create table
			//----------------------------------------
			rc=sqlite3_exec(db,"create table if not exists FOO(a text,b text)");
			if(rc!=SQLITE_OK){
				log("Error: Failed to create table");
				log(sqlite3_errmsg(db));
			}else{
				//parepared statement test
				log("Info: Table created");
				//----------------------------------------
				//populate table
				//----------------------------------------
				rc = sqlite3_prepare_v2(db, "INSERT INTO FOO(a,b)VALUES(?,?)","res");
				if(rc!=SQLITE_OK){
					log("Error: Failed to create prepared statement");
					log(sqlite3_errmsg(db));
				}else{
					log("Info: Prepared statement created");
					rc=sqlite3_exec(db,"BEGIN TRANSACTION");    
					if(rc!=SQLITE_OK){
						log("Error: Failed to create prepared statement");
						log(sqlite3_errmsg(db));
					}else{
						log("Info: Transaction started");
						//create data
						var arrparameters=[];
						for(var i=0;i<4096;i++){
							arrparameters.push(["foo"+i,"bar"+i]);
						}
						//insert data into table
						arrparameters.forEach(function(parameter,parameteridx){
							log("Info: Inserting "+JSON.stringify(parameter));
							rc=sqlite3_bind_text(res,1,parameter[0],parameter[0].length);
							if(rc!=SQLITE_OK){
								log("Error: Failed bind parameter");
								log(sqlite3_errmsg(db));
							}else{
								//log("Info: parameter bound");
							}
							rc=sqlite3_bind_text(res,2,parameter[1],parameter[1].length);
							if(rc!=SQLITE_OK){
								log("Error: Failed bind parameter");
								log(sqlite3_errmsg(db));
							}else{
								log("Info: parameter bound");
							}
							rc=sqlite3_step(res);
							if(rc!=SQLITE_DONE){
								log("Error: Failed to commit");
								log(sqlite3_errmsg(db));
							}else{
								log("Info: Transaction ended");
							}
							sqlite3_reset(res);
						});
						rc=sqlite3_exec(db,"COMMIT TRANSACTION");    
						if(rc!=SQLITE_OK){
							log("Error: Failed to end prepared statement");
							log(sqlite3_errmsg(db));
						}else{
							log("Info: Transaction comitted");
							sqlite3_finalize(res);
							if(rc!=SQLITE_OK){
								log("Error: Failed to finalize statement");
								log(sqlite3_errmsg(db));
							}else{
								log("Info: Statement finalized");
							}
						}
					}
					//----------------------------------------
					//select from table
					//----------------------------------------
					rc=sqlite3_prepare_v2(db,"SELECT * from FOO","res");
					if(rc!=SQLITE_OK){
						log("Error: Failed to open database "+dbpath);
						log(sqlite3_errmsg(db));
					}else{
						log("Info: Query executed on "+dbpath+" successfully");
						var rowidx=0;
						log('----------------------------------------')
						log('FOO:');
						log('----------------------------------------')
						while(sqlite3_step(res)==SQLITE_ROW){
							//log("Info: Row ["+rowidx+"]");
							//log("Info: Column Count: "+sqlite3_column_count(res));
							var rowObj=[];
							for(var colidx=0;colidx<sqlite3_column_count(res);colidx++){
								var objtypes={};
								objtypes[SQLITE_INTEGER]="integer";
								objtypes[SQLITE_FLOAT]="float";
								objtypes[SQLITE_TEXT]="text";
								objtypes[SQLITE_BLOB]="blob";
								objtypes[SQLITE_NULL]="null";
								var strtype=objtypes[sqlite3_column_type(res,colidx)];
								var colnam=sqlite3_column_name(res,colidx);
								//log("Info: Column ["+colidx+"]["+strtype+"]["+colnam+"] Value: "+sqlite3_column_text(res,colidx));
								rowObj.push(sqlite3_column_text(res,colidx));
							}
							//log(rowObj.join(','));
							println(rowObj.join(','));
							rowidx++;
						}
						log('----------------------------------------')
					}
				}
			}
			sqlite3_close(db);
			log("Info: Database "+dbpath+" closed");
		};
	}catch(e){
		log(e.toString());
		ret.err=e.toString();
	}
	log('Info: sqlitetest(): end')
}

/*! Database execute
 *  \param `String` dbpath path to database file
 *  \q `String` sql statement 
 *  \return `Object` containing status/error
 */
function dbexec(dbpath,q,cb){
	log('Info: dbexec(): start')
	var ret={};
	try{
		var dbvarnam="db";
		var rc=sqlite3_open(dbpath,dbvarnam);
		db=eval(dbvarnam);//workaround for now, use object arg later
		if(rc!=SQLITE_OK){
			log("Error: Failed to open database "+dbpath);
			log(sqlite3_errmsg(db));
			ret.err=sqlite3_errmsg(db);
		}else{
			log("Info: Database "+dbpath+" opened");
			rc=sqlite3_exec(db,q);
			if(rc!=SQLITE_OK){
				log("Error: Failed to create table");
				ret.err=sqlite3_errmsg(db);
			}else{
				ret.msg='Statement executed';
			}
			sqlite3_close(db);
			log("Info: Database "+dbpath+" closed");
		};
	}catch(e){
		log(e.toString());
		ret.err=e.toString();
	}
	log('Info: dbexec(): end')
	return ret;
}

/*! Database execute prepared statements (unimplemented)
 *  \param `String` dbpath path to database file
 *  \q `String` sql statement 
 *  \pdata `Array` prepared statement data
 *  \return `Object` containing result/error
 */
function dbexecprepared(dbpath,q,pdata){
	log('Info: dbexecprepared(): start')
	var ret={rows:[]};
	try{
		var dbvarnam="db";
		var rc=sqlite3_open(dbpath,dbvarnam);
		db=eval(dbvarnam);//workaround for now, use object arg later
		if(rc!=SQLITE_OK){
			log("Error: Failed to open database "+dbpath);
			log(sqlite3_errmsg(db));
			ret.err=sqlite3_errmsg(db);
		}else{
			log("Info: Database "+dbpath+" opened");
			rc = sqlite3_prepare_v2(db,q,"res");
			if(rc!=SQLITE_OK){
				log("Error: Failed to create prepared statement");
				log(sqlite3_errmsg(db));
				ret.err=sqlite3_errmsg(db);
			}else{
				log("Info: Prepared statement created");
				rc=sqlite3_exec(db,"BEGIN TRANSACTION");    
				if(rc!=SQLITE_OK){
					log("Error: Failed to create prepared statement");
					log(sqlite3_errmsg(db));
					ret.err=sqlite3_errmsg(db);
				}else{
					log("Info: Transaction started");
					//create data
					var arrparameters=pdata;
					//insert data into table
					arrparameters.forEach(function(parameterrow,parameteridx){
						log("Info: Inserting "+JSON.stringify(parameterrow));
						parameterrow.forEach(function(parametercol,parameteridx){
							rc=sqlite3_bind_text(res,1+parameteridx,parametercol,parametercol.length);
							if(rc!=SQLITE_OK){
								log("Error: Failed bind parameter");
								log(sqlite3_errmsg(db));
							}else{
								//log("Info: parameter bound");
							}
						})
						rc=sqlite3_step(res);
						if(rc!=SQLITE_DONE){
							log("Error: Failed to commit");
							log(sqlite3_errmsg(db));
						}else{
							log("Info: Transaction ended");
						}
						sqlite3_reset(res);
					});
					rc=sqlite3_exec(db,"COMMIT TRANSACTION");    
					if(rc!=SQLITE_OK){
						log("Error: Failed to end prepared statement");
						log(sqlite3_errmsg(db));
						ret.err=sqlite3_errmsg(db);
					}else{
						log("Info: Transaction comitted");
						sqlite3_finalize(res);
						if(rc!=SQLITE_OK){
							log("Error: Failed to finalize statement");
							log(sqlite3_errmsg(db));
							ret.err=sqlite3_errmsg(db);
						}else{
							log("Info: Statement finalized");
						}
					}
				}
			}
			sqlite3_close(db);
			log("Info: Database "+dbpath+" closed");
		};
	}catch(e){
		log(e.toString());
		ret.err=e.toString();
	}
	log('Info: dbexecprepared(): end')
	return ret;













}

/*! Database execute prepared statements (partially implemented)
 *  \param `String` dbpath path to database file
 *  \q `String` sql statement 
 *  \cb `Function` row callback function (unimplemented)
 *  \return `Object` containing result/error
 */
function dbquery(dbpath,q,cb){
	log('Info: dbquery(): start')
	var ret={rows:[]};
	try{
		var dbvarnam="db";
		var rc=sqlite3_open(dbpath,dbvarnam);
		db=eval(dbvarnam);//workaround for now, use object arg later
		if(rc!=SQLITE_OK){
			log("Error: Failed to open database "+dbpath);
			log(sqlite3_errmsg(db));
			ret.err=sqlite3_errmsg(db);
		}else{
			log("Info: Database "+dbpath+" opened");
			//----------------------------------------
			//select from table
			//----------------------------------------
			rc=sqlite3_prepare_v2(db,q,'res');
			if(rc!=SQLITE_OK){
				log("Error: Failed to open database "+dbpath);
				log(sqlite3_errmsg(db));
				ret.err=sqlite3_errmsg(db);
			}else{
				log("Info: Query executed on "+dbpath+" successfully");
				var rowidx=0;
				while(sqlite3_step(res)==SQLITE_ROW){
					var rowObj=[];
					for(var colidx=0;colidx<sqlite3_column_count(res);colidx++){
						var objtypes={};
						objtypes[SQLITE_INTEGER]="integer";
						objtypes[SQLITE_FLOAT]="float";
						objtypes[SQLITE_TEXT]="text";
						objtypes[SQLITE_BLOB]="blob";
						objtypes[SQLITE_NULL]="null";
						var strtype=objtypes[sqlite3_column_type(res,colidx)];
						var colnam=sqlite3_column_name(res,colidx);
						//log("Info: Column ["+colidx+"]["+strtype+"]["+colnam+"] Value: "+sqlite3_column_text(res,colidx));
						rowObj.push(sqlite3_column_text(res,colidx));//todo, handle types and push with correct function
					}
					ret.rows.push(rowObj);
					rowidx++;
				}
			}
			sqlite3_close(db);
			log("Info: Database "+dbpath+" closed");
		};
	}catch(e){
		log(e.toString());
		ret.err=e.toString();
	}
	log('Info: dbquery(): end')
	return ret;
}

function sqlitetest2(){
	log('Info: sqlitetest(): start')
	try{
		var dbpath="./db/a.db";
		var dbvarnam="db";
		var rc=sqlite3_open(dbpath,dbvarnam);
		db=eval(dbvarnam);//workaround for now, use object arg later for reference modification, simple variable parameters dont support this in js
		if(rc!=SQLITE_OK){
			log("Error: Failed to open database "+dbpath);
			log(sqlite3_errmsg(db));
			return -1;
		}
		log("Info: Database "+dbpath+" opened");
		//----------------------------------------
		//drop table
		//----------------------------------------
		rc=sqlite3_exec(db,"drop table if exists FOO");
		if(rc!=SQLITE_OK){
			log("Error: Failed to create table");
			log(sqlite3_errmsg(db));
			sqlite3_close(db);
			return -1;
		}
		//----------------------------------------
		//create table
		//----------------------------------------
		rc=sqlite3_exec(db,"create table if not exists FOO(a text,b text)");
		if(rc!=SQLITE_OK){
			log("Error: Failed to create table");
			log(sqlite3_errmsg(db));
			sqlite3_close(db);
			return -1;
		}
		//----------------------------------------
		//populate table
		//----------------------------------------
		rc = sqlite3_prepare_v2(db, "INSERT INTO FOO(a,b)VALUES(?,?)","res");
		if(rc!=SQLITE_OK){
			log("Error: Failed to create prepared statement");
			log(sqlite3_errmsg(db));
			sqlite3_close(db);
			return -1;
		}
		rc=sqlite3_exec(db,"BEGIN TRANSACTION");    
		if(rc!=SQLITE_OK){
			log("Error: Failed to create prepared statement");
			sqlite3_close(db);
			return -1;
		}
		//create data
		var arrparameters=[];
		for(var i=0;i<4096;i++){
			arrparameters.push(["foo"+i,"bar"+i]);
		}
		//insert data into table
		arrparameters.forEach(function(parameter,parameteridx){
			log("Info: Inserting "+JSON.stringify(parameter));
			rc=sqlite3_bind_text(res,1,parameter[0],parameter[0].length);
			if(rc!=SQLITE_OK){
				log("Error: Failed bind parameter");
				log(sqlite3_errmsg(db));
			}else{
				//log("Info: parameter bound");
			}
			rc=sqlite3_bind_text(res,2,parameter[1],parameter[1].length);
			if(rc!=SQLITE_OK){
				log("Error: Failed bind parameter");
				log(sqlite3_errmsg(db));
			}else{
				log("Info: parameter bound");
			}
			rc=sqlite3_step(res);
			if(rc!=SQLITE_DONE){
				log("Error: Failed to commit");
				log(sqlite3_errmsg(db));
			}else{
				log("Info: Transaction ended");
			}
			sqlite3_reset(res);
		});
		rc=sqlite3_exec(db,"COMMIT TRANSACTION");    
		if(rc!=SQLITE_OK){
			log("Error: Failed to end prepared statement");
			log(sqlite3_errmsg(db));
			sqlite3_close(db);
			return -1;
		}
		sqlite3_finalize(res);
		if(rc!=SQLITE_OK){
			log("Error: Failed to finalize statement");
			log(sqlite3_errmsg(db));
			sqlite3_close(db);
			return -1;
		}
		//----------------------------------------
		//select from table
		//----------------------------------------
		rc=sqlite3_prepare_v2(db,"SELECT * from FOO","res");
		if(rc!=SQLITE_OK){
			log("Error: Failed to open database "+dbpath);
			log(sqlite3_errmsg(db));
			sqlite3_close(db);
			return -1;
		}
		var rowidx=0;
		while(sqlite3_step(res)==SQLITE_ROW){
			var rowObj=[];
			for(var colidx=0;colidx<sqlite3_column_count(res);colidx++){
				var objtypes={};
				objtypes[SQLITE_INTEGER]="integer";
				objtypes[SQLITE_FLOAT]="float";
				objtypes[SQLITE_TEXT]="text";
				objtypes[SQLITE_BLOB]="blob";
				objtypes[SQLITE_NULL]="null";
				var strtype=objtypes[sqlite3_column_type(res,colidx)];
				var colnam=sqlite3_column_name(res,colidx);
				rowObj.push(sqlite3_column_text(res,colidx));
			}
			println(rowObj.join(','));
			rowidx++;
		}
		sqlite3_close(db);
		log("Info: Database "+dbpath+" closed");
	}catch(e){
		log(e.toString());
		ret.err=e.toString();
	}
	log('Info: sqlitetest(): end')
}

