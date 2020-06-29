/**
 * @file scr/html.js
 * @author Ockert van Schalkwyk
 * @brief Basic html utilities, including routing, etc
 * @version 0.1
 */
/*! loads code used */
load('./scr/lib.js');
/*! Sample query string parsing, with path extraction and renderfile invocation.
 *  By default `../res/html/index.html` will be rendered. Since the CGI program
 *  is executed from its current directory, i.e. the current working directory
 *  is the same as where the binary exists on disk, and since the templates
 *  are in the parent folder in `./res/html/index.html`, we have to specify
 *  this relative path. Possible solutions include using an absolute path
 *  specification, or by storing the CGI program in the project root to avoid
 *  the '..' relative path specification to the templates. Another alternative
 *  is to modify the current working directory to that of the initial javascript
 *  file executed by the javascript environment in C
 *
 *  Todo: Implement propper templating, where the html file is parsed and
 *  token replacement implemented, or some other scheme of filling in tokens
 *  in the html string
 *
 *  \return nothing
 */
function route(){
	log("Info: route: start");
	var qs=getEnv()['QUERY_STRING'];
	var filepath=getQueryVariable(qs,"path");
	filepath=filepath==null?"../res/html/index.html":filepath;
	renderfile(filepath)
	log("Info: route: end");
}
/*! tries to render a file, with some minor mime type detection based on extension
 *  \return nothing
 */
function renderfile(path){
	log("Info: renderfile: start");
	try{
		var contents=file2string(path);
		if(path==null){
			print("Content-Type: application/json\n\n");
			print(JSON.stringify({err:[path,"not found"].join(" ")}));
		}else{
			var mimetype="text/plain";
			if(path.lastIndexOf('.')>0){
				var extension=path.substring(path.lastIndexOf('.')+1);//.toLowerCase();
				switch(extension){
					case "htm":
					case "html":
						mimetype="text/html";
						break;
					case "json":
						mimetype="application/json";
						break;
					default:
						log("Warning: renderfile: failed to determine mime type");
						mimetype="text/plain";
						break;
					
				}
			}
			print("Content-Type: "+mimetype+"\n\n");
			print(contents)
		}
	}catch(e){
		log("Error: "+e.toString());
		print("Content-Type: application/json\n\n");
		print(JSON.stringify({error:e.toString()}))
	}
	log("Info: renderfile: end");
}
/*! reads file from path
 *  \return `String` or `null` if not found
 */
function file2string(path){
	log("Info: file2string: start");
	res=null;
	res=FileIo.readfile(path);//'../scr/'+id+'.js')
	res=new TextDecoder("utf-8").decode(res);
	if(typeof res==='string'){
		return res;
	}else{
		log("Error: file2string: failed to convert to string");
	}
	log("Info: file2string: end");
	return res;
}
