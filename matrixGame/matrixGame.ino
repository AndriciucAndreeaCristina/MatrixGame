#include "Constants.h"
#include <EEPROM.h>
#include <LiquidCrystal.h>
#include <LedControl.h>
#include <ezButton.h>
#include "Joystick.h"
#include "LEDMatrix.h"
#include "LCDDisplay.h"

Joystick* joystick = Joystick::getJoystickInstance();
LEDMatrix ledMatrix(DIN, CLK, CS);
LCDDisplay lcd(RS, EN, D4, D5, D6, D7);

void setup() {
  Serial.begin(9600);
}

void loop() {
  joystick->updateButtonState();
  ledMatrix.generateMap();
  ledMatrix.updateDisplay();
  lcd.printString("Hello, world!");
  delay(1000);
  lcd.printString("Arduino", 0, 1);
  delay(1000);
}
