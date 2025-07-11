#ifndef LED_ACTUATOR_H
#define LED_ACTUATOR_H

#include "ModestIoT.h"

/// @brief LED actuator class that extends the base Actuator interface
class LedActuator : public Actuator {
public:
    /// @brief Constructor
    /// @param pin Digital output pin connected to the LED
    LedActuator(int pin);

    /// @brief Initializes the LED actuator by setting pin mode and default state
    void begin();
    
    /// @brief Controls the LED state (ON/OFF)
    /// @param state True to turn LED ON, false to turn LED OFF
    void activate(bool state) override;
    
    /// @brief Returns the current state of the LED
    /// @return True if LED is ON, false if LED is OFF
    bool getState() const;

private:
    int pin;                    // Digital output pin connected to the LED
    bool lastState = false;     // Last known state of the LED (default: OFF)