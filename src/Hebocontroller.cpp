#if defined(ARDUINO_NODEMCU_32S)
#include <Hebocontroller.h>

/* Hebobot */
Hebobot::Hebobot(const String name, const unsigned long baudrate) : _baudrate(baudrate), name(name) { }

void Hebobot::init() {
    pinMode(MOTOR_1B, OUTPUT);
    pinMode(MOTOR_2B, OUTPUT);
    pinMode(MOTOR_1F, OUTPUT);
    pinMode(MOTOR_2F, OUTPUT);
}

void Hebobot::drive(const String value) {
    switch (value[0]) {
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
    }
}

/* Hebocontroller */
Hebocontroller::Hebocontroller(Hebobot hebobot) : _hebobot(hebobot) { }

void Hebocontroller::init() {
    #ifdef PLATFORMIO
        BLEDevice::init(std::string(_hebobot.name.c_str()));
    #else
        BLEDevice::init(_hebobot.name);
    #endif
    _bleServer         = BLEDevice::createServer();
    _bleService        = _bleServer->createService(SERVICE_UUID);
    _bleCharacteristic = _bleService->createCharacteristic(CHARACTERISTIC_UUID, BLECharacteristic::PROPERTY_READ);
    _bleCharacteristic->setValue("0");
    _bleService->start();
    BLEAdvertising *bleAdvertising = BLEDevice::getAdvertising();
    bleAdvertising->addServiceUUID(SERVICE_UUID);
    bleAdvertising->setScanResponse(true);
    bleAdvertising->setMinPreferred(0x06);
    bleAdvertising->setMinPreferred(0x12);
    BLEDevice::startAdvertising();
}

void Hebocontroller::poll() {
    if (_bleServer->getConnectedCount() > 0) {
        #ifdef PLATFORMIO
            String value = String(_bleCharacteristic->getValue().c_str());
        #else
            String value = _bleCharacteristic->getValue();
        #endif
        _hebobot.drive(value);
    }
}
#endif /* defined(ARDUINO_NODEMCU_32S) */
