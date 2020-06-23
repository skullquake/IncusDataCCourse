/**
 * @file scr/fsutils.js
 * @author Ockert van Schalkwyk
 * @brief Various file system utilities
 * @version 0.1
 */
/*! Test function for fread */
function freadtest(){
	log("Info: freadtest: start");
	var ret={msg:''};
	var filepath="./a.txt";
	var filemode="rb";
	log("Info: freadtest: opening file "+filepath);
	var fp=fopen(filepath,filemode);
	if(fp==null){
		log("Error: freadtest: Failed to open file "+filepath);
	}else{
		log("Info: freadtest: file opened");
		var buf=new ArrayBuffer(1024);
		var dv=new DataView(buf);
		var bytesread=0;
		var contents="";
		while((bytesread=fread({buf:buf,size:1,count:32,stream:fp}))>0){
			//todo: the buffer is passed in 'via reference' and populated up to a point
			//      the value returned by fread is the point up to where the buffer was
			//	populated. When reading the buffer, you then have to read up to this point
			//	Depending on how appropriate this, the buffer may need to be adjusted
			//	in C and resized automatically so you can just use it immediately
			//	in the script
			//	Alternatively a data view or new buffer can be created off the
			//	original buffer used in the read
			//reference: https://wiki.duktape.org/howtobuffers2x
			if(bytesread>0){//change to standard while read
				var bufview=new Uint8Array(buf,0,bytesread);log("");log("bufview.length:"+bufview.length);
				txt=new TextDecoder("utf-8").decode(buf);
				txt=new TextDecoder("utf-8").decode(bufview);
				if(typeof txt==='string'){
					ret.msg+=txt;
				}else{
					log("Error: freadtest: failed to convert buffer to string");
				}
			}else{
				log("Error: freadtest: no bytes read\n");
			}
		}
		log_("\n");

		/*
		bytesread=fread({buf:buf,size:1,count:buf.length,stream:fp});
		log("Info: freadtest: buffer length: "+buf.length);
		if(bytesread>0){//change to standard while read
			log("Info: freadtest: "+bytesread+" bytes read");
			res=new TextDecoder("utf-8").decode(buf);
			if(typeof res==='string'){
				log("Info: freadtest: contents:");
				log(res);
			}else{
				log("Error: freadtest: failed to convert buffer to string");
			}
		}else{
			log("Error: freadtest: no bytes read\n");
		}
		*/

		if(fclose(fp)==EOF){
			log("Error: freadtest: Failed to close file "+filepath);
		}else{
			log("Info: freadtest: File "+filepath+" closed");
		}
	}
	log("Info: freadtest: end");
	return ret;
}
/*! Test function for fwrite */
function fwritetest(){
	log("Info: fwritetest: start");
	var ret={};
	var filepath="./a.txt";
	var filemode="wb+";
	log("Info: fwritetest: opening file "+filepath);
	var fp=fopen(filepath,filemode);
	if(fp==null){
		log("Error: fwritetest: Failed to open file "+filepath);
	}else{
		log("Info: fwritetest: file opened");
		var glyphs="0123456789abcde";
		var msg=""
		var msglen=512;
		for(var i=0;i<msglen;i++){
			msg+=glyphs[Math.floor(Math.random()*glyphs.length)]
		}
		var buf=new Buffer(msg);
		var byteswritten=fwrite(buf,1,buf.length,fp);
		log("Info: fwritetest: buffer length: "+buf.length);
		log("Info: fwritetest: "+byteswritten+" bytes written");
		log("Info: fwritetest: closing file "+filepath);
		if(fclose(fp)==EOF){
			log("Error: fwritetest: Failed to close file "+filepath);
		}else{
			log("Info: fwritetest: File "+filepath+" closed");
		}
		fclose(fp);
	}
	log("Info: fwritetest: end");
	return ret;
}
/*! Test function for mkdir */
function mkdirtest(){
	log("Info: mkdirtest: start");
	println(typeof(mkdir_p));
	log("Info: S_IRWXU:"+S_IRWXU);
	log("Info: S_IRUSR:"+S_IRUSR);
	log("Info: S_IWUSR:"+S_IWUSR);
	log("Info: S_IXUSR:"+S_IXUSR);
	log("Info: S_IRWXG:"+S_IRWXG);
	log("Info: S_IRGRP:"+S_IRGRP);
	log("Info: S_IWGRP:"+S_IWGRP);
	log("Info: S_IXGRP:"+S_IXGRP);
	log("Info: S_IRWXO:"+S_IRWXO);
	log("Info: S_IROTH:"+S_IROTH);
	log("Info: S_IWOTH:"+S_IWOTH);
	log("Info: S_IXOTH:"+S_IXOTH);
	log("Info: S_ISUID:"+S_ISUID);
	log("Info: S_ISGID:"+S_ISGID);
	log('Info: main(): end')
	for(var i=0;i<32;i++){
		for(var j=0;j<32;j++){
			var dirpath="../out/test"+i+"/test"+j;
			log("Info: mkdirtest: creating "+dirpath);
			mkdir_p(dirpath,S_IRWXU);
		}
	}
	log("Info: mkdirtest: end");
}
/*! fileposition test
 *  \return nothing
 */
