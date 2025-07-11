#include "IrrigationDevice.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

IrrigationDevice::IrrigationDevice(RelayActuator& relay, LedActuator& led)
    : relay(relay), led(led) {}

void IrrigationDevice::setup() {
    Serial.begin(115200);
    relay.begin();
    led.begin();
    connectWiFi();
}

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

    delay(10000); // Wait before next request
}

void IrrigationDevice::connectWiFi() {
    WiFi.begin("Wokwi-GUEST", "");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi connected.");
}

void IrrigationDevice::sendData(const String& jsonPayload) {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        http.begin("http://192.168.100.7:5000/api/v1/actuators/status"); // Edge endpoint
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

                bool activate = (action == "irrigate");
                relay.activate(activate);
                led.activate(activate);

                Serial.println(activate ? "IRRIGATION ACTIVATED" : "IRRIGATION DEACTIVATED");
            } else {
                Serial.print("Failed to parse JSON: ");
                Serial.println(error.c_str());
            }
        } else {
            Serial.printf("HTTP POST failed: %s\n", http.errorToString(httpResponseCode).c_str());
        }

        http.end();
    } else {
        Serial.println("WiFi not connected. Skipping request.");
    }
}
