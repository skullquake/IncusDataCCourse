/**
 * @file scr/raw.js
 * @author Ockert van Schalkwyk
 * @brief testing generating raw data
 * @version 0.1
 */
/*! testing writing raw data - main test invoker
 *  \return nothing
 */
function rawtest(){
	log("Info: rawtest: start");
	rawtest4();
	log("Info: rawtest: end");
}
/*! testing writing raw data
 *  \return nothing
 */
function rawtest0(){
	log("Info: rawtest0: start");
	var CHUNK_ID  =new Buffer("MyFmt000");				//magic
	var CHUNK_UINT8 =new Buffer(charToByteArray(  0xff));		//65535
	var CHUNK_UINT16=new Buffer(shortToByteArray( 0xffff));		//4294967295
	var CHUNK_UINT32=new Buffer(intToByteArray(   0xffffffff));	//281474976710655
	var CHUNK_UINT64=new Buffer(longToByteArray(  0xffffffffffff));	//281474976710655 //cant create literal!
	var CHUNK_FLOAT32=new Float32Array([1.2345]);//???
	var CHUNK_FLOAT64=new Float64Array([5.4321]);//???
	log(JSON.stringify(CHUNK_FLOAT32))

	/*
	CHUNK_SZ8 [0]=0x01;//0x7f;//0b00001111;//cannot 0b11111111 !
	CHUNK_SZ8 [1]=0x02;//0b00001111;

	CHUNK_SZ16[0]=0x03;//0b00001111;//lo
	CHUNK_SZ16[1]=0x04;//0b00001111;//hi

	CHUNK_SZ16[2]=0xff;//0b00001111;//lo
	CHUNK_SZ16[3]=0x00;//0b00001111;//hi

	CHUNK_SZ32[0]=0xff;//0b00001111;//lohi
	CHUNK_SZ32[1]=0x00;//0b00001111;//hilo
	CHUNK_SZ32[2]=0x00;//0b00001111;//lohi
	CHUNK_SZ32[3]=0x00;//0b00001111;//lolo

	CHUNK_SZ32[4]=0xff;//0b00001111;//lohi
	CHUNK_SZ32[5]=0x00;//0b00001111;//hilo
	CHUNK_SZ32[6]=0x00;//0b00001111;//lohi
	CHUNK_SZ32[7]=0x00;//0b00001111;//lolo
	var buf=new Buffer(
		 CHUNK_ID+		new Buffer(8)+
		new Buffer(CHUNK_SZ8)+	new Buffer(14)+
		new Buffer(CHUNK_SZ16)+	new Buffer(12)+
		new Buffer(CHUNK_SZ32)+	new Buffer(8)
		//new Buffer(longToByteArray(4096))
	)
	var buf=new Uint8Array([CHUNK_ID,CHUNK_ID])
	*/

	//issue resolved with weird concatenation overflows for values in excess of 0x7f as follows:
	var buf=new Buffer(80)
	buf.set(CHUNK_ID,0x00)
	buf.set(CHUNK_UINT8,0x10)
	buf.set(CHUNK_UINT16,0x20)
	buf.set(CHUNK_UINT32,0x30)
	buf.set(CHUNK_UINT64,0x40)
	//buf.set(CHUNK_FLOAT32,0x50)//?? issue - cant do buf.set with Float32Array
	//buf.set(CHUNK_FLOAT64,0x60)//?? issue - cant do buf.set with Float64Array
	print("Content-Type: audio/midi\n\n");
	write(buf);
	write(CHUNK_FLOAT32);write(new Buffer(12));
	write(CHUNK_FLOAT64);write(new Buffer(8));

	log(JSON.stringify(new Buffer(buf)));
	log("Info: rawtest0: end");
}
/*! testing writing raw data
 *  \return nothing
 */
function rawtest1(){
	log("Info: rawtest1: start");
	var buf=new Buffer("________________");
	buf[0]=0b00000000;
	buf[1]=0b00001111;
	buf[2]=0b11110000;
	buf[3]=0b11111111;
	log("Info: buffertest: buf: "+JSON.stringify(buf));
	log("Info: buffertest: buf: length: "+buf.length);
	log("Info: buffertest: typeof buf:"+typeof(buf))
	log("Info: buffertest: keys buf:"+Object.keys(buf).join(','))
	var val=0xffffffffffff
	log(val);
	//var buf2=new Buffer(longToByteArray(0xffffffffffff))
	var buf2=new Buffer(intToByteArray(0xffffffffffff))
	print("Content-Type: audio/midi\n\n");
	write(buf2);
	log("Info: rawtest1: end");
}

