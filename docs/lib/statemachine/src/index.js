import React from 'react';
import ReactDOM from 'react-dom';
import './index.css';
import App from './App';
import { Provider } from 'react-redux'
import { store } from './MyStore'

ReactDOM.render( <Provider store={store}><App /></Provider>, document.getElementById( stateopts.root ) );
