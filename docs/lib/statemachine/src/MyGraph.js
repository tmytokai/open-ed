import React, { Component } from 'react';
import { connect } from 'react-redux'
import { DataSet, Network } from "vis"; // https://visjs.org/

const setnodes = state => {
    let data = stateopts.nodes;
    data.forEach( d => d['color'] = { background: stateopts.background[ d['id'] ][state], border: '#000000' } );
    return data;
}

class MyGraph extends Component {

    constructor(props) {
        super(props);

        this.network = null;
        this.networkRef = React.createRef();
        this.blink = false;

        // blink
        setInterval( ()=>{
            if( this.network != null ){
                const { state } = this.props.state;

                let nodes = [];
                stateopts.nodes.forEach( d => { if( stateopts.blink[ d['id'] ] [state] ) nodes.push( d['id'] ); } );
                if( nodes.length ){
                    if( this.blink ){
                        this.network.selectNodes( nodes, false );
                        this.blink = false;
                    }
                    else{
                        this.network.unselectAll();
                        this.blink = true;
                    }
                }
           }
        }, stateopts.blinkspeed );
    }
  
    render() {
        const { state } = this.props.state;

        if( this.network != null ){
            const data = {
                nodes: new DataSet( setnodes(state) ),
                edges: new DataSet( stateopts.edges ),
            };
            this.network.setData(data);
            this.network.redraw();
        }

        return (
            <div ref={this.networkRef} />
        );
    }

    componentDidMount() {
        const { state } = this.props.state;

        const data = {
            nodes: new DataSet( setnodes(state) ),
            edges: new DataSet( stateopts.edges ),
        };

        const options = {
          width:  stateopts.width,
          height: stateopts.height,
          physics:{
            enabled: false
          },

          nodes:{
            borderWidth: 1,
            shape: 'circle',
            chosen:{
                node: function(values, id, selected, hovering) {
                    values.color = '#FFFFFF';
                },
            },
            color: {
                background: '#FFFFFF',
                border: '#000000',
            },
            fixed: true,
            labelHighlightBold: false,
          },

          edges:{
            color: {
                color:'#000000',
                highlight:'#000000',
                hover: '#000000',
                inherit: false,
                opacity: 1.0,
            },
            chosen: false,
          },
        };

        this.network = new Network( this.networkRef.current, data, options );
    }
}

const mapStateToProps = state => ({
    state: state
});

const mapDispatchToProps = {
}

export default connect( mapStateToProps, mapDispatchToProps )(MyGraph);
