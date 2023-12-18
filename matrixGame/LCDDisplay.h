#include "Arduino.h"
#include "EEPROM.h"
#include <string.h>
#ifndef LCDDISPLAY_H
#define LCDDISPLAY_H

extern Joystick joystick;
extern char currentPlayer[MAX_NAME_LENGTH + 1];
extern int playerNameLength;
extern int currentLetter;
extern int brightnessLCD;
extern int contrastLCD;
extern int difficultyLevel;
extern bool isSoundOn;
extern char *bestPlayers[3];
extern int bestScores[3];
extern LEDMatrix ledMatrix;

class LCDDisplay {
private:
  LiquidCrystal lcd;
  int contrastValue = 150;
  int scrollPosition = 0;
  const int scrollInterval = 300;
  int cursorLine;
  const char *menuItems[5] = { "Start", "Highscores", "Settings", "About", "How to Play" };
  const char *settingsItems[7] = { "Enter name", "Sound", "Dificulty", "LCD Brightness", "LCD Contrast", "LED Brightness", "BACK" };
  int itemCount;
  JoystickDirection lastDirection;

public:
  LCDDisplay(int rs, int enable, int d4, int d5, int d6, int d7)
    : lcd(rs, enable, d4, d5, d6, d7) {
    pinMode(CONTRAST_PIN, OUTPUT);
    EEPROM.get(eepromBrightnessLCD, brightnessLCD);
    analogWrite(D5, brightnessLCD);
    lcd.clear();
    cursorLine = -1;
    EEPROM.get(eepromContrastLCD, contrastLCD);
    for (int i = 0; i < 3; i++) {
      EEPROM.put(eepromPlayerNames + i * sizeof(bestPlayers[0]), bestPlayers[i]);
      EEPROM.put(eepromPlayerNames + 3 * sizeof(bestPlayers[0]) + i * sizeof(bestScores[0]), bestScores[i]);
    }
    EEPROM.get(eepromToggleSound, isSoundOn);
    contrastValue = contrastLCD;
    analogWrite(CONTRAST_PIN, contrastValue);
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("    WELCOME!    ");
    lcd.createChar(0, bombSymbol);
    EEPROM.get(eepromDificulty, difficultyLevel);
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
        lcd.print("                    ");
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

  void handleUp(JoystickDirection &lastDirection, const char *items[], int itemCount) {
    if (lastDirection != UP) {
      if (cursorLine > 0) {
        cursorLine--;
      }
      lcd.clear();
      printLine(0, items[cursorLine], true);
      if (cursorLine < itemCount - 1) {
        printLine(1, items[cursorLine + 1], false);
      }
      lastDirection = UP;
    }
  }

  void handleDown(JoystickDirection &lastDirection, const char *items[], int itemCount) {
    if (lastDirection != DOWN) {
      if (cursorLine < itemCount - 1) {
        cursorLine++;
      }
      lcd.clear();
      if (cursorLine > 0) {
        printLine(0, items[cursorLine - 1], false);
      }
      printLine(1, items[cursorLine], true);
    }
    lastDirection = DOWN;
  }

  void displayItems(JoystickDirection direction, const char *items[], int itemCount) {
    lastDirection = joystick.getJoystickLastDirection();
    if (cursorLine == -1) {
      lcd.clear();
      cursorLine = 0;
      printLine(cursorLine, items[cursorLine], true);
      printLine(cursorLine + 1, items[cursorLine + 1], false);
    }
    switch (direction) {
      case UP:
        handleUp(lastDirection, items, itemCount);
        break;
      case DOWN:
        handleDown(lastDirection, items, itemCount);
        break;
      default:
        lastDirection = CENTER;
        break;
    }
    joystick.setJoystickLastDirection(lastDirection);
  }
  void updateDisplayMenu(JoystickDirection direction) {
    itemCount = sizeof(menuItems) / sizeof(menuItems[0]);
    displayItems(direction, menuItems, itemCount);
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
    const char *instructions = "Move around using the joystick, collect the keys and avoid the bombs.";
    scrollableSecondLine("  How to play:  ", instructions);
  }

  void updateDisplaySettings(JoystickDirection direction) {
    itemCount = sizeof(settingsItems) / sizeof(settingsItems[0]);
    displayItems(direction, settingsItems, itemCount);
  }

  void enterName() {
    int offset = (DISPLAY_WIDTH - MAX_NAME_LENGTH) / 2;

    lcd.clear();
    lcd.setCursor(offset - 1, 0);
    lcd.print('<');
    lcd.print(currentPlayer);
    lcd.setCursor(DISPLAY_WIDTH - offset, 0);
    lcd.print('>');
    lcd.setCursor(1, 1);
    lcd.print("LPress to save!");
    lcd.setCursor(offset, 0);
    lcd.cursor();

    static int letterIndex = 0;
    char name[MAX_NAME_LENGTH + 1];
    strncpy(name, currentPlayer, MAX_NAME_LENGTH);

    for (int i = strlen(name); i < MAX_NAME_LENGTH; ++i) {
      name[i] = 'A';
    }
    name[MAX_NAME_LENGTH] = '\0';

    JoystickDirection direction = joystick.getJoystickDirection();
    if (direction == LEFT) {
      if (letterIndex > 0) {
        letterIndex--;
      }
    } else if (direction == RIGHT) {
      if (letterIndex < MAX_NAME_LENGTH - 1) {
        letterIndex++;
      } else if (letterIndex == MAX_NAME_LENGTH) {
        lcd.setCursor(0, 1);
        lcd.print(">");
      }
    } else if (direction == UP) {
      if (name[letterIndex] < 'Z') {
        name[letterIndex]++;
      }
    } else if (direction == DOWN) {
      if (name[letterIndex] > 'A') {
        name[letterIndex]--;
      }
    }
    strncpy(currentPlayer, name, MAX_NAME_LENGTH + 1);
    lcd.setCursor(offset + letterIndex, 0);
    lcd.print(name[letterIndex]);
    lcd.blink();
    delay(200);

    for (int i = MAX_NAME_LENGTH; i >= 0; --i) {
      if (name[i] != ' ') {
        name[i + 1] = '\0';
        break;
      }
    }
    lcd.noCursor();
  }

  void matrixBrightnessControl(JoystickDirection direction) {
    static int prevBrightness = brightnessLED;
    static bool brightnessChanged = false;
    lcd.setCursor(0, 0);
    lcd.print("LED Brightness:");
    lcd.setCursor(5, 1);
    if (direction != CENTER) {
      if (!brightnessChanged) {
        if (direction == LEFT) {
          if (brightnessLED > 1) {
            brightnessLED -= stepBrightLED;
            brightnessChanged = true;
          }
        } else if (direction == RIGHT) {
          if (brightnessLED < 16) {
            brightnessLED += stepBrightLED;
            brightnessChanged = true;
          }
        }
      }
    } else {
      brightnessChanged = false;
    }

    if (prevBrightness != brightnessLED) {
      lcd.print(brightnessLED);
      ledMatrix.setIntensity(brightnessLED);
      EEPROM.put(eepromBrightnessLED, brightnessLED);
      prevBrightness = brightnessLED;
    } else {
      lcd.print(brightnessLED);
    }
  }

  void lcdBrightnessControl(JoystickDirection direction) {
    static int prevBrightness = brightnessLCD;
    static bool brightnessChanged = false;

    lcd.setCursor(0, 0);
    lcd.print("LCD Brightness:");
    lcd.setCursor(5, 1);

    if (direction != CENTER) {
      if (!brightnessChanged) {
        if (direction == LEFT) {
          if (brightnessLCD > 1) {
            brightnessLCD -= stepBrightLCD;
            brightnessChanged = true;
          }
        } else if (direction == RIGHT) {
          if (brightnessLCD < 255) {
            brightnessLCD += stepBrightLCD;
            brightnessChanged = true;
          }
        }
      }
    } else {
      brightnessChanged = false;
    }

    if (prevBrightness != brightnessLCD) {
      lcd.print("  ");
      lcd.setCursor(5, 1);
      lcd.print(brightnessLCD);
      analogWrite(D5, brightnessLCD);
      EEPROM.put(eepromBrightnessLCD, brightnessLCD);
      prevBrightness = brightnessLCD;
    } else {
      lcd.print("  ");
      lcd.setCursor(5, 1);
      lcd.print(brightnessLCD);
    }
  }

  void lcdContrastControl(JoystickDirection direction) {
    static int prevContrast = contrastLCD;
    static bool contrastChanged = false;

    lcd.setCursor(0, 0);
    lcd.print("LCD Contrast:");
    lcd.setCursor(5, 1);

    if (direction != CENTER) {
      if (!contrastChanged) {
        if (direction == LEFT) {
          if (contrastLCD > 5) {
            contrastLCD -= stepContrast;
            contrastChanged = true;
          }
        } else if (direction == RIGHT) {
          if (contrastLCD < 200) {
            contrastLCD += stepContrast;
            contrastChanged = true;
          }
        }
      }
    } else {
      contrastChanged = false;
    }
    lcd.print("  ");
    lcd.setCursor(5, 1);
    lcd.print(contrastLCD);
    if (prevContrast != contrastLCD) {

      analogWrite(CONTRAST_PIN, contrastLCD);
      EEPROM.put(eepromContrastLCD, contrastLCD);
      prevContrast = contrastLCD;
    }
  }

  void displayHighscores(JoystickDirection direction) {
    static int cursorLine = -1;  // Initialize cursorLine as a static variable

    switch (direction) {
      case UP:
        if (direction != joystick.getJoystickLastDirection() && cursorLine > 0) {
          cursorLine--;
        }
        break;

      case DOWN:
        if (direction != joystick.getJoystickLastDirection() && cursorLine < 2) {
          cursorLine++;
        }
        break;

      default:
        break;
    }

    if (cursorLine == -1) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Best scores:");
      cursorLine = 0;
      printPlayerScore(cursorLine);
    } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Best scores:");
      printPlayerScore(cursorLine);
    }

