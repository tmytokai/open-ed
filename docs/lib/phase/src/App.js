import React, { Component } from 'react';
import MyConsole from './MyConsole';
import MySin from './MySin';

class App extends Component {

    constructor(props) {
        super(props);
    }

    render() {

        return (
            <div>
                <MyConsole />
                <MySin />
            </div>
        );
    }
}

export default App;
