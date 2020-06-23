/**
 * @file scr/midi.js
 * @author Ockert van Schalkwyk
 * @brief Testing midi data generation, uses jsmidgen.js
 * @version 0.1
 */
/*! Testing jsmidgen, not working yet
 *  \return nothing
 */
function miditest(){
	log("Info: miditest: start");
	var Midi=require('jsmidgen');
	var file=new Midi.File();
	var track=new Midi.Track();
	for(var i=0;i<4096;i++){
		track.addNote(0, 'c4', 64);
	}
	file.addTrack(track);
	var bytes=file.toBytes();
	print("Content-type: audio/midi\n\n");
	write(new Buffer(bytes));
	log("Info: miditest: end");

}
