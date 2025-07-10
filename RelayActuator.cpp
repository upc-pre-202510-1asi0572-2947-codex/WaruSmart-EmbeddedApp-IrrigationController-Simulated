#include "RelayActuator.h"
#include <Arduino.h>

/**
 * @brief Constructor for the RelayActuator class, initializes the pin.
 *
 * @param pin Pin connected to the relay actuator.
 */
RelayActuator::RelayActuator(int pin) : pin(pin) {}

/**
 * @brief Initializes the relay actuator by setting the pin mode to OUTPUT.
 * Also, sets the initial state of the relay to OFF.
 */
void RelayActuator::begin() {
    pinMode(pin, OUTPUT);  // Set the pin mode to OUTPUT
    activate(false);       // Turn off the relay initially
}

/**
 * @brief Activates or deactivates the relay based on the given state.
 *
 * @param state true to activate the relay (turn ON), false to deactivate it (turn OFF).
 */
void RelayActuator::activate(bool state) {
    digitalWrite(pin, state ? HIGH : LOW);  // Set the pin to HIGH (ON) or LOW (OFF) based on state
    lastState = state;  // Store the last state
}

/**
 * @brief Returns the current state of the relay.
 *
 * @return true if the relay is activated (ON), false if deactivated (OFF).
 */
bool RelayActuator::getState() const {
    return lastState;  // Return the last recorded state
}
