import React, { Component } from 'react';
import { connect } from 'react-redux'
import { Chart, Line } from 'react-chartjs-2';
import annotationPlugin from 'chartjs-plugin-annotation';

class MySin extends Component {

    constructor(props) {
        super(props);
        Chart.register(annotationPlugin);
    }

    render() {

        const t_min = -3*20.0;
        const t_max = 3*20.0;

	const { phi, w } = this.props.state;
        const delay = Math.floor(  phi / w * 1000)/1000;
        const delaypos = 3*20.0 - ( phi / w )*20.0;

        const options = {
            animation: false,
            responsive: false,
            plugins: {
                legend: {
                    display: false
                },
               annotation: {
                   annotations: {
                       line1: {
                           type: 'line',
                           xMin: 3*20.0,
                           xMax: 3*20.0,
                           borderColor: 'rgb(0, 0, 0)',
                           borderWidth: 1,
                           borderDash: [10,10],
			   label: {
			       enabled: false
			   }
                       },
                       line2: {
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
                       line3: {
                           type: 'line',
                           xMin: delaypos,
                           xMax: delaypos,
                           borderColor: 'rgb(255, 99, 132)',
                           borderWidth: 2,
			   label: {
			       enabled: true,
			       content: "t ="+(-delay),
			       position: "end",
			       yAdjust: 30
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
                    title: {
                        display: true,
                        text: 't [秒]',
                        font: {
                            size: 24
                        }
                    },
        	    grid: {
        		display: false,
        	    },
                    ticks: {
                        autoSkip: false,
                        maxRotation: 0,
                        callback: (value, index, values) => {
        		    return index % 20 ? "" : (index-3*20)/20;
                        }
                    }
                },
                y: {
                    title: {
                        display: true,
                        text: 'f(t)',
                        font: {
                            size: 24
                        }
                    },
        	    grid: {
        		display: false,
        	    },
                    ticks: {
                        callback: (value, index, values) => {
        		    return "";
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

        for( let t = t_min; t <= t_max; t += 1 ){
            data.labels.push( t );
            data.datasets[0].data.push( Math.sin( w * t/20 + phi ) );
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
}

export default connect( mapStateToProps, mapDispatchToProps )(MySin);
