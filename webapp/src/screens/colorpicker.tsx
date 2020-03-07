
import React from 'react'
import './colorpicker.scss'

import { MdDone as Done, MdExitToApp as Cancel } from 'react-icons/md'
import RGBStrip from '../devices/rgbstrip'

export interface HSV {
    hue: number,
    sat: number,
    val: number
}

export interface HSL {
    hue: number,
    sat: number,
    light: number
}

export interface IColorPickerState {
    hsv: HSV
}

export interface IColorPickerProps {
    hsv: HSV,
    device: RGBStrip
}

export default class Colorpicker extends React.Component<IColorPickerProps, IColorPickerState> {
    constructor(props: IColorPickerProps) {
        super(props)

        this.state = {hsv: props.hsv}
        this.onSliderClick = this.onSliderClick.bind(this)
        this.hsvToHsl = this.hsvToHsl.bind(this)
        this.onPaletteClick = this.onPaletteClick.bind(this)
    }

    hsvToHsl(hsv: HSV): HSL {
        let l = hsv.val * (1 - hsv.sat / 2)
        l = (l === 0 || l === 1) ? 0 : (hsv.val - l) * Math.min(l, 1 - l)

        return {hue: hsv.hue, sat: hsv.sat, light: l}
    }

    onSliderClick(event: React.MouseEvent<HTMLDivElement, MouseEvent>) {
        const { left, right } = (event.target as any).getBoundingClientRect()
        const hue = ((event.pageX - left) / (right - left)) * 360

        this.setState({hsv: {
            ...this.state.hsv,
            hue: hue
        }})

        this.deviceUpdate()
    }

    onPaletteClick(event: React.MouseEvent<HTMLDivElement, MouseEvent>) {
        const { left, right, top, bottom } = (event.target as any).getBoundingClientRect()

        this.setState({hsv: {
            ...this.state.hsv,
            val: 1 - Math.min((event.pageY - top) / (bottom - top), 1),// / event.nativeEvent.offsetWidth
            sat: (event.pageX - left) / (right - left)
        }})

        this.deviceUpdate()
    }

    deviceUpdate() {
        const { device } = this.props

        device.setColor(this.state.hsv)
    }

    render() {
        const { hue, sat, light } = this.hsvToHsl(this.state.hsv)

        return (
            <div className="colorpicker">
                <div className="main">
                    <div className="palette-preview-container">
                        <div className="palette" onClick={this.onPaletteClick} style={{backgroundColor: `hsl(${this.state.hsv.hue}, 100%, 50%)`}}>
                            <div id="sat"></div>
                            <div id="value"></div>
                        </div>
                        <div className="preview" style={{backgroundColor: `hsl(${hue}, ${sat * 100}%, ${light * 100}%)`}}/>
                    </div>
                    <div className="hue-slider" onClick={this.onSliderClick}/>
                </div>
                <ul className="control-buttons">
                    <li><Cancel/></li>
                    <li><Done/></li>
                </ul>
            </div>
        )
    }
}