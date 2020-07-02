/**
 * @file scr/lib.js
 * @author Ockert van Schalkwyk
 * @brief Various utility functions. Todo: turn into module, to avoid reloading
 * @version 0.1
 */
/*! Extract some information from the global `Duktape` object and convert
 *  to `JSON` object
 *  \return `JSON` object containing information
 */
function dukEnv2Obj(){
	log('Info: dukEnv2Obj():start')
	var ret={
		version:Duktape.version,
		env:Duktape.env,
		info:Duktape.info(),
		gc:Duktape.gc()
	};
	log('Info: dukEnv2Obj():end')
	return ret;
}
/*! Generate buffer - test
 *  Reference: https://wiki.duktape.org/howtobuffers1x
 *  \return `JSON` object containing some data
 */
function genBuffer(){
	log('Info: genBuffer():start')
	var ret={};
	try{

		var buf0=null;
		{
			var plain=Duktape.dec('hex', '4142434445464748');
			var buf0=new Buffer(plain);
			buf0[0]=0x61;
		}
		var buf1=null;
		{
			// Create a plain buffer of 8 bytes
			var buf1 = new Buffer(8);
			// Fill it using index properties
			for (var i = 0; i < buf1.length; i++) {
			    buf1[i] = 0x41 + i;
			}
			// Print other virtual properties
			log(buf1.length);             // -> 8
			log(buf1.byteLength);         // -> 8
			log(buf1.byteOffset);         // -> 0
			log(buf1.BYTES_PER_ELEMENT);  // -> 1
			log(buf1);  // -> 1
			log('enc:');
			log(Duktape.enc('jx', buf1)); // -> |4142434445464748|
			// Because a buf1 buffer doesn't have an actual property table, new
			// properties cannot be added (this behavior is similar to a buf1 string).
			buf1.dummy = 'foo';
			log(buf1.dummy);              // -> undefined
			// Duktape JX format can be used for dumping
			log(Duktape.enc('jx', buf1)); // -> |4142434445464748|
			// typeof is 'buffer'
			log(typeof buf1);             // -> buffer
		}
		ret={
			buf0:buf0,
			buf1:buf1,
		};
	}catch(e){
		ret.err=e.toString();
	}
	log('Info: genBuffer():end')
	return ret;
}
/*! Module search implementation
 *  \return nothing
 */
Duktape.modSearch=function(id){
	log("Info: Duktape.modsearch: start");
	log("Info: Duktape.modsearch: importing "+id);
	try{
		res=FileIo.readfile('./scr/'+id+'.js')
		res=new TextDecoder("utf-8").decode(res);
		if(typeof res==='string'){
			log("Info: Duktape.modsearch: "+id+" found");
			return res;
		}else{
			log("Error: Duktape.modsearch: "+id+" not found");
		}
	}catch(e){
		log("Info: Duktape.modsearch: failed to import "+id+":"+e.toString());
	}
	log("Info: Duktape.modsearch: end");
}