    joystick.setJoystickLastDirection(direction);
  }

  void printPlayerScore(int line) {
    lcd.setCursor(0, 1);
    lcd.print(bestPlayers[line]);
    lcd.setCursor(10, 1);
    lcd.print(bestScores[line]);
    EEPROM.put(eepromPlayerNames + line * sizeof(bestPlayers[0]), bestPlayers[line]);
    EEPROM.put(eepromPlayerNames + 3 * sizeof(bestPlayers[0]) + line * sizeof(bestScores[0]), bestScores[line]);
    delay(5);
  }
  void toggleSound(JoystickDirection direction) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sound: ");

    if (direction == RIGHT) {
      isSoundOn = true;
      lcd.print("ON");
    } else if (direction == LEFT) {
      isSoundOn = false;
      lcd.print("OFF");
    } else {
      // For other joystick movements, keep the current status displayed
      lcd.print(isSoundOn ? "ON" : "OFF");
    }
    EEPROM.put(eepromToggleSound, isSoundOn);
    delay(5);
  }
  void displayDifficultyLevel(JoystickDirection direction) {
    static JoystickDirection lastDirection = joystick.getJoystickLastDirection();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Difficulty:");

    if (direction != CENTER) {
      if (direction == RIGHT && difficultyLevel < 4 && lastDirection != RIGHT) {
        difficultyLevel++;
        lastDirection = RIGHT;
      } else if (direction == LEFT && difficultyLevel > 0 && lastDirection != LEFT) {
        difficultyLevel--;
        lastDirection = LEFT;
      }
    } else {
      lastDirection = CENTER;
    }

    lcd.setCursor(5, 1);
    lcd.print(difficultyLevel);
    EEPROM.put(eepromDificulty, difficultyLevel);
  }

  void gamePlay() {
    lcd.setCursor(0, 0);
    lcd.print("Walls left: ");
    lcd.print(" ");
    lcd.print(ledMatrix.getBricksLeft());
  }
};

#endif /*LCDDISPLAY_H*/