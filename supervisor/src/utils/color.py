
from const import (
    COLOR_RGB,
    COLOR_RGBW
)

class RGB:
    def __init__(self, r, g, b):
        self.r = r
        self.g = g
        self.b = b

    def to_list(self):
        return [self.r, self.g, self.b]

    def encode(self):
        return bytearray([COLOR_RGB] + self.to_list())

class RGBW:
    def __init__(self, r, g, b, w):
        self.r = r
        self.g = g
        self.b = b
        self.w = w

    def to_list(self):
        return [self.r, self.g, self.b]

    def encode(self):
        return bytearray([COLOR_RGBW] + self.to_list())