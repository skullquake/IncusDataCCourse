/**
 * @file scr/caca/caca.js
 * @author Ockert van Schalkwyk
 * @brief caca tests
 * @version 0.1
 */
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
