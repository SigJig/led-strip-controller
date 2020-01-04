
from abc import ABC, abstractmethod
from connectors.lan import LANConnector

class Device(ABC):
    connector = LANConnector
    id_ = None

    def __init__(self, conn_args={}, *args, **kwargs):
        self.conn = self.connector(**conn_args)

    @abstractmethod
    def save(self, *args, **kwargs): pass
