
/**
 * @file scr/a.js
 * @author Ockert van Schalkwyk
 * @brief main function
 * @version 0.1
 */
/*! loads */
load('./scr/lib/lib.js');
load('./scr/lib/db.js');
/*! Main driver - called at end of this script
 *  \return 0 on success, !0 on error
 */
function main(){
	log('info:srv:init:start');
	dbexec('./db/a.db',file2str('./sql/schema.sql'));
	dbexec('./db/a.db',file2str('./sql/startup.sql'));
	log('info:srv:init:end');
	return 0;
}
function file2str(path){
	log("Info: freadtest: start");
	var ret=null;
	var filepath=path;
	var filemode="rb";
	var fp=fopen(filepath,filemode);
	if(fp==null){
		log("Error: freadtest: Failed to open file "+filepath);
	}else{
		var buf=new ArrayBuffer(1024);
		var dv=new DataView(buf);
		var bytesread=0;
		var contents="";
		ret='';
		while((bytesread=fread({buf:buf,size:1,count:32,stream:fp}))>0){
			if(bytesread>0){//change to standard while read
				var bufview=new Uint8Array(buf,0,bytesread);
				txt=new TextDecoder("utf-8").decode(buf);
				txt=new TextDecoder("utf-8").decode(bufview);
				if(typeof txt==='string'){
					ret+=txt;
				}else{
					log("Error: freadtest: failed to convert buffer to string");
				}
			}else{
				log("Error: freadtest: no bytes read\n");
			}
		}
		if(fclose(fp)==EOF){
			log("Error: freadtest: Failed to close file "+filepath);
		}else{
		}
	}
	return ret;
}
//--------------------------------------------------------------------------------
main();//!
//--------------------------------------------------------------------------------
