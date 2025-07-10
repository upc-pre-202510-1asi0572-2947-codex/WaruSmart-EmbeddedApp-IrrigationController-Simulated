#ifndef RELAY_ACTUATOR_H
#define RELAY_ACTUATOR_H

#include "ModestIoT.h"

/**
 * @class RelayActuator
 * @brief Class to control a relay actuator.
 *
 * This class provides methods to control a relay connected to a specific pin
 * and check its current state.
 */
class RelayActuator : public Actuator {
public:
    /**
     * @brief Constructor for the RelayActuator class.
     *
     * @param pin Pin connected to the relay actuator.
     */
    RelayActuator(int pin);

    /**
     * @brief Initializes the relay actuator by setting the pin mode to OUTPUT.
     * Also, turns off the relay initially.
     */
    void begin();

    /**
     * @brief Activates or deactivates the relay based on the given state.
     *
     * @param state true to activate the relay (turn ON), false to deactivate it (turn OFF).
     */
    void activate(bool state) override;

    /**
     * @brief Returns the current state of the relay.
     *
     * @return true if the relay is activated (ON), false if deactivated (OFF).
     */
    bool getState() const;

private:
    int pin;               /**< Pin connected to the relay actuator */
    bool lastState = false; /**< Last known state of the relay (ON/OFF) */
};

#endif