/*! testing writing raw data - create pixel data
 *  format:
 *  pos:    desc:  size:  type:
 *  0x00    magic  0x08   char
 *  0x08    bpp    0x04   uint32
 *  0x0b    width  0x04   uint32
 *  0x10    height 0x04   uint32
 *  0x14    data   --     uint8
 *  \return nothing
 */
function rawtest2(){
	log("Info: rawtest3: start");
	var t0=new Date();
	var bpp=24;
	var width=128;
	var height=128;
	print("Content-Type: application/octet-stream\n");
	print("X-Format: MyFmt002\n");
	print("X-BPP: "+bpp+"\n");
	print("X-Width: "+width+"\n");
	print("X-Height: "+height+"\n");
	print("\n");
	write(new Buffer("MyFmt002"));
	write(new Uint32Array([bpp,width,height]));
	log("Info: rawtest3: header: ["+((new Date()).getTime()-t0.getTime())+" ms]");
	var r=0;
	var g=0;
	var b=0;
	t0=new Date();
	var databuf=new Uint8Array(bpp/0x08*width*height);
	var dataidx=0x00;
	for(var i=0;i<height;i++){
		for(var j=0;j<width;j++){
			r=Math.floor(i/height*255);
			b=Math.floor(j/width*255);
			g=Math.floor((1-i/height)*255);
			databuf[dataidx++]=r;
			databuf[dataidx++]=g;
			databuf[dataidx++]=b;
		}
	}
	var dataidx=0x00;
	for(var i=0;i<height;i=i+32){
		for(var j=0;j<width;j++){
			r=254;
			b=254;
			g=254;
			databuf[i*width+j+0x00]=r;
			databuf[i*width+j+0x01]=g;
			databuf[i*width+j+0x02]=b;
		}
	}
	var dur=((new Date()).getTime()-t0.getTime())
	log("Info: rawtest3: data: ["+dur+" ms]");
	write(new Uint32Array([dur]));
	write(databuf);
	log("Info: rawtest3: end");
}
/*! testing writing raw data
 *  \return nothing
 */
function rawtest3(){
	log("Info: rawtest3: start");

	print("Content-Type: application/octet-stream\n\n");

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

	log("Info: rawtest3: end");
}
/*! testing writing raw data - for oscillator
 *  \return nothing
 */
