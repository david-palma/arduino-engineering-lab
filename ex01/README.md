# Exercise 1

This exercise is the same as the previous one with the only difference that a led connected to pin 13 is used instead of using the built-in led.

## Schematic

<p align="center">
    <img src="./ex01_schem.png" height="503px" alt="Schematic"></img>
</p>

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
