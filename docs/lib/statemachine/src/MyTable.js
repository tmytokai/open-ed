import React, { Component } from 'react';
import { connect } from 'react-redux'
import parse from 'html-react-parser'

class MyTable extends Component {

    constructor(props) {
        super(props);
    }
  
    render() {
        const { state } = this.props.state;

        return (
            <div>
              <table className='statetable'>
              <tbody>
              <tr>
                <td className='diag' ><div className='diagright'>イベント</div><div className='diagleft'>現在の状態</div></td>
                <td className={ state%2 == 0 ? 'blink' : ''}>スイッチ ON</td>
                <td className={ state%2 == 1 ? 'blink' : ''}>スイッチ OFF</td>
              </tr>

              { stateopts.tr.map( ( tr, i ) => (
                <tr key={i} >
                  <td className={state == i ? 'hl' : ''} >{ parse( tr.td1 ) }</td>
                  <td>{ parse( tr.td2 ) }</td>
                  <td>{ parse( tr.td3) }</td>
                </tr> 
              ) ) }

              </tbody>
              </table>
            </div>
        );
    }
}

const mapStateToProps = state => ({
    state: state
});

const mapDispatchToProps = {
}

export default connect( mapStateToProps, mapDispatchToProps )(MyTable);
