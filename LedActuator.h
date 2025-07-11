#ifndef LED_ACTUATOR_H
#define LED_ACTUATOR_H

#include "ModestIoT.h"

class LedActuator : public Actuator {
public:
    LedActuator(int pin);

    void begin();
    void activate(bool state) override;
    bool getState() const;

private:
    int pin;
    bool lastState = false;
};

#endif

