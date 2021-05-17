import React, { Component } from 'react';
import { connect } from 'react-redux'
import { Chart, Line } from 'react-chartjs-2';
import annotationPlugin from 'chartjs-plugin-annotation';
import MovableAnnotations from '../../modules/MovableAnnotations';
import { setPhi } from './MyStore';

class MySin extends Component {

    constructor(props) {
        super(props);
        Chart.register(annotationPlugin);

	this.movableAnnotations = new MovableAnnotations( this.cbSetValue.bind(this) );
	this.movableAnnotations.add( 'lineStart' );
    }

    cbSetValue(id,px,py){
       const phi = Math.floor( -px * this.props.state.w * 100.0 )/100.0;
       this.props.setPhi( phi );
    }

    render() {

        const { phi, w } = this.props.state;
        const delay = phi/w;

        const options = {
            animation: false,
            responsive: false,

            plugins: {
                legend: {
                    display: false
                },

                annotation: {
                   enter : ctx => this.movableAnnotations.enter(ctx),
                   leave : ctx => this.movableAnnotations.leave(ctx),

                   annotations: {

                       lineYaxis: {
                           type: 'line',
                           xMin: 0,
                           xMax: 0,
                           borderColor: 'rgb(0, 0, 0)',
                           borderWidth: 1,
                           borderDash: [10,10],
			   label: {
			       enabled: false
			   }
                       },

                       lineXAxis: {
                           type: 'line',
                           yMin: 0,
                           yMax: 0,
                           borderColor: 'rgb(0, 0, 0)',
                           borderWidth: 1,
                           borderDash: [10,10],
			   label: {
			       enabled: false
			   }
                       },

                       lineStart: {
                           type: 'line',
                           xMin: -delay,
                           xMax: -delay,
                           borderColor: 'rgb(255, 0, 0)',
                           borderWidth: 1,
			   label: {
			       enabled: true,
			       content: "Start",
			       position: "end",
                               backgroundColor: 'rgba(0, 0, 0, 0.6 )',
			       yAdjust: 32
			   }
                      }
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
		    min: phaseopts.x_min,
		    max: phaseopts.x_max,
                    ticks: {
			stepSize: phaseopts.x_step,
                    },
                    title: {
                        display: true,
                        text: 't [秒]',
                        font: {
                            size: 24
                        }
                    },
        	    grid: {
        		display: false,
        	    }
                },

                y: {
                    type: 'linear',
		    min: -1.0,
		    max:  1.0,
                    ticks: {
                          display: false,
                    },
                    title: {
                        display: true,
                        text: 'f(t)',
                        font: {
                            size: 24
                        }
                    },
        	    grid: {
        		display: false,
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

        let t = phaseopts.x_min;
        for( let i = 0; t < phaseopts.x_max; i++ ){
            t = phaseopts.x_min + 0.05 * i;
            data.labels.push( t );
            data.datasets[0].data.push( Math.sin( w * t + phi ) );
        }

        return (
            <Line data={data} options={options} width={500} height={300} />
        );
    }
}

const mapStateToProps = state => ({
    state: state
});

const mapDispatchToProps = {
    setPhi
}

export default connect( mapStateToProps, mapDispatchToProps )(MySin);
