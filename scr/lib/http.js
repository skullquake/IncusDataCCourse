/**
 * @file scr/http.js
 * @author Ockert van Schalkwyk
 * @brief Various cgi http utility functions
 * @version 0.1
 */
/*! Deprecated: native function `getEnv()` from src/duk/native.c now returns `JSON` object anyways.
 *  Extracts environmental variables, parses and populates into return `JSON` object
 *  \return `JSON` object containing environmental variables
 */
var _global=this;
function env2obj(){
	log('Info: env2obj():start')
	var ret={};
	try{
		var env={};
		getEnv().forEach(function(e,eidx){
			env[e.substring(0,e.indexOf('='))]=e.substring(e.indexOf('=')+1);
		});
		ret=env;
	}catch(e){
		ret.err=e.toString();
	}
	log('Info: env2obj():end')
	return ret;
}
/*! This returns the query string
 *  \return `String` that is query string
 */
function getQueryString(){
	log('Info: getQueryString(): start')
	log('Info: getQueryString(): end')
	return getEnv()['QUERY_STRING'];
}
/*! This is supposed to convert the query string into an object
 *  references: https://stackoverflow.com/questions/7722683/how-to-get-all-query-string-values-using-javascript#48357046
 *  \return `JSON` object containing information
 */
function queryString2Obj(){
	log('Info: queryString2Obj():start')
	var ret={};
	var vars=[],hash;
	var qs=getQueryString();
	var hashes=qs.slice(qs.indexOf('?')+1).split('&');
	for(var i=0;i<hashes.length;i++){
		hash=hashes[i].split('=');
		vars.push(hash[0]);
		vars[hash[0]]=hash[1];
	}
	vars.forEach(function(v,vidx){
		log("Info: queryString2Obj: var["+vidx+"]: "+v);
		ret[v]=getQueryVariable(qs,v)
	});
	log('Info: queryString2Obj():end')
	return ret;
}
/*! Extracts value from query string
 *  \param query `String` query to scan
 *  \param variable Used as key to scan `query` to find value
 *  \return `String` with value if found, otherwise `null`
 */
function getQueryVariable(query,variable) {
	log('Info: getQueryVariable():start')
	var vars = query.split('&');
	for (var i = 0; i < vars.length; i++) {
		var pair = vars[i].split('=');
		if (decodeURIComponent(pair[0]) == variable) {
			return decodeURIComponent(pair[1]);
		}
	}
	log('Info: getQueryVariable():end')
	return null;
}
/*! Generates response. with appropriate headers
 *   Automatically detects object type, if `Object`, sets
 *   `Content-Type` to `application/json`, if `String`, sets `Content-Type` to
 *   `text/plain`, otherwise returns messages in `text/plain` printing error
 *   Response is printed out to `stdout` using native exposed function `print`
 *   Todo: optional extra parameters/object containing extras, for additional
 *   headers, content-type override, etc
 *
 *  \param m Either `Object` or `String` to respond with
 *  \return nothing
 */
function respond(m){
	log('Info: respond():start')
	var res='';
	var httpversion='HTTP/1.1';
	var rescod=200;
	var resmsg='OK';
	var hdrs={
		"Date":new Date().toString(),
		"Server":"Mongoose",
		"Keep-Alive":"timeout=3, max=50",
		"Connection":"Keep-Alive",
		"Content-Type":"text/html; charset=iso-8859-1"
	};
	var body='';
	switch(typeof(m)){
		case 'string':
			hdrs['Content-Type']='text/plain';
			body=m;
			break;
		case 'object':
			hdrs['Content-Type']='application/json';
			body=JSON.stringify(m,0,'\t');
			break;
		case 'number':
			hdrs['Content-Type']='text/plain';
			body=m.toString();
			break;
		case 'number':
		case 'null':
			hdrs['Content-Type']='application/text';
			rescod=400;
			body="NULL";
			break;
		default:
			hdrs['Content-Type']='application/json';
			rescod=400;
			resmsg="Error"
			body="Unable to serialize type "+typeof(m);
			break;
	}
	//hdrs['Content-Length']=body.length;
	reslines=[];
	reslines.push(httpversion);
	reslines.push([rescod,resmsg].join(' '));
	Object.keys(hdrs).forEach(function(hdr,hdridx){
		reslines.push([hdr,hdrs[hdr]].join(': '));
	});
	res=reslines.join('\n');
	res+='\n\n';
	res+=body;
	print(res);
	log('Info: respond():end')
	return;
}
/*! get the http method
 *  \return `String` with method if found, else `null`
 */
function getMethod(){
	log("Info: getMethod: start");
	var ret=null;
	try{
		ret=getEnv().REQUEST_METHOD
	}catch(e){
		log("Error: getMethod: failed to obtain method: "+e.toString());
		ret=null;
	}
	log("Info: getMethod: end");
	return ret;
}
/*! get the content type
 *  \return `String` with content type if found, else `null`
 */
