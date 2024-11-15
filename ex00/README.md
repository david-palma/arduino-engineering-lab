# Exercise 0

This exercise consists in the simplest thing to do with an Arduino to see the physical output: blinking the on-board LED.

## Code

```c
// initialisation
void setup()
{
    // LED_BUILTIN pin initialisation as an output
    pinMode(LED_BUILTIN, OUTPUT);
}

// main loop function
void loop()
{
    digitalWrite(LED_BUILTIN, HIGH); // turn the LED on
    delay(1000);                     // wait for a second
    digitalWrite(LED_BUILTIN, LOW);  // turn the LED off
    delay(1000);                     // wait for a second
}
```
