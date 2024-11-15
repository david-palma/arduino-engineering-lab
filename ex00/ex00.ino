// Arduino programming
// Exercise n. 00

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