function rawtest4(){
	log("Info: rawtest3: start");
	try{
		var t0=new Date();
		var bpm=255;
		var basefq=12;
		//frequences
		var tones=[];
		/*
		//tet
		for(var i=0;i<=12;i++){
			fq=basefq*Math.pow(2,i/12);
			tones.push(fq);
		}
		*/
		//just
		tones=[
			basefq*1,	//c
			basefq*9/8,	//d
			basefq*6/5,	//eb
			basefq*5/4,	//e
			basefq*4/3,	//f
			basefq*9/8*5/4,	//f#
			basefq*3/2,	//g
			basefq*4/3*6/5,	//ab
			basefq*4/3*5/4,	//a
			basefq*3/2*6/5,	//bb
			basefq*3/2*5/4,	//b
		];
		//build note variables
		var _this=this;
		[2,3,4,5,6,7,8].forEach(function(o,oidx){
			['c','d','eb','e','f','fs','g','ab','a','bb','b'].forEach(function(n,nidx){
				eval('_this.'+(n+oidx)+'='+Math.pow(2,oidx)*tones[nidx])
			});
		});
		//chords
		//todo:
		//	occurance weights,
		//	duration weight,
		//	forced and preferred resolutions,
		//	decorations???
		//	etc
		//
		var chords=[
			//----------------
			//Triads
			//----------------
			[
				{cps:g4,decoration:[g4,f4,g4,a4,g4]},
				{cps:e4},
				{cps:c3},
				{cps:c3},
			],
			[
				{cps:fs4},
				{cps:d4},
				{cps:a4},
				{cps:d3},
			],
			[
				{cps:a4},
				{cps:f4},
				{cps:c4},
				{cps:f3},
			],
			[
				{cps:a4},
				{cps:f4},
				{cps:d4},
				{cps:f3},
			],
			[
				{cps:ab4},
				{cps:f4},
				{cps:d4},
				{cps:f3},
			],
			[
				{cps:g4},
				{cps:d4},
				{cps:bb3},
				{cps:g3},
			],
			[
				{cps:g4},
				{cps:d4},
				{cps:b3},
				{cps:g3},
			],
			[
				{cps:g4},
				{cps:eb4},
				{cps:bb3},
				{cps:eb3},
			],
			[
				{cps:eb4},
				{cps:c4},
				{cps:ab3},
				{cps:c3},
			],
			//----------------
			//Fourths and such
			//----------------
			[
				{cps:g4,decoration:[g4,a4,g4,f4]},
				{cps:d4},
				{cps:g3},
				{cps:c3},
			],
			[
				{cps:d4},
				{cps:c4,decoration:[c4,a3,bb3,c4]},
				{cps:g3},
				{cps:f3},
			],
			[
				{cps:f4},
				{cps:c4,decoration:[c4,b4,c4,c4]},
				{cps:g3},
				{cps:d3},
			],
			[
				{cps:g4},
				{cps:f4,decoration:[f4,d4,eb4,f4]},
				{cps:bb3},
				{cps:eb3},
			],
			[
				{cps:f4},
				{cps:eb4},
				{cps:bb3},
				{cps:f3},
			],
		];
		//durations
		durs=[
			0.5,
			1.0,
			2.0,
			4.0
		];
		//durations
		amps=[
			0,
			0.04,
			0.05,
			0.04,
			0.05,
			0.04,
			0.05,
			0.04,
			0.05,
		];
		//construct channels
		var nch=chords[0].length;		//!channel count should not be linked to chord members
		var nchordchanges=8192*2;
		bpm=80;
		var voices=[];				//initialize voices array
		for(var i=0;i<nch;i++){voices.push([]);}
		var lastidx=-1;				//help in avoiding repeated chords
		var chordidx=null;
		var beatcount=0;
		for(var i=0;i<nchordchanges;i++){
			chordidx=Math.floor(Math.random()*chords.length);
			while(chordidx==lastidx){
				chordidx=Math.floor(Math.random()*chords.length);
			}
			lastidx=chordidx;
			//rests - should be handled differently
			var amp=amps[Math.floor(Math.random()*amps.length)]//Math.random()*1;
			if(amp==0){
				var dur=1.0;
			}else{
				var dur=durs[Math.floor(Math.random()*durs.length)];
			}
			beatcount+=dur;
			for(var j=0;j<nch;j++){
				freqmod=(1+0.1*(0.5+Math.sin(beatcount)/10)/2);
				//freqmod=tones[Math.floor(Math.random()*tones.length)];
				cps=chords[chordidx][j].cps
				if(chords[chordidx][j].decoration!=null){
					if(Math.random()<0.5){//random decoration or not
						chords[chordidx][j].decoration.forEach(function(decoration,decorationidx){
							voices[j].push({
								cps:freqmod*decoration,
								dur:dur/chords[chordidx][j].decoration.length,
								amp:amp
							});

						});
					}else{
						voices[j].push({
							cps:freqmod*cps,
							dur:dur,
							amp:amp
						});
					}
				}else{
					voices[j].push({
						cps:freqmod*cps,
						dur:dur,
						amp:amp
					});
				}
			}
		}
		//serialize to binary
		print("Content-Type: application/octet-stream\n");
		print("X-Format: MyFmt004\n");
		print("X-Description: Binary music format\n");
		print("X-Bpm: "+bpm+"\n");
		print("X-Nch: "+nch+"\n");
		print("\n");
		write(new Buffer("MyFmt004"));

		write(new Uint32Array([bpm,nch]));
		for(var i=0;i<voices.length;i++){
			var nevt=voices[i].length;
			write(new Uint32Array([nevt]));
			for(var j=0;j<nevt;j++){
				var cps=voices[i][j].cps;
				var dur=voices[i][j].dur;
				var amp=voices[i][j].amp;
				write(new Float64Array([cps,dur,amp]));
			}
		}
/*
		//duplicate channels - echos
		var necho=2;
		channels.forEach(function(channel,channelidx){
			for(var i=0;i<necho;i++){
				channeldup=[];
				channel.forEach(function(evt,evtidx){
					evtdup={cps:evt.cps*1.005,dur:evt.dur+necho*0.2,amp:evt.amp*0.75};
					channeldup.push(evtdup);
				});
				channels.push(channeldup);
			}
		});
		nch=Math.floor(nch*necho);
*/

	}catch(e){
		log("Error: rawtest3: "+e.toString());
	}
	log("Info: rawtest3: end");
}
/*! testing writing raw data - for oscillator - uses tet, scale, durs, etc.
 *  \return nothing
 */
