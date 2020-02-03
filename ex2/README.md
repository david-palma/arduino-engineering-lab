# Exercise 2

This exercise makes use of array to turn ON and OFF multiple LEDs in sequence.

## Schematic

<p align="center">
    <img src="./ex2_schem.png" height="500px" alt="Schematic"></img>
</p>

## Code

```c
// define constants
const int led_pins[] = { 9, 10, 11, 12, 13 };        // array of LED pins
const int no_pins    = sizeof(no_pins)/sizeof(int);  // number of pins
const int between_HL = 500;                          // milliseconds between ON and OFF

// initialisation
void setup()
{
    // set the digital pins as outputs using a for loop
    for(int cnt = 0; cnt < no_pins - 1; cnt++)
    {
        pinMode(led_pins[cnt], OUTPUT);
    }
}

// main loop function
void loop()
{
    // turn the leds ON and OFF from first to last
    for(int cnt = 0; cnt < no_pins; cnt++)
    {
        digitalWrite(led_pins[cnt], HIGH);  // turn the LED on
        delay(between_HL);                  // wait for a second
        digitalWrite(led_pins[cnt], HIGH);  // turn the LED off
        delay(between_HL);                  // wait for a second
    }

    // turn the leds ON and OFF from last to first
    for(int cnt = no_pins - 2; cnt >= 0; cnt--)
    {
        digitalWrite(led_pins[cnt], HIGH);  // turn the LED on
        delay(between_HL);                  // wait for a second
        digitalWrite(led_pins[cnt], HIGH);  // turn the LED off
        delay(between_HL);                  // wait for a second
    }
}
```
