
import enum
import falcon
from connectors.mqtt import MQTTConnector

class HSV:
    def __init__(self, dict_=None, **kwargs):
        if dict_ is None:
            dict_ = kwargs

        print(dict_)

        self.hue = dict_.get('hue')
        self.sat = dict_.get('sat')
        self.val = dict_.get('val')

    def __str__(self):
        return f'hsv-{self.hue}-{self.sat}-{self.val}'

    def to_dict(self):
        return vars(self)

class RGBStrip:
    opts = {
        'active': bool,
        'fade': bool,
        'color': HSV
    }

    state = {
        'active': False,
        'fade': True,
        'color': HSV(hue=0, sat=1, val=1)
    }

    def __init__(self, **conn_args):
        print('rgbstrip initalized')
        self.connector = MQTTConnector.instance(**conn_args)

    def on_get(self, req, resp, *args, **kwargs):
        resp.media = self.to_dict()

    def on_patch(self, req, resp, *args, **kwargs):
        for k, v in req.media.items():
            if k.lower() not in self.opts:
                raise falcon.HTTPBadRequest(f'Unrecognized field {k}')

            type_ = self.opts[k]
            self.state[k] = type_(v)

        resp.status = falcon.HTTP_200
        resp.media = self.to_dict()

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
