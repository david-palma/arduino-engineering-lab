// Arduino Engineering Lab
// Exercise n. 06 - central system

#include <Xbee.h>

Xbee xbee = Xbee(); // Initialise Xbee communication

void setup()
{
    // Start serial communication for debugging
    Serial.begin(9600);
    xbee.begin(9600);
    Serial.println("Central system initialized. Waiting for data...");
}

void loop()
{
    // Check if data is available from the sensor node
    if (xbee.available())
    {
        String data = xbee.receiveData(); // Receive data from the sensor node
        // Print received data to Serial Monitor
        Serial.println("Received Data: " + data);

        // You can store or process the data as needed
        // For example, save it to a file or send it to the PC
    }

    delay(1000); // Wait for 1 second before checking again
}
