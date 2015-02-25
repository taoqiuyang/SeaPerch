#ifndef _ControlReader_H
#define _ControlReader_H

#include <Arduino.h>
#include "ControlPin.h"

class ControlReader {
public:
    ControlReader() : joystickMidPointX(0), joystickMidPointY(0) {
    }

    void calibrate() {
        for (int i = 0; i < 200; i++) {
            joystickMidPointX = (joystickMidPointX + analogRead(JOYSTICK_HORIZONTAL)) / 2;
            delay(1);
            joystickMidPointY = (joystickMidPointY + analogRead(JOYSTICK_VERTICAL)) / 2;
            delay(1);
        }
    }

    double getNormalizedJoystickX() {
        return processJoystick(JOYSTICK_HORIZONTAL, joystickMidPointX);
    }

    double getNormalizedJoystickY() {
        return processJoystick(JOYSTICK_VERTICAL, joystickMidPointY);
    }

private:
    int joystickMidPointX;
    int joystickMidPointY;

    double processJoystick(int pinId, int midPoint) {
        double normalized;
        int rawValue = analogRead(pinId);

        //-----------------normalize----------------
        //map the ADC reading to [-1, 1]
        if (rawValue < midPoint - 1) {
            normalized = 1.0 * (midPoint - rawValue) / midPoint;
        }
        if (rawValue > midPoint + 1) {
            normalized = -1.0 * (rawValue - midPoint) / (1023 - midPoint);
        }
        if (normalized > 1) {
            normalized = 1;
        }
        if (normalized < -1) {
            normalized = -1;
        }
        //-----------------apply curve--------------
        return normalized + 1;
    }
};

#endif