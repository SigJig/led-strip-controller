
import React from 'react'

export const statusClasses = {
    inactive: 'border-inactive',
    success: 'border-success'
}

export type StatusType = keyof typeof statusClasses

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
    statusClass: StatusType,
    activate: ((event: React.ChangeEvent<HTMLInputElement>) => void)
}