#ifndef LCDDISPLAY_H
#define LCDDISPLAY_H

class LCDDisplay {
private:
  LiquidCrystal lcd;
  int contrastValue;
public:
  LCDDisplay(int rs, int enable, int d4, int d5, int d6, int d7)
    : lcd(rs, enable, d4, d5, d6, d7) {
    pinMode(CONTRAST_PIN, OUTPUT);
    EEPROM.get(EEPROM_CONTRAST_ADDR, contrastValue);
    lcd.clear();
    lcd.noCursor();
    lcd.noAutoscroll();
    analogWrite(CONTRAST_PIN, contrastValue);
    lcd.begin(16, 2);
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
};

#endif /*LCDDISPLAY_H*/