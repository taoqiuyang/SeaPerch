#include <Arduino.h>

#include "ControlPin.h"
#include "ControlReader.h"
#include "SeaPerch_ControlMode.h"

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
    controlSpecs.setSlidePotValue(analogRead(SLIDE_POT));
    controlSpecs.setSlidePotMode(SPEED);
    controlSpecs.setNormalized_joystick_X(processJoystick(JOYSTICK_HORIZONTAL, joystickMidPointX));
    controlSpecs.setNormalized_joystick_Y(processJoystick(JOYSTICK_VERTICAL, joystickMidPointY));
}

//map the ADC reading to [-1, 1]
const float ControlReader::processJoystick(int pinId, int midPoint) const {
    int rawValue = analogRead(pinId);

    if (rawValue <= midPoint) {
        return (midPoint - rawValue) / (float)midPoint;
    } else {
        return -1 * (rawValue - midPoint) / (float)(1023 - midPoint);
    }
}