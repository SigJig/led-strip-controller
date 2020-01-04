
from .base import Connector
from .mixins import HTTPConnector

class LANConnector(Connector, HTTPConnector):
    def __init__(self, ip, *args, **kwargs):
        self.ip = ip

        super().__init__(*args, **kwargs)