#ifndef BUZZER_H
#define BUZZER_H

class Buzzer {
private:
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
};

#endif /*BUZZER_H*/