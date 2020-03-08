
import React from 'react'
import axios from 'axios'
import Strings from '../const/strings'

import { IconType } from 'react-icons'
import { IDevice, IButton, StatusType } from './base'
import { AiOutlineBulb as Bulb } from 'react-icons/ai'
import { GoGear as Gear } from 'react-icons/go'
import { Circle } from '../components/shapes'
import colorHandler, { HSV } from '../utils/color'
import Colorpicker from '../screens/colorpicker'

const URI = 'http://192.168.1.220:8000/devices'

export default class RGBStrip implements IDevice {
    public icon: IconType = Bulb
    public buttons: IButton[]
    public statusClass: StatusType= 'inactive'
    public title!: string
    public desc!: string
    public data!: { color: HSV, active: boolean, fade: boolean }

    constructor(public id: number) {
        this.buttons = [
            {
                title: Strings.changeColor,
                action: () => React.createElement(Colorpicker, {device: this}),
                renderIcon: () => React.createElement(Circle, {color: this.data.color.cssString})
            },
            {
                title: Strings.manage,
                action: () => {},
                renderIcon: () => React.createElement(Gear, {})
            }
        ]
    }

    get endpoint(): string {
        return `${URI}/${this.id}`
    }

    setColor(hsv: HSV) {
        this.data.color = hsv

        return this.sendUpdate()
    }
    
    sendUpdate() {
        const { active, fade, color } = this.data
        const { type, value } = color
        
        return axios.patch(this.endpoint, {
            active,
            fade,
            color: {
                type, value
            }
        })
    }

    setStatusClass() {
        this.statusClass = this.data.active ? 'success' : 'inactive'
    }

    async fetch() {
        const { state, name, desc } = (await axios.get(this.endpoint)).data
        const { active, fade, color } = state

        this.title = name
        this.desc = desc
        this.data = {
            active,
            fade,
            color: colorHandler(color)
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