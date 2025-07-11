#include "ModestIoT.h"
#include "RelayActuator.h"
#include "LedActuator.h"
#include "IrrigationDevice.h"


RelayActuator relay(14);
LedActuator led(12);
IrrigationDevice device(relay, led);

void setup() {
  device.setup();
}

void loop() {
  device.loop();
}
