#include <ArduinoBLE.h>

#define MOTOR_1F 10
#define MOTOR_1B 9
#define MOTOR_2F 8
#define MOTOR_2B 7
#define SPEED 180

// Botname can't have uppercase letters!
#define BOT_NAME "hebobot #1"

BLEService ledService("19B10000-E8F2-537E-4F6C-D104768A1214");
BLECharCharacteristic switchCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);

void setup() {
  pinMode(MOTOR_1F, OUTPUT);
  pinMode(MOTOR_1B, OUTPUT);
  pinMode(MOTOR_2F, OUTPUT);
  pinMode(MOTOR_2B, OUTPUT);

  if (!BLE.begin()) {
    while (1);
  }

  BLE.setLocalName(BOT_NAME);
  BLE.setAdvertisedService(ledService);

  ledService.addCharacteristic(switchCharacteristic);

  BLE.addService(ledService);

  BLE.setEventHandler(BLEConnected, blePeripheralConnectHandler);
  BLE.setEventHandler(BLEDisconnected, blePeripheralDisconnectHandler);

  switchCharacteristic.setEventHandler(BLEWritten, switchCharacteristicWritten);
  switchCharacteristic.setValue(0);

  BLE.advertise();
}

void loop() {
  BLE.poll();
}

void switchCharacteristicWritten(BLEDevice central, BLECharacteristic characteristic) {
  char value = switchCharacteristic.value();
  switch (value) {
    case 'w' :
      analogWrite(MOTOR_1B, 0);
      analogWrite(MOTOR_2B, 0);
      analogWrite(MOTOR_1F, SPEED);
      analogWrite(MOTOR_2F, SPEED);
      break;
    case 's' :
      analogWrite(MOTOR_1B, SPEED);
      analogWrite(MOTOR_2B, SPEED);
      analogWrite(MOTOR_1F, 0);
      analogWrite(MOTOR_2F, 0);
      break;
    case 'a' :
      analogWrite(MOTOR_1B, SPEED);
      analogWrite(MOTOR_2B, 0);
      analogWrite(MOTOR_1F, 0);
      analogWrite(MOTOR_2F, SPEED);
      break;
    case 'd' :
      analogWrite(MOTOR_1B, 0);
      analogWrite(MOTOR_2B, SPEED);
      analogWrite(MOTOR_1F, SPEED);
      analogWrite(MOTOR_2F, 0);
      break;
    default:
      analogWrite(MOTOR_1F, 0);
      analogWrite(MOTOR_2F, 0);
      analogWrite(MOTOR_1B, 0);
      analogWrite(MOTOR_2B, 0);
      break;
  ;}
}