function rawtest4_000(){
	log("Info: rawtest4_000: start");
	var t0=new Date();
	try{
		var bpm=255;
		var bfq=55;
		var nch=8;
		var durs=[1,2]
		var scale=[0,2,4,5,7,9,11];
		var octave=[-1,0];
		var octaveRatio=4;
		var phrase=[0,1,2,3,4]
		//create channels
		var channels=[];
		for(var i=0;i<nch;i++){channels.push([])}
		var nevt=512;
		channels.forEach(function(channel,channelidx){
			var phraseRendition=0;
			var transposition=Math.floor(Math.random()*4)-2;
			for(var i=0;i<nevt;i++){
				var inversion=Math.random()<0.5;
				for(var j=0;j<phrase.length;j++){
					var cps=
						bfq*
						Math.pow(octaveRatio,
							//octave:
							//octave[Math.floor(Math.random()*octave.length)]
							1//channelidx
						)*
						Math.pow(
							octaveRatio,
							(
								transposition+(
									scale[
										(
										inversion?
											(phrase[j]):
											4-(phrase[j])
										)
										%scale.length
									]
								)
							)
							/12);
					var dur=durs[Math.floor(Math.random()*durs.length)];
					var amp=0.01+Math.random()*0.1;
					channel.push({
						cps:cps,
						dur:dur,
						amp:amp
					});
				}
			}
		});
		//serialize to binary
		print("Content-Type: application/octet-stream\n");
		print("X-Format: MyFmt004\n");
		print("X-Description: Binary music format\n");
		print("X-Bpm: "+bpm+"\n");
		print("X-Nch: "+nch+"\n");
		print("\n");
		write(new Buffer("MyFmt004"));
		write(new Uint32Array([bpm,nch]));
		channels.forEach(function(channel,channelidx){
			var nevt=channel.length;
			write(new Uint32Array([nevt]));
			channel.forEach(function(evt,evtidx){
				var cps=evt.cps;
				var dur=evt.dur;
				var amp=evt.amp;
				write(new Float64Array([cps,dur,amp]));
			});
		});
	}catch(e){
		log("Error: rawtest4_000: "+e.toString());
	}
	var t1=new Date();
	log("Info: rawtest4_000: end ["+(t1.getTime()-t0.getTime())+" ms]");
}
/*! testing writing raw data - for oscillator - uses tet, scale, durs, etc.
 *  \return nothing
 */
