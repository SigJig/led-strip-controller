
from abc import abstractmethod, ABC

class Connector(ABC):
    @abstractmethod
    def send_instruction(self, *args, **kwargs): pass
