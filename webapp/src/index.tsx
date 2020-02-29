
import React from 'react'
import ReactDOM from 'react-dom'
import './index.css'
import * as serviceWorker from './serviceWorker'

import Navbar from './components/navbar'
import Devices from './screens/devices'

import { AiOutlineBulb } from 'react-icons/ai'

const App: React.FC = () => {
    return (
        <div>
            <Navbar/>
            <Devices devices={Array(6).fill({
                title: "Desk Lights (Back Left)",
                buttons: [
                    {
                        title: "Manage",
                        action: () => {}
                    },
                    {
                        title: "Change Color",
                        action: () => {}
                    }
                ],
                desc: "Lightsource",
                Icon: AiOutlineBulb
            })}/>
        </div>
    )
}

ReactDOM.render(<App/>, document.getElementById('root'))

// If you want your app to work offline and load faster, you can change
// unregister() to register() below. Note this comes with some pitfalls.
// Learn more about service workers: https://bit.ly/CRA-PWA
serviceWorker.unregister()
