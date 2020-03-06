
from .base import Connector
import paho.mqtt.client as mqtt

MQTT_DEFAULT_PORT = 1883

class MQTTConnector(Connector):
    class _client(mqtt.Client):
        def on_connect(self, client, userdata, flags, rc):
            print('MQTT Client connected.')

            client.subscribe('output/')

        def on_message(self, client, userdata, msg):
            print(f'[{msg.topic}]: {msg.payload}')

    instances = {}

    @classmethod
    def instance(cls, **opts):
        host = opts.get('host', None)

        if host is None:
            raise Exception('host is none')

        pair = (host, opts.get('port', MQTT_DEFAULT_PORT))

        if pair in cls.instances:
            return cls.instances[pair]

        instance = MQTTConnector(opts)
        cls.instances[pair] = instance

        return instance

    def __init__(self, connection_opts):
        self.client = type(self)._client()
        self.client.connect(**connection_opts)

        self.client.loop_start()

    def __getattr__(self, attr):
        return getattr(self.client, attr)