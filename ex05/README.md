# Exercise 5

This exercise involves controlling a servo motor's position wirelessly using a Bluetooth module (HC-05) and an Arduino. The Bluetooth module will receive angle commands from a smartphone, which will control the servo motor's position in real time.

## Tools Required

- Arduino Uno (or any compatible board)
- HC-05 or HC-06 Bluetooth module
- Servo motor (e.g., SG90 or MG996R)
- External power source for the servo (if needed)
- Jumper wires
- Serial Bluetooth Terminal app (available for iOS/Android)

## Schematic Description

| HC-05 Pin | Arduino Pin                     |
| --------- | ------------------------------- |
| VCC       | 5V                              |
| GND       | GND                             |
| TXD       | RX (Pin 10 via voltage divider) |
| RXD       | TX (Pin 11)                     |

Ensure the voltage divider is used for the RXD pin of the HC-05 to step down the Arduino's 5V TX signal to 3.3V.

| Servo Pin | Arduino Pin               |
| --------- | ------------------------- |
| VCC       | External 5V or Arduino 5V |
| GND       | GND                       |
| Signal    | Pin 9                     |

Ensure the servo motor has sufficient power. If using a high-torque servo, consider an external power source.

## Code

```c
#include <SoftwareSerial.h>
#include <Servo.h>

// Define RX and TX pins for the Software Serial port
SoftwareSerial BTSerial(10, 11); // RX | TX

// Create a Servo object
Servo myServo;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  BTSerial.begin(9600);

  // Attach the servo to pin 9
  myServo.attach(9);

  // Set the servo to the initial position (90 degrees)
  myServo.write(90);
  Serial.println("Servo is ready! Send angle (0-180).");
}

void loop() {
  // Check if data is available via Bluetooth
  if (BTSerial.available()) {
    String command = BTSerial.readStringUntil('\n'); // Read the command
    command.trim(); // Remove any extra spaces or line breaks

    // Convert the command to an integer
    int angle = command.toInt();

    // Validate the angle and move the servo
    if (angle >= 0 && angle <= 180) {
      myServo.write(angle); // Set servo position
      Serial.print("Moving servo to ");
      Serial.print(angle);
      Serial.println(" degrees.");

      // Send feedback to the Bluetooth device
      BTSerial.print("Servo moved to ");
      BTSerial.print(angle);
      BTSerial.println(" degrees.");
    } else {
      Serial.println("Invalid angle received.");
      BTSerial.println("Error: Angle must be between 0 and 180.");
    }
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
   - Open the Bluetooth terminal app, connect to the HC-05, and send angle values (e.g., 90, 45, 135).
   - Observe the servo moving to the specified position.

When you send a valid angle (0–180), the servo motor will rotate to that position. The Arduino will print a confirmation message to the Serial Monitor and send feedback to the Bluetooth terminal app. If an invalid angle is sent, an error message will be displayed in both the Serial Monitor and the app.

### Extensions

1. **Add Multi-Servo Support:**
   - Expand the code to control multiple servos using different commands (e.g., "A90" for Servo A at 90 degrees).
2. **Implement a Reset Command:**
   - Add a specific command (e.g., "reset") to return the servo to its default position.
3. **Combine with Sensors:**
   - Use a sensor (e.g., ultrasonic or temperature) to send real-time data to the smartphone along with servo control.
4. **Build a Robotic Arm:**
   - Use multiple servos and Bluetooth commands to control a robotic arm’s joints.
