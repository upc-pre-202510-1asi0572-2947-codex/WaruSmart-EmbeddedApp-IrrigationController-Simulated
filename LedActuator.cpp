#include "LedActuator.h"
#include <Arduino.h>

LedActuator::LedActuator(int pin) : pin(pin) {}

void LedActuator::begin() {
    pinMode(pin, OUTPUT);
    activate(false);
}

void LedActuator::activate(bool state) {
    digitalWrite(pin, state ? HIGH : LOW);
    lastState = state;
}

bool LedActuator::getState() const {
    return lastState;
}
