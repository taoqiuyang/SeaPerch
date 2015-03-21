#ifndef _SeaPerch_ControlSpecs_H
#define _SeaPerch_ControlSpecs_H

#include "SeaPerch_ControlMode.h"

class ControlSpecs {
public:
    explicit ControlSpecs();

    ControlSpecs(const ControlSpecs& controlSpecs);

    const float getNormalized_joystick_X() const;

    void setNormalized_joystick_X(const float aNormalized_joystick_X);

    const float getNormalized_joystick_Y() const;

    void setNormalized_joystick_Y(const float aNormalized_joystick_Y);

    const int getSlidePot() const;

    void setSlidePot(const int aSlidePot);

    const ControlMode getSlidePotMode() const;

    void setSlidePotMode(const ControlMode controlMode);

private:
    int slidePot;
    ControlMode slidePotMode;
    float normalized_joystick_X;
    float normalized_joystick_Y;
};

#endif