function rawtest4_001(){
	log("Info: rawtest4_001: start");
	var t0=new Date();
	try{
		var bpm=255;
		var dur=10;
		var bfq=40;
		var nch=4;
		var durs=[1,2]
		var scale=[0,2,4,5,7,9,11];
		var octave=[-1,0];
		var octaveRatio=4;
		var phrase=[0,0,3,3,2,3,4,4,5,5,5,5]
		//create channels
		var channels=[];
		for(var i=0;i<nch;i++){channels.push([])}
		var nevt=512;
		channels.forEach(function(channel,channelidx){
			var phraseRendition=0;
			var transposition=Math.floor(Math.random()*4)-2;
			for(var i=0;i<nevt;i++){
				var inversion=Math.random()<0.5;
				for(var j=0;j<phrase.length;j++){
					var cps=
						bfq*
						Math.pow(octaveRatio,
							//octave:
							//octave[Math.floor(Math.random()*octave.length)]
							1//channelidx
						)*
						Math.pow(
							octaveRatio,
							(
								transposition+(
									scale[
										(
										inversion?
											(phrase[j]):
											5-(phrase[j])
										)
										%scale.length
									]
								)
							)
							/12);
					var dur=durs[Math.floor(Math.random()*durs.length)];
					var amp=0.01+Math.random()*0.1;
					channel.push({
						cps:cps,
						dur:dur,
						amp:amp
					});
				}
			}
		});
		//duplicate channels - echos
		var necho=2;
		channels.forEach(function(channel,channelidx){
			for(var i=0;i<necho;i++){
				channeldup=[];
				channel.forEach(function(evt,evtidx){
					evtdup={cps:evt.cps*1.005,dur:evt.dur+necho*0.2,amp:evt.amp*0.75};
					channeldup.push(evtdup);
				});
				channels.push(channeldup);
			}
		});
		nch=Math.floor(nch*necho);
		//serialize to binary
		print("Content-Type: application/octet-stream\n");
		print("X-Format: MyFmt004\n");
		print("X-Description: Binary music format\n");
		print("X-Bpm: "+bpm+"\n");
		print("X-Nch: "+nch+"\n");
		print("\n");
		write(new Buffer("MyFmt004"));
		write(new Uint32Array([bpm,nch]));
		channels.forEach(function(channel,channelidx){
			var nevt=channel.length;
			write(new Uint32Array([nevt]));
			channel.forEach(function(evt,evtidx){
				var cps=evt.cps;
				var dur=evt.dur;
				var amp=evt.amp;
				write(new Float64Array([cps,dur,amp]));
			});
		});
	}catch(e){
		log("Error: rawtest4_001: "+e.toString());
	}
	var t1=new Date();
	log("Info: rawtest4_001: end ["+(t1.getTime()-t0.getTime())+" ms]");
}
/*! testing writing raw data - for oscillator - uses tet, scale, durs, multiple scales, decorations, multiple octaves etc.
 *  \return nothing
 */
function rawtest4_002(){
	log("Info: rawtest4_002: start");
	var t0=new Date();
	try{
		var bpm=125;
		var bfq=220;
		var nch=4;
		var durs=[0.5,0.5,0.5,0.5,0.5,1,2]
		var scalemajor=			[0,2,4,5,7,9,11];
		var scaleharmonicminor=		[0,2,3,5,7,8,11];
		var scalemelodicminorascending=	[0,2,3,5,7,9,11];
		var scalemelodicminordescending=[0,2,3,5,7,8,10];
		var scales=[
			scalemajor,
			scaleharmonicminor,
			scalemelodicminorascending,
			scalemelodicminordescending,
		]
		var octave=[-1,0];
		var octaveRatio=4;
		var phrase=[1,8,7,8,1,8,1,8,7,6,5,4,3,2]
		//var phrase=[0,3,5,6,5,3];
		//var phrase=[0,3,5,8];
		//var phrase=[0,1,2,3];
		//create channels
		var channels=[];
		for(var i=0;i<nch;i++){channels.push([])}
		var nevt=512;
		channels.forEach(function(channel,channelidx){
			for(var i=0;i<nevt;i++){
				//transforme phrase
				phrasetransformed=[];
				var translation=Math.floor(Math.random()*4)
				var inv=Math.random()<0.5;
				phrase.forEach(function(note,noteidx){
					phrasetransformed.push(
						inv?
						note+translation:
						8-note+translation
					);
				});
				var rev=Math.random()<0.5;
				if(rev){
					phrasetransformed=phrasetransformed.reverse();
				}else{
				}
				//transform scale
				scaletransformed=[];
				var scale=scales[Math.floor(Math.random()*scales.length)];
				scale.forEach(function(tone,toneidx){
					scaletransformed.push(tone);
				});
				var transposition=Math.floor(Math.random()*4)
				scaletransformed.forEach(function(tone,toneidx){
					tone+=transposition;
				});
				//octave
				var octave=channelidx-2;
				//push phrase
				phrasetransformed.forEach(function(note,noteidx){
					var dur=durs[Math.floor(Math.random()*durs.length)];
					//todo: decorations
					//todo: passing tone injection, only for longer notes
						//looks like the decoration sometimes produce values 
						//the webaudio oscillators dont like
					var usedecorate=dur>=1?Math.random()<0.5:false;
					arrevt=[];
					if(usedecorate){
						var decorations=[
							[note+1,note,note+1,note,note+1,note,note+1,note],
							[note,note-1,note],
							[note,note-2,note-1,note],
							[note,note+2,note+1,note]
						];
						var selecteddecoration=decorations[Math.floor(Math.random()*decorations.length)]
						selecteddecoration.forEach(function(note,noteidx){
							cps=Math.pow(2,octave)*Math.pow(2,Math.floor(note/scaletransformed.length))*Math.pow(2,scaletransformed[note%scaletransformed.length]/12)*bfq
							dur=dur/selecteddecoration.length;
							if(dur==null)log("!!!!!!!!!#");
							var amp=Math.random()*0.1;
							arrevt.push({
								cps:cps,
								dur:dur,
								amp:amp
							})
						});
					}else{
						cps=Math.pow(2,octave)*Math.pow(2,Math.floor(note/scaletransformed.length))*Math.pow(2,scaletransformed[note%scaletransformed.length]/12)*bfq;
						if(dur==null)log("!!!!!!!!!");
						var amp=Math.random()*0.1;
						arrevt.push({
							cps:cps,
							dur:dur,
							amp:amp
						})
					}
					arrevt.forEach(function(evt,evtidx){
						channel.push(evt);
					});
				});
			}

		});
		//duplicate channels - echos
		/*
		var necho=2;
		channels.forEach(function(channel,channelidx){
			for(var i=0;i<necho;i++){
				channeldup=[];
				channel.forEach(function(evt,evtidx){
					evtdup={cps:evt.cps*1.005,dur:evt.dur+necho*0.2,amp:evt.amp*0.75};
					channeldup.push(evtdup);
				});
				channels.push(channeldup);
			}
		});
		nch*=necho;
		*/
		//serialize to binary
		print("Content-Type: application/octet-stream\n");
		print("X-Format: MyFmt004\n");
		print("X-Description: Binary music format\n");
		print("X-Bpm: "+bpm+"\n");
		print("X-Nch: "+nch+"\n");
		print("\n");
		write(new Buffer("MyFmt004"));
		write(new Uint32Array([bpm,nch]));
		channels.forEach(function(channel,channelidx){
			var nevt=channel.length;
			write(new Uint32Array([nevt]));
			channel.forEach(function(evt,evtidx){
				var cps=evt.cps;
				var dur=evt.dur;
				var amp=evt.amp;
				//log("evtidx: "+evtidx+":"+JSON.stringify({cps:cps,dur:dur,amp:amp}));
				write(new Float64Array([cps,dur,amp]));
			});
		});
	}catch(e){
		log("Error: rawtest4_002: "+e.toString());
	}
	var t1=new Date();
	log("Info: rawtest4_002: end ["+(t1.getTime()-t0.getTime())+" ms]");
}
/*! testing writing raw data - simplified version - for oscillator - triands
 *  \return nothing
 */
