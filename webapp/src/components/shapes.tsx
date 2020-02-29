
import React from 'react'

export interface ICircleProps {
    color: any
}

export interface ICircleState {
    color: any
}

export class Circle extends React.Component<ICircleProps, ICircleState> {
    constructor(props: ICircleProps) {
        super(props)

        this.state = {
            color: props.color
        }
    }

    render() {
        const { color } = this.state

        return (
            <div style={
                {
                    backgroundColor: color,
                    borderRadius: '50%'
                }
            }/>
        )
    }
}