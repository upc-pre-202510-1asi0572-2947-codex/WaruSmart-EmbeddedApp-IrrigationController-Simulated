#ifndef IRRIGATION_DEVICE_H
#define IRRIGATION_DEVICE_H

#include "ModestIoT.h"
#include "RelayActuator.h"
#include "LedActuator.h"
#include <Arduino.h>

class IrrigationDevice : public Device {
public:
    IrrigationDevice(RelayActuator& relay, LedActuator& led);

    void setup() override;
    void loop() override;

private:
    RelayActuator& relay;
    LedActuator& led;

    void connectWiFi();
    void sendData(const String& jsonPayload);
};

#endif
