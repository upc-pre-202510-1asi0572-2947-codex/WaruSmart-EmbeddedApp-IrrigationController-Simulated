#include "IrrigationDevice.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

/// @brief Constructor
/// @param relay Reference to the relay actuator for irrigation control
/// @param led Reference to the LED actuator for status indication
IrrigationDevice::IrrigationDevice(RelayActuator& relay, LedActuator& led)
    : relay(relay), led(led) {}

/// @brief Initializes the irrigation device and its components
void IrrigationDevice::setup() {
    Serial.begin(115200);  // Initialize serial communication
    relay.begin();         // Initialize relay actuator
    led.begin();           // Initialize LED actuator
    connectWiFi();         // Establish WiFi connection
}

/// @brief Main execution loop for device operation
void IrrigationDevice::loop() {
    // Create the JSON body with only the device ID
    DynamicJsonDocument doc(256);
    doc["device_id"] = "waru-smart-001";

    String jsonPayload;
    serializeJson(doc, jsonPayload);

    Serial.println("Sending JSON to edge:");
    Serial.println(jsonPayload);

    // Send and handle the request
    sendData(jsonPayload);

    delay(10000);  // Wait 10 seconds before next request
}

/// @brief Establishes WiFi connection
void IrrigationDevice::connectWiFi() {
    WiFi.begin("Wokwi-GUEST", "");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi connected.");
}

/// @brief Sends data payload to remote server
/// @param jsonPayload JSON formatted data to be transmitted
void IrrigationDevice::sendData(const String& jsonPayload) {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        http.begin("http://192.168.100.7:5000/api/v1/actuators/status");  // Edge endpoint
        http.addHeader("Content-Type", "application/json");

        int httpResponseCode = http.POST(jsonPayload);

        if (httpResponseCode > 0) {
            String response = http.getString();
            Serial.printf("HTTP %d - Response received:\n", httpResponseCode);
            Serial.println(response);

            // Parse the JSON response
            DynamicJsonDocument responseDoc(1024);
            DeserializationError error = deserializeJson(responseDoc, response);

            if (!error) {
                String action = responseDoc["action"];
                float soilMoisture = responseDoc["soil_moisture"];

                Serial.printf("Action: %s | Soil Moisture: %.1f%%\n", action.c_str(), soilMoisture);

                // Determine activation state based on server response
                bool activate = (action == "irrigate");
                relay.activate(activate);  // Control irrigation pump/valve
                led.activate(activate);    // Update status LED

                Serial.println(activate ? "IRRIGATION ACTIVATED" : "IRRIGATION DEACTIVATED");
            } else {
                Serial.print("Failed to parse JSON: ");
                Serial.println(error.c_str());
            }
        } else {
            Serial.printf("HTTP POST failed: %s\n", http.errorToString(httpResponseCode).c_str());
        }

        http.end();  // Close HTTP connection
    } else {
        Serial.println("WiFi not connected. Skipping request.");
    }