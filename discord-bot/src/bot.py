
import os, discord, asyncio, colorsys, aiohttp

PREFIX = '!'
COLORS = {}

DEFAULT_OPTS = {
    'device': 0
}

def device_url(id):
    return os.environ['API_URL'] + 'devices/' + str(id)

def get_color(color):
    try:
        return hex_to_rgb(color)
    except ValueError:
        if color in COLORS: return get_color(COLORS[color])

        raise

def hex_to_rgb(hex_):
    if hex_.startswith('#'):
        hex_ = hex_.lstrip('#')

    return [int(x) for x in bytearray.fromhex(hex_)]

class _Client(discord.Client):
    async def on_ready(self):
        print(f'[{repr(self.user)}] Logged in')

    async def on_message(self, message):
        if message.author.bot: return

        args = message.content.split()
        command = args.pop(0)

        if not command.startswith(PREFIX): return
        
        command = command.lstrip(PREFIX)
        options, args = self._parse_args(args)

        if command == 'set':
            color_raw = args.pop(0)
            
            if save := options.get('save', None):
                COLORS[save] = color_raw

            try:
                color = get_color(color_raw)
            except ValueError:
                embed = discord.Embed(description='E du mongo æll')#, color='#ff0000')
            else:
                embed = discord.Embed(description=f'Color changed to {color}')#, color=color_raw)

                async with aiohttp.ClientSession() as session:
                    hsv = colorsys.rgb_to_hsv(*color)
                    hsv = [hsv[0] * 360, hsv[1], hsv[2] / 255]

                    await session.patch(device_url(options.get('device')), json={'color': {'type': 'hsv', 'value': hsv}})
                
            await message.channel.send(embed=embed)
        elif command == 'list':
            await message.channel.send(embed=discord.Embed(description=','.join(COLORS.keys())))


    def _parse_args(self, args):
        options, _args = DEFAULT_OPTS, []

        for i in args:
            if i.startswith('-'):
                i = i.lstrip('-')

                if '=' in i:
                    k, v = i.split('=')
                else:
                    k, v = i, None

                options[k] = v
            else:
                _args.append(i)

        return options, _args

if __name__ == '__main__':
    import os
    from dotenv import load_dotenv
    
    load_dotenv()

    client = _Client()
    client.run(os.environ['DISCORD_TOKEN'])
