#include <Arduino.h>

#include "ControlPin.h"
#include "LCDDisplayer.h"
#include "ControlReader.h"

ControlReader::ControlReader(KeyDetector &aKeyDetector, LCDDisplayer &aLCDDisplayer) : keyDetector(aKeyDetector),
                                                                                       lcdDisplayer(aLCDDisplayer),
                                                                                       joystickMidPointX(0),
                                                                                       joystickMidPointY(0),
                                                                                       controlMode(SPEED) {
}

void ControlReader::calibrate() {
    for (int i = 0; i < 200; i++) {
        joystickMidPointX = (joystickMidPointX + analogRead(JOYSTICK_HORIZONTAL)) / 2;
        delay(1);
        joystickMidPointY = (joystickMidPointY + analogRead(JOYSTICK_VERTICAL)) / 2;
        delay(1);
    }
}

void ControlReader::readControlSpecs(ControlSpecs &controlSpecs) {
    controlSpecs.setSlidePotValue(analogRead(SLIDE_POT));
    controlSpecs.setSlidePotMode(detectControlMode());
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

ControlMode ControlReader::detectControlMode() {
    if (keyDetector.detectKey() == SELECT) {
        if (controlMode == SPEED) {
            controlMode = DEPTH;
            lcdDisplayer.display("Auto-Depth Mode");
        } else if (controlMode == DEPTH) {
            controlMode = SPEED;
            lcdDisplayer.display("Speed Ctrl Mode");
        }
    }

    return controlMode;
}