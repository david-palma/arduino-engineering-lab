// Pin connected to the piezo buzzer
const int buzzerPin = 8;

// Define notes for the melody (frequency in Hz)
#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523

// Define the melody: "Jingle Bells"
int melody[] =
{
  NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4,
  NOTE_G4, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_F4, NOTE_F4,
  NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4,
  NOTE_D4, NOTE_D4, NOTE_E4, NOTE_D4, NOTE_G4
};

// Define note durations (4 = quarter note, 8 = eighth note, etc.)
int noteDurations[] =
{
  8, 8, 4, 8, 8, 4, 8, 8, 8, 8, 4, 8, 8, 8,
  8, 8, 8, 8, 8, 4, 8, 8, 8, 8, 8, 4
};

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
    int note = melody[i];           // Get the note (frequency in Hz)
    int duration = noteDuration[i]; // Get the note duration

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
  long delayValue = 1000000 / frequency / 2;     // Calculate delay for the high and low part of the wave
  long  numCycles = frequency * duration / 1000; // Calculate number of cycles for the given duration

  for (long i = 0; i < numCycles; i++)
  {
    digitalWrite(pin, HIGH); // Turn the buzzer on
    delayMicroseconds(delayValue);
    digitalWrite(pin, LOW);  // Turn the buzzer off
    delayMicroseconds(delayValue);
  }
}
