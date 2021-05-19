import React, { Component } from 'react';
import { connect } from 'react-redux'
import { inc } from './MyStore';

class MySwitch extends Component {

    constructor(props) {
        super(props);
        this.pushed = false
    }
  
    onmousedown = (e) => {
        this.props.inc();
        this.pushed = true;
    }

    onmouseup = (e) => {
        if( this.pushed ){
            this.props.inc();
            this.pushed = false;
        }
    }

    render() {
        return (
            <button type='button' id='button' className='switch' onMouseDown={ this.onmousedown } >スイッチ</button>
        );
    }

    componentDidMount() {
        document.addEventListener( 'mouseup', this.onmouseup );
    }
}

const mapStateToProps = state => ({
});

const mapDispatchToProps = {
    inc
}

export default connect( mapStateToProps, mapDispatchToProps )(MySwitch);
