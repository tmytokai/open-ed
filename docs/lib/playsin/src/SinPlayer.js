class SinPlayer {

    constructor() {
        this.context = null;
        this.oscillator = null;
        this._playing = false;
    }

    get playing() {
        return this._playing;
    }

    play (freq) {

        if( ! this._playing ){
//           console.log( 'freq='+freq );
           let AudioContext = window.AudioContext || window.webkitAudioContext;
           this.context = new AudioContext();
           this.oscillator = this.context.createOscillator();
           this.oscillator.connect( this.context.destination );
           this.oscillator.frequency.value = freq;
           this.oscillator.start();
           this._playing = true;
       }
       else{
           this.oscillator.stop();
           this.context.close();
           this._playing = false;
       }
    }

    setFreq (freq){
        if( this._playing ) this.oscillator.frequency.value = freq;
    }
}

export default SinPlayer;
