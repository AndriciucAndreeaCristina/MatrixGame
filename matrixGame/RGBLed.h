#ifndef RGBLED_H
#define RGBLED_H

class RGBLed {
private:
  unsigned long lastBlinkTime;
  bool isOn;
public:
  RGBLed() {
    pinMode(RED_PIN, OUTPUT);
    pinMode(GREEN_PIN, OUTPUT);
    pinMode(BLUE_PIN, OUTPUT);
  }
  void setColor(int red, int green, int blue) {
    analogWrite(RED_PIN, red);
    analogWrite(GREEN_PIN, green);
    analogWrite(BLUE_PIN, blue);
  }
  void blinkColor(int red, int green, int blue, int blinkInterval) {
    unsigned long currentMillis = millis();
    if (currentMillis - lastBlinkTime >= blinkInterval) {
      lastBlinkTime = currentMillis;
      if (isOn) {
        setColor(0, 0, 0);  
        isOn = false;
      } else {
        setColor(red, green, blue); 
        isOn = true;
      }
    }
  }
};

#endif /*RGBLED_H*/