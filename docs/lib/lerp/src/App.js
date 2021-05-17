import React, { Component } from 'react';
import MyTable from './MyTable';
import MyLine from './MyLine';

export default class App extends Component {

    constructor(props) {
        super(props);
    }

    render() {

        return (
            <div>
              <table className='lerpframe' ><tbody><tr>
              <td>
                <MyTable />
              </td>
              <td>
                <MyLine />
              </td>
              </tr></tbody></table>
            </div>
        );
    }
}
