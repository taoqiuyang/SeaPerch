#ifndef _ControlReader_H
#define _ControlReader_H

class ControlReader {
public:
    ControlReader();

    void calibrate();

    double getNormalizedJoystickX();

    double getNormalizedJoystickY();

    int getSlidePot();

private:
    int joystickMidPointX;
    int joystickMidPointY;

    double processJoystick(int pinId, int midPoint);
};

#endif