
export type ColorType = 'hsv' | 'hsl' | 'rgb' | 'hex'

export interface IColor {
    type: ColorType,
    value: number[] | string
}

export abstract class Color implements IColor {
    abstract type: ColorType
    abstract get cssString(): string

    abstract get value(): number[] | string

    set(values: object): void {
        for (const [k, v] of Object.entries(values)) {
            (this as any)[k] = v
        }
    }
}

export class HSL extends Color {
    public type: ColorType = 'hsl'
    public hue!: number
    public sat!: number
    public light!: number

    constructor(value: [number, number, number]) {
        super()

        const [ hue, sat, light ] = value

        this.set({hue, sat, light})
    }

    get cssString(): string {
        const { hue, sat, light, type } = this

        return `${type}(${hue}, ${sat * 100}%, ${light * 100}%)`
    }

    get value(): number[] {
        const { hue, sat, light } = this

        return [ hue, sat, light ]
    }
}

export class HSV extends Color {
    public type: ColorType = 'hsv'
    public hue!: number
    public sat!: number
    public val!: number
    
    constructor(value: [number, number, number]) {
        super()

        const [ hue, sat, val ] = value

        this.set({hue, sat, val})
    }

    get cssString(): string {
        const { hue, sat, val } = this

        const l = val * (1 - sat / 2)
        const s = (l === 0 || l === 1) ? 0 : (val - l) / Math.min(l, 1 - l)

        return `hsl(${hue}, ${s * 100}%, ${l* 100}%)`
    }

    get value(): number[] {
        const { hue, sat, val } = this

        return [hue, sat, val]
    }
}

export const colorMap: {[K in ColorType]?: any} = {
    hsv: HSV,
    hsl: HSL
}

export default function handler({type, value}: IColor) {
    if (type in colorMap) {
        return new colorMap[type](value)
    }

    throw new Error(`Unrecognized color type '${type}'`)
}