import React, { Component } from 'react';
import MyTable from './MyTable';
import MySwitch from './MySwitch';
import MyGraph from './MyGraph';

export default class App extends Component {

    constructor(props) {
        super(props);
    }
  
    render() {
        return (
            <div>
              <table className='stateframe'><tbody><tr>
              <td>
                { stateopts.showtable ? <MyTable /> : '' }
              </td>
              <td>
                <MySwitch />
                <MyGraph />
              </td>

              </tr></tbody></table>
            </div>
        );
    }
}
