#include <Giantocontroller.h>

#define IN1 4  // Arduino pin 4 is connected to MDDS30 pin IN1.
#define AN1 5  // Arduino pin 5 is connected to MDDS30 pin AN1.
#define AN2 6  // Arduino pin 6 is connected to MDDS30 pin AN2.
#define IN2 7  // Arduino pin 7 is connected to MDDS30 pin IN2.

// Botname can't have uppercase letters!
#define BOT_NAME "hebobot #1"

signed int left, right;

Giantocon giantocon(IN1, IN2, AN1, AN2);
BLEService bleService("19B10000-E8F2-537E-4F6C-D104768A1214");
BLECharCharacteristic bleCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);

void setup() {
  if (!BLE.begin()) {
    while (1);
  }

  BLE.setLocalName(BOT_NAME);
  BLE.setAdvertisedService(bleService);

  bleService.addCharacteristic(bleCharacteristic);

  BLE.addService(bleService);

  bleCharacteristic.setEventHandler(BLEWritten, bleReadHandler);
  bleCharacteristic.setValue(0);

  BLE.advertise();
}

void loop() {
  BLE.poll();
}

void bleReadHandler(BLEDevice central, BLECharacteristic characteristic) {
  char value = bleCharacteristic.value();
  switch (value) {
    case 'w':
      left = 100;
      right = -100;
      break;
    case 's':
      left = -100;
      right = 100;
      break;
    case 'a':
      left = -100;
      right = -100;
      break;
    case 'd':
      left = 100;
      right = 100;
      break;
    default:
      left = 0;
      right = 0;
      break;
  }
  giantocon.control(left, right);
}
