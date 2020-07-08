/**
 * @file scr/a.js
 * @author Ockert van Schalkwyk
 * @brief main function
 * @version 0.1
 */
load('./scr/ncurses/main.js');
load('./scr/dukglue/dukglue.js');
/*! Main driver - called at end of this script
 *  \return 0 on success, !0 on error
 */
function main(){
	log('Info: main(): start');
	//ncurses_test();
	dukglue_test();
	log('Info: main(): end');
	return 0;
}
//--------------------------------------------------------------------------------
main();//!
//--------------------------------------------------------------------------------
