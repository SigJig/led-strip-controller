
import React from 'react'
import { IconType } from 'react-icons/lib/cjs'
import { FaRegLightbulb as Bulb } from 'react-icons/fa'

import './devices.css'

interface ICardState {

}

interface ICardProps {
    image: IconType,
    text: string
}

const devices = Array(8).fill(
    {
        image: Bulb,
        text: 'Desk Lights (Back Left)'
    }
)

export class DeviceCard extends React.Component<ICardProps, ICardState> {
    render() {
        const { image, text } = this.props

        return (
            <div className="device-card">
                <span>{text}</span>
                <div className="device-switch"></div>
                <div className="device-status"></div>
            </div>
        )
    }
}

export default class Devices extends React.Component<{}, {}> {
    render() {
        return (
            <div className="devices">
                {devices.map(x => <DeviceCard {...x}/>)}
            </div>
        )
    }
}