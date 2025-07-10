#include "DhtSensor.h"

/**
 * @brief Constructor for DhtSensor class, initializes the pin to which the sensor is connected
 *
 * @param pin Pin to which the DHT sensor is connected
 */
DhtSensor::DhtSensor(int pin) : pin(pin) {}

/**
 * @brief Initializes the DHT sensor by setting up the pin and sensor type (DHT22)
 *
 * This method sets up the DHT sensor on the specified pin and configures it as a DHT22 sensor.
 */
void DhtSensor::begin() {
    dht.setup(pin, DHTesp::DHT22);  // Initialize the DHT sensor with the specified pin and type
}

/**
 * @brief Updates temperature and humidity readings from the sensor
 *
 * This method retrieves the current temperature and humidity values from the DHT sensor
 * and stores them in the member variables. It also checks if the readings are valid.
 */
void DhtSensor::update() {
    // Get the temperature and humidity data from the sensor
    TempAndHumidity data = dht.getTempAndHumidity();

    // Store the temperature and humidity values
    temperature = data.temperature;
    humidity = data.humidity;

    // Check if the values are valid (not NaN)
    valid = !(isnan(temperature) || isnan(humidity));

    // Print the results to the console
    if (valid) {
        Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.print(" °C, Humidity: ");
        Serial.print(humidity);
        Serial.println(" %");
    } else {
        // If the readings are invalid, print an error message
        Serial.println("Invalid sensor readings.");
    }
}
