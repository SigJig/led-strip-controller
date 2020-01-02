
class Connector:
    pass

class LANConnector(Connector):
    def __init__(self, ip):
        self.ip = ip
