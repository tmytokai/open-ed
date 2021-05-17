import React, { Component } from 'react';
import MyConsole from './MyConsole';
import MySin from './MySin';

export default class App extends Component {

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
