/**
*  Constants.h - All the constants in the game, like arduino pins, thresholds, delay intervals etc
*/


/***************** JOYSTICK.H *****************/
#define JOYSTICK_X A0
#define JOYSTICK_Y A1
#define JOYSTICK_SW 2
#define JOYSTICK_MIN_THRESHOLD 200
#define JOYSTICK_MAX_THRESHOLD 800
#define SHORT_PRESS_TIME 300
#define LONG_PRESS_TIME 800
enum JoystickDirection {
  LEFT,
  RIGHT,
  UP,
  DOWN,
  CENTER
};

/***************** LEDMATRIX.H *****************/
#define DIN 12
#define CS 11
#define CLK 10
const uint8_t textStart[][8] = {
  { 0b00000000,
    0b00011000,
    0b00100100,
    0b00001100,
    0b00110000,
    0b00100100,
    0b00001000,
    0b00000000 },
  { 0b00000000,
    0b01111100,
    0b00010000,
    0b00010000,
    0b00010000,
    0b00010000,
    0b00000000,
    0b00000000 },
  { 0b00000000,
    0b00111100,
    0b00100100,
    0b00100100,
    0b00111100,
    0b00100100,
    0b00100100,
    0b00000000 },
  { 0b00000000,
    0b00111100,
    0b00100100,
    0b00111100,
    0b00001100,
    0b00010100,
    0b00100100,
    0b00000000 },
  { 0b00000000,
    0b01111100,
    0b00010000,
    0b00010000,
    0b00010000,
    0b00010000,
    0b00000000,
    0b00000000 }
};
const int matrixSize = 8;
const int textStartN = 5;
const int LEDMatrixInterval = 100;
const byte doubleSquare[matrixSize] = {
  0b11111111,
  0b11000011,
  0b10111101,
  0b10100101,
  0b10100101,
  0b10111101,
  0b11000011,
  0b11111111
};
const byte heartSymbol[matrixSize] = {
  B00000000,
  B01100110,
  B11111111,
  B11111111,
  B01111110,
  B00111100,
  B00011000,
  B00000000
};
const byte questionMark[matrixSize] = {
  B00111100,
  B01000010,
  B00100000,
  B00010000,
  B00001000,
  B00000000,
  B00001000,
  B00000000
};

const byte logo[matrixSize] = {
  B00111100,
  B01111110,
  B11011011,
  B11011011,
  B11011011,
  B01111110,
  B00111100,
  B00000000
};
byte endGame[matrixSize][matrixSize] = {
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 0, 1, 0, 0, 0, 0, 1, 0 },
  { 0, 0, 1, 0, 0, 1, 0, 0 },
  { 0, 0, 0, 1, 1, 0, 0, 0 },
  { 0, 0, 0, 1, 1, 0, 0, 0 },
  { 0, 0, 1, 0, 0, 1, 0, 0 },
  { 0, 1, 0, 0, 0, 0, 1, 0 },
  { 1, 0, 0, 0, 0, 0, 0, 1 }
};
byte happyFace[matrixSize][matrixSize] = {
  { 0, 0, 1, 1, 1, 1, 0, 0 },
  { 0, 1, 0, 0, 0, 0, 1, 0 },
  { 1, 0, 1, 0, 0, 1, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 1, 0, 0, 1, 0, 1 },
  { 1, 0, 0, 1, 1, 0, 0, 1 },
  { 0, 1, 0, 0, 0, 0, 1, 0 },
  { 0, 0, 1, 1, 1, 1, 0, 0 }
};
#define eepromBrightnessLED 0
#define eepromBrightnessLCD 2
#define eepromContrastLCD 4
#define eepromPlayerNames 6
#define eepromToggleSound 100
#define eepromDificulty 104

/***************** LCDDISPLAY.H *****************/
#define RS 9
#define EN 8
#define D4 7
#define D5 6
#define D6 5
#define D7 4
#define CONTRAST_PIN 3
#define DISPLAY_WIDTH 16
const char *aboutText1 = "   Bomberman";
const char *aboutText2 = "Author/Github: AndriciucAndreeaCristina";
const byte bombSymbol[8] = {
  0b00001,
  0b00010,
  0b00100,
  0b01110,
  0b11111,
  0b11111,
  0b11111,
  0b01110
};
const int interval = 100;
const int squareCount = 10;
const int stepBrightLED = 1;
const int stepBrightLCD = 10;
const int stepContrast = 5;


/***************** LED.H *****************/
#define BLUE_PIN A3
#define GREEN_PIN A4
#define RED_PIN A5

/***************** MENU.H *****************/
#define MAX_NAME_LENGTH 6
enum States {
  IDLE,
  START,
  MENU,
  ABOUT,
  HOW_TO_PLAY,
  HIGHSCORES,
  SETTINGS,
  ENTER_NAME,
  LCD_BRIGHTNESS_CONTROL,
  LCD_CONTRAST_CONTROL,
  MATRIX_BRIGHTNESS_CONTROL,
  SOUND,
  DIFICULTY,
  GAMEPLAY,
  END_LOSE,
  END_WIN
};
static States systemState = IDLE;


/***************** BUZZER.H *****************/
#define BUZZER_PIN A2
#define NOTE_E4 330
#define NOTE_A4 440
#define NOTE_B4 494
#define NOTE_E5 659
#define NOTE_D5 587
#define NOTE_C5 523
#define NOTE_G5 784
#define NOTE_F5 698
#define NOTE_G4 392
