#include "Constants.h"
#include <EEPROM.h>
#include <LiquidCrystal.h>
#include <LedControl.h>
#include <ezButton.h>
#include "Joystick.h"
#include "LEDMatrix.h"
#include "LCDDisplay.h"
#include "Buzzer.h"
#include "RGBLed.h"

Joystick joystick;
LEDMatrix ledMatrix(DIN, CLK, CS);
static LCDDisplay lcd(RS, EN, D4, D5, D6, D7);
Buzzer buzzer;
RGBLed rgbLed;

#include "Menu.h"
Menu* menu = Menu::getMenuInstance();

void setup() {
  Serial.begin(9600);
}

void loop() {
  joystick.updateButtonState();
  menu->handleStates();
}