function filepositiontest(){
	log("Info: filepositiontest: start");
	//test constants
	log("Info: filepositiontest: SEEK_SET: "+SEEK_SET);
	log("Info: filepositiontest: SEEK_CUR: "+SEEK_CUR);
	log("Info: filepositiontest: SEEK_END: "+SEEK_END);
	var ret={msg:''};
	var filepath="./a.txt";
	var filemode="rb";
	log("Info: filepositiontest: opening file "+filepath);
	var fp=fopen(filepath,filemode);
	if(fp==null){
		log("Error: filepositiontest: Failed to open file "+filepath);
	}else{
		log("Info: filepositiontest: file opened");
		//fseek test
		fseek({stream:fp,offset:0,origin:SEEK_END});
		var filesize=ftell({stream:fp});//note new style, use argument as obj
		fseek({stream:fp,offset:4,origin:SEEK_SET});
		var buf=new ArrayBuffer(1024);
		var dv=new DataView(buf);
		var bytesread=0;
		var contents="";
		while((bytesread=fread({buf:buf,size:1,count:4,stream:fp}))>0){
			//test ftell
			//log("Info: filepositiontest: ftell: "+ftell({stream:fp}));//note new style, use argument as obj
			var bufview=new Uint8Array(buf,0,bytesread);
			txt=new TextDecoder("utf-8").decode(bufview);
			if(typeof txt==='string'){
				log_(txt);
			}else{
				log("Error: filepositiontest: failed to convert buffer to string");
			}
		}
		log_("\n");
		log("Info: filepositiontest: filesize: "+filesize);
		if(fclose(fp)==EOF){
			log("Error: filepositiontest: Failed to close file "+filepath);
		}else{
			log("Info: filepositiontest: File "+filepath+" closed");
		}
	}
	log("Info: filepositiontest: end");
	return ret;
}
/*! stat test
 *  \return nothing
 */
function stattest(){//also tests fstat
	log("Info: [f]stattest: start");
	var ret={};
	var filepath="./a.txt";
	var filemode="r";
	log("Info: [f]stattest: opening file "+filepath);
	var fp=fopen(filepath,filemode);
	if(fp==null){
		log("Error: [f]stattest: Failed to open file "+filepath);
	}else{
		log("Info: [f]stattest: opened "+filepath);
		fnum=fileno({stream:fp});
		log("Info: [f]stattest: fileno: "+fnum);
		log(JSON.stringify(fstat({fildes:fnum}),0,'\t'));
		if(fclose(fp)==EOF){
			log("Error: [f]stattest: Failed to close file "+filepath);
		}else{
			log("Info: [f]stattest: File "+filepath+" closed");
		}
	
	}
	ls("./").forEach(function(path,pathidx){
		log(path+":");
		log(JSON.stringify(stat({path:path}),0,'\t'));
	});
	log("Info: [f]stattest: end");
	return ret;
}
/*! dirent test
 *  \return nothing
 */
