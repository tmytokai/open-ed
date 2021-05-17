import React, { Component } from 'react';
import { connect } from 'react-redux'
import { setFreq } from './MyStore';
import SinPlayer from './SinPlayer';

class MyConsole extends Component {

    constructor(props) {
        super(props);
        this.player = new SinPlayer();
    }

    play = () => {
	this.player.play( this.props.state.freq );
        this.forceUpdate();
    }

    render() {

	const freq = this.props.state.freq;
        const T = Math.floor( 1000.0/freq * 100)/100;
        const label = this.player.playing ? "停止" : "再生";

        this.player.setFreq( freq );

        return (
              <div>
                <input type="button" value={ label }  onClick={ this.play } />　
                <input type="button" value="UP"   onClick={ () => this.props.setFreq( Math.min( freq + 20, playsinopts.freq_max ) ) } />　
                <input type="button" value="DOWN" onClick={ () => this.props.setFreq( Math.max( freq - 20, playsinopts.freq_min ) ) } />　
                <p>
		周波数 f = { freq } [Hz]
                </p>
                <p>
		周期　 T = { T } [ミリ秒]
                </p>
              </div>
        );
    }
}

const mapStateToProps = state => ({
    state: state
});

const mapDispatchToProps = {
    setFreq
}

export default connect( mapStateToProps, mapDispatchToProps )(MyConsole);
