# Exercise 07

This exercise involves generating a Christmas melody using a piezo buzzer connected to an Arduino board. The melody will be played and recorded for further analysis. The recorded sound will be analysed using Python to gain insights into its time-domain and frequency-domain characteristics, along with a visual representation of its spectrogram and chromatic spectrum.

The main objectives of the exercise are as follows:

- Generate a Christmas melody, "Jingle Bells," using an Arduino and a piezo buzzer.
- Play the melody and record the sound using a microphone connected to a PC.
- Perform signal analysis using Python to visualise the waveform, frequency spectrum (FFT), and spectrogram.
- Display the chromatic spectrum to analyse the musical notes and their intensities over time.

## Explanation of the Process

### Melody Generation

- The **Arduino** generates the "Jingle Bells" melody using predefined frequencies for each note.
- A **piezo buzzer** connected to **Pin 8** and **GND** plays the melody.
- The melody is created by looping through an array of notes and using the `tone()` function to generate the appropriate frequencies.

### Recording the Melody

- A microphone is used to record the sound produced by the piezo buzzer during playback.
- The recording is stored as a **WAV file** using Python for subsequent analysis.

### Signal Analysis

- A **Python script** is used to process the recorded melody and extract insights:
    - **Time-domain visualisation**: Displays the waveform of the melody to understand how the signal varies over time.
    - **Frequency-domain analysis**: Calculates the Fast Fourier Transform (FFT) to examine the frequency components of the melody.
    - **Spectrogram visualisation**: Shows how the frequency content of the melody evolves over time.
    - **Chromatic spectrum analysis**: Identifies the intensities of musical notes in the melody and displays them graphically.

## Tools Required

- Arduino Uno (or any compatible board)
- Piezo buzzer
- Breadboard
- Jumper wires
- A computer with Python and the following libraries installed:
    - `numpy`
    - `matplotlib`
    - `sounddevice`
    - `librosa`
    - `scipy`

## Schematic Description

| **Component** | **Arduino Pin** | **Description**                   |
| ------------- | --------------- | --------------------------------- |
| Piezo buzzer  | Pin 8           | Plays the melody                  |
| GND           | GND             | Connects the ground of the buzzer |

## Code

### Arduino Code

This Arduino code generates a simple "Jingle Bells" melody using a piezo buzzer.

```c
// Pin connected to the piezo buzzer
const int buzzerPin = 8;

// Define notes for the melody (frequency in Hz)
#define NOTE_C4 262
#define NOTE_D4 294
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_G4 392
#define NOTE_A4 440
#define NOTE_B4 494
#define NOTE_C5 523

// Define the melody: "Jingle Bells"
int melody[] =
    {
        NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4,
        NOTE_G4, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_F4, NOTE_F4,
        NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4,
        NOTE_D4, NOTE_D4, NOTE_E4, NOTE_D4, NOTE_G4};

// Define note durations (4 = quarter note, 8 = eighth note, etc.)
int noteDurations[] =
    {
        8, 8, 4, 8, 8, 4, 8, 8, 8, 8, 4, 8, 8, 8,
        8, 8, 8, 8, 8, 4, 8, 8, 8, 8, 8, 4};

// Number of notes
int numberOfNotes = sizeof(melody) / sizeof(melody[0]);

void setup()
{
    // Set the buzzer pin as an output
    pinMode(buzzerPin, OUTPUT);
}

void loop()
{
    for (int i = 0; i < numberOfNotes; i++)
    {
        int note = melody[i];            // Get the note (frequency in Hz)
        int duration = noteDurations[i]; // Get the note duration

        // Play the note
        tone(buzzerPin, note, duration);
        delay(duration * 1.30); // Pause between notes (slightly longer than note duration)
    }

    // Add a delay before repeating the melody
    delay(1000);
}

// Function to play the tone on the buzzer
void tone(int pin, int frequency, int duration)
{
    long delayValue = 1000000 / frequency / 2;    // Calculate delay for the high and low part of the wave
    long numCycles = frequency * duration / 1000; // Calculate number of cycles for the given duration

    for (long i = 0; i < numCycles; i++)
    {
        digitalWrite(pin, HIGH); // Turn the buzzer on
        delayMicroseconds(delayValue);
        digitalWrite(pin, LOW); // Turn the buzzer off
        delayMicroseconds(delayValue);
    }
}
```

