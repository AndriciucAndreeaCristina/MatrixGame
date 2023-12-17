#include "Constants.h"
#include <EEPROM.h>
#include <LiquidCrystal.h>
#include <ezButton.h>
#include "Joystick.h"
#include "LEDMatrix.h"
#include "LCDDisplay.h"

Joystick* joystick = Joystick::getJoystickInstance();
LEDMatrix ledMatrix(DIN, CLK, CS);

void setup() {
  Serial.begin(9600);
}

void loop() {
  joystick->updateButtonState();
  //matrix.setPixel(0, 0, 2); // Set the pixel at (0, 0) to 1
  ledMatrix.generateMap();
  ledMatrix.updateDisplay();
  delay(500);
}