function getContentType(){
	log("Info: getContentType: start")
	log("Info: getContentType: end")
	return getEnv().HTTP_CONTENT_TYPE;
}
/*! Gets CGI post body from stdin
 *  \param query `String` query to scan
 *  \param variable Used as key to scan `query` to find value
 *  \return `String` with value if found, otherwise `null`
 */
function getBody(){
	log("Info: getBody: start");
	var ret=null;
	//preliminary - read post body
	var method=getEnv().REQUEST_METHOD;
	if(method=='POST'){
		var content_length=parseInt(getEnv().HTTP_CONTENT_LENGTH);
		var buf=new ArrayBuffer(content_length);//otherwise you get superflous 0x00 elements
		if(	fread({buf:buf,size:1,count:content_length,stream:stdin})==
			content_length
		){
			strbody=new TextDecoder("utf-8").decode(buf);
			switch(getContentType()){
				case "application/json":
					try{
						var json=JSON.parse(strbody);
						ret=json;
					}catch(e){
						log("Error: getbody: Failed to parse json: "+e.toString());
						ret=strbody;
					}
					break;
				default:
					ret=strbody;
					break;
			};
		}else{
			log("Error: freadtest: no bytes read\n");
		}
	}else{
		//not a post, no body
	}
	log("Info: getBody: end");
	return ret;
}
/*! Preliminary test function 
 *  \param query `String` query to scan
 *  \param variable Used as key to scan `query` to find value
 *  \return `String` with value if found, otherwise `null`
 */
function httptest(){
	log('Info: httptes(): start')
	log(JSON.stringify(getEnv()));
	log(getQueryString());
	//log(getQueryVariable(getQueryString(),'action'))
	//log(getQueryVariable(getQueryString(),'arg0'))
	//log(getEnv().REQUEST_METHOD);
	//log(getEnv().HTTP_CONTENT_LENGTH);
	//log(JSON.stringify(env2obj()))//broken
	//log(JSON.stringify(queryString2Obj()));
	//log(getContentType());
	//log(getBody());///todo: native log detect if is object and serializes for printf
	log(JSON.stringify(queryString2Obj()))
	log('Info: httptest(): end')
}
/*! act demuxer - general handler for post and get, act is the action, params the parameters (post),
 *  for get the query string is parsed to an object and the entire thing becomes the paraemters
 *  the expectation is that the function is to be called with a single object as parameter
 *  \return nothing
 */
function actdemux(){
	log('Info: actdemux: start')
	try{
		//todo: handle post and get, extract relevant parameters
		var act=null;
		var params=null;
		switch(getMethod()){
			case 'POST':
				var body=getBody();
				log(JSON.stringify(queryString2Obj()));
				act=body.action;
				params=null;
				try{
					params=typeof(eval(body.params))=='object'?eval(body.params):null;
				}catch(e){
					log('Error: actdemux: no params');
				}
				break;
			case 'GET':
				act=queryString2Obj().act;
				params=queryString2Obj();
				break;
		}
		switch(typeof(act)){
			case 'string':
				log('1');
				try{
					log(_global)
					log(_global[act])
					log(act)
					if(typeof(_global[act])=='function'){
						log('2');
						fn=eval(act);
						fn(params);
					}else{
						log('3');
						log('Error: actdemux: '+act+' not a function');
						hdlError('action '+act+' not defined');
					}
				}catch(e){
					log('Error: actdemux: '+e.toString());
				}
				break;
			case 'undefined':
				log('2');
				log('Error: actdemux: act undefined');
				hdlError('action undefined');
				break;
			default:
				log('3');
				log('Error: actdemux: act invalid type');
				hdlError('action not a string');
				break;
		}

	}catch(e){
		hdlError(e.toString);
	}
	log('Info: actdemux: end')
	return 0;
}
/*! Handles error, writes out JSON error for client
 *  \return nothing
 */
function hdlError(e){
	log('Info: hdlError(): end')
	print("Content-Type: application/json\n\n");
	print(JSON.stringify({"Error":e.toString()}));
	log('Info: hdlError(): end')
}
/*! test action
 *  \return nothing
 */
function action0(params){
	log('Info: action0(): start')
	try{
		var width=params.width;
		var height=params.height;
		var data=[];
		for(var i=0;i<height;i++){
			var row=[];
			for(var j=0;j<width;j++){
				row.push(j);
			}
			data.push(row);
		}
		ret=data;
	}catch(e){
		res.Error=e.toString();
	}
	print("Content-Type: application/json\n\n");
	print(JSON.stringify(ret));
	log('Info: action0(): end')
}
/*! test action
 *  \return nothing
 */
function action1(params){
	log('Info: action1(): end')
	print("Content-Type: application/json\n\n");
	print(JSON.stringify({msg:'action1 stub',params:params}));
	log('Info: action1(): end')
}
