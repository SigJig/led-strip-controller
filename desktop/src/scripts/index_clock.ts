
window.onload = function onload() {

    function setClock() {
        function formatNumber(num: number): string {
            return num > 9 ? num.toString() : `0${num.toString()}`
        }

        const date = new Date()
        const [ hours, minutes ] = [date.getHours(), date.getMinutes()]

        document.getElementById('clock-text')!.innerHTML =formatNumber(hours) + ':' + formatNumber(minutes)
    }

    setInterval(setClock, 100)

}