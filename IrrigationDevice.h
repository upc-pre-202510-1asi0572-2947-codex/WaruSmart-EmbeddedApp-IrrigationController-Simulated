#ifndef IRRIGATION_DEVICE_H
#define IRRIGATION_DEVICE_H

#include "ModestIoT.h"
#include "DhtSensor.h"
#include "RelayActuator.h"
#include "LedActuator.h"

/**
 * @class IrrigationDevice
 * @brief Class to manage an irrigation system with sensors and actuators.
 *
 * This class interfaces with a DHT sensor, relay actuator, and LED actuator to manage irrigation
 * based on environmental conditions like temperature and humidity.
 */
class IrrigationDevice : public Device {
public:
    /**
     * @brief Constructor to initialize the DHT sensor, relay, and LED actuator.
     *
     * @param dhtSensor DHT sensor to read temperature and humidity.
     * @param relay Relay actuator to control irrigation.
     * @param led LED actuator to indicate irrigation status.
     */
    IrrigationDevice(DhtSensor& dhtSensor, RelayActuator& relay, LedActuator& led);

    /**
     * @brief Setup method to initialize devices and WiFi.
     *
     * Initializes the DHT sensor, relay, LED actuator, and connects to WiFi.
     */
    void setup() override;

    /**
     * @brief Main loop to monitor sensors and control irrigation.
     *
     * Checks sensor values and activates/deactivates irrigation accordingly.
     */
    void loop() override;

private:
    DhtSensor& dht;            /**< Reference to DHT sensor for temperature and humidity */
    RelayActuator& relay;      /**< Reference to relay actuator for controlling irrigation */
    LedActuator& led;          /**< Reference to LED actuator for status indication */

    /**
     * @brief Connects the device to WiFi.
     */
    void connectWiFi();

    /**
     * @brief Sends sensor data to the server.
     *
     * @param jsonPayload The data in JSON format to be sent.
     */
    void sendData(const String& jsonPayload);
};

#endif

