#include "ModestIoT.h"
#include "RelayActuator.h"
#include "LedActuator.h"
#include "IrrigationDevice.h"

// Create actuator instances
RelayActuator relay(14);  // Relay connected to pin 14 for irrigation control
LedActuator led(12);      // LED connected to pin 12 for status indication

// Create irrigation device with the actuators
IrrigationDevice device(relay, led);

/// @brief Arduino setup function - called once at startup
void setup() {
  device.setup();  // Initialize the irrigation device and its components
}

/// @brief Arduino main loop function - called repeatedly
void loop() {
  device.loop();  // Execute the main device operation cycle