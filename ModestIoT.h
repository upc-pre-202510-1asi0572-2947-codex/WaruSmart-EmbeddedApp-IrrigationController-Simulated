#ifndef MODEST_IOT_H
#define MODEST_IOT_H

// Base class for events
class Event {};

// Base class for commands
class Command {};

// Abstract class for sensors
// Derived classes should implement the update method to read sensor data
class Sensor {
public:
  virtual void update() = 0;  // Pure virtual function to update sensor readings
};

// Abstract class for actuators
// Derived classes should implement the activate method to control the actuator
class Actuator {
public:
  virtual void activate(bool state) = 0;  // Pure virtual function to activate/deactivate the actuator
};

// Abstract class for devices
// Derived classes should implement setup and loop for initialization and continuous operations
class Device {
public:
  virtual void setup() = 0;  // Pure virtual function for device setup
  virtual void loop() = 0;   // Pure virtual function for device operations in the main loop
};

#endif

