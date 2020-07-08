/**
 * @file scr/pthread/pthreada.js
 * @author Ockert van Schalkwyk
 * @brief pthread tests
 * @version 0.1
 */
function jstestpthread(){
	log("info:jstestpthread:start");
	for(var i=0;i<32;i++){
		try{
			var tobj0=mk_pthread_t();
			pthread_create(
				tobj0,
				0,
				function(){
					log('##callback['+i+']##');
					usleep(200000);
				},
				{}
			);
			//pthread_join(tobj0,0);
			free(tobj0);
		}catch(e){
			log(e.toString());
		}
	}
	log("info:jstestpthread:end");
}
