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
	jstestcaca();
	log('Info: main(): end');
	return 0;
}
function jstestcaca(){
	var dp=caca_create_display();
	cv=caca_get_canvas(dp);
	caca_set_display_title(dp,"Hello!");
	//caca_set_color_ansi(cv, CACA_BLACK, CACA_WHITE);
	var glyphs='.:xX'
	while(true){//for(var i=0;i<4096*32;i++){
		caca_put_str(cv,Math.random()*128,Math.random()*32,glyphs[Math.floor(Math.random()*glyphs.length)]);
		caca_refresh_display(dp);
	}
	caca_get_event(dp,CACA_EVENT_KEY_PRESS/*, &ev, -1*/);
	caca_free_display(dp);
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
