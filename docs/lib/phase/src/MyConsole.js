import React, { Component } from 'react';
import { connect } from 'react-redux'
import { setPhi, setW } from './MyStore';

class MyConsole extends Component {

    constructor(props) {
        super(props);
    }

    render() {

	const { phi, w } = this.props.state;
        const delay = Math.floor(  phi / w * 1000)/1000;
        const T = Math.floor(  2 * Math.PI / w * 100)/100;

        let strsig = '-';
        let strphi = '-';
        let strsec = '-';
        let strmov = '-';
        let strf = '';
        if( phi > 0 ){
            strsig = 'プラス';
            strphi = phi + ' [rad] 進んでいる';
            strsec = delay + ' [秒] 進んでいる';
            strmov = '左に' + delay + ' [秒] ';
            strf = '+ '+phi;
        }
        if( phi < 0 ){
            strsig = 'マイナス';
            strphi = (-phi) + ' [rad] 遅れている';
            strsec = (-delay) + ' [秒] 遅れている';
            strmov = '右に' + (-delay) + ' [秒] ';
            strf = '- ' + (-phi);
        }

        return (
              <div>
                <p>
                  <input type="button" value="UP"  onClick={ () => this.props.setPhi( phi + 0.5 ) } />　
                  <input type="button" value="DOWN"  onClick={ () => this.props.setPhi( phi - 0.5 ) } />　
                  初期位相 Φ = { phi } [rad]
                </p>
                <p>
                  <input type="button" value="UP"  onClick={ () => this.props.setW( w + 0.5 ) } />　
                  <input type="button" value="DOWN"  onClick={ () => this.props.setW( w - 0.5 ) } />　
                  角周波数 w = { w } [rad/秒]、周期 T = { T } [秒]
                </p>
                <p>
                  |Φ|/w = { Math.abs(delay) }
                </p>
               <table><tbody>
                 <tr><th>Φの符号</th><th>位相が・・・</th><th>秒で言い換えると・・・</th><th>平行移動方向と距離</th></tr>
                 <tr>
                   <td className="center">{strsig}</td>
                   <td className="center">{strphi}</td>
                   <td className="center">{strsec}</td>
                   <td className="center">{strmov}</td>
                 </tr>
               </tbody></table>
                <p>
                  f(t) = a ・ sin ( {w}・t {strf} )
                </p>
            </div>
        );
    }
}

const mapStateToProps = state => ({
    state: state
});

const mapDispatchToProps = {
    setPhi,
    setW
}

export default connect( mapStateToProps, mapDispatchToProps )(MyConsole);
