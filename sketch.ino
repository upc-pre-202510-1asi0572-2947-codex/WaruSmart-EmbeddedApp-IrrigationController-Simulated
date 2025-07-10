#include "ModestIoT.h"
#include "DhtSensor.h"
#include "RelayActuator.h"
#include "LedActuator.h"
#include "IrrigationDevice.h"

// Create instances of sensor, relay actuator, and LED actuator
DhtSensor dht(15);          // DHT sensor connected to pin 15
RelayActuator relay(14);    // Relay actuator connected to pin 14
LedActuator led(12);        // LED actuator connected to pin 12

// Create an irrigation device instance with the sensor and actuators
IrrigationDevice device(dht, relay, led);

void setup() {
  device.setup();  // Initialize the irrigation device (sensor, actuators, WiFi)
}

void loop() {
  device.loop();   // Continuously monitor sensors and control the irrigation
}

