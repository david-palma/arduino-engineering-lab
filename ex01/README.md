# Exercise 1

This exercise is the same as the previous one with the only difference that a led connected to pin 13 is used instead of using the built-in led.

## Schematic Description

### Components and Connections

| **Component** | **Pin/Connection** | **Arduino Pin** | **Description**                                                                 |
|---------------|--------------------|-----------------|---------------------------------------------------------------------------------|
| **LED**       | Anode              | 13              | Turns ON and OFF as programmed in the code to create a blinking effect.         |
|               | Cathode            | GND (via Resistor) | Connects to ground through a 220Ω resistor to ensure safe current flow.         |

### Schematic Description Table

| **Connection**          | **Pin**      | **Purpose**                                                                                   |
|--------------------------|--------------|---------------------------------------------------------------------------------------------|
| LED to Arduino           | 13           | Controls the ON/OFF state of the LED based on the programme logic.                           |
| LED to Ground (via Resistor) | GND          | Ensures safe operation of the LED by limiting current with a resistor.                       |

## Code

```c
// define constants
const int led_pin = 13;

// initialisation
void setup()
{
    // set the digital pin as output
    pinMode(led_pin, OUTPUT);
}

// main loop function
void loop()
{
    digitalWrite(led_pin, HIGH); // turn the LED on
    delay(1000);                 // wait for a second
    digitalWrite(led_pin, LOW);  // turn the LED off
    delay(1000);                 // wait for a second
}
```

## Exercise Steps

1. **Connect the External LED**:
   - Connect the anode of an LED to digital pin 13 on the Arduino.
   - Use appropriate resistors (e.g., 220Ω) in series with the LED to limit current.
   - Connect the cathode of the LED to the GND rail.

2. **Upload the Arduino Code**:
   - Copy the provided code for blinking the LED.
   - Open the Arduino IDE, paste the code, and upload it to the Arduino.

3. **Observe LED Behaviour**:
   - The external LED connected to pin 13 will turn ON for one second and OFF for one second in a continuous loop.
   - Modify the `delay()` values in the code if you wish to change the blinking speed.

4. **Experiment and Modify**:
   - Try connecting the LED to a different pin and update the `led_pin` value in the code accordingly.
   - Experiment with different delay durations to observe variations in blinking speed.
