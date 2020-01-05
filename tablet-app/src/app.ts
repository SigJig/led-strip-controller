
import path from 'path'
import { app, BrowserWindow } from 'electron'

function create() {
    const window = new BrowserWindow({
        width: 900,
        height: 600,
        titleBarStyle: 'hidden',
        backgroundColor: '#111',
        show: false,
    })

    window.maximize()
    window.removeMenu()
    window.loadFile(path.join(process.cwd(), 'static', 'html', 'control.html'))

    window.once('ready-to-show', window.show)
}

app.on('ready', create)