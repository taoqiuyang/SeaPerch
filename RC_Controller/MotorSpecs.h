#ifndef _MotorSpecs_H
#define _MotorSpecs_H

class MotorSpecs {
public:
    float getNormalized_joystick_X() const;
    void setNormalized_joystick_X(float normalized_joystick_X);
    float getNormalized_joystick_Y() const;
    void setNormalized_joystick_Y(float normalized_joystick_Y);

private:
    float normalized_joystick_X;
    float normalized_joystick_Y;
};

#endif