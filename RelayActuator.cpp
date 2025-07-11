#include "RelayActuator.h"
#include <Arduino.h>

RelayActuator::RelayActuator(int pin) : pin(pin) {}

void RelayActuator::begin() {
    pinMode(pin, OUTPUT);
    activate(false);
}

void RelayActuator::activate(bool state) {
    digitalWrite(pin, state ? HIGH : LOW);
    lastState = state;
}

bool RelayActuator::getState() const {
    return lastState;
}
