
import { app, BrowserWindow } from 'electron'

function create() {
    const window = new BrowserWindow({
        width: 900,
        height: 600,
        titleBarStyle: 'hiddenInset'
    })
}

app.on('ready', create)