#ifndef LEDMATRIX_H
#define LEDMATRIX_H
#include "RGBLed.h"

extern int brightnessLED;
extern int difficultyLevel;
extern Joystick joystick;
RGBLed rgbLed;

class LEDMatrix {
private:
  LedControl lc;
  bool fastBlink = false;
  int n = 8;
  int brightnessValue;
  float wallProb;
  int row;
  int letter;
  int currentPositionColPlayer;
  int currentPositionRowPlayer;
  int keysLeft;
  int score;
  int viewTop = 0;
  int viewLeft = 0;
  unsigned long lastMoveTime = 0;
  unsigned long lastBlinkTime = 0;
  unsigned long lastBlinkTimeBomb = 0;
  bool blinkState = false;
  int bricks = 0;
  bool lost = false;
  bool won = false;
  bool blinkStateBomb = false;
  int blinkInterval = 0;
  const int blinkIntervalPlayer = 300;
  const int blinkIntervalBomb = 100;
  unsigned long flashStartTime = 0;
  unsigned long bombStartTime = 0;
  const int flashInterval = 2000;
  byte matrix[matrixSize][matrixSize] = {
    { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0 }
  };
  int bombPositionRow = 0;
  int bombPositionCol = 0;
  bool bombActive = false;
  bool flashState = false;
public:
  LEDMatrix(int dataPin, int clkPin, int csPin)
    : lc(dataPin, clkPin, csPin, 1) {
    lc.shutdown(0, false);
    EEPROM.get(eepromBrightnessLED, brightnessLED);
    brightnessValue = brightnessLED;
    lc.setIntensity(0, brightnessValue);
    lc.clearDisplay(0);
    row = 0;
    letter = 0;
    currentPositionRowPlayer = 1;
    currentPositionColPlayer = 1;
  }