function rawtest4_003(){
	log("Info: rawtest4_003: start");
	var t0=new Date();
	try{
		var bpm=125;
		var bfq=220;
		var nch=3;
		var durs=[1,2,4];
		var scale=[0,2.04,3.86,4.98,7.02,8.84,10.88];
		scale.forEach(function(tone,toneidx){
			scale[toneidx]=tone+Math.random()/2;
		});
		var octave=[-1,0];
		var octaveRatio=4;
		var minnote=0;
		var maxnote=8;
		//create channels
		var channels=[];
		for(var i=0;i<nch;i++){channels.push([])}
		var nevt=512;
		var cantus=[];
		for(var i=0;i<nevt;i++){
			//todo: stay in range
			if(cantus.length>0){
					if(cantus.length>1){
						if(
							Math.abs(
								cantus[cantus.length-1]-
								cantus[cantus.length-2]
							)>2
						){
							var diff=
								cantus[cantus.length-1]-
								cantus[cantus.length-2]
							;
							note=cantus[cantus.length-1]+(diff<0?1:-1);
						}else{
							var note=cantus[cantus.length-1]+
								(Math.random()<0.5?1:-1)*
								Math.floor(Math.random()*4)
							;
							while(note<minnote&&note>maxnote){
								note=cantus[cantus.length-1]+
									(Math.random()<0.5?1:-1)*
									Math.floor(Math.random()*4)
								;
							}
						}
					}else{
						var note=cantus[cantus.length-1]+
							(Math.random()<0.5?1:-1)*
							Math.floor(Math.random()*4)
						;
						while(note<minnote&&note>maxnote){
							note=cantus[cantus.length-1]+
								(Math.random()<0.5?1:-1)*
								Math.floor(Math.random()*4)
							;
						}
					}
			}else{
				var note=Math.floor(Math.random()*scale.length)
			}
			cantus.push(note);
		}
		channels.forEach(function(channel,channelidx){
			for(var i=0;i<nevt;i++){
				amp=0.1;
				//harmonize
				var wide=Math.random()<0.5?true:false;
				switch(channelidx){
					case 0:
						note=cantus[i];
						break;
					case 1:
						note=cantus[i]+2;
						//note=wide?note+12:note;
						amp/=2;
						break;
					case 2:
						note=cantus[i]+(Math.random()<0.5?4:5);
						amp/=2;
						break;
					default:
						note=cantus[i];
						amp/=2;
						break;
				}
				cps=
					Math.pow(2,Math.floor(note/scale.length))*
					//today: convert this to scale cps table 
					Math.pow(2,scale[(note<0?Math.abs(note):note)%scale.length]/12)*//might resolve other issues with null cps
					bfq
				;
				//dur=durs[i%durs.length];
				dur=durs[Math.floor(Math.random()*durs.length)];
				channel.push({
					cps:cps,
					dur:dur,
					amp:amp
				})
			}

		});
		//serialize to binary
		print("Content-Type: application/octet-stream\n");
		print("X-Format: MyFmt004\n");
		print("X-Description: Binary music format\n");
		print("X-Bpm: "+bpm+"\n");
		print("X-Nch: "+nch+"\n");
		print("\n");
		write(new Buffer("MyFmt004"));
		write(new Uint32Array([bpm,nch]));
		channels.forEach(function(channel,channelidx){
			var nevt=channel.length;
			write(new Uint32Array([nevt]));
			channel.forEach(function(evt,evtidx){
				var cps=evt.cps;
				var dur=evt.dur;
				var amp=evt.amp;
				//log("evtidx: "+evtidx+":"+JSON.stringify({cps:cps,dur:dur,amp:amp}));
				write(new Float64Array([cps,dur,amp]));
			});
		});
	}catch(e){
		log("Error: rawtest4_003: "+e.toString());
	}
	var t1=new Date();
	log("Info: rawtest4_003: end ["+(t1.getTime()-t0.getTime())+" ms]");
}


