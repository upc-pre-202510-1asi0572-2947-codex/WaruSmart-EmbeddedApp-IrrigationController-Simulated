#include "IrrigationDevice.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino.h>

// Constructor to initialize the DHT sensor, relay, and LED actuator
IrrigationDevice::IrrigationDevice(DhtSensor& dhtSensor, RelayActuator& relay, LedActuator& led)
    : dht(dhtSensor), relay(relay), led(led) {}

// Setup method for initializations
void IrrigationDevice::setup() {
    Serial.begin(115200);    // Initialize serial communication
    dht.begin();             // Initialize DHT sensor
    relay.begin();           // Initialize relay
    led.begin();             // Initialize LED
    connectWiFi();           // Connect to WiFi
}

// Main loop to check sensor readings and control irrigation
void IrrigationDevice::loop() {
    dht.update();  // Update DHT sensor readings

    if (!dht.valid) {
        Serial.println("Error reading sensor");
        delay(2000);
        return;
    }

    Serial.printf("Temperature: %.1f °C | Humidity: %.1f %%\n", dht.temperature, dht.humidity);

    // Activate irrigation if temperature > 30°C or humidity < 40%
    bool activateIrrigation = (dht.temperature > 30.0 || dht.humidity < 40.0);
    relay.activate(activateIrrigation);
    led.activate(activateIrrigation);

    // Log irrigation status
    Serial.println(activateIrrigation ? "Irrigation ACTIVATED" : "Irrigation DEACTIVATED");

    // Create JSON payload for server
    String json = "{";
    json += "\"device_id\": \"waru-smart-001\",";
    json += "\"soil_moisture\":" + String(50,1) + ",";
    json += "\"temperature\":" + String(dht.temperature, 1) + ",";
    json += "\"humidity\":" + String(dht.humidity, 1) + ",";
    json += "\"zone\": \"C\"";
    json += "}";

    // Log generated JSON
    Serial.println("JSON generated:");
    Serial.println(json);

    sendData(json);  // Send data to server

    delay(10000);  // Wait before the next loop
}

// Connect to WiFi
void IrrigationDevice::connectWiFi() {
    WiFi.begin("Wokwi-GUEST", "");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi connected.");
}

// Send data to the server using POST
void IrrigationDevice::sendData(const String& jsonPayload) {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;

        // Send POST request to the server
        http.begin("http://192.168.82.2:9080/api/v1/monitoring/device-metrics");
        http.addHeader("Content-Type", "application/json");

        int httpResponseCode = http.POST(jsonPayload);

        if (httpResponseCode > 0) {
            Serial.printf("POST sent. Response code: %d\n", httpResponseCode);
            String response = http.getString();
            Serial.println("Server response:");
            Serial.println(response);
        } else {
            Serial.printf("Error in POST: %s\n", http.errorToString(httpResponseCode).c_str());
        }

        http.end();
    } else {
        Serial.println("No WiFi connection to send data.");
    }
}

