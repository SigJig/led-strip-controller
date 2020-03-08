
import React from 'react'
import Strings from '../const/strings'
import './navbar.scss'

import { IconType } from 'react-icons'
import { AiOutlineBulb } from 'react-icons/ai'
import { GoGear } from 'react-icons/go'
import { IoIosLink } from 'react-icons/io'

import Devices from '../screens/devices'
import Colorpicker from '../screens/colorpicker'

import RGBStrip from '../devices/rgbstrip'

import {
    BrowserRouter as Router,
    NavLink,
    Route,
    Switch,
    Link
} from 'react-router-dom'

interface INavState {
    date: Date
}

export const devices = [
    new RGBStrip(0),
]

const routes: [string, string, IconType][] = [
    ['/devices', Strings.devices, AiOutlineBulb],
    ['/connectors', Strings.connectors, IoIosLink],
    ['/settings', Strings.settings, GoGear]
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

                return res >= 10 ? res.toString() : ('0' + res.toString())
            }
        })
        

        return `${converter.getHours}:${converter.getMinutes}:${converter.getSeconds}`
    }

    componentDidMount() {
        this.handleClock.apply(this, [])
    }

    render() {
        return (
            <Router>
                <nav className="navbar">
                    <span id="clock" className="fs-nav-elem">{this.fmtDate.apply(this)}</span>
                    <ul>
                        {routes.map(([route, text, icon]) => (
                            <li>
                                <NavLink to={route} activeClassName="active">
                                    <span className="fs-nav-elem">{text}</span>
                                    {React.createElement(icon, {className: "mob-nav-elem"})}
                                </NavLink>
                            </li>
                        ))}
                    </ul>
                </nav>

                <Switch>
                    <Route path="/devices/:deviceId/color" component={Colorpicker}/>
                    <Route path="/devices"><Devices devices={devices}/></Route>
                </Switch>
            </Router>
        )
    }
}