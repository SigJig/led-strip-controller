
# from devices import Devices

class Supervisor:
    missing_devices = []

    def __init__(self, opts=[]):
        self.opts = opts

    def register_device(self, device):
        pass

    def run(self):
        pass

if __name__ == '__main__':
    manifest = {
        'devices': [
            {
                'type': 'ledstrip',
                'name': 'LED Strip Controller',
                'connection': {
                    'host': '192.168.1.132',
                    'port': '80'
                }
            }
        ]
    }

    Supervisor().run()
