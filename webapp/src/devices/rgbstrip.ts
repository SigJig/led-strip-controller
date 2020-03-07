
import React from 'react'
import axios from 'axios'
import Strings from '../const/strings'

import { IDevice, IButton, StatusType } from './base'
import { AiOutlineBulb as Bulb } from 'react-icons/ai'
import { GoGear as Gear } from 'react-icons/go'
import { Circle } from '../components/shapes'
import Colorpicker, { HSV } from '../screens/colorpicker'

const URI = 'http://192.168.1.220:8000/devices/1'

export default class RGBStrip implements IDevice {
    public icon: any
    public buttons: IButton[]
    public statusClass: StatusType= 'inactive'
    public data: { hsv: HSV, active: boolean, fade: boolean } = {
        hsv: {hue: 0, sat: 1, val: 1},
        active: true,
        fade: true
    }

    constructor(public title: string, public color: string, public desc?: string) {

        this.icon = Bulb
        this.desc = desc || Strings.rgbstrip
        this.buttons = [
            {
                title: Strings.changeColor,
                action: () => React.createElement(Colorpicker, {device: this, hsv: this.data.hsv}),
                renderIcon: () => React.createElement(Circle, {color: this.color})
            },
            {
                title: Strings.manage,
                action: () => {},
                renderIcon: () => React.createElement(Gear, {})
            }
        ]
    }

    setColor(hsv: HSV) {
        this.data.hsv = hsv

        
        return this.sendUpdate()
    }
    
    sendUpdate() {
        const { active, fade, hsv } = this.data
        
        return axios.patch(URI, {
            active,
            fade,
            color: hsv
        })
    }

    setStatusClass() {
        this.statusClass = this.data.active ? 'success' : 'inactive'
    }

    async fetch() {
        const { active, fade, color } = (await axios.get(URI)).data

        this.data = {
            active,
            fade,
            hsv: color
        }

        this.setStatusClass()
    }

    async activate({target}: any) {
        const { checked } = target

        this.statusClass = 'inactive'

        try {
            this.data.active = checked

            await this.sendUpdate()

            this.setStatusClass()
        } catch (e) {
            console.log(e)
        }
    }
}