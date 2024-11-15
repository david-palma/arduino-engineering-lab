// Arduino Engineering Lab
// Exercise n. 06 - sensor node

#include <DHT.h>
#include <SPI.h>
#include <Wire.h>
#include <Xbee.h> // For Xbee module. If using NRF24L01, replace with appropriate library

// Pin setup
#define DHTPIN 2    // DHT sensor pin
#define LDRPIN A0   // LDR sensor pin
#define MQ135PIN A1 // MQ-135 sensor pin

DHT dht(DHTPIN, DHT22); // Initialise DHT22 sensor
Xbee xbee = Xbee();     // Initialise Xbee communication

void setup()
{
    // Start serial communication for debugging
    Serial.begin(9600);
    xbee.begin(9600);
    dht.begin();
    pinMode(LDRPIN, INPUT);   // Set LDR pin as input
    pinMode(MQ135PIN, INPUT); // Set MQ-135 pin as input
}

void loop()
{
    // Read temperature and humidity from DHT sensor
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();
    int lightIntensity = analogRead(LDRPIN); // Read light intensity from LDR
    int airQuality = analogRead(MQ135PIN);   // Read air quality from MQ-135

    // Check if the readings failed
    if (isnan(temperature) || isnan(humidity))
    {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }

    // Format the data to be sent (comma-separated)
    String data = String(temperature) + "," + String(humidity) + "," + String(lightIntensity) + "," + String(airQuality);

    // Send the data wirelessly via Xbee
    xbee.sendData(data.c_str());

    // Print the data to Serial Monitor for debugging
    Serial.println("Data Sent: " + data);

    // Wait for a short period before sending the next data
    delay(2000);
}
