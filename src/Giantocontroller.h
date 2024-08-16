#ifndef GIANTOCONTROLLER_H
#define GIANTOCONTROLLER_H

#if !defined(ARDUINO_ARDUINO_NANO33BLE)
#error "This Library only works with 'Arduino Nano 33 BLE' Boards"
#else

#include <Arduino.h>
#include <ArduinoBLE.h>

class Giantocon {
public:
    Giantocon(int in1Pin, int in2Pin, int an1Pin, int an2Pin);
    virtual void control(signed int left, signed int right);
private:
    uint8_t _an1Pin, _an2Pin, _in1Pin, _in2Pin;
    int _motorLSpeed, _motorRSpeed;
};

#endif /* !defined(ARDUINO_ARDUINO_NANO33BLE) */
#endif /* GIANTOCONTROLLER_H */
