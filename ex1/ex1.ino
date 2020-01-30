/**
 * Exercise no. 1
 **/

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
    digitalWrite(led_pin, HIGH);   // turn the LED on
    delay(1000);                   // wait for a second
    digitalWrite(led_pin, LOW);    // turn the LED off
    delay(1000);                   // wait for a second
}
