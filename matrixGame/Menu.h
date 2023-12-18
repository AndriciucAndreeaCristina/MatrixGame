#include "EEPROM.h"
#include "HardwareSerial.h"
#ifndef MENU_H
#define MENU_H

class Menu {
private:
  static Menu* menuInstance;
  bool generate = true;
  Menu() {
    systemState = IDLE;
  }
public:
  static Menu* getMenuInstance() {
    if (menuInstance == nullptr) {
      menuInstance = new Menu();
    }

    return menuInstance;
  }

  void handleStates() {
    switch (systemState) {
      case IDLE:
        {
          lcd.updateDisplayIntro();
          ledMatrix.updateDisplayIntro();
          if (joystick.isButtonShortPressed()) {
            systemState = MENU;
          }
          break;
        }
      case MENU:
        {
          JoystickDirection direction = joystick.getJoystickDirection();
          ledMatrix.updateDisplayMenu();
          lcd.updateDisplayMenu(direction);
          joystick.updateButtonState();
          if (joystick.isButtonShortPressed()) {
            int choice = lcd.getMenuItemIndex();
            Serial.println(choice);
            lcd.clear();
            switch (choice) {
              case 0:
                systemState = START;
                break;
              case 1:
                systemState = HIGHSCORES;
                break;
              case 2:
                systemState = SETTINGS;
                break;
              case 3:
                systemState = ABOUT;
                break;
              case 4:
                systemState = HOW_TO_PLAY;
                break;
              default:
                break;
            }
            lcd.resetCursorLine();
          }
          break;
        }
      case START:
        {
          lcd.clear();
          ledMatrix.gamePlay();
          break;
        }
      case HOW_TO_PLAY:
        {
          Serial.println("HOW_TO_PLAY");
          lcd.updateHowToPlay();
          ledMatrix.updateHowToPlay();
          joystick.updateButtonState();
          if (joystick.isButtonShortPressed()) {
            lcd.resetCursorLine();
            systemState = MENU;
          }
          break;
        }
      case ABOUT:
        {
          Serial.println("About");
          ledMatrix.updateAbout();
          lcd.updateAbout();
          joystick.updateButtonState();
          if (joystick.isButtonShortPressed()) {
            lcd.resetCursorLine();
            systemState = MENU;
          }
          break;
        }
      case HIGHSCORES:
        {
          lcd.resetCursorLine();
          JoystickDirection direction = joystick.getJoystickDirection();
          lcd.clear();
          lcd.displayHighscores(direction);
          if (joystick.isButtonShortPressed()) {
            lcd.resetCursorLine();
            systemState = MENU;
          }
          break;
        }
      case SETTINGS:
        {
          Serial.println("Menu Settings");
          JoystickDirection direction = joystick.getJoystickDirection();
          lcd.updateDisplaySettings(direction);
          ledMatrix.updateDisplaySettings();
          joystick.updateButtonState();
          if (joystick.isButtonShortPressed()) {
            /* "Enter name", "Sound", "Dificulty", "LCD Brightness", "LCD Contrast", "LED Brightness" };*/
            int choice = lcd.getMenuItemIndex();
            Serial.println(choice);
            lcd.clear();
            switch (choice) {
              case 0:
                systemState = ENTER_NAME;
                break;
              case 1:
                systemState = SOUND;
                break;
              case 2:
                systemState = DIFICULTY;
                break;
              case 3:
                systemState = LCD_BRIGHTNESS_CONTROL;
                break;
              case 4:
                systemState = LCD_CONTRAST_CONTROL;
                break;
              case 5:
                systemState = MATRIX_BRIGHTNESS_CONTROL;
                break;
              case 6:
                systemState = MENU;
                break;
              default:
                break;
            }
            lcd.resetCursorLine();
          }
          break;
        }
      case ENTER_NAME:
        {
          lcd.clear();
          lcd.enterName();
          joystick.updateButtonState();
          if (joystick.isButtonLongPressed()) {
            lcd.resetCursorLine();
            systemState = SETTINGS;
          }
          break;
        }
      case LCD_BRIGHTNESS_CONTROL:
        {
          lcd.clear();
          JoystickDirection direction = joystick.getJoystickDirection();
          lcd.lcdBrightnessControl(direction);
          joystick.updateButtonState();
          if (joystick.isButtonShortPressed()) {
            lcd.resetCursorLine();
            systemState = SETTINGS;
          }
          break;
        }
      case LCD_CONTRAST_CONTROL:
        {
          lcd.clear();
          JoystickDirection direction = joystick.getJoystickDirection();
          lcd.lcdContrastControl(direction);
          joystick.updateButtonState();
          if (joystick.isButtonShortPressed()) {
            lcd.resetCursorLine();
            systemState = SETTINGS;
          }
          break;
        }
      case MATRIX_BRIGHTNESS_CONTROL:
        {
          lcd.clear();
          JoystickDirection direction = joystick.getJoystickDirection();
          lcd.matrixBrightnessControl(direction);
          Serial.println("MATRIX_BRIGHTNESS_CONTROL");
          joystick.updateButtonState();
          if (joystick.isButtonShortPressed()) {
            lcd.resetCursorLine();
            systemState = SETTINGS;
          }
          break;
        }
      case SOUND:
        {
          lcd.clear();
          JoystickDirection direction = joystick.getJoystickDirection();
          lcd.toggleSound(direction);
          joystick.updateButtonState();
          if (joystick.isButtonShortPressed()) {
            lcd.resetCursorLine();
            systemState = SETTINGS;
          }
          break;
        }
      case GAMEPLAY:
        {
          
          lcd.printLine(0, "Walls left:  ", false);
          int bricks = ledMatrix.getBricksLeft();
          char* nr = (char*)bricks;
          lcd.printLine(1, nr, false);
          lcd.gamePlay();
          ledMatrix.gamePlay();
          
          break;
        }
      case DIFICULTY:
        {
          lcd.clear();
          JoystickDirection direction = joystick.getJoystickDirection();
          lcd.displayDifficultyLevel(direction);
          joystick.updateButtonState();
          if (joystick.isButtonShortPressed()) {
            lcd.resetCursorLine();
            systemState = SETTINGS;
          }
          break;
        }
      case END_LOSE:
        {
          Serial.println("End_lose");
          break;
        }
      case END_WIN:
        {
          Serial.println("End_win");
          break;
        }
      default:
        {
          Serial.println("Case not implemented yet!");
          break;
        }
    }
  }
};

#endif /*MENU_H*/

Menu* Menu::menuInstance = nullptr;