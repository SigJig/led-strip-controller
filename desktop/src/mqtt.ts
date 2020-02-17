
import MQTT from 'mqtt'

const { MQTT_PORT, MQTT_HOST } = process.env

const client = MQTT.connect({
    port: MQTT_PORT,
    host: MQTT_HOST
})

client.on('connect', () => {
    client.subscribe('fuck')
})

client.on('error', err => console.log(err))

client.on('message', (topic, message) => {
    console.log(`[${topic}] ${message.toString()}`)
})

export default client