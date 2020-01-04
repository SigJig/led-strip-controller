
from aiohttp import web
from ..routes import routes

@routes.view('/devices/active', name='active_devices')
class ActiveDevicesView(web.View):
    async def post(self):
        ip = self.request.transport.remote

    async def get(self):
        pass

@routes.view('/devices/active/{identifier}', name='active_device')
class ActiveDeviceView(web.View):
    async def delete(self):
        pass

    async def get(self):
        pass
