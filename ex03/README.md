# Exercise 3

This exercise consists in measuring the environmental temperature using a TMP36 temperature sensor with Arduino. This sensor is able to measure a fairly wide range of temperature (-50°C to 125°C) with a pretty good resolution (0.1°C).

## Schematic Description

### Components and Connections

| **Component**         | **Pin/Connection** | **Arduino Pin** | **Description**                                                                                 |
|------------------------|--------------------|-----------------|---------------------------------------------------------------------------------------------|
| **TMP36 Sensor**       | VCC                | 5V              | Provides power to the TMP36 temperature sensor.                                              |
|                        | GND                | GND             | Connects the ground of the TMP36 to Arduino's ground.                                        |
|                        | Analog Output      | A0              | Outputs a voltage proportional to the temperature, connected to Arduino's A0 pin.           |
| **LEDs (3x)**          | Anode              | 2, 3, 4         | Indicates temperature range. Each LED is connected to a digital pin of the Arduino.         |
|                        | Cathode            | GND (via Resistor) | Connects to ground through a 220Ω resistor to limit current.                                |

### Schematic Description Table

| **Connection**         | **Pin**   | **Purpose**                                                                                       |
|-------------------------|-----------|---------------------------------------------------------------------------------------------------|
| TMP36 Sensor to Arduino | VCC, GND, A0 | Provides temperature readings to the Arduino for processing and display via LEDs or Serial Monitor. |
| LEDs to Arduino         | 2, 3, 4   | Lights up LEDs to indicate the temperature range based on thresholds defined in the code.         |

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
    for (int cnt = 0; cnt < no_pins; cnt++)
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

## Exercise Steps

1. **Connect the TMP36 Temperature Sensor**:
   - Connect the sensor's VCC pin to the 5V pin on the Arduino.
   - Connect the GND pin of the sensor to the Arduino's GND.
   - Connect the analog output pin of the TMP36 to the A0 pin on the Arduino.

2. **Set Up LEDs for Temperature Indication**:
   - Connect LEDs to digital pins 2, 3, and 4 of the Arduino.
   - Use appropriate resistors (e.g., 220Ω) in series with the LEDs to limit current.

3. **Upload the Arduino Code**:
   - Copy the provided code for temperature measurement.
   - Open the Arduino IDE, paste the code, and upload it to the Arduino.

4. **Monitor the Temperature**:
   - Open the Serial Monitor to observe the temperature readings.
   - Observe the LEDs lighting up according to the temperature range.

5. **Adjust the Baseline if Necessary**:
   - The baseline temperature can be adjusted in the code to fit the desired range for LED activation.
