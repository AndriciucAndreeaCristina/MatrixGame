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
          Serial.println("Idle");
          lcd.LCDintroMenu();
          break;
        }
      case MENU:
        {
          Serial.println("Menu");
          break;
        }
      case START:
        {
          Serial.println("Start");
          break;
        }
      case ABOUT:
        {
          Serial.println("About");
          break;
        }
      case HIGHSCORES:
        {
          Serial.println("HighScores");
          break;
        }
      case SETTINGS:
        {
          Serial.println("Settings");
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