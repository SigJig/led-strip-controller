
import React from 'react'
import './devices.scss'
import { AiOutlineBulb as Bulb } from 'react-icons/ai'

const routes = [
    'Devices', 'Connectors', 'Settings'
]

export default class Alt extends React.Component<{}, {}> {
    render() {
        return (
            <div className="container">
                <ul>
                    {Array(6).fill(undefined).map(x => (
                    <li>
                        <Bulb className="icon"/>
                        <span>Desk Lights (Back Left)</span>
                        <span>Lightsource</span>
                        <label>
                            <input type="checkbox"/>
                            <span></span>
                        </label>
                    </li>
                    ))}
                </ul>
            </div>
        )
    }
}