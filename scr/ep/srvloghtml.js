/**
 * @file scr/ep/srvloghtml.js
 * @author Ockert van Schalkwyk
 * @brief require test
 * @version 0.1
 */
load('./scr/lib/db.js');
/*! loads */
/*! Main driver - called at end of this script
 *  \return 0 on success, !0 on error
 */
function main(){
	log('Info: main(): start');
	mg_printf(nc,"HTTP/1.0 200 OK\r\n");
	mg_printf(nc,"Content-Type: text/html\r\n");
	mg_printf(nc,"\r\n");
	var r=dbquery("./db/a.db","SELECT * from SRVLOG",function(){log("stub callback");});
	try{
		Node=require("./scr/mod/wid/node.js");
		ntable=new Node().setNodeName('table');
		r.rows.forEach(function(row,rowix){
			nrow=new Node().setNodeName('table');
			row.forEach(function(col,colix){
				nrow.addChild(
					new Node()
						.setNodeName('td')
						.setText(col)
				);
			})
			ntable.addChild(nrow);
		});
		mg_printf(nc,ntable.toString());
	}catch(e){
		mg_printf(nc,e.toString());
	}
	log('Info: main(): end');
	return 0;
}
Duktape.modSearch=function(id){
	res=readFile(id.split('?')[0]);
	//log(res);
	//res=readFile('res/'+id.split('?')[0]);//cachebusted
	if(typeof res==='string'){
		return res;
	}
}
function readFile(path){
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
