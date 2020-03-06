
import enum
import falcon
from connectors.mqtt import MQTTConnector

class RGBStrip:
    opts = {
        'active': bool,
        'fade': bool,
        'color': str
    }

    state = {
        'active': False,
        'fade': True,
        'color': 'hsv-0-0-0'
    }

    def __init__(self, **conn_args):
        print('rgbstrip initalized')
        self.connector = MQTTConnector.instance(**conn_args)

    def on_patch(self, req, resp, *args, **kwargs):
        print('hello?')
        for k, v in req.media.items():
            if k.lower() not in self.opts:
                raise falcon.HTTPBadRequest(f'Unrecognized field {k}')

            type_ = self.opts[k]
            self.state[k] = type_(v)

        resp.status = falcon.HTTP_200
        resp.media = {}

        self._write()

    def _write(self):
        flag = self.ControlFlags.NA

        flag |= self.ControlFlags.ON if self.state['active'] else self.ControlFlags.OFF

        if self.state['fade']:
            flag |= self.ControlFlags.FADE

        self.connector.publish('strips/1', f'{flag} {self.state["color"]}')

    class ControlFlags(enum.IntEnum):
        NA = 0x00
        OFF = 0x01
        ON = 0x02
        FADE = 0x04
