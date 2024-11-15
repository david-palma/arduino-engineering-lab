// Arduino programming
// Exercise n. 04

#include <SoftwareSerial.h>

// Define RX and TX pins for the Software Serial port
SoftwareSerial BTSerial(10, 11); // RX | TX

void setup()
{
    // Initialise hardware serial port (for monitoring)
    Serial.begin(9600);
    // Initialise Bluetooth serial port
    BTSerial.begin(9600);

    Serial.println("Bluetooth Module is ready!");
}

void loop()
{
    // Check if data is available on Bluetooth
    if (BTSerial.available())
    {
        char incomingData = BTSerial.read(); // Read the data
        Serial.print("Received via Bluetooth: ");
        Serial.println(incomingData); // Print on Serial Monitor

        // Echo the received data back to the Bluetooth device
        BTSerial.write(incomingData);
    }

    // Check if data is available on Serial Monitor
    if (Serial.available())
    {
        char outgoingData = Serial.read(); // Read the data
        BTSerial.write(outgoingData);      // Send it to the Bluetooth device
        Serial.print("Sent via Bluetooth: ");
        Serial.println(outgoingData);
    }
}
