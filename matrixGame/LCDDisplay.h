#include <string.h>
#ifndef LCDDISPLAY_H
#define LCDDISPLAY_H

extern Joystick joystick;

class LCDDisplay {
private:
  LiquidCrystal lcd;
  int contrastValue;
  int scrollPosition = 0;
  const int scrollInterval = 300;
  int cursorLine;
  const char *menuItems[4] = { "Settings", "About", "How to Play", "Start" };
  const int itemCount = sizeof(menuItems) / sizeof(menuItems[0]);
  JoystickDirection lastDirection;

public:
  LCDDisplay(int rs, int enable, int d4, int d5, int d6, int d7)
    : lcd(rs, enable, d4, d5, d6, d7) {
    pinMode(CONTRAST_PIN, OUTPUT);
    EEPROM.get(EEPROM_CONTRAST_ADDR, contrastValue);
    lcd.clear();
    cursorLine = -1;
    analogWrite(CONTRAST_PIN, contrastValue);
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("    WELCOME!    ");
    lcd.createChar(0, bombSymbol);
  }

  void clear() {
    lcd.clear();
  }

  void scrollableSecondLine(const char *string1, const char *string2) {
    lcd.setCursor(0, 0);
    lcd.print(string1);
    unsigned long currentMillis = millis();
    static unsigned long previousMillis = 0;
    const long interval = 300;
    if (currentMillis - previousMillis >= scrollInterval) {
      previousMillis = currentMillis;
      lcd.setCursor(0, 1);

      int messageLength = strlen(string2);
      if (scrollPosition >= 0 && scrollPosition < messageLength) {
        lcd.print(&string2[scrollPosition]);
        if (scrollPosition + 16 < messageLength) {
          scrollPosition++;
        } else {
          scrollPosition = -1;
        }
      } else {
        lcd.print("                    ");  // Clear line
        scrollPosition = 0;
      }
    }
  }

  void updateDisplayIntro() {
    scrollableSecondLine("    WELCOME!    ", "Press the joystick button to continue!");
  }
  void printLine(int line, const char *text, bool isSelected) {
    lcd.setCursor(0, line);
    if (isSelected) {
      lcd.print("->");
    } else {
      lcd.print("  ");
    }
    lcd.print(text);
  }

  void handleUp(JoystickDirection &lastDirection) {
    if (lastDirection != UP) {
      if (cursorLine > 0) {
        cursorLine--;
      }
      lcd.clear();
      printLine(0, menuItems[cursorLine], true);
      if (cursorLine < itemCount - 1) {
        printLine(1, menuItems[cursorLine + 1], false);
      }
      lastDirection = UP;
    }
  }

  void handleDown(JoystickDirection &lastDirection) {
    if (lastDirection != DOWN) {
      if (cursorLine < itemCount - 1) {
        cursorLine++;
      }
      lcd.clear();
      if (cursorLine > 0) {
        printLine(0, menuItems[cursorLine - 1], false);
      }
      printLine(1, menuItems[cursorLine], true);
    }
    lastDirection = DOWN;
  }

  void updateDisplayMenu(JoystickDirection direction) {
    lastDirection = joystick.getJoystickLastDirection();
    if (cursorLine == -1) {
      lcd.clear();
      cursorLine = 0;
      printLine(cursorLine, menuItems[cursorLine], true);
      printLine(cursorLine + 1, menuItems[cursorLine + 1], false);
    }
    switch (direction) {
      case UP:
        handleUp(lastDirection);
        break;
      case DOWN:
        handleDown(lastDirection);
        break;
      default:
        lastDirection = CENTER;
        break;
    }
    joystick.setJoystickLastDirection(lastDirection);
  }
  int getMenuItemIndex() {
    return cursorLine;
  }
  void resetCursorLine() {
    cursorLine = -1;
  }
  
  void updateAbout() {
    lcd.setCursor(0, 0);
    lcd.print(aboutText1);
    lcd.write((uint8_t)0);
    scrollableSecondLine(aboutText1, aboutText2);
  }

  void updateHowToPlay() {
    const char* instructions = "Move around using the joystick, collect the keys and avoid the bombs.";
    scrollableSecondLine("  How to play:  ", instructions);
  }
};

#endif /*LCDDISPLAY_H*/