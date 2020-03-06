
import React from 'react'

export interface IButton {
    renderIcon?: CallableFunction,
    title: string,
    action: any
}

export interface IDevice {
    buttons: IButton[],
    title: string,
    icon: any,
    desc?: string,
    activate: ((event: React.ChangeEvent<HTMLInputElement>) => void)
}