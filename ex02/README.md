# Exercise 2

This exercise makes use of array to turn ON and OFF multiple LEDs in sequence.

## Schematic Description

### Components and Connections

| **Component** | **Pin/Connection**   | **Arduino Pin** | **Description**                                                                               |
|---------------|----------------------|-----------------|-------------------------------------------------------------------------------------------|
| **LEDs (5x)** | Anode                | 9, 10, 11, 12, 13 | Indicates sequence by turning ON and OFF in an order defined by the programme logic.       |
|               | Cathode              | GND (via Resistor) | Connects to ground through a 220Ω resistor to limit current.                               |

### Schematic Description Table

| **Connection**          | **Pin**      | **Purpose**                                                                                   |
|--------------------------|--------------|---------------------------------------------------------------------------------------------|
| LEDs to Arduino          | 9, 10, 11, 12, 13 | Controls the ON/OFF state of LEDs in a sequence as programmed in the code.                   |
| LEDs to Ground (via Resistors) | GND          | Ensures safe operation of LEDs by limiting current with resistors.                           |

## Code

```c
// define constants
const int led_pins[] = {9, 10, 11, 12, 13};         // array of LED pins
const int no_pins = sizeof(led_pins) / sizeof(int); // number of pins
const int between_HL = 250;                         // milliseconds between ON and OFF

// initialisation
void setup()
{
    // set the digital pins as outputs using a for loop
    for (int cnt = 0; cnt < no_pins; cnt++)
    {
        pinMode(led_pins[cnt], OUTPUT);
        digitalWrite(led_pins[cnt], LOW);
    }
}

// main loop function
void loop()
{
    // turn the leds ON and OFF from first to last
    for (int cnt = 0; cnt < no_pins; cnt++)
    {
        digitalWrite(led_pins[cnt], HIGH); // turn the LED on
        delay(between_HL);                 // wait for a second
        digitalWrite(led_pins[cnt], HIGH); // turn the LED off
        delay(between_HL);                 // wait for a second
    }

    // turn the leds ON and OFF from last to first
    for (int cnt = no_pins - 2; cnt >= 1; cnt--)
    {
        digitalWrite(led_pins[cnt], HIGH); // turn the LED on
        delay(between_HL);                 // wait for a second
        digitalWrite(led_pins[cnt], HIGH); // turn the LED off
        delay(between_HL);                 // wait for a second
    }
}
```

## Exercise Steps

1. **Connect the LEDs**:
   - Connect five LEDs to digital pins 9, 10, 11, 12, and 13 on the Arduino.
   - Use appropriate resistors (e.g., 220Ω) in series with the LEDs to limit current.
   - Connect the cathode of each LED to the GND rail.

2. **Upload the Arduino Code**:
   - Copy the provided code for sequential LED blinking.
   - Open the Arduino IDE, paste the code, and upload it to the Arduino.

3. **Observe LED Behaviour**:
   - LEDs will turn ON and OFF in sequence from first to last and then from last to first.
   - Adjust the `between_HL` constant in the code if needed to modify the delay between LED toggling.

4. **Experiment and Modify**:
   - Experiment with adding more LEDs or changing the sequence logic in the code.
