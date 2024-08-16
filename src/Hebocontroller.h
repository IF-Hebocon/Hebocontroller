#ifndef HEBOCONTROLLER_H
#define HEBOCONTROLLER_H

#if !defined(ARDUINO_NODEMCU_32S)
#error "This Library only works with 'Arduino NodeMCU 32s' Boards"
#else

#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#define SERVICE_UUID        "19B10000-E8F2-537E-4F6C-D104768A1214"
#define CHARACTERISTIC_UUID "19B10001-E8F2-537E-4F6C-D104768A1214"
#define MOTOR_1B 32
#define MOTOR_1F 33
#define MOTOR_2B 25
#define MOTOR_2F 26
#define SPEED 180

class Hebobot {
    private:
        unsigned int _baudrate;
    public:
        String name;
        Hebobot(String name, unsigned long baudrate);
        virtual void init();
        virtual void drive(String value);
};

class Hebocontroller {
    public:
        Hebocontroller(Hebobot hebobot);
        virtual void init();
        virtual void poll();
    private:
        Hebobot _hebobot;
        BLEServer *_bleServer;
        BLEService *_bleService;
        BLECharacteristic *_bleCharacteristic;
};
#endif /* !defined(ARDUINO_NODEMCU_32S) */
#endif /* HEBOCONTROLLER_H */
