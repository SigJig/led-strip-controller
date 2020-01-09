
import { app, BrowserWindow } from 'electron'
import { staticFile } from './helpers'

app.on('ready', function loadInitial() {

    const window = new BrowserWindow({
        width: 900,
        height: 600,
        show: false,
        frame: false
    })

    window.maximize()
    window.loadFile(staticFile('html', 'controls.html'))
    window.once('ready-to-show', window.show)

})