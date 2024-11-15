# Exercise 3

This exercise consists in measuring the environmental temperature using a TMP36 temperature sensor with Arduino. This sensor is able to measure a fairly wide range of temperature (-50°C to 125°C) with a pretty good resolution (0.1°C).

## Schematic

<p align="center">
    <img src="./ex03_schem.png" height="525px" alt="Schematic"></img>
</p>

## Code

```c
// define constants
const int sensor_pin = A0;
const float baseline = 20.0;
const int led_pins[] = {2, 3, 4};                   // array of LED pins
const int no_pins = sizeof(led_pins) / sizeof(int); // number of pins
const int wait_next = 2000;                         // milliseconds between two acquisitions

// initialisation
void setup()
{
    // open a serial connection
    Serial.begin(9600);

    // set the digital pins as outputs using a for loop
    for (int cnt = 0; cnt < no_pins - 1; cnt++)
    {
        pinMode(led_pins[cnt], OUTPUT);
        digitalWrite(led_pins[cnt], LOW);
    }
}

// main loop function
void loop()
{
    // read the sensor value from ADC on AnalogIn pin 0
    int sensor_value = analogRead(sensor_pin);

    // send the 10-bit sensor value out the serial port
    Serial.print("Sensor value: ");
    Serial.print(sensor_value);

    // convert the ADC reading to voltage
    float voltage = (sensor_value / 1024.0) * 5;

    // send the voltage level out the serial port
    Serial.print(", Voltage: ");
    Serial.print(voltage);

    // convert voltage to temperature (500 mV offset)
    float temperature = (voltage - 0.5) * 100;

    // send the temperaure out the serial port
    Serial.print(", Degrees in Celsius: ");
    Serial.println(temperature);

    if (temperature < baseline)
    {
        // temperature less than 20°C
        digitalWrite(led_pins[0], LOW); // OFF
        digitalWrite(led_pins[1], LOW); // OFF
        digitalWrite(led_pins[2], LOW); // OFF
    }
    else if (temperature > baseline + 2 &&
             temperature < baseline + 8)
    {
        // temperature between 22°C and 28°C
        digitalWrite(led_pins[0], HIGH); // ON
        digitalWrite(led_pins[1], LOW);  // OFF
        digitalWrite(led_pins[2], LOW);  // OFF
    }
    else if (temperature > baseline + 8 &&
             temperature < baseline + 12)
    {
        // temperature between 28°C and 32°C
        digitalWrite(led_pins[0], HIGH); // ON
        digitalWrite(led_pins[1], HIGH); // ON
        digitalWrite(led_pins[2], LOW);  // OFF
    }
    else if (temperature > baseline + 12)
    {
        // temperature greater than 32°C
        digitalWrite(led_pins[0], HIGH); // ON
        digitalWrite(led_pins[1], HIGH); // ON
        digitalWrite(led_pins[2], HIGH); // ON
    }

    // wait 2s
    delay(wait_next);
}
```
