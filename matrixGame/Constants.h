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
#define EEPROM_BRIGHTNESS_ADDR 20
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
const int n = 8;
const int textStartN = 5;
const int LEDMatrixInterval = 100;
const byte doubleSquare[n] = {
  0b11111111,
  0b11000011,
  0b10111101,
  0b10100101,
  0b10100101,
  0b10111101,
  0b11000011,
  0b11111111
};
const byte heartSymbol[8] = {
  B00000000,
  B01100110,
  B11111111,
  B11111111,
  B01111110,
  B00111100,
  B00011000,
  B00000000
};
const byte questionMark[8] = {
  B00111100,
  B01000010,
  B00100000,
  B00010000,
  B00001000,
  B00000000,
  B00001000,
  B00000000
};


/***************** LCDDISPLAY.H *****************/
#define RS 9
#define EN 8
#define D4 7
#define D5 6
#define D6 5
#define D7 4
#define CONTRAST_PIN 3
#define EEPROM_CONTRAST_ADDR 10
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


/***************** LED.H *****************/
#define BLUE_PIN A3
#define GREEN_PIN A4
#define RED_PIN A5

/***************** MENU.H *****************/
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
  MATRIX_BRIGHTNESS_CONTROL,
  SOUND,
  GAMEPLAY,
  END_LOSE,
  END_WIN
};
static States systemState = IDLE;

/***************** BUZZER.H *****************/
#define BUZZER_PIN A2
#define NOTE_B0 31
#define NOTE_C1 33
#define NOTE_CS1 35
#define NOTE_D1 37
#define NOTE_DS1 39
#define NOTE_E1 41
#define NOTE_F1 44
#define NOTE_FS1 46
#define NOTE_G1 49
#define NOTE_GS1 52
#define NOTE_A1 55
#define NOTE_AS1 58
#define NOTE_B1 62
#define NOTE_C2 65
#define NOTE_CS2 69
#define NOTE_D2 73
#define NOTE_DS2 78
#define NOTE_E2 82
#define NOTE_F2 87
#define NOTE_FS2 93
#define NOTE_G2 98
#define NOTE_GS2 104
#define NOTE_A2 110
#define NOTE_AS2 117
#define NOTE_B2 123
#define NOTE_C3 131
#define NOTE_CS3 139
#define NOTE_D3 147
#define NOTE_DS3 156
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_FS3 185
#define NOTE_G3 196
#define NOTE_GS3 208
#define NOTE_A3 220
#define NOTE_AS3 233
#define NOTE_B3 247
#define NOTE_C4 262
#define NOTE_CS4 277
#define NOTE_D4 294
#define NOTE_DS4 311
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_FS4 370
#define NOTE_G4 392
#define NOTE_GS4 415
#define NOTE_A4 440
#define NOTE_AS4 466
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_CS5 554
#define NOTE_D5 587
#define NOTE_DS5 622
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_FS5 740
#define NOTE_G5 784
#define NOTE_GS5 831
#define NOTE_A5 880
#define NOTE_AS5 932
#define NOTE_B5 988
#define NOTE_C6 1047
#define NOTE_CS6 1109
#define NOTE_D6 1175
#define NOTE_DS6 1245
#define NOTE_E6 1319
#define NOTE_F6 1397
#define NOTE_FS6 1480
#define NOTE_G6 1568
#define NOTE_GS6 1661
#define NOTE_A6 1760
#define NOTE_AS6 1865
#define NOTE_B6 1976
#define NOTE_C7 2093
#define NOTE_CS7 2217
#define NOTE_D7 2349
#define NOTE_DS7 2489
#define NOTE_E7 2637
#define NOTE_F7 2794
#define NOTE_FS7 2960
#define NOTE_G7 3136
#define NOTE_GS7 3322
#define NOTE_A7 3520
#define NOTE_AS7 3729
#define NOTE_B7 3951
#define NOTE_C8 4186
#define NOTE_CS8 4435
#define NOTE_D8 4699
#define NOTE_DS8 4978