/**
 * Exercise no. 2
 **/

// define constants
const int led_pins[] = { 9, 10, 11, 12, 13 };         // array of LED pins
const int no_pins    = sizeof(led_pins)/sizeof(int);  // number of pins
const int between_HL = 250;                           // milliseconds between ON and OFF

// initialisation
void setup()
{
    // set the digital pins as outputs using a for loop
    for(int cnt = 0; cnt < no_pins; cnt++)
    {
        pinMode(led_pins[cnt], OUTPUT);
        digitalWrite(led_pins[cnt], LOW);
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
    for(int cnt = no_pins - 2; cnt >= 1; cnt--)
    {
        digitalWrite(led_pins[cnt], HIGH);  // turn the LED on
        delay(between_HL);                  // wait for a second
        digitalWrite(led_pins[cnt], HIGH);  // turn the LED off
        delay(between_HL);                  // wait for a second
    }
}
