# Arduino programming
# Exercise n. 06 - data visualisation

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
