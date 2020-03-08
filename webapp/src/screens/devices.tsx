
import React from 'react'
import { IDevice, IButton, statusClasses } from '../devices/base'
import './devices.scss'
import { Redirect } from 'react-router-dom'

export interface IDevicesProps {
    devices: Array<IDevice>
}

export interface IDevicesState {
    loading: boolean,
    redirect?: string
}

export default class Devices extends React.Component<IDevicesProps, IDevicesState> {
    state = { loading: true, redirect: undefined }

    async refresh() {
        await Promise.all(this.props.devices.map(x => x.fetch()))
    }

    async refreshLoop() {
        await this.refresh()

        setTimeout(async () => {
            await this.refreshLoop()
        }, 2000)
    }

    async componentDidMount() {
        await this.refreshLoop()

        this.setState({loading: false})
    }

    renderButtons(buttons: IButton[]) {
        return (
            <ul className="buttons">
                {buttons.map(x => (
                    <li onClick={x.action.bind(this)}>
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
        if (this.state.redirect) return <Redirect to={this.state.redirect!}/>

        return (
            <div className="container">
                {this.renderDevices()}
            </div>
        )
    }
}