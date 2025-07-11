#include "RelayActuator.h"
#include <Arduino.h>

/// @brief Constructor
/// @param pin Digital output pin connected to the relay
RelayActuator::RelayActuator(int pin) : pin(pin) {}

/// @brief Initializes the relay actuator by setting pin mode and default state
void RelayActuator::begin() {
    pinMode(pin, OUTPUT);  // Configure pin as digital output
    activate(false);       // Set initial state to OFF (relay open)
}

/// @brief Controls the relay state (ON/OFF)
/// @param state True to turn relay ON (close circuit), false to turn relay OFF (open circuit)
void RelayActuator::activate(bool state) {
    digitalWrite(pin, state ? HIGH : LOW);  // Write digital signal to pin
    lastState = state;                      // Store current state for later retrieval
}

/// @brief Returns the current state of the relay
/// @return True if relay is ON (closed), false if relay is OFF (open)
bool RelayActuator::getState() const {
    return lastState;  // Return the last