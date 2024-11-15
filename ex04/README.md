# Exercise 4

This exercise demonstrates how to use a Bluetooth module (HC-05) with an Arduino to send and receive data wirelessly. The Arduino will echo back any received data via Bluetooth and print it to the Serial Monitor.

## Tools Required

- Arduino Uno (or any compatible board)
- HC-05 or HC-06 Bluetooth module
- Jumper wires
- Two resistors (1kΩ and 2kΩ) for a voltage divider
- Power source (e.g., USB cable or 9V battery)
- Serial Bluetooth Terminal app (available for iOS/Android)

## Schematic Description

| HC-05 Pin | Arduino Pin                     |
| --------- | ------------------------------- |
| VCC       | 5V                              |
| GND       | GND                             |
| TXD       | RX (Pin 10 via voltage divider) |
| RXD       | TX (Pin 11)                     |

Ensure the voltage divider is used for the RXD pin of the HC-05 to step down the Arduino's 5V TX signal to 3.3V.

## Code

```c
#include <SoftwareSerial.h>

// Define RX and TX pins for the Software Serial port
SoftwareSerial BTSerial(10, 11); // RX | TX

void setup() {
  // Initialise hardware serial port (for monitoring)
  Serial.begin(9600);
  // Initialise Bluetooth serial port
  BTSerial.begin(9600);

  Serial.println("Bluetooth Module is ready!");
}

void loop() {
  // Check if data is available on Bluetooth
  if (BTSerial.available()) {
    char incomingData = BTSerial.read(); // Read the data
    Serial.print("Received via Bluetooth: ");
    Serial.println(incomingData); // Print on Serial Monitor

    // Echo the received data back to the Bluetooth device
    BTSerial.write(incomingData);
  }

  // Check if data is available on Serial Monitor
  if (Serial.available()) {
    char outgoingData = Serial.read(); // Read the data
    BTSerial.write(outgoingData); // Send it to the Bluetooth device
    Serial.print("Sent via Bluetooth: ");
    Serial.println(outgoingData);
  }
}
```

## Exercise Steps

1. **Connect the Hardware:**
   - Build the circuit as per the schematic diagram.
   - Ensure the HC-05's LED is blinking, indicating it is in pairing mode.
2. **Pair the Bluetooth Module:**
   - On your phone, search for nearby Bluetooth devices.
   - Pair with the HC-05 using the default password (1234 or 0000).
3. **Install a Bluetooth Terminal App:**
   - Download a serial Bluetooth terminal app (e.g., "Serial Bluetooth Terminal") on your phone.
4. **Test Communication:**
   - Open the app, connect to the HC-05, and type a message.
   - Observe the message being echoed back on the app and printed on the Arduino Serial Monitor.

When you send a character or string from the Bluetooth terminal app, it will appear in the Arduino Serial Monitor. Similarly, typing in the Serial Monitor will send data to the Bluetooth terminal app.
