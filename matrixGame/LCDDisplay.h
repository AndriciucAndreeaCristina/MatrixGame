#ifndef LCDDISPLAY_H
#define LCDDISPLAY_H

class LCDDisplay {
private:
  LiquidCrystal lcd;
  int contrastValue;
  unsigned long lastUpdate;
  int scrollPos;
  const int scrollInterval = 150;
  const int displayHeight = 2;
  const int displayWidth = 16;
  unsigned long previousMillisIntro = 0;
public:
  LCDDisplay(int rs, int enable, int d4, int d5, int d6, int d7)
    : lcd(rs, enable, d4, d5, d6, d7) {
    pinMode(CONTRAST_PIN, OUTPUT);
    EEPROM.get(EEPROM_CONTRAST_ADDR, contrastValue);
    lcd.clear();
    analogWrite(CONTRAST_PIN, contrastValue);
    lcd.begin(16, 2);
    scrollPos = 0;
    lastUpdate = 0;
  }
  void printString(const String &str) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(str);
  }
  void printString(const String &str, int col, int row) {
    lcd.setCursor(col, row);
    lcd.print(str);
  }
  void LCDintroMenu() {
    
  }
};

#endif /*LCDDISPLAY_H*/