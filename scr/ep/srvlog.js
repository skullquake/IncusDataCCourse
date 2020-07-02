/**
 * @file scr/ep/srvlog.js
 * @author Ockert van Schalkwyk
 * @brief database server log endpoint management
 * @version 0.1
 */
/*! loads */
load('./scr/lib/db.js');
/*! Main driver - called at end of this script
 *  \return 0 on success, !0 on error
 */
function main(){
	log("info:ep:srvlog:start");
	try{
		var r=dbquery("./db/a.db","SELECT * from SRVLOG",function(){});
		mg_printf(nc,"HTTP/1.0 200 OK\r\n");
		mg_printf(nc,"Content-Type: application/json\r\n");
		mg_printf(nc,"\r\n");
		mg_printf(nc,JSON.stringify(r,0,'\t'));
		log("info:ep:srvlog:end");
	}catch(e){
		mg_printf(nc,"HTTP/1.0 200 OK\r\n");
		mg_printf(nc,"Content-Type: application/json\r\n");
		mg_printf(nc,"\r\n");
		mg_printf(nc,JSON.stringify({err:e.String()}));
	}
	return 0;
}
//--------------------------------------------------------------------------------
main();//!
//--------------------------------------------------------------------------------
