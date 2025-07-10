#include "LedActuator.h"
#include <Arduino.h>

/**
 * @brief Constructor for the LedActuator class, initializes the pin.
 *
 * @param pin Pin connected to the LED actuator.
 */
LedActuator::LedActuator(int pin) : pin(pin) {}

/**
 * @brief Initializes the LED actuator by setting the pin mode to OUTPUT.
 * Also, sets the initial state of the LED to OFF.
 */
void LedActuator::begin() {
    pinMode(pin, OUTPUT);  // Set pin mode to OUTPUT
    activate(false);       // Turn off LED initially
}

/**
 * @brief Activates or deactivates the LED based on the given state.
 *
 * @param state true to turn the LED on, false to turn it off.
 */
void LedActuator::activate(bool state) {
    digitalWrite(pin, state ? HIGH : LOW);  // Set pin to HIGH or LOW based on state
    lastState = state;  // Store the last state
}

/**
 * @brief Returns the current state of the LED.
 *
 * @return true if the LED is on, false if it is off.
 */
bool LedActuator::getState() const {
    return lastState;  // Return the last recorded state
}

