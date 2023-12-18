#ifndef BUZZER_H
#define BUZZER_H

extern bool sound;

class Buzzer {
private:
  const int notes[14] = { NOTE_E4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_E5, NOTE_D5, NOTE_C5,
                          NOTE_A4, NOTE_C5, NOTE_E5, NOTE_G5, NOTE_F5, NOTE_E5, NOTE_C5 };
  const int noteDuration = 200;
  const int pauseBetweenNotes = 100;

  unsigned long previousNoteMillis = 0;
  int currentNote = 0;
  bool notePlaying = false;

public:
  Buzzer() {
    pinMode(BUZZER_PIN, OUTPUT);
  }
  void playTone(int frequency, int duration) {
    tone(BUZZER_PIN, frequency, duration);
  }
  void stopTone() {
    noTone(BUZZER_PIN);
  }
  void playMelody() {
    unsigned long currentMillis = millis();

    if (currentMillis - previousNoteMillis >= (notePlaying ? noteDuration : pauseBetweenNotes)) {
      previousNoteMillis = currentMillis;

      if (notePlaying) {
        noTone(BUZZER_PIN);
        notePlaying = false;
      } else {
        tone(BUZZER_PIN, notes[currentNote]);
        notePlaying = true;
        currentNote++;

        if (currentNote >= sizeof(notes) / sizeof(notes[0])) {
          currentNote = 0;  // Restart the song
        }
      }
    }
  }
};

#endif /*BUZZER_H*/