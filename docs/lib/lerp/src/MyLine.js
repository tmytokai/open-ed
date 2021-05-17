import React, { Component } from 'react';
import { connect } from 'react-redux'
import { Chart, Line } from 'react-chartjs-2';
import annotationPlugin from 'chartjs-plugin-annotation';
import MovableAnnotations from '../../modules/MovableAnnotations';
import { setXY1, setXY2, setX } from './MyStore';

class MyLine extends Component {

    constructor(props) {
        super(props);
        Chart.register(annotationPlugin);

	this.movableAnnotations = new MovableAnnotations( this.cbSetValue.bind(this) );
        [ 'pointXY1', 'pointXY2', 'pointX', 
          'labelX1', 'labelY1', 'labelX2', 
          'labelY2', 'labelX', 'labelY' ].forEach( i => this.movableAnnotations.add( i ) );
    }

    cbSetValue(id,px,py){

        const { x1, x2, y1, y2, x } = this.props.state;

        px = Math.floor(px*100)/100;
        py = Math.floor(py*100)/100;

        if( id == 'pointXY1' ) this.props.setXY1( {x:px, y:py} );
        if( id == 'pointXY2' ) this.props.setXY2( {x:px, y:py} );
        if( id == 'pointX' ) this.props.setX( px );
        if( id == 'labelX1' ) this.props.setXY1( {x:px, y:y1} );
        if( id == 'labelY1' ) this.props.setXY1( {x:x1, y:py} );
        if( id == 'labelX2' ) this.props.setXY2( {x:px, y:y2} );
        if( id == 'labelY2' ) this.props.setXY2( {x:x2, y:py} );
        if( id == 'labelX' ) this.props.setX( px );
        if( id == 'labelY' ){
            const b = (y2-y1)/(x2-x1);
            this.props.setX( Math.floor( (py-y1)/b + x1)*100/100 );
        }
    }

    render() {

        const { x1, x2, y1, y2, x } = this.props.state;
        const b = (y2-y1)/(x2-x1);
        const y = y1 + b * (x-x1);

        const options = {
            animation: false,
            responsive: false,

            plugins: {
                legend: {
                    display: false
                },
                tooltip:{
	            enabled: false
                },
                annotation: {
                    enter : ctx => this.movableAnnotations.enter(ctx),
                    leave : ctx => this.movableAnnotations.leave(ctx),

                    annotations: {

                       labelX1 : {
                           type: 'line',
                           xMin: x1,
                           xMax: x1,
                           yMin: y1,
                           borderColor: 'rgb(0, 0, 0)',
                           borderWidth: 1,
                           borderDash: [5,5],
			   label: {
			       enabled: true,
			       content: "x1",
			       position: "end",
                               backgroundColor: 'rgba(0, 0, 0, 0.6 )',
			       yAdjust: 32
			   }
                       },

                       labelY1: {
                           type: 'line',
                           yMin: y1,
                           yMax: y1,
                           xMax: x1,
                           borderColor: 'rgb(0, 0, 0)',
                           borderWidth: 1,
                           borderDash: [5,5],
			   label: {
			       enabled: true,
			       content: "y1",
                               backgroundColor: 'rgba(0, 0, 0, 0.6 )',
			       position: "start",
			       xAdjust: -32
			   }
                       },

                       labelX2: {
                           type: 'line',
                           xMin: x2,
                           xMax: x2,
                           yMin: y2,
                           borderColor: 'rgb(0, 0, 0)',
                           borderWidth: 1,
                           borderDash: [5,5],
			   label: {
			       enabled: true,
			       content: "x2",
			       position: "end",
                               backgroundColor: 'rgba(0, 0, 0, 0.6 )',
			       yAdjust: 32
			   }
                       },

                       labelY2: {
                           type: 'line',
                           yMin: y2,
                           yMax: y2,
                           xMax: x2,
                           borderColor: 'rgb(0, 0, 0)',
                           borderWidth: 1,
                           borderDash: [5,5],
			   label: {
			       enabled: true,
			       content: "y2",
                               backgroundColor: 'rgba(0, 0, 0, 0.6 )',
			       position: "start",
			       xAdjust: -32
			   }
                       },

                       labelX: {
                           display: ( x1 != x2 )  ? true : false,
                           type: 'line',
                           xMin: x,
                           xMax: x,
                           yMin: y,
                           borderColor: 'rgb(0, 0, 0)',
                           borderWidth: 1,
                           borderDash: [5,5],
			   label: {
			       enabled: true,
			       content: "x",
                               backgroundColor: 'rgba(0, 0, 0, 0.6 )',
			       position: "end",
			       yAdjust: 32
			   }
                       },

                       labelY: {
                           display: ( lerpopts.y_min <= y && y <= lerpopts.y_max )  ? true : false,
                           type: 'line',
                           yMin: y,
                           yMax: y,
                           xMax: x,
                           borderColor: 'rgb(0, 0, 0)',
                           borderWidth: 1,
                           borderDash: [5,5],
			   label: {
			       enabled: true,
			       content: "y",
                               backgroundColor: 'rgba(0, 0, 0, 0.6 )',
			       position: "start",
			       xAdjust: -28
			   }
                       },

                       pointXY1: {
                           type: 'point',
                           xValue: x1,
                           yValue: y1,
                           radius: 6,
                           backgroundColor: 'rgb(255, 0, 0 )',
                       },

                       pointXY2: {
                           type: 'point',
                           xValue: x2,
                           yValue: y2,
                           radius: 6,
                           backgroundColor: 'rgb(255, 0, 0 )',
                       },

                       pointX: {
                           display: ( lerpopts.y_min <= y && y <= lerpopts.y_max )  ? true : false,
                           type: 'point',
                           xValue: x,
                           yValue: y,
                           radius: 6,
                           backgroundColor: 'rgb(0, 255, 0 )',
                       },

                    }
                }
            },

            elements: {
        	point:{
        	    radius: 0
        	}
            },

            scales: {
                x: {
                    type: 'linear',
		    min: lerpopts.x_min,
		    max: lerpopts.x_max,
                    ticks: {
			stepSize: lerpopts.x_step,
                        font: {
                            size: 9
                        }
                    },
                    title: {
                        display: true,
                        text: 'x',
                        font: {
                            size: 24
                        }
                    }
                },

                y: {
                    type: 'linear',
		    min: lerpopts.y_min,
		    max: lerpopts.y_max,
                    ticks: {
			stepSize: lerpopts.y_step
                    },
                    title: {
                        display: true,
                        text: 'y',
                        font: {
                            size: 24
                        }
                    }
                },
            }
        };

        let data = {
            labels: [],
            datasets: [{
                data: [],
                borderColor: 'rgb(0, 0, 0)',
                borderWidth: 1,
            }]
        };

        if( x1 != x2 ){
            data.labels.push( lerpopts.x_min );
            data.datasets[0].data.push( y1 + b *(lerpopts.x_min-x1) );

            data.labels.push( x1 );
            data.datasets[0].data.push( y1 );

            data.labels.push( x2 );
            data.datasets[0].data.push( y2 );

            data.labels.push( lerpopts.x_max );
            data.datasets[0].data.push( y1 + b *(lerpopts.x_max-x1) );
        }
        else{ // vertical line
            data.labels.push( x1 );
            data.datasets[0].data.push( lerpopts.y_min );
            data.labels.push( x1 );
            data.datasets[0].data.push( lerpopts.y_max );
        }

        return (
            <Line data={data} options={options} width={lerpopts.width} height={lerpopts.height} />
        );
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

export default connect( mapStateToProps, mapDispatchToProps )(MyLine);
