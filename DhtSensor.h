#ifndef DHT_SENSOR_H
#define DHT_SENSOR_H

#include "DHTesp.h"

/**
 * @class DhtSensor
 * @brief Class for reading temperature and humidity from a DHT sensor (DHT22).
 */
class DhtSensor {
public:
    // Constructor to initialize the sensor pin
    DhtSensor(int pin);

    // Initializes the sensor
    void begin();

    // Updates the temperature and humidity readings
    void update();

    // Sensor readings
    float temperature = 0;
    float humidity = 0;
    bool valid = false;

private:
    int pin;       // Pin connected to the sensor
    DHTesp dht;    // DHT sensor object
};

#endif
