
import abc

class Connector(abc.ABC):
    @abc.abstractclassmethod
    def instance(cls, *args, **kwargs): pass