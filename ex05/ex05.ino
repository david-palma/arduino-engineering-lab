// Arduino programming
// Exercise n. 05
#include <SoftwareSerial.h>
#include <Servo.h>

// Define RX and TX pins for the Software Serial port
SoftwareSerial BTSerial(10, 11); // RX | TX

// Create a Servo object
Servo myServo;

void setup()
{
    // Initialize serial communication
    Serial.begin(9600);
    BTSerial.begin(9600);

    // Attach the servo to pin 9
    myServo.attach(9);

    // Set the servo to the initial position (90 degrees)
    myServo.write(90);
    Serial.println("Servo is ready! Send angle (0-180).");
}

void loop()
{
    // Check if data is available via Bluetooth
    if (BTSerial.available())
    {
        String command = BTSerial.readStringUntil('\n'); // Read the command
        command.trim();                                  // Remove any extra spaces or line breaks

        // Convert the command to an integer
        int angle = command.toInt();

        // Validate the angle and move the servo
        if (angle >= 0 && angle <= 180)
        {
            myServo.write(angle); // Set servo position
            Serial.print("Moving servo to ");
            Serial.print(angle);
            Serial.println(" degrees.");

            // Send feedback to the Bluetooth device
            BTSerial.print("Servo moved to ");
            BTSerial.print(angle);
            BTSerial.println(" degrees.");
        }
        else
        {
            Serial.println("Invalid angle received.");
            BTSerial.println("Error: Angle must be between 0 and 180.");
        }
    }
}
