/**
 * @file scr/a.js
 * @author Ockert van Schalkwyk
 * @brief main function
 * @version 0.1
 */
/*! Main driver - called at end of this script
 *  \return 0 on success, !0 on error
 */
function main(){
	log('info:curl:main():start');
	try{
		var errorbuf=malloc(CURL_ERROR_SIZE+1);
		var databufsz=4096;
		var databuf=malloc(databufsz);
		//curl_test();
		for(var i=0;i<4;i++){
			curl_global_init(CURL_GLOBAL_ALL);
			var hdl=curl_easy_init();
			var r;
			var r=curl_easy_setopt(hdl,CURLOPT_ERRORBUFFER,errorbuf);
			if(r!=CURLE_OK){
				log("error:curl:curl_easy_perform:CURLOPT_ERRORBUFFER");
			}
			r=curl_easy_setopt(hdl,CURLOPT_URL,"http://127.0.0.1:1234/duk?scr=./scr/ep/main.js");
			if(r!=CURLE_OK){
				log("error:curl:curl_easy_perform:CURLOPT_URL");
				printf(errorbuf);
				printf("\n");
			}
			r=curl_easy_setopt(hdl,CURLOPT_FOLLOWLOCATION,1);
			if(r!=CURLE_OK){
				log("error:curl:curl_easy_perform:CURLOPT_FOLLOWLOCATION");
				printf(errorbuf);
				printf("\n");
			}
			/*
			r=curl_easy_setopt(hdl,CURLOPT_WRITEDATA,databuf);
			if(r!=CURLE_OK){
				log("error:curl:curl_easy_perform:CURLOPT_WRITEDATA");
				printf(errorbuf);
				printf("\n");
			}
			*/
			//r=curl_easy_setopt(hdl,CURLOPT_CONNECT_ONLY,1);
			if(r!=CURLE_OK){
				log("error:curl:curl_easy_perform:CURLOPT_CONNECT_ONLY");
				printf(errorbuf);
				printf("\n");
			}
			r=curl_easy_perform(hdl);
			//CURL_EXTERN CURLcode curl_easy_recv(CURL *curl, void *buffer, size_t buflen,size_t *n);
			r=curl_easy_recv(hdl,databuf,databufsz,1);
			if(r!=CURLE_OK){
				log("error:curl:curl_easy_recv");
				printf(errorbuf);
				printf("\n");
			}
			printf(databuf);
			curl_easy_cleanup(hdl);
		}
		free(errorbuf);
		free(databuf);
		/*
		a=malloc(32);
		sprintf(a,"lorem\nipsum\n");
		printf(a);
		free(a);
		//printf("asdf");      
		*/
	}catch(e){
		log("error:curl:main():"+e.toString());
	}
	log('info:curl:main():end');
	return 0;
}
//--------------------------------------------------------------------------------
main();//!
//--------------------------------------------------------------------------------
