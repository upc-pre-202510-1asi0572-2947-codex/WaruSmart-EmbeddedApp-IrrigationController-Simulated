#ifndef LED_ACTUATOR_H
#define LED_ACTUATOR_H

#include "ModestIoT.h"

/**
 * @class LedActuator
 * @brief Class to control an LED actuator.
 *
 * This class controls an LED connected to a specified pin, allowing activation and state checking.
 */
class LedActuator : public Actuator {
public:
    /**
     * @brief Constructor for the LedActuator class.
     *
     * @param pin Pin connected to the LED actuator.
     */
    LedActuator(int pin);

    /**
     * @brief Initializes the LED actuator by setting the pin mode to OUTPUT.
     * Also, turns off the LED initially.
     */
    void begin();

    /**
     * @brief Activates or deactivates the LED based on the given state.
     *
     * @param state true to turn the LED on, false to turn it off.
     */
    void activate(bool state) override;

    /**
     * @brief Returns the current state of the LED.
     *
     * @return true if the LED is on, false if it is off.
     */
    bool getState() const;

private:
    int pin;               /**< Pin connected to the LED actuator */
    bool lastState = false; /**< Last known state of the LED (ON/OFF) */
};

#endif


