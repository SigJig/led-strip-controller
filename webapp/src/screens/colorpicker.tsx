
import React from 'react'
import './colorpicker.scss'

import { MdDone as Done, MdExitToApp as Cancel } from 'react-icons/md'
import { Color, HSV } from '../utils/color'
import { devices } from '../components/navbar'
import RGBStrip from '../devices/rgbstrip'

import { match, Redirect } from 'react-router-dom'

export interface IColorPickerState {
    color?: HSV,
    device?: RGBStrip,
    loading: boolean,
    done: boolean
}

export interface IColorPickerProps {
    match: match
}

export default class Colorpicker extends React.Component<IColorPickerProps, IColorPickerState> {
    constructor(props: IColorPickerProps) {
        super(props)

        this.onSliderClick = this.onSliderClick.bind(this)
        this.onPaletteClick = this.onPaletteClick.bind(this)

        this.state = { loading: true, done: false }
    }

    onSliderClick(event: React.MouseEvent<HTMLDivElement, MouseEvent>) {
        const { left, width } = (event.target as any).getBoundingClientRect()
        const hue = ((event.pageX - left) / width) * 360

        this.state.color!.set({hue: hue})
        this.deviceUpdate()
    }

    onPaletteClick(event: React.MouseEvent<HTMLDivElement, MouseEvent>) {
        const { left, right, top, bottom, width, height } = (event.target as any).getBoundingClientRect()

        this.state.color!.set({
            val: 1 - Math.min((event.pageY - top) / height, 1),// / event.nativeEvent.offsetWidth
            sat: (event.pageX - left) / width
        })
        this.deviceUpdate()
    }

    deviceUpdate() {
        const { device, color } = this.state

        device!.setColor(color!)
    }

    async componentDidMount() {
        const { deviceId }: any = this.props.match.params
        const device = devices[parseInt(deviceId)]

        console.log(device, deviceId, this.props)

        await device!.fetch()

        this.setState({loading: false, color: device!.data.color, device: device})
    }

    render() {
        if (this.state.loading) return <h1>Loading</h1>

        if (this.state.done)
            return <Redirect to="/devices"/>

        const { color } = this.state
        const { hue, cssString } = color!

        return (
            <div className="colorpicker">
                <div className="main">
                    <div className="palette-preview-container">
                        <div className="palette" onClick={this.onPaletteClick} style={{backgroundColor: `hsl(${hue}, 100%, 50%)`}}>
                            <div id="sat"></div>
                            <div id="value"></div>
                        </div>
                        <div className="preview" style={{background: cssString}}/>
                    </div>
                    <div className="hue-slider" onClick={this.onSliderClick}/>
                </div>
                <ul className="control-buttons">
                    <li onClick={() => this.setState({done: true})}><Done/></li>
                </ul>
            </div>
        )
    }
}