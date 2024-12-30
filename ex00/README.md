# Exercise 0

This exercise consists of performing the simplest task with an Arduino to observe physical output: blinking the on-board LED.

## Schematic Description

This exercise does not require an external schematic as it utilises the built-in LED present on the Arduino board.

### Built-in LED Description

| **Component**    | **Pin/Connection** | **Arduino Pin** | **Description**                                                                 |
|-------------------|--------------------|-----------------|---------------------------------------------------------------------------------|
| **Built-in LED**  | LED_BUILTIN        | 13 (or equivalent) | The built-in LED blinks ON and OFF according to the delay values in the code.  |

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

## Exercise Steps

1. **Understand the On-Board LED**:
   - The Arduino comes with a built-in LED, which is typically connected to the `LED_BUILTIN` pin. For most boards, this corresponds to pin 13.
   - This exercise uses the built-in LED to create a simple blinking effect.

2. **Upload the Arduino Code**:
   - Copy the provided code for blinking the on-board LED.
   - Open the Arduino IDE, paste the code, and upload it to the Arduino.

3. **Observe LED Behaviour**:
   - The on-board LED will turn ON for one second and OFF for one second in a continuous loop.
   - Modify the `delay()` values in the code if you wish to change the blinking speed.

4. **Experiment with Timing**:
   - Adjust the `delay()` durations to make the LED blink faster or slower.
   - Try adding additional logic, such as double blinking, to enhance the exercise.
