import { createStore } from 'redux';

const initialState = {
    phi: 0.0,
    w: 2.0
};

const parse = (value, max, min )  => {
    let result = parseFloat( value );
    if( isNaN( result ) ) result = 0.0;
    if( result > max ) result = max;
    if( result < min ) result = min;
    return result;
};

const setPhi = value => ({
    type: "SETPHI", 
    phi: parse(value, 3.0, -3.0 )
});

const setW = value => ({
    type: "SETW", 
    w: parse(value, 4.0,  1 )
});


const reducer = ( state = initialState, action ) => {
    switch ( action.type ) {
        case "SETPHI":
            return {  ...state, phi: action.phi }
        case "SETW":
            return {  ...state, w: action.w }
        default:
            return state;
    }
}

const store = createStore( reducer, initialState );

export { setPhi, setW, store };
