
import json
from utils.color import RGB
from .base import Device

class LEDStrip(Device):
    color = RGB(255, 255, 255)

    @property
    def payload(self):
        return json.dumps({
            'color': self.color.encode()
        })

    def save(self):
        self.conn.send_instruction(self.payload)