import asyncio
import sys
from asyncio import AbstractEventLoop
from sys import argv

import controller
from bleak import BleakScanner, BleakClient, BleakGATTCharacteristic, BLEDevice
from controller import KeyboardEvent


class Keyboard:
    def __init__(self, loop: AbstractEventLoop, device_number: int, polling_rate: int = 100):
        self._client = None
        self._loop = loop
        self._service_uuid = "19B10000-E8F2-537E-4F6C-D104768A1214"
        self._characteristic_uuid = "19B10001-E8F2-537E-4F6C-D104768A1214"
        self._poling_rate = polling_rate
        self._keys = []
        self._current_key = ' '
        self.device_number = device_number

        controller.hook_key('w', self._key_hook)
        controller.hook_key('a', self._key_hook)
        controller.hook_key('s', self._key_hook)
        controller.hook_key('d', self._key_hook)
        controller.hook_key('esc', lambda _: sys.exit(0))

    def _key_hook(self, event: KeyboardEvent):
        if event.event_type == controller.KEY_DOWN and event.name not in self._keys:
            self._keys.append(event.name)
            self._current_key = event.name
        if event.event_type == controller.KEY_UP and event.name in self._keys:
            self._keys.remove(event.name)

            if len(self._keys) == 0:
                self._current_key = ' '
            elif event.name == self._current_key:
                self._current_key = self._keys[-1]

    def _device_filter(self, _device: BLEDevice, advertisement):
        if _device.name is None:
            return False
        name = f'{sys.argv[2] if len(sys.argv) == 3 else "hebobot"} #{str(self.device_number)}'
        print(f'"{name}"')
        return _device.name == name

    def close(self, _event: KeyboardEvent = None):
        self._loop.call_soon(self._client.disconnect)

    @staticmethod
    def disconnect(client: BleakClient):
        print(f"Disconnected from {client.address}")

    async def handle_keys(self, client: BleakClient, characteristic: BleakGATTCharacteristic):
        await asyncio.sleep(1 / self._poling_rate)
        await client.write_gatt_char(characteristic, bytearray(self._current_key.encode('utf-8')), response=True)

    async def start(self):
        device = await BleakScanner.find_device_by_filter(self._device_filter)
        async with BleakClient(device, disconnected_callback=self.disconnect) as self._client:
            service = self._client.services.get_service(self._service_uuid)
            characteristic = service.get_characteristic(self._characteristic_uuid)
            print(f"Connected to client {self._client.address}")
            while True:
                await self.handle_keys(self._client, characteristic)


def main():
    if len(argv) <= 2:
        print("Please specify service and characteristic uuid as cli parameters")
        return
    loop = asyncio.new_event_loop()
    _keyboard = Keyboard(loop, int(argv[1]))
    try:
        loop.run_until_complete(_keyboard.start())
    except KeyboardInterrupt:
        print("Programm was closed")
    finally:
        loop.close()


if __name__ == '__main__':
    main()
