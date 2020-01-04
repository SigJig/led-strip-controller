
from abc import abstractmethod, ABC

class Connector(ABC):
    def send_instruction(self, *args, **kwargs): pass