function direnttest(){
	log("Info: direnttest: start");
	var ret={};
	var dppath="/usr/bin";
	var dp=opendir({dirname:dppath});
	var ep=null;
	while((ep=readdir({dirp:dp}))!=null){
		var epjson=dirent2json({dirp:ep});
		var epstatjson=stat({path:dppath+"/"+epjson.d_name});
		log(JSON.stringify(epstatjson));
		log(JSON.stringify(epjson));
	}
	closedir({dirp:dp});
	log("Info: direnttest: end");
	return ret;
}
/*! recursive listing function
 *  \return `JSON` object with directory entries
 */
function lsrec(dppath,filter,ret){
	//todo: generate hierarchical structure as opposed to flat array
	//todo: test for symlinks, dont follow
	//todo: memory handling, cutting out when things get too extreme
	//todo: filter, for example if you want to filter by file extension
	//todo: combine contains and extension search criteria

	ret=ret==null?{path:dppath,entries:[]}:ret;
	filter=filter==null?{extension:null,contains:null}:filter;

	var dp=opendir({dirname:dppath});
	var ep=null;
	while((ep=readdir({dirp:dp}))!=null){
		var epjson=dirent2json({dirp:ep});
		var epstatjson=stat({path:dppath+"/"+epjson.d_name});
		if(epjson.d_name!='..'&&epjson.d_name!='.'){
			log(dppath+"/"+epjson.d_name)
			var add=false;
			if(filter.extension==null){
				add=true;
			}else
			if(
				epjson.d_name.indexOf('.'+filter.extension)==
				epjson.d_name.length-(filter.extension+1).length
			){
				add=true;
			}
			if(add){
				ret.entries.push({
					type:epstatjson.directory?"Directory":"File",
					name:epjson.d_name,
					path:dppath+"/"+epjson.d_name
				});
			}
			if(epstatjson.directory){
				lsrec(
					dppath+"/"+epjson.d_name,
					filter,
					ret
				);
			}else{
			}
		}
	}
	closedir({dirp:dp});
	return ret;
}
/*! recursive listing test function - outer function to call
 *  \return `JSON` object with directory entries
 */
function lsrectest(){
	log("Info: lsrectest: start");
	//ret=lsrec(".");
	ret=lsrec("/home/skullquake/src/KronosGroup",{extension:'xcf',contains:'exture'});
	log("Info: lsrectest: end");
	return ret;

}
/*! Utility for converting char to a byte array
 *  \return nothing
 */
function charToByteArray(/*long*/long) {
    // we want to represent the input as a 8-bytes array
    var byteArray = [0];
    for ( var index = 0; index < byteArray.length; index ++ ) {
        var byte = long & 0xff;
        byteArray [ index ] = byte;
        long = (long - byte) / 256 ;
    }

    return byteArray;
};
/*! Utility for converting short to a byte array
 *  \return nothing
 */
function shortToByteArray(/*long*/long) {
    // we want to represent the input as a 8-bytes array
    var byteArray = [0, 0];
    for ( var index = 0; index < byteArray.length; index ++ ) {
        var byte = long & 0xff;
        byteArray [ index ] = byte;
        long = (long - byte) / 256 ;
    }

    return byteArray;
};
/*! Utility for converting an int to a byte array
 *  \return nothing
 */
function intToByteArray(/*long*/long) {
    // we want to represent the input as a 8-bytes array
    var byteArray = [0, 0, 0, 0];
    for ( var index = 0; index < byteArray.length; index ++ ) {
        var byte = long & 0xff;
        byteArray [ index ] = byte;
        long = (long - byte) / 256 ;
    }

    return byteArray;
};
/*! Utility for converting a long to a byte array
 *  \return nothing
 */
function longToByteArray(/*long*/long) {
    // we want to represent the input as a 8-bytes array
    var byteArray=[0,0,0,0,0,0,0,0];
    for ( var index = 0; index < byteArray.length; index ++ ) {
        var byte = long & 0xff;
        byteArray [ index ] = byte;
        long = (long - byte) / 256 ;
    }

    return byteArray;
};
