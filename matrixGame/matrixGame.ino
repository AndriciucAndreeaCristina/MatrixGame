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

char* bestPlayers[3] = { "NONAME1", "NONAME2", "NONAME3" };
int bestScores[3] = { 0, 0, 0 };
char currentPlayer[MAX_NAME_LENGTH + 1];
int playerNameLength = 0;
int currentLetter = 'A';
int brightnessLED;
int brightnessLCD;
int contrastLCD;
bool isSoundOn;
int difficultyLevel;
static Joystick joystick;
static LEDMatrix ledMatrix(DIN, CLK, CS);
static LCDDisplay lcd(RS, EN, D4, D5, D6, D7);
Buzzer buzzer;


void setup() {
  ledMatrix.initMatrix();
  ledMatrix.generateMap();
  Serial.begin(9600);
}


#include "Menu.h"
static Menu* menu = Menu::getMenuInstance();


void loop() {
  joystick.updateButtonState();
  menu->handleStates();
  if (isSoundOn) {
    buzzer.playMelody();
  }
}

