import librosa
import librosa.display
import matplotlib.pyplot as plt
import numpy as np
import sounddevice as sd
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
