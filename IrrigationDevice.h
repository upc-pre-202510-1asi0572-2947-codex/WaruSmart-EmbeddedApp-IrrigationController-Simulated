#ifndef IRRIGATION_DEVICE_H
#define IRRIGATION_DEVICE_H

#include "ModestIoT.h"
#include "RelayActuator.h"
#include "LedActuator.h"
#include <Arduino.h>

/// @brief Irrigation device class that manages relay and LED actuators for irrigation control
class IrrigationDevice : public Device {
public:
    /// @brief Constructor
    /// @param relay Reference to the relay actuator for irrigation control
    /// @param led Reference to the LED actuator for status indication
    IrrigationDevice(RelayActuator& relay, LedActuator& led);

    /// @brief Initializes the irrigation device and its components
    void setup() override;
    
    /// @brief Main execution loop for device operation
    void loop() override;

private:
    RelayActuator& relay;  // Reference to relay actuator for irrigation control
    LedActuator& led;      // Reference to LED actuator for status indication

    /// @brief Establishes WiFi connection
    void connectWiFi();
    
    /// @brief Sends data payload to remote server
    /// @param jsonPayload JSON formatted data to be transmitted
    void sendData(const String& jsonPayload);