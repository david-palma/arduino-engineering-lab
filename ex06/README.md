# Exercise 6

This exercise involves building a Wireless Sensor Network (WSN) using Arduino boards to monitor various environmental parameters such as temperature, humidity, light intensity, and air quality. The data from the sensors will be transmitted wirelessly through a Sensor Node (with an Xbee or NRF24L01 module) to a Central System. On the central system, the received data will be stored and visualised for monitoring purposes.
The main objectives of the exercise are as follows:

- Create a wireless sensor node using Arduino to monitor environmental parameters (temperature, humidity, light intensity, and air quality).
- Transmit sensor data wirelessly to a central system using Xbee or NRF24L01 modules.
- Receive and store the data on the central system.
- Visualise the received data on a PC for real-time monitoring and logging.

## Explanation of the Process

### Sensor Node

- The **DHT22** measures temperature and humidity.
- The **LDR** measures light intensity.
- The **MQ-135** measures air quality.
- The data is sent wirelessly to the central system using the **Xbee/NRF24L01** module.

### Central System

- The central **Arduino** receives the data from the sensor node via the **Xbee/NRF24L01** module.
- This data can be viewed in the **Serial Monitor** or sent to a **PC** for storage and visualisation.

### PC Data Visualisation

- A **Python script** is used to receive data from the Arduino and visualise it in real-time using **Matplotlib**, allowing you to monitor the environmental parameters continuously.
- The script also stores the data for further analysis or logging.

## Tools Required

- 2x Arduino Uno boards (one for the sensor node and one for the central system)
- Xbee or NRF24L01 wireless modules (2x for communication between nodes and central system)
- DHT22 (or similar) temperature and humidity sensor
- LDR (Light Dependent Resistor) for light intensity measurement
- MQ-135 or similar air quality sensor (for detecting gases such as CO2, NH3, etc.)
- Jumper wires
- Power supply for Arduino and sensor nodes
- PC for the central monitoring system

## Schematic Overview

### 1. Sensor Node (Arduino with Xbee/NRF24L01)

- DHT22 sensor connected to Pin 2 for temperature and humidity.
- LDR sensor connected to Pin A0 for light intensity measurement.
- MQ-135 sensor connected to Pin A1 for air quality measurement.
- Xbee/NRF24L01 module connected for wireless communication.

#### Schematic Description Table

| **Component**                             | **Pin/Connection** | **Arduino Pin/Port**        | **Description**                                                                           |
| ----------------------------------------- | ------------------ | --------------------------- | ----------------------------------------------------------------------------------------- |
| **DHT22 (Temperature & Humidity Sensor)** | VCC                | 5V                          | Powers the DHT22 sensor with 5V.                                                          |
|                                           | GND                | GND                         | Connects the ground of the DHT22 to Arduino's ground.                                     |
|                                           | Data               | Pin 2                       | Data line of the DHT22 sensor connected to digital pin 2.                                 |
| **LDR (Light Dependent Resistor)**        | VCC                | 5V                          | Powers the LDR sensor with 5V.                                                            |
|                                           | GND                | GND                         | Connects the ground of the LDR sensor to Arduino's ground.                                |
|                                           | Analog Output      | A0                          | Analog output of the LDR sensor connected to analog pin A0 to measure light intensity.    |
| **MQ-135 (Air Quality Sensor)**           | VCC                | 5V                          | Powers the MQ-135 sensor with 5V.                                                         |
|                                           | GND                | GND                         | Connects the ground of the MQ-135 to Arduino's ground.                                    |
|                                           | Analog Output      | A1                          | Analog output of the MQ-135 sensor connected to analog pin A1 for air quality reading.    |
| **Xbee/NRF24L01 Wireless Module**         | VCC                | 3.3V (for Xbee or NRF24L01) | Powers the Xbee or NRF24L01 module with 3.3V (Xbee requires 3.3V).                        |
|                                           | GND                | GND                         | Connects the ground of the Xbee or NRF24L01 module to Arduino's ground.                   |
|                                           | Data TX            | Pin 1 (for Xbee)            | Serial TX of the wireless module connected to Arduino's TX pin (Pin 1) for communication. |
|                                           | Data RX            | Pin 0 (for Xbee)            | Serial RX of the wireless module connected to Arduino's RX pin (Pin 0) for communication. |

### 2. **Central System (Arduino with Xbee/NRF24L01):**

- Xbee/NRF24L01 connected to the central Arduino to receive data from the sensor node.

#### Schematic Description Table

| **Component**                     | **Pin/Connection** | **Arduino Pin/Port**        | **Description**                                                                           |
| --------------------------------- | ------------------ | --------------------------- | ----------------------------------------------------------------------------------------- |
| **Xbee/NRF24L01 Wireless Module** | VCC                | 3.3V (for Xbee or NRF24L01) | Powers the Xbee or NRF24L01 module with 3.3V (Xbee requires 3.3V).                        |
|                                   | GND                | GND                         | Connects the ground of the Xbee or NRF24L01 module to Arduino's ground.                   |
|                                   | Data TX            | Pin 1 (for Xbee)            | Serial TX of the wireless module connected to Arduino's TX pin (Pin 1) for communication. |
|                                   | Data RX            | Pin 0 (for Xbee)            | Serial RX of the wireless module connected to Arduino's RX pin (Pin 0) for communication. |

## Code

### Code for Sensor Node

