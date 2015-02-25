#include <Arduino.h>

#include "ControlPin.h"
#include "ControlReader.h"

ControlReader::ControlReader() : joystickMidPointX(0), joystickMidPointY(0) {
}

void ControlReader::calibrate() {
    for (int i = 0; i < 200; i++) {
        joystickMidPointX = (joystickMidPointX + analogRead(JOYSTICK_HORIZONTAL)) / 2;
        delay(1);
        joystickMidPointY = (joystickMidPointY + analogRead(JOYSTICK_VERTICAL)) / 2;
        delay(1);
    }
}

const double ControlReader::getNormalizedJoystickX() const {
    return processJoystick(JOYSTICK_HORIZONTAL, joystickMidPointX);
}

const double ControlReader::getNormalizedJoystickY() const {
    return processJoystick(JOYSTICK_VERTICAL, joystickMidPointY);
}

const int ControlReader::getSlidePot() const {
    return analogRead(SLIDE_POT);
}

const double ControlReader::processJoystick(int pinId, int midPoint) const {
    double normalized;
    int rawValue = analogRead(pinId);

    //-----------------normalize----------------
    //map the ADC reading to [-1, 1]
    if (rawValue < midPoint - 1) {
        normalized = (midPoint - rawValue) / (double)midPoint;
    }
    if (rawValue > midPoint + 1) {
        normalized = (midPoint - rawValue) / (double)(1023 - midPoint);
    }

    //-----------------apply curve--------------
    return normalized + 1;
}