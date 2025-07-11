#include "LedActuator.h"
#include <Arduino.h>

/// @brief Constructor
/// @param pin Digital output pin connected to the LED
LedActuator::LedActuator(int pin) : pin(pin) {}

/// @brief Initializes the LED actuator by setting pin mode and default state
void LedActuator::begin() {
    pinMode(pin, OUTPUT);  // Configure pin as digital output
    activate(false);       // Set initial state to OFF
}

/// @brief Controls the LED state (ON/OFF)
/// @param state True to turn LED ON, false to turn LED OFF
void LedActuator::activate(bool state) {
    digitalWrite(pin, state ? HIGH : LOW);  // Write digital signal to pin
    lastState = state;                      // Store current state for later retrieval
}

/// @brief Returns the current state of the LED
/// @return True if LED is ON, false if LED is OFF
bool LedActuator::getState() const {
    return lastState;  // Return the last