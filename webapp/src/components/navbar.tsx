
import React from 'react'
import Strings from '../const/strings'
import './navbar.scss'

import { AiOutlineBulb } from 'react-icons/ai'
import { GoGear } from 'react-icons/go'
import { IoIosLink } from 'react-icons/io'

interface INavState {
    date: Date
}

const routes = [
    [Strings.devices, AiOutlineBulb],
    [Strings.connectors, IoIosLink],
    [Strings.settings, GoGear]
]

export default class Navbar extends React.Component<{}, INavState> {
    state = { date: new Date(0) }

    handleClock = () => {
        this.setState({date: new Date()})

        setTimeout(this.handleClock, 300)
    }

    fmtDate() {
        const { date } = this.state
        const converter = new Proxy(date, {
            get(t: any, v: any, r: any) {
                const fnc = Reflect.get(t, v, r)
                const res = fnc.apply(t)

                return res > 10 ? res.toString() : ('0' + res.toString())
            }
        })
        

        return `${converter.getHours}:${converter.getMinutes}:${converter.getSeconds}`
    }

    componentDidMount() {
        this.handleClock.apply(this, [])
    }

    render() {
        return (
            <nav className="navbar">
                <span className="fs-nav-elem">{this.fmtDate.apply(this)}</span>
                <ul>
                    {routes.map(([text, icon]) => (
                        <li>
                            <span className="fs-nav-elem">{text}</span>
                            {React.createElement(icon, {className: "mob-nav-elem"})}
                        </li>
                    ))}
                </ul>
            </nav>
        )
    }
}