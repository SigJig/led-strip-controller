
import React from 'react'
import './devices.scss'

const routes = [
    'Devices', 'Connectors', 'Settings'
]

interface IButton {
    Icon?: JSX.Element,
    title: string,
    action: CallableFunction
}

interface IDevicesProps {
    devices: Array<{
        buttons: any[],
        title: string,
        Icon: any,
        desc?: string
    }>
}

export default class Devices extends React.Component<IDevicesProps, {}> {
    renderDevices() {
        const { devices } = this.props;

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
                            {buttons && buttons.length && (
                                <ul className="buttons">
                                    <li>Change Color</li>
                                    <li>Manage</li>
                                </ul>
                            )}
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