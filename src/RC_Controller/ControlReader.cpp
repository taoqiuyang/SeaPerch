#include <Arduino.h>

#include "ControlPin.h"
#include "LCDDisplayer.h"
#include "ControlReader.h"

ControlReader::ControlReader(LCDDisplayer &aLCDDisplayer) : lcdDisplayer(aLCDDisplayer),
                                                                                       joystickMidPointX(0),
                                                                                       joystickMidPointY(0) {
}

void ControlReader::initialize() {
    pinMode(JOYSTICK_PUSHBUTTON, INPUT);
    digitalWrite(JOYSTICK_PUSHBUTTON, HIGH);

    for (int i = 0; i < 200; i++) {
        joystickMidPointX = (joystickMidPointX + analogRead(JOYSTICK_HORIZONTAL)) / 2;
        delay(1);
        joystickMidPointY = (joystickMidPointY + analogRead(JOYSTICK_VERTICAL)) / 2;
        delay(1);
    }

    lcdDisplayer.display(depthControlMsg[defaultDepthMode]);
}

void ControlReader::readControlSpecs(ControlSpecs &controlSpecs) {
    controlSpecs.setSpeedControlMode(LIMIT_ON);
    controlSpecs.setSlidePotValue(analogRead(SLIDE_POT));
    controlSpecs.setDepthControlMode(detectDepthControlMode());
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

DepthControlMode ControlReader::detectDepthControlMode() {
    static DepthControlMode depthControlMode = defaultDepthMode;

    if (currentKey == SELECT) {
        if (depthControlMode == MANUAL_SPEED) {
            depthControlMode = AUTO_DEPTH;
            digitalWrite(SLIDE_POT_LED, HIGH);
        } else if (depthControlMode == AUTO_DEPTH) {
            depthControlMode = MANUAL_SPEED;
            digitalWrite(SLIDE_POT_LED, LOW);
        }

        lcdDisplayer.display(depthControlMsg[depthControlMode]);
        currentKey = NOT_DETECTED;
    }

    return depthControlMode;
}