
import falcon

class DeviceHandler:
    def on_get(self, req, resp, device_id):
        device_id = int(device_id)

        resp.status = falcon.HTTP_200
        resp.media = {
            'color': '#fff',
            'device': device_id
        }


api = falcon.API()

device_handler = DeviceHandler()
api.add_route('/devices/{device_id}', device_handler)