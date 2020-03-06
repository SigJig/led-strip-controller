
import React from 'react'
import axios from 'axios'
import Strings from '../const/strings'

import { IDevice, IButton } from './base'
import { AiOutlineBulb as Bulb } from 'react-icons/ai'
import { GoGear as Gear } from 'react-icons/go'
import { Circle } from '../components/shapes'

export default class RGBStrip implements IDevice {
    public icon: any
    public buttons: IButton[]

    constructor(public title: string, public color: string, public desc?: string) {

        this.icon = Bulb
        this.desc = desc || Strings.rgbstrip
        this.buttons = [
            {
                title: Strings.changeColor,
                action: () => {},
                renderIcon: () => React.createElement(Circle, {color: this.color})
            },
            {
                title: Strings.manage,
                action: () => {},
                renderIcon: () => React.createElement(Gear, {})
            }
        ]
    }

    async activate({target}: React.ChangeEvent<HTMLInputElement>) {
        try {
            await axios.patch('http://localhost:8000/devices/1', {
                active: target.checked,
                fade: true,
                color: 'hsv-300-1-1'
            })
        } catch (e) {
            throw e
        }
    }
}