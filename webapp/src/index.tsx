
import React from 'react'
import ReactDOM from 'react-dom'
import './index.scss'
import * as serviceWorker from './serviceWorker'

import Navbar from './components/navbar'
import Devices from './screens/devices'

import RGBStrip from './devices/rgbstrip'

const devices = [
    new RGBStrip("Testing strip", "#9c0879")
]

const App: React.FC = () => {
    return (
        <div>
            <Navbar/>
            <Devices devices={devices}/>
        </div>
    )
}

ReactDOM.render(<App/>, document.getElementById('root'))

// If you want your app to work offline and load faster, you can change
// unregister() to register() below. Note this comes with some pitfalls.
// Learn more about service workers: https://bit.ly/CRA-PWA
serviceWorker.unregister()
