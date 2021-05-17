import { createStore } from 'redux';

const initialState = {
    freq: playsinopts.freq
};

const setFreq = value => ({
    type: "SETFREQ", 
    freq: Math.max( Math.min( value, playsinopts.freq_max ), playsinopts.freq_min )
});

const reducer = ( state = initialState, action ) => {
    switch ( action.type ) {
        case "SETFREQ":
            return { ...state, freq: action.freq }
        default:
            return state;
    }
}

const store = createStore( reducer, initialState );

export { setFreq, store };
