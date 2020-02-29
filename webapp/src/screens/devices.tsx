
import React from 'react'
import './devices.scss'

const routes = [
    'Devices', 'Connectors', 'Settings'
]

export interface IButton {
    renderIcon?: CallableFunction,
    title: string,
    action: any
}

export interface IDevice {
    buttons: IButton[],
    title: string,
    Icon: any,
    desc?: string
}

export interface IDevicesProps {
    devices: Array<IDevice>
}

export default class Devices extends React.Component<IDevicesProps, {}> {
    renderButtons(buttons: IButton[]) {
        return (
            <ul className="buttons">
                {buttons.map(x => (
                    <li onClick={x.action}>
                        {x.renderIcon && x.renderIcon()}
                        <span>{x.title}</span>
                    </li>
                ))}
            </ul>
        )
    }

    renderDevices() {
        const { devices } = this.props

        return (
            <ul className="device-list">
                {
                    devices.map(({buttons, title, Icon, desc}) => (
                        <li className="device-item">
                            <Icon className="icon"/>
                            <span className="title">{title}</span>
                            {desc && (
                                <span className="desc">{desc}</span>
                            )}
                            <label>
                                <input type="checkbox"/>
                                <span/>
                            </label>
                            {buttons && buttons.length && this.renderButtons(buttons)}
                        </li>
                    ))
                }
            </ul>
        )
    }

    render() {
        return (
            <div className="container">
                {this.renderDevices()}
            </div>
        )
    }
}