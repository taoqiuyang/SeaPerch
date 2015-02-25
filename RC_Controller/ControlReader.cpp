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

void ControlReader::readControlSpecs(ControlSpecs &controlSpecs) const {
    controlSpecs.setNormalized_joystick_X(processJoystick(JOYSTICK_HORIZONTAL, joystickMidPointX));
    controlSpecs.setNormalized_joystick_Y(processJoystick(JOYSTICK_VERTICAL, joystickMidPointY));
    controlSpecs.setSlidePot(analogRead(SLIDE_POT));
}

//map the ADC reading to [-1, 1]
const double ControlReader::processJoystick(int pinId, int midPoint) const {
    double normalized;
    int rawValue = analogRead(pinId);

    if (rawValue < midPoint - 1) {
        return (midPoint - rawValue) / (double)midPoint + 1;
    } else if (rawValue > midPoint + 1) {
        return -1 * (rawValue - midPoint) / (double)(1023 - midPoint) + 1;
    } else {
        return 1;
    }
}