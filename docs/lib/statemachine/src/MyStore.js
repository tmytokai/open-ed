import { createStore } from 'redux';

const initialState = {
    state: 0
};

const inc = () => ({
    type: 'INC'
});

const reducer = ( state = initialState, action ) => {
    switch (action.type) {
        case 'INC':
            return { state: (state.state + 1)%stateopts.states };
        default:
            return state;
    }
}

const store = createStore( reducer, initialState );

export { inc, store };
