
import { remote } from 'electron'

const { Notification } = remote

window.onload = function onload() {
    document.getElementById('demo')!.onclick = () => {
        console.log('Click!')
        new Notification({body: 'Its clicked cunt', title: 'Notification'})
    }
}
