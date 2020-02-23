
import MQTT, { IClientOptions } from 'mqtt'

export class Connector {
    constructor() {
        console.log('IUHDWAUHIDAWHUID WA')
    }
}

export class MQTTConnector extends Connector {
    public instance: MQTT.Client

    constructor(public opts: IClientOptions) {
        super()

        this.instance = MQTT.connect(opts)
    }
}

export class DeviceFactory {
    constructor(public deviceClass: any, public connector: Connector) {

    }

    create(...args: any[]) {
        return this.deviceClass.create(this.connector, ...args)
    }
}

export enum PacketCode {
    OFF = 0x01,
    ON = 0x02,
    FADE = 0x04
}

export class Device {
    public connector?: Connector

    constructor(public id: number, public name: string, public image: any) {

    }

    static create(connector: Connector, ...args: [number, string, any]) {
        const i = new Device(...args);
        i.connector = connector

        return i
    }

    power(on: boolean, fade: boolean = true) {
        const instr = `${((on ? PacketCode.ON : PacketCode.OFF) | Number(fade && PacketCode.FADE))} hsl-190-1-0.5`
        console.log(instr);

        (this.connector as MQTTConnector).instance.publish(`strips/${this.id}`, instr)
    }
}

export const connector = new MQTTConnector({host: '192.168.1.220', port: 1883})
export const fac = new DeviceFactory(Device, connector)

export const d1 = fac.create(1, 'Desk Strip (Back Left)', null)
