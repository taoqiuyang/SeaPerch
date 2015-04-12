#ifndef _ControlReader_H
#define _ControlReader_H

#include <SeaPerch_ControlMode.h>
#include <SeaPerch_ControlSpecs.h>

#include "KeyDetector.h"
#include "LCDDisplayer.h"

class ControlReader {
public:
    ControlReader(KeyDetector &aKeyDetector, LCDDisplayer &aLCDDisplayer);

    void calibrate();

    void readControlSpecs(ControlSpecs &controlSpecs);

private:
    int joystickMidPointX;
    int joystickMidPointY;
    ControlMode controlMode;
    KeyDetector &keyDetector;
    LCDDisplayer &lcdDisplayer;

    const float processJoystick(int pinId, int midPoint) const;
    ControlMode detectControlMode();
};

#endif