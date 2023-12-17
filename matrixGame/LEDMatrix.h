#ifndef LEDMATRIX_H
#define LEDMATRIX_H

class LEDMatrix {
private:
  LedControl lc;
  int brightnessValue;
  float wallProb = 0.1;
  int n = 8;
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
    for (int row = 0; row < 8; row++) {
      for (int col = 0; col < 8; col++) {
        lc.setLed(0, row, col, matrix[row][col]);
      }
    }
  }
};

#endif /*LEDMATRIX_H*/