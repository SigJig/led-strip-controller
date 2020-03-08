
import React from 'react'
import { IDevice, IButton, statusClasses } from '../devices/base'
import './devices.scss'

export interface IDevicesProps {
    devices: Array<IDevice>
}

export interface IDevicesState {
    loading: boolean
}

export default class Devices extends React.Component<IDevicesProps, IDevicesState> {
    state = { loading: true }

    async refresh() {
        await Promise.all(this.props.devices.map(x => x.fetch()))

        this.setState({loading: false})
    }

    async refreshLoop() {
        await this.refresh()

        setTimeout(async () => {
            await this.refreshLoop()
        }, 2000)
    }

    componentDidMount() {
        this.refreshLoop()
    }

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
        if (this.state.loading) return <h1>Loading</h1>

        const { devices } = this.props

        return (
            <ul className="device-list">
                {
                    devices.map((device: IDevice) => {
                        const { buttons, title, icon, desc, data } = device

                        return (
                            <li className={`device-item ${statusClasses[device.statusClass!]}`}>
                                {React.createElement(icon, {className: "icon"})}
                                <span className="title">{title}</span>
                                {desc && (
                                    <span className="desc">{desc}</span>
                                )}
                                <label>
                                    <input type="checkbox" checked={data.active} onClick={(e) => this.handleActivate(device, e)}/>
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

    async handleActivate(device: IDevice, event: any) {
        const { activate } = device

        await activate.call(device, event)

        this.forceUpdate()
    }

    render() {
        return (
            <div className="container">
                {this.renderDevices()}
            </div>
        )
    }
}