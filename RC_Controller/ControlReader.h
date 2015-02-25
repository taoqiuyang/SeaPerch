#ifndef _ControlReader_H
#define _ControlReader_H

class ControlReader {
public:
    ControlReader();

    void calibrate();

    const double getNormalizedJoystickX() const;

    const double getNormalizedJoystickY() const;

    const int getSlidePot() const;

private:
    int joystickMidPointX;
    int joystickMidPointY;

    const double processJoystick(int pinId, int midPoint) const;
};

#endif