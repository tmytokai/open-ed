import React, { Component } from 'react';
import { connect } from 'react-redux'
import { setFreq } from './MyStore';
import { Chart, Line } from 'react-chartjs-2';
import annotationPlugin from 'chartjs-plugin-annotation';
import MovableAnnotations from '../../modules/MovableAnnotations';

class MySin extends Component {

    constructor(props) {
        super(props);
        Chart.register(annotationPlugin);

	this.movableAnnotations = new MovableAnnotations( this.cbSetValue.bind(this) );
	this.movableAnnotations.add( 'lineT' );
    }

    cbSetValue(id,px,py){
	const freq = Math.floor( 1000.0/px );
	this.props.setFreq( freq );
    }

    render() {

        const freq = this.props.state.freq;
        const T = 1.0/freq*1000.0;

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

                       lineXaxis: {
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

                       lineT: {
                           type: 'line',
                           xMin: T,
                           xMax: T,
                           borderColor: 'rgb(0, 0, 0)',
                           borderWidth: 1,
                           borderDash: [10,10],
			   label: {
			       enabled: true,
			       content: "T",
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
		    min: 0,
		    max: playsinopts.x_max,
                    ticks: {
			stepSize: playsinopts.x_step,
                    },
                    title: {
                        display: true,
                        text: 'ミリ秒',
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
                        text: '振幅',
                        font: {
                            size: 24
                        }
                    },
        	    grid: {
        		display: false,
        	    },
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

        let t = 0;
        for( let i = 0; t < playsinopts.x_max; i++ ){
            t = 0.05 * i;
            data.labels.push( t );
            data.datasets[0].data.push( Math.sin( 2*Math.PI * freq * t/1000. ) );
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
    setFreq
}

export default connect( mapStateToProps, mapDispatchToProps )(MySin);
