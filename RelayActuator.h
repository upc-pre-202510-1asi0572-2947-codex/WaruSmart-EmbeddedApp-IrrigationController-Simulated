#ifndef RELAY_ACTUATOR_H
#define RELAY_ACTUATOR_H

#include "ModestIoT.h"

/// @brief Relay actuator class that extends the base Actuator interface
class RelayActuator : public Actuator {
public:
    /// @brief Constructor
    /// @param pin Digital output pin connected to the relay
    RelayActuator(int pin);

    /// @brief Initializes the relay actuator by setting pin mode and default state
    void begin();
    
    /// @brief Controls the relay state (ON/OFF)
    /// @param state True to turn relay ON (close circuit), false to turn relay OFF (open circuit)
    void activate(bool state) override;
    
    /// @brief Returns the current state of the relay
    /// @return True if relay is ON (closed), false if relay is OFF (open)
    bool getState() const;

private:
    int pin;                    // Digital output pin connected to the relay
    bool lastState = false;     // Last known state of the relay (default: