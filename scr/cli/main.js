/**
 * @file scr/a.js
 * @author Ockert van Schalkwyk
 * @brief main function
 * @version 0.1
 */
/*! loads
load('./scr/lib/lib.js');
load('./scr/lib/db.js');
load('./scr/lib/fsutils.js');
 */
/*! Main driver - called at end of this script
 *  \return 0 on success, !0 on error
 */
function main(){
	log('Info: main(): start');
	caca_test();////rawtest();
	log('Info: main(): end');
	return 0;
}
//--------------------------------------------------------------------------------
function rawtest(){
	//log('info:rawtest:start');
	write(new Buffer("MyFmt002"));
	var nelem=8;								//nelem
	write(new Uint32Array([nelem]));					//write
	var val=0.0;
	for(var i=0;i<nelem;i++){						//loop
		val+=Math.random();
		write(new Float64Array([val]));					//write float chunk
	}
	var nelem=8;								//nelem
	write(new Uint32Array([nelem]));					//write
	val=0;
	for(var i=0;i<nelem;i++){						//loop
		val+=8;
		write(new Buffer(intToByteArray(val)));				//write float chunk
	}
	//log('info:rawtest:end');
};
//--------------------------------------------------------------------------------
main();//!
//--------------------------------------------------------------------------------
