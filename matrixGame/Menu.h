#include "HardwareSerial.h"
#ifndef MENU_H
#define MENU_H

class Menu {
private:
  static Menu* menuInstance;
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
                systemState = SETTINGS;
                break;
              case 1:
                systemState = ABOUT;
                break;
              case 2:
                systemState = HOW_TO_PLAY;
                break;
              case 3:
                systemState = START;
                break;
              default:
                break;
            }
          }
          break;
        }
      case START:
        {
          Serial.println("Start");
          lcd.clear();
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
          Serial.println("HighScores");
          break;
        }
      case SETTINGS:
        {
          Serial.println("Menu Settings");
          lcd.clear();
          joystick.updateButtonState();
          if (joystick.isButtonShortPressed()) {
            lcd.resetCursorLine();
            systemState = MENU;
          }
          break;
        }
      case ENTER_NAME:
        {
          Serial.println("EnterName");
          break;
        }
      case LCD_BRIGHTNESS_CONTROL:
        {
          Serial.println("LCD Brightness control");
          break;
        }
      case MATRIX_BRIGHTNESS_CONTROL:
        {
          Serial.println("MATRIX_BRIGHTNESS_CONTROL");
          break;
        }
      case SOUND:
        {
          Serial.println("Sound");
          break;
        }
      case GAMEPLAY:
        {
          Serial.println("Gameplay");
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