
import enum
import falcon
from devices.rgbstrip import RGBStrip

class CorsMiddleware:
    def process_request(self, req, resp):
        resp.set_header('Access-Control-Allow-Origin', req.get_header('origin'))
        resp.set_header('Access-Control-Allow-Methods', '*')
        resp.set_header('Access-Control-Allow-Headers', '*')

app = falcon.App(middleware=[CorsMiddleware()])

app.add_route('/devices/{device_id:int}', RGBStrip(host='localhost', port=1883))

print('Init completed')