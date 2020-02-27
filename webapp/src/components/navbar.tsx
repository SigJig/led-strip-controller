
import React from 'react'
import Strings from '../const/strings'
import './navbar.scss'

interface INavState {

}

const routes = [
    'devices', 'connectors', 'settings'
].map(x => (Strings as any)[x].toUpperCase())

export default class Navbar extends React.Component<{}, INavState> {
    render() {
        return (
            <nav className="navbar">
                <ul>
                    {routes.map(x => <li>{x}</li>)}
                </ul>
            </nav>
        )
    }
}