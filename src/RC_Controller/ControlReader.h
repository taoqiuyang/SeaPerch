#ifndef _ControlReader_H
#define _ControlReader_H

#include <SeaPerch_ControlMode.h>
#include <SeaPerch_ControlSpecs.h>

#include "KeyDetector.h"
#include "LCDDisplayer.h"

class ControlReader {
public:
    ControlReader(LCDDisplayer &aLCDDisplayer);

    void initialize();

    void readControlSpecs(ControlSpecs &controlSpecs);

private:
    int joystickMidPointX;
    int joystickMidPointY;
    LCDDisplayer &lcdDisplayer;
    static const DepthControlMode defaultDepthMode = MANUAL_SPEED;

    const float processJoystick(int pinId, int midPoint) const;

    DepthControlMode detectDepthControlMode();
};

#endif