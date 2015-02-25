#ifndef _ControlReader_H
#define _ControlReader_H

#include <SeaPerch_ControlSpecs.h>

class ControlReader {
public:
    ControlReader();

    void calibrate();

    void readControlSpecs(ControlSpecs &controlSpecs) const;

    const int getSlidePot() const;

private:
    int joystickMidPointX;
    int joystickMidPointY;

    const double processJoystick(int pinId, int midPoint) const;
};

#endif