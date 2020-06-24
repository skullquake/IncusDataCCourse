
/**
 * @file scr/a.js
 * @author Ockert van Schalkwyk
 * @brief main function
 * @version 0.1
 */
/*! loads */
load('./scr/lib/lib.js');
load('./scr/lib/db.js');
load('./scr/lib/fsutils.js');
/*! Main driver - called at end of this script
 *  \return 0 on success, !0 on error
 */
function main(){
	log('Info: main(): start');
	mg_printf(nc,"HTTP/1.0 200 OK\r\n");
	mg_printf(nc,"Content-Type: text/plain\r\n");
	mg_printf(nc,"\r\n");
	for(var i=0;i<32;i++){
		mg_printf(nc,"test "+i+"\n");
	}
	log('Info: main(): end');
	return 0;
}
//--------------------------------------------------------------------------------
main();//!
//--------------------------------------------------------------------------------