The following code reads environmental parameters (temperature, humidity, light intensity, and air quality) and transmits the data wirelessly to the central system.

```c
#include <DHT.h>
#include <SPI.h>
#include <Wire.h>
#include <Xbee.h> // For Xbee module. If using NRF24L01, replace with appropriate library

// Pin setup
#define DHTPIN 2    // DHT sensor pin
#define LDRPIN A0   // LDR sensor pin
#define MQ135PIN A1 // MQ-135 sensor pin

DHT dht(DHTPIN, DHT22); // Initialise DHT22 sensor
Xbee xbee = Xbee();     // Initialise Xbee communication

void setup()
{
    // Start serial communication for debugging
    Serial.begin(9600);
    xbee.begin(9600);
    dht.begin();
    pinMode(LDRPIN, INPUT);   // Set LDR pin as input
    pinMode(MQ135PIN, INPUT); // Set MQ-135 pin as input
}

void loop()
{
    // Read temperature and humidity from DHT sensor
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();
    int lightIntensity = analogRead(LDRPIN); // Read light intensity from LDR
    int airQuality = analogRead(MQ135PIN);   // Read air quality from MQ-135

    // Check if the readings failed
    if (isnan(temperature) || isnan(humidity))
    {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }

    // Format the data to be sent (comma-separated)
    String data = String(temperature) + "," + String(humidity) + "," + String(lightIntensity) + "," + String(airQuality);

    // Send the data wirelessly via Xbee
    xbee.sendData(data.c_str());

    // Print the data to Serial Monitor for debugging
    Serial.println("Data Sent: " + data);

    // Wait for a short period before sending the next data
    delay(2000);
}

```

### Code for Central System

The central system will receive the data sent by the sensor node via Xbee or NRF24L01 and store it for visualisation on the PC. Here is the code for the central system using Arduino.

```c
#include <Xbee.h>

Xbee xbee = Xbee(); // Initialise Xbee communication

void setup()
{
    // Start serial communication for debugging
    Serial.begin(9600);
    xbee.begin(9600);
    Serial.println("Central system initialized. Waiting for data...");
}

void loop()
{
    // Check if data is available from the sensor node
    if (xbee.available())
    {
        String data = xbee.receiveData(); // Receive data from the sensor node
        // Print received data to Serial Monitor
        Serial.println("Received Data: " + data);

        // You can store or process the data as needed
        // For example, save it to a file or send it to the PC
    }

    delay(1000); // Wait for 1 second before checking again
}
```

## Receiving and Visualising Data on the PC

Once the data is received by the central system, it can be displayed using the Arduino IDE's Serial Monitor. To store the data for further processing, a Python script using PySerial can be employed to read from the Arduino's serial port and save the data to a file.

### Python script to store and visualise data

```python
import time
import matplotlib.pyplot as plt
import serial

# Set up serial connection to Arduino
ser = serial.Serial("COM3", 9600)  # Change 'COM3' to your Arduino's port
time.sleep(2)  # Wait for the serial connection to be established

# Create lists to store data for visualisation
temperatures = []
humidities = []
light_intensities = []
air_qualities = []


def read_data():
    while True:
        # Read a line of data from Arduino
        data = ser.readline().decode("utf-8").strip()

        if data:
            # Split the data into components
            temperature, humidity, light, air_quality = data.split(",")

            # Print the data
            print(
                f"Temperature: {temperature} °C, Humidity: {humidity} %, Light: {light}, Air Quality: {air_quality}"
            )

            # Store the data for later visualisation
            temperatures.append(float(temperature))
            humidities.append(float(humidity))
            light_intensities.append(int(light))
            air_qualities.append(int(air_quality))

            # Update the visualisation
            plot_data()


def plot_data():
    # Plot real-time data
    plt.clf()  # Clear the previous plot
    plt.subplot(2, 2, 1)
    plt.plot(temperatures, label="Temperature (°C)")
    plt.title("Temperature")

    plt.subplot(2, 2, 2)
    plt.plot(humidities, label="Humidity (%)")
    plt.title("Humidity")

    plt.subplot(2, 2, 3)
    plt.plot(light_intensities, label="Light Intensity")
    plt.title("Light Intensity")

    plt.subplot(2, 2, 4)
    plt.plot(air_qualities, label="Air Quality")
    plt.title("Air Quality")

    plt.tight_layout()
    plt.draw()
    plt.pause(0.1)


if __name__ == "__main__":
    plt.ion()  # Turn on interactive mode for real-time plotting
    read_data()
```

## Exercise Steps

1. **Set up the Sensor Node:**
   - Assemble the sensors (DHT22, LDR, and MQ-135) and connect them to the Arduino as per the schematic.
   - Connect the wireless communication module (Xbee/NRF24L01) to the Arduino.
   - Upload the provided Sensor Node code to the Arduino.

2. **Set up the Central System:**
   - Connect the wireless communication module to the central Arduino.
   - Upload the provided Central System code to the Arduino.

3. **Connect the Central Arduino to PC:**
   - Use a USB cable to connect the central Arduino to your PC for data transfer.

4. **Test Communication:**
   - Open the Serial Monitor in the Arduino IDE on the central system to check for incoming data.

5. **Visualise Data on PC:**
   - Install the required Python libraries (`matplotlib` and `pyserial`) on your PC.
   - Run the provided Python script to visualise the data in real-time.
