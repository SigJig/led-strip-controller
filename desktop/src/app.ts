
import './mqtt'
import { app, BrowserWindow } from 'electron'
import { staticFile } from './helpers'
import Dotenv from 'dotenv'

Dotenv.config()

app.on('ready', function loadInitial() {

    const window = new BrowserWindow({
        width: 900,
        height: 600,
        show: false,
        frame: false,
        webPreferences: {
            nodeIntegration: true
        }
    })

    window.maximize()
    window.loadFile(staticFile('html', 'index.html'))
    window.once('ready-to-show', window.show)

})