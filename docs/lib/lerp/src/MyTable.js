import React, { Component } from 'react';
import { connect } from 'react-redux'
import { setXY1, setXY2, setX } from './MyStore';

class MyTable extends Component {

    constructor(props) {
        super(props);

        this.target = {};
    }

    render() {

        const { x1, x2, y1, y2, x } = this.props.state;
        const b = (y2-y1)/(x2-x1);
	const y = y1 + b * (x-x1);

        return (
              <div>
              <table className='lerptable'>
              <tbody>
              <tr>
                <td className='diag'></td>
                <td>{lerpopts.table.labelx}</td>
                <td>{lerpopts.table.labely}</td>
              </tr>
              <tr>
                <td>{lerpopts.table.labelp1}</td>
                <td>x1 = <input id='x1' type='text' size='5' onInput={ e => this.props.setXY1( { x: e.target.value, y: this.props.state.y1 } ) } defaultValue={ lerpopts.x1 } /></td>
                <td>y1 = <input id='y1' type='text' size='5' onInput={ e => this.props.setXY1( { x: this.props.state.x1, y: e.target.value } ) } defaultValue={ lerpopts.y1 } /></td>
              </tr>
              <tr>
                <td>{lerpopts.table.labelp2}</td>
                <td>x2 = <input id='x2' type='text' size='5' onInput={ e => this.props.setXY2( { x: e.target.value, y: this.props.state.y2 } ) } defaultValue={ lerpopts.x2 } /></td>
                <td>y2 = <input id='y2' type='text' size='5' onInput={ e => this.props.setXY2( { x: this.props.state.x2, y: e.target.value } ) } defaultValue={ lerpopts.y2 } /></td>
              </tr>
              </tbody>
              </table>

              <p>b = (y2-y1)/(x2-x1)</p>
              <p>y = y1 + b*(x-x1)</p>
              <p>x = <input id='x' type='text' size='5' onInput={ e => this.props.setX( e.target.value ) } defaultValue={ lerpopts.x } /> の時 y = { Math.floor(y*100.0)/100.0 } </p> 

              </div>
        );
    }

    componentDidMount() {
        [ 'x1', 'x2', 'y1', 'y2', 'x' ].forEach( i => this.target[ i ] = document.getElementById( i ) );
    }

    componentDidUpdate(){
        const { x1, x2, y1, y2, x } = this.props.state;

        const getValue = id => {
            const value = parseFloat( this.target[id].value );
            if( isNaN( value ) ) return 0.0;
            return value;
        }

        if( x1 != getValue('x1') ) this.target['x1'].value = x1;
        if( x2 != getValue('x2') ) this.target['x2'].value = x2;
        if( y1 != getValue('y1') ) this.target['y1'].value = y1;
        if( y2 != getValue('y2') ) this.target['y2'].value = y2;
        if( x !=  getValue('x') )  this.target['x'].value = x;
    }
}

const mapStateToProps = state => ({
    state: state
});

const mapDispatchToProps = {
    setXY1,
    setXY2,
    setX
}

export default connect( mapStateToProps, mapDispatchToProps )(MyTable);
