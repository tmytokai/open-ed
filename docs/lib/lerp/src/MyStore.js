import { createStore } from 'redux';

const initialState = {
    x1: lerpopts.x1,
    x2: lerpopts.x2,
    y1: lerpopts.y1,
    y2: lerpopts.y2,
    x:  lerpopts.x,
};

const parse = (value, min, max )  => {
    const result = parseFloat( value );
    if( isNaN( result ) ) return 0.0;
    return Math.max( Math.min( result, max ), min );
};

const setXY1 = value => ({
    type: 'SETXY1',
    x1: parse( value.x, lerpopts.x_min, lerpopts.x_max ),
    y1: parse( value.y, lerpopts.y_min, lerpopts.y_max )
});

const setXY2 = value => ({
    type: 'SETXY2',
    x2: parse( value.x, lerpopts.x_min, lerpopts.x_max ),
    y2: parse( value.y, lerpopts.y_min, lerpopts.y_max )
});

const setX = value => ({
    type: 'SETX',
    x: parse( value, lerpopts.x_min, lerpopts.x_max )
});

const reducer = ( state = initialState, action ) => {
    switch ( action.type ) {
        case 'SETXY1':
            return { ...state, x1: action.x1, y1: action.y1 };
        case 'SETXY2':
            return { ...state, x2: action.x2, y2: action.y2 };
        case 'SETX':
            return { ...state, x: action.x };
        default:
            return state;
    }
}

const store = createStore( reducer, initialState );

export { setXY1, setXY2, setX, store };
