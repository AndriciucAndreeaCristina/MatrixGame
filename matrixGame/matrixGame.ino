#include "Joystick.h"

Joystick* joystick = Joystick::getJoystickInstance();

void setup() {
  Serial.begin(9600);
}

void loop() {
  joystick->updateButtonState();
}
