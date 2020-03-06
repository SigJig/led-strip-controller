
import React from 'react'
import { IDevice, IButton } from '../devices/base'
import './devices.scss'

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
        console.log(devices)

        return (
            <ul className="device-list">
                {
                    devices.map((device: IDevice) => {
                        const {buttons, title, icon, desc, activate} = device

                        return (
                            <li className="device-item">
                                {React.createElement(icon, {className: "icon"})}
                                <span className="title">{title}</span>
                                {desc && (
                                    <span className="desc">{desc}</span>
                                )}
                                <label>
                                    <input type="checkbox" onChange={activate.bind(device)}/>
                                    <span/>
                                </label>
                                {buttons && buttons.length && this.renderButtons(buttons)}
                            </li>
                        )
                    })
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