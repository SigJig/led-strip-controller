
from .base import Connector
from .mixins import HTTPConnector

class LANConnector(Connector, HTTPConnector):
    pass