/*! testing writing raw data - lookup and indexing
 *  \return nothing
 */
function rawtest5(){
	log("rawtest5: start");
	var nelem=32;
	var lookup=[0.0,0.25,0.5,0.75,1.0];
	var dataidx=[];
	for(var i=0;i<nelem;i++){
		dataidx.push(i%lookup.length);
	}
	var datanlookup=new Uint8Array([lookup.length])
	var datalookup=new Float32Array(lookup)
	var datanidx=new Uint8Array([nelem]);
	var dataidx=new Uint8Array(dataidx);
	print("Content-Type: application/octet-stream\n\n");
	write(new Buffer("MyFmt005"));
	write(datanlookup);
	write(datalookup);
	write(datanidx);
	write(dataidx);
	log("rawtest5: end");
}
/*! testing writing raw data - points3drgba
 *  \return nothing
 */
function rawtest6(){
	var t0=new Date();
	var nelem=8192;
	var data=[];
	log("rawtest6: start");
	var x=0;
	var y=0;
	var z=0;
	var r=255;
	var g=128;
	var b=64;
	var a=255;
	for(var i=0;i<nelem;i++){
		var val=Math.random();
		x=Math.random;
		y=Math.random;
		z=Math.random;
		r=val*255;//Math.floor((Math.random()*255))
		g=val*255;//Math.floor((Math.random()*255))
		b=val*255;//Math.floor((Math.random()*255))
		a=Math.floor((Math.random()*255))
		data.push({
			x:Math.random(),
			y:Math.random(),
			z:Math.random(),
			r:r,
			g:g,
			b:b,
			a:a,
		});
	}
	print("Content-Type: application/octet-stream\n\n");
	write(new Buffer("MyFmt006"));
	write(new Uint32Array([data.length]));
	data.forEach(function(p,pidx){
		write(new Float32Array([p.x,p.y,p.z]));
		write(new Uint8Array([p.r,p.g,p.b,p.a]));
	});
	var t1=new Date();
	log("rawtest6: end ["+(t1.getTime()-t0.getTime())+" ms]");
}


/*! Utility for converting char to a byte array
 *  \return array of integral values
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
 *  \return array of integral values
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
 *  \return array of integral values
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
 *  \return array of integral values
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