## Python Code for Analysis

The Python script records the melody and performs the following analyses:

- **Time Domain**: Displays the waveform.
- **Frequency Domain**: Computes the Fast Fourier Transform (FFT).
- **Spectrogram**: Shows how the frequencies vary over time.
- **Pitch and Chromatic Spectrum**: Visualises the intensity of musical notes.

```python
import numpy as np
import matplotlib.pyplot as plt
import sounddevice as sd
import librosa
import librosa.display
from scipy.fft import fft
from scipy.io.wavfile import write

# Record audio
duration = 10  # Recording duration in seconds
samplerate = 48000  # Sampling rate in Hz
print("Recording...")
audio = sd.rec(int(duration * samplerate), samplerate=samplerate, channels=1)
sd.wait()
print("Recording finished.")

# Save audio as a WAV file
write("xmas_melody.wav", samplerate, (audio * 32767).astype(np.int16))

# Load audio for analysis
y, sr = librosa.load("xmas_melody.wav")

# Time Domain: Plot waveform
plt.figure(figsize=(10, 4))
librosa.display.waveshow(y, sr=sr)
plt.title("Waveform of the Melody")
plt.xlabel("Time (s)")
plt.ylabel("Amplitude")
plt.grid()
plt.show()

# Frequency Domain: FFT
Y = fft(y)
frequencies = np.linspace(0, sr, len(Y))
magnitude = np.abs(Y)
plt.figure(figsize=(10, 4))
plt.plot(frequencies[: len(frequencies) // 2], magnitude[: len(magnitude) // 2])
plt.title("Frequency Spectrum (FFT)")
plt.xlabel("Frequency (Hz)")
plt.ylabel("Magnitude")
plt.grid()
plt.show()

# Spectrogram
plt.figure(figsize=(10, 4))
D = librosa.amplitude_to_db(np.abs(librosa.stft(y)), ref=np.max)
librosa.display.specshow(D, sr=sr, x_axis="time", y_axis="log", cmap="magma")
plt.colorbar(format="%+2.0f dB")
plt.title("Spectrogram")
plt.xlabel("Time (s)")
plt.ylabel("Frequency (Hz)")
plt.show()

# Chromatic Spectrum
C = librosa.feature.chroma_stft(y=y, sr=sr)
plt.figure(figsize=(10, 4))
librosa.display.specshow(C, x_axis="time", y_axis="chroma", cmap="cool")
plt.colorbar()
plt.title("Chromatic Spectrum")
plt.xlabel("Time (s)")
plt.ylabel("Note")
plt.show()
```

## Exercise Steps

1. **Assemble the Circuit:**

    - Connect the piezo buzzer to **Pin 8** and **GND** on the Arduino board.
    - Ensure all connections are secure on the breadboard.

2. **Upload the Arduino Code:**

    - Open the Arduino IDE on your PC.
    - Copy the provided Arduino code into the IDE and verify it to ensure there are no errors.
    - Connect your Arduino to the PC via USB and upload the code.

3. **Prepare for Recording:**

    - Set up a microphone connected to your PC.
    - Ensure the microphone is configured as the default recording device in your system's audio settings.

4. **Play and Record the Melody:**

    - Once the Arduino code is uploaded, the buzzer will start playing "Jingle Bells."
    - Simultaneously, run the Python script to record the sound. The script will save the recording as a WAV file.

5. **Analyse the Recorded Melody:**

    - Run the Python script to process and analyse the recorded audio.
    - Observe the visualisations, including:
        - Waveform of the melody in the time domain.
        - Frequency spectrum (FFT) showing the dominant frequencies.
        - Spectrogram showing frequency variation over time.
        - Chromatic spectrum highlighting the musical notes.

6. **Review the Results:**

    - Evaluate the graphical outputs for insights into the melody's characteristics.
    - Optionally, modify the Arduino code to change the melody and repeat the analysis.