  int getBricksLeft() {
    return bricks;
  }
  void setIntensity(int brightnessValue) {
    lc.setIntensity(0, brightnessValue);
  }
  void generateMap() {
    switch (difficultyLevel) {
      case 1:
        wallProb = 0.4;
        break;
      case 2:
        wallProb = 0.5;
        break;
      case 3:
        wallProb = 0.6;
        break;
      case 4:
        wallProb = 0.7;
        break;
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        float r = random(0, 100) / 100.0;
        if (r < wallProb && i != currentPositionRowPlayer && j != currentPositionColPlayer) {
          matrix[i][j] = 1;
          bricks++;
        } else {
          matrix[i][j] = 0;
        }
      }
    }
  }


  void updateDisplayIntro() {
    static long previousMillisIntro = 0;
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillisIntro >= LEDMatrixInterval) {
      previousMillisIntro = currentMillis;
      if (letter < textStartN) {
        lc.setRow(0, row, textStart[letter][row]);
        row++;
        if (row >= matrixSize) {
          row = 0;
          letter++;
          lc.clearDisplay(0);
        }
      } else {
        letter = 0;
        row = 0;
      }
    }
  }
  void staticFigure(byte fig[]) {
    lc.clearDisplay(0);
    for (int i = 0; i < matrixSize; i++) {
      lc.setRow(0, i, fig[i]);
    }
  }
  void updateDisplayMenu() {
    staticFigure(doubleSquare);
  }

  void updateAbout() {
    staticFigure(heartSymbol);
  }

  void updateHowToPlay() {
    staticFigure(questionMark);
  }

  void updateDisplaySettings() {
    staticFigure(logo);
  }

  void moveDot(JoystickDirection direction) {
    switch (direction) {
      case UP:
        if (currentPositionRowPlayer != 0 && (matrix[(currentPositionRowPlayer - 1) % n][currentPositionColPlayer] == 0)) {
          currentPositionRowPlayer = (currentPositionRowPlayer - 1) % n;
        }
        break;
      case DOWN:
        if (currentPositionRowPlayer != n - 1 && (matrix[(currentPositionRowPlayer + 1) % n][currentPositionColPlayer] == 0)) {
          currentPositionRowPlayer = (currentPositionRowPlayer + 1) % n;
        }
        break;
      case RIGHT:
        if (currentPositionColPlayer != 0 && (matrix[currentPositionRowPlayer][(currentPositionColPlayer - 1) % n] == 0)) {
          currentPositionColPlayer = (currentPositionColPlayer - 1) % n;
        }
        break;
      case LEFT:
        if (currentPositionColPlayer != n - 1 && (matrix[currentPositionRowPlayer][(currentPositionColPlayer + 1) % n] == 0)) {
          currentPositionColPlayer = (currentPositionColPlayer + 1) % n;
        }
        break;
      case CENTER:
        break;
    }
  }
  void blinkDot(bool state, int row, int col) {
    lc.setLed(0, row, col, state);
  }

  void updateDisplay() {
    if (!lost && !won) {
      for (int row = 0; row < matrixSize; row++) {
        for (int col = 0; col < matrixSize; col++) {
          lc.setLed(0, row, col, matrix[row][col]);
        }
      }
      lc.clearDisplay(0);
      blinkDot(blinkState, currentPositionRowPlayer, currentPositionColPlayer);
      blinkDot(blinkStateBomb, bombPositionRow, bombPositionCol);
      if (bombTimerUp()) {
        flashBomb();
        clearWalls();
        bombActive = false;
        fastBlink = false;
        blinkInterval = 100;
        blinkStateBomb = false;
        if (currentPositionRowPlayer == bombPositionRow || currentPositionColPlayer == bombPositionCol) {
          lost = true;
          systemState = END_LOSE;
          lc.clearDisplay(0);
          for (int row = 0; row < matrixSize; row++) {
            for (int col = 0; col < matrixSize; col++) {
              lc.setLed(0, row, col, endGame[row][col]);
            }
          }
        }
      }
    }
    if (won) {
      for (int row = 0; row < matrixSize; row++) {
        for (int col = 0; col < matrixSize; col++) {
          lc.setLed(0, row, col, happyFace[row][col]);
        }
      }
    }
  }
  void blinkBomb(bool state) {
    rgbLed.blinkColor(125, 125, 0, flashInterval);
    lc.setLed(0, bombPositionRow, bombPositionCol, state);
  }
  bool flashIntervalUp() {
    if (millis() > flashStartTime + flashInterval) {
      return true;
    } else {
      return false;
    }
  }
  bool bombTimerUp() {
    if (bombActive && millis() > bombStartTime + flashInterval) {
      return true;
    } else {
      return false;
    }
  }

  void flashBomb() {
    flashStartTime = millis();
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (i == bombPositionRow || j == bombPositionCol) {
          lc.setLed(0, i, j, true);
        }
      }
    }
    flashState = true;
    delay(5);
  }


  void clearWalls() {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (i == bombPositionRow || j == bombPositionCol) {
          if (matrix[i][j])
            bricks--;
          matrix[i][j] = 0;
        }
      }
    }
    if (bricks == 0) {
      won = true;
      systemState = END_WIN;
    }
    lc.clearDisplay(0);
  }
  void gamePlay() {
    joystick.updateButtonState();
    checkButton();
    if (millis() - lastMoveTime >= interval) {
      JoystickDirection direction = joystick.getJoystickDirection();
      moveDot(direction);
      lastMoveTime = millis();
    }
    if (millis() - lastBlinkTime >= interval * 3) {
      blinkState = !blinkState;
      lastBlinkTime = millis();
    }
    updateDisplay();
  }
  void checkButton() {
    if (joystick.isButtonShortPressed()) {
      Serial.println("A short press is detected");
      fastBlink = !fastBlink;
      if (fastBlink) {
        bombPositionRow = currentPositionRowPlayer;
        bombPositionCol = currentPositionColPlayer;
        bombStartTime = millis();
        bombActive = true;
      } else {
        bombPositionRow = 0;
        bombPositionCol = 0;
        bombActive = false;
      }
    }
    if (joystick.isButtonLongPressed()) {
      Serial.println("A long press is detected");
      if (lost || won) {
        lost = false;
        won = false;
        systemState = GAMEPLAY;
        bombPositionRow = 0;
        bombPositionCol = 0;
        currentPositionColPlayer = n / 2;
        currentPositionRowPlayer = n / 2;
        bricks = 0;
        initMatrix();
        generateMap();
      }
    }
  }
  void initMatrix() {
    lc.shutdown(0, false);
    lc.setIntensity(0, brightnessLED);
    lc.clearDisplay(0);
  }
};

#endif /*LEDMATRIX_H*/