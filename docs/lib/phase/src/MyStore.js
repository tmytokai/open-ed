import { createStore } from 'redux';

const initialState = {
    phi: phaseopts.phi,
    w: phaseopts.w,
};

const setPhi = value => ({
    type: "SETPHI", 
    phi: Math.max( Math.min( value, phaseopts.phi_max ), phaseopts.phi_min )
});

const setW = value => ({
    type: "SETW", 
    w: Math.max( Math.min( value, phaseopts.w_max ), phaseopts.w_min )
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
