
import abc

class Color(abc.ABC):
    @abc.abstractmethod
    def __str__(self): pass

    @abc.abstractmethod
    def to_dict(self): pass

class HSV(Color):
    def __init__(self, dict_=None, **kwargs):
        if dict_ is None:
            dict_ = kwargs

        if not isinstance(dict_, dict):
            if isinstance(dict_, list):
                self.hue, self.sat, self.val = dict_
            else:
                raise TypeError(repr(self) + f' Expected dict, list, got {type(dict_)}')
        else:
            self.hue, self.sat, self.val = (dict_.get(x) for x in ('hue', 'sat', 'val'))

    def __str__(self):
        return f'hsv-{self.hue}-{self.sat}-{self.val}'

    def to_dict(self):
        return {
            'type': 'hsv',
            'value': [self.hue, self.sat, self.val]
        }

COLOR_MAP = {
    'hsv': HSV
}

def color_handler(dict_=None, **kwargs):
    if dict_ is None:
        dict_ = kwargs

    try:
        type_, value = dict_['type'], dict_['value']
    except KeyError as e:
        raise e
    else:
        type_ = type_.lower()

        if type_ in COLOR_MAP:
            return COLOR_MAP[type_](value)

        raise Exception(f'Invalid color type {type_}')
