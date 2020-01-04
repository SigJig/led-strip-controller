
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
    Supervisor().run()
