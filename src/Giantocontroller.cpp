#include <Giantocontroller.h>

Giantocontroller::Giantocontroller(int in1Pin, int in2Pin, int an1Pin, int an2Pin) {
    _an1Pin = an1Pin;
    _an2Pin = an2Pin;
    _in1Pin = in1Pin;
    _in2Pin = in2Pin;

    pinMode(_an1Pin, OUTPUT);
    pinMode(_an2Pin, OUTPUT);
    pinMode(_in1Pin, OUTPUT);
    pinMode(_in2Pin, OUTPUT);
}

void Giantocontroller::control(signed int left, signed int right) {
    if (left >= 0) {
        if (left > 100) left = 100;
        left = left * 2.55;
        analogWrite(_an1Pin, left);
        digitalWrite(_in1Pin, LOW);
    }
    else if (left < 0) {
        if (left < -100) left = -100;
        left = left * -2.55;
        analogWrite(_an1Pin, left);
        digitalWrite(_in1Pin, HIGH);
    }

    if (right >= 0) {
        if (right > 100) right = 100;
        right = right * 2.55;
        analogWrite(_an2Pin, right);
        digitalWrite(_in2Pin, HIGH);
    }
    else if (right < 0) {
        if (right < -100) right = -100;
        right = right * -2.55;
        analogWrite(_an2Pin, right);
        digitalWrite(_in2Pin, LOW);
    }
}
