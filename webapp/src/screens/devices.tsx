
import React from 'react'
import { IconType } from 'react-icons/lib/cjs'
import { AiOutlineBulb as Bulb } from 'react-icons/ai'

// import { d1 } from '../connector'

import './devices.css'

interface ICardState {
    checked: boolean
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
    constructor(props: ICardProps) {
        super(props)

        this.state = { checked: false }
        this.toggleCheckbox = this.toggleCheckbox.bind(this)
    }

    toggleCheckbox({target}: React.ChangeEvent<HTMLInputElement>) {
        const { checked } = target

        // d1.power(checked)
        this.setState({checked: checked})
    }

    render() {
        const { image, text } = this.props
        const A = image;

        return (
            <div className="device-card">
                <div className="device-inner">
                    <A className="device-icon"/>
                    <span>{text}</span>
                    <label className="device-switch">
                        <input type="checkbox" onChange={this.toggleCheckbox}/>
                        <span className="slider"></span>
                    </label>
                </div>
                <div className={"device-status " + (this.state.checked ? "success" : "")}></div>
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