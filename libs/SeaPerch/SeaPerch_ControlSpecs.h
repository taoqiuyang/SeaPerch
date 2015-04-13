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

    const int getSlidePotValue() const;

    void setSlidePotValue(const int aSlidePotValue);

    const DepthControlMode getDepthControlMode() const;

    void setDepthControlMode(const DepthControlMode aDepthControlMode);

    const SpeedControlMode getSpeedControlMode() const;

    void setSpeedControlMode(const SpeedControlMode aSpeedControlMode);

private:
    int slidePotValue;
    float normalized_joystick_X;
    float normalized_joystick_Y;
    DepthControlMode depthControlMode;
    SpeedControlMode speedControlMode;
};

#endif