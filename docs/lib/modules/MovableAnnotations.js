//  extension of chartjs-plugin-annotation 
class MovableAnnotations {

    constructor(cb){
	this.data = [];
        this.cb = cb;
	this.dragging = '';

        document.addEventListener( 'mousedown', this.down.bind(this) );
        document.addEventListener( 'mousemove', this.move.bind(this) );
        document.addEventListener( 'mouseup',   this.up.bind(this) );
    }

    add(id){
	this.data[id] ={
	    id : id,
	    chart : null,
            element : null,
            offsetX : 0,
            offsetY : 0
        };
    }

    // connected to options.plugins.annotation.enter
    enter(ctx){
	const id = ctx.element.options.id;
//        console.log( 'enter: ' + id );
        if( this.data[id] ){
            this.data[id].entered = true;
	    this.data[id].chart = ctx.chart;
	    this.data[id].element = ctx.element;
	}
    }

    // connected to options.plugins.annotation.leave
    leave(ctx){
	const id = ctx.element.options.id;
//        console.log( 'leave: ' + id );
        if( this.data[id] ){
	    this.data[id].entered = false;
	}
    }

    down(ev){

	if( this.dragging != '' ) return;

        for( let id in this.data ){
            if( this.data[id].entered ){
//                console.log(id);
//                console.log('down');
//                console.log(this.data[id].element);
//                console.log(ev);
                this.dragging = id;
	        this.data[id].offsetX = this.data[id].element.x - ev.screenX;
	        this.data[id].offsetY = this.data[id].element.y - ev.screenY;
            }
        }
    }

    move(ev){
	if( this.dragging != '' ){
            const id = this.dragging;
	    const x =this.data[id].chart.scales.x.getValueForPixel( ev.screenX + this.data[id].offsetX ); 
	    const y =this.data[id].chart.scales.y.getValueForPixel( ev.screenY + this.data[id].offsetY ); 
	    this.cb(id,x,y);
        }
    }

    up(ev){
	if( this.dragging != '' ){
//            console.log('up');
	    this.dragging = '';
	}
    }
}

export default MovableAnnotations;
