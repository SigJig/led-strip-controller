
import enum
import falcon
from devices.rgbstrip import RGBStrip

DEVICES = [
    RGBStrip(name='Testing strip', desc='RGB Ledstrip', host='localhost', port=1883)
]

class DeviceResource:
    def _get_device(self, id_):
        try:
            return DEVICES[id_]
        except IndexError:
            raise falcon.HTTPNotFound()

    def on_get(self, req, resp, device_id):
        device = self._get_device(device_id)
        
        f = getattr(device, 'get', device.to_dict)
        
        resp.media = f()

    def on_patch(self, req, resp, device_id):
        device = self._get_device(device_id)
        device.update(req.media)

        resp.media = device.to_dict()


class CorsMiddleware:
    def process_request(self, req, resp):
        resp.set_header('Access-Control-Allow-Origin', req.get_header('origin'))
        resp.set_header('Access-Control-Allow-Methods', '*')
        resp.set_header('Access-Control-Allow-Headers', '*')

app = falcon.App(middleware=[CorsMiddleware()])

app.add_route('/devices/{device_id:int}', DeviceResource())

print('Init completed')