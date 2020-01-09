
window.onload = function onload() {

    function setClock() {
        const date = new Date()
        const fmt = `${date.getHours()}:${date.getMinutes()}`

        document.getElementById('clock-text')!.innerHTML = fmt
    }

    setInterval(setClock, 100)

}