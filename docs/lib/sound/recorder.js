    "use strict";

    // AudioContext
    let audioCtx = null; 

    // AudioNodes
    let audioMediaSrc = null;
    let audioProcessor = null;

    let sampleRate = 0;
    let duration = 0.0;
    let numberOfChannels = 0;

    // data structure for recording
    let audioRec = {
	stream : null,
	node : null,
	data : null,
	dataView : null,
    }

    const SetupAudioContext = function () {

	if( audioCtx == null ){
	    audioCtx = new (window.AudioContext || window.webkitAudioContext)();
	}
    }

    const RecAudio = function (){

	if( audioRec.stream != null ) return;

	navigator.mediaDevices.getUserMedia( { audio: true } )
	    .then( s => {

		audioRec.stream = s;
		sampleRate = 0;
		duration = 0.0;
		numberOfChannels = 0;

		audioRec.data = null;
		audioRec.dataView = null;

		SetupAudioContext();
		audioMediaSrc = audioCtx.createMediaStreamSource( audioRec.stream );

		// NOTE: ScriptProcessorNode will be deprecated and replaced by Audio Worker
		audioProcessor = audioCtx.createScriptProcessor( 1024, 1, 1 );
		audioProcessor.onaudioprocess = function( event ){

		    if( audioRec.stream != null ){

			duration += event.inputBuffer.duration;
			document.getElementById( "duration" ).innerText = "" + duration.toFixed(1);

			if( audioRec.data == null ){
			    sampleRate = event.inputBuffer.sampleRate;
			    numberOfChannels = event.inputBuffer.numberOfChannels;
			    console.log( "rate = " + sampleRate );
			    console.log( "channels = " + numberOfChannels );
			    
			    audioRec.data = new Array( numberOfChannels );
			    for( let i = 0; i < numberOfChannels; ++i ){
				audioRec.data[i] = [];
			    }
			}
   
			for( let i = 0; i < numberOfChannels ; ++i ){
			    Array.prototype.push.apply( audioRec.data[i], event.inputBuffer.getChannelData( i ) );
			}
		    }
		};

		audioMediaSrc.connect( audioProcessor );
		audioProcessor.connect( audioCtx.destination );
	    } );
    }

    const StopRecAudio = function (){

	if( audioMediaSrc == null ) return;

	audioRec.stream.getTracks().forEach( t => t.stop() );
	audioRec.stream = null;

	audioMediaSrc.disconnect();
	audioCtx.close();

	audioCtx = null;
	audioMediaSrc = null;
	audioProcessor = null;

	console.log( "duration = " + duration );
	console.log( "length = " + audioRec.data[0].length );

	CreateDataView();
	audioRec.data = null;

	if( audioRec.node == null ){
	    audioRec.node = document.createElement( "a" );
	    document.getElementById( 'rec' ).appendChild( audioRec.node );
	    audioRec.node.download = 'out.wav';
	}
	audioRec.node.href = window.URL.createObjectURL( new Blob( [ audioRec.dataView ], { type: 'audio/wav' } ) );
	audioRec.node.click();
    }

   const CreateDataView = function(){

       let setString = ( offset, string ) => {
	   for( let i = 0; i < string.length; ++i ){
               audioRec.dataView.setUint8( offset+i, string.charCodeAt(i) );
	   }
       };

       numberOfChannels = 1; // uses just left channel
       let length = audioRec.data[0].length;
       let blocksize = 16/8 * numberOfChannels;
       let datasize = length * blocksize;

       audioRec.dataView = new DataView( new ArrayBuffer( 44 + datasize ) );

       setString( 0, 'RIFF' );
       audioRec.dataView.setUint32( 4, 44 + datasize -8, true );
       setString( 8, 'WAVE');
       setString( 12, 'fmt ');
       audioRec.dataView.setUint32( 16, 16, true); // 16 byte = size of fmt
       audioRec.dataView.setUint16( 20, 1, true); // format = MS PCM
       audioRec.dataView.setUint16( 22, numberOfChannels, true); // channels
       audioRec.dataView.setUint32( 24, sampleRate, true); // rate
       audioRec.dataView.setUint32( 28, sampleRate * blocksize, true); // rate * blocksize
       audioRec.dataView.setUint16( 32, blocksize, true); // blocksize
       audioRec.dataView.setUint16( 34, 16, true); // bits
       setString( 36, 'data');
       audioRec.dataView.setUint32( 40, datasize, true);
       let offset = 44;
       for( let i = 0; i < length; ++i ){
	   let data = Math.max( -32768, Math.min( 32767, audioRec.data[0][i] * 32768 ) );
	   audioRec.dataView.setInt16( offset, data, true );
	   offset += 2;
       }
    }
