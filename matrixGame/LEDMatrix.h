#ifndef LEDMATRIX_H
#define LEDMATRIX_H

class LEDMatrix {
private:
  LedControl lc;
  int brightnessValue;
  float wallProb;
  int row;
  int letter;
  byte matrix[8][8] = {
    { 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 1 }
  };

public:
  LEDMatrix(int dataPin, int clkPin, int csPin)
    : lc(dataPin, clkPin, csPin, 1) {
    lc.shutdown(0, false);
    lc.setIntensity(0, 8);
    lc.clearDisplay(0);
    wallProb = 0.5;
    row = 0;
    letter = 0;
  }
  void generateMap() {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        float r = random(0, 100) / 100.0;
        if (r < wallProb) {
          matrix[i][j] = 1;
        } else {
          matrix[i][j] = 0;
        }
      }
    }
  }
  void updateDisplay() {
    for (int row = 0; row < n; row++) {
      for (int col = 0; col < n; col++) {
        lc.setLed(0, row, col, matrix[row][col]);
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
        if (row >= n) {
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
  void updateDisplayMenu() {
    lc.clearDisplay(0);
    for (int i = 0; i < n; i++) {
      lc.setRow(0, i, doubleSquare[i]);
    }
  }
  void updateAbout() {
    lc.clearDisplay(0);
    for (int i = 0; i < n; i++) {
      lc.setRow(0, i, heartSymbol[i]);
    }
  }
  void updateHowToPlay() {
    lc.clearDisplay(0);
    for (int i = 0; i < n; i++) {
      lc.setRow(0, i, questionMark[i]);
    }
  }
};

#endif /*LEDMATRIX_H*/