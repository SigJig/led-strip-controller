
import enum
import falcon
from connectors.mqtt import MQTTConnector
from color import color_handler, HSV

class RGBStrip:
    opts = {
        'active': bool,
        'fade': bool,
        'color': color_handler
    }

    state = {
        'active': False,
        'fade': True,
        'color': HSV(hue=0, sat=1, val=1)
    }

    def __init__(self, **conn_args):
        self.connector = MQTTConnector.instance(**conn_args)

    def update(self, body):
        for k, v in body.items():
            if k.lower() not in self.opts:
                raise falcon.HTTPBadRequest(f'Unrecognized field {k}')

            type_ = self.opts[k]
            self.state[k] = type_(v)

        self._write()

    def to_dict(self):
        return {**self.state, 'color': self.state['color'].to_dict()}

    def _write(self):
        flag = self.ControlFlags.NA

        flag |= self.ControlFlags.ON if self.state['active'] else self.ControlFlags.OFF

        if self.state['fade']:
            flag |= self.ControlFlags.FADE

        self.connector.publish('strips/1', f'{flag} {str(self.state["color"])}')

    class ControlFlags(enum.IntEnum):
        NA = 0x00
        OFF = 0x01
        ON = 0x02
        FADE = 0x04
