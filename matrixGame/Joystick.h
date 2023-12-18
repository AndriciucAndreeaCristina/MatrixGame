#ifndef JOYSTICK_H
#define JOYSTICK_H

class Joystick {
private:
  int xValue;
  int yValue;
  int pressedTime;
  int releasedTime;
  int isShortPress = false;
  int isLongPress = false;
  JoystickDirection joystickState;
  ezButton button;
  bool wasPressed;
  JoystickDirection lastDirection;

public:
  Joystick()
    : button(JOYSTICK_SW) {
    pinMode(JOYSTICK_X, INPUT);
    pinMode(JOYSTICK_Y, INPUT);
    pinMode(JOYSTICK_SW, INPUT_PULLUP);
    button.setDebounceTime(100);
    joystickState = CENTER;
    lastDirection = CENTER;
  }
  int readX() {
    xValue = analogRead(JOYSTICK_X);
    return xValue;
  }
  int readY() {
    yValue = analogRead(JOYSTICK_Y);
    return yValue;
  }
  ezButton getButton() {
    return button;
  }
  bool isButtonShortPressed() {
    return isShortPress;
  }
  bool isButtonLongPressed() {
    return isLongPress;
  }
  void updateButtonState() {
    isShortPress = false;
    isLongPress = false;
    button.loop();
    if (button.isPressed()) {
      isShortPress = false;
      isLongPress = false;
      pressedTime = millis();
      wasPressed = true;
    }
    if (button.isReleased() && wasPressed) {
      releasedTime = millis();
      long pressDuration = releasedTime - pressedTime;
      if (pressDuration < SHORT_PRESS_TIME) {
        Serial.println("short");
        isShortPress = true;
      }
      if (pressDuration > LONG_PRESS_TIME) {
        Serial.println("long");
        isLongPress = true;
      }
    }
  }

  JoystickDirection getJoystickDirection() {
    xValue = readX();
    yValue = readY();
    if (xValue < JOYSTICK_MIN_THRESHOLD) {
      joystickState = LEFT;
    } else if (xValue > JOYSTICK_MAX_THRESHOLD) {
      joystickState = RIGHT;
    } else {
      if (yValue < JOYSTICK_MIN_THRESHOLD) {
        joystickState = UP;
      } else if (yValue > JOYSTICK_MAX_THRESHOLD) {
        joystickState = DOWN;
      } else {
        joystickState = CENTER;
      }
    }
    return joystickState;
  }
  JoystickDirection getJoystickLastDirection() {
    return lastDirection;
  }
  void setJoystickLastDirection(JoystickDirection dir) {
    lastDirection = dir;
  }
  void handleMenu() {
  }
};

#endif /*JOYSTICK_H*/
