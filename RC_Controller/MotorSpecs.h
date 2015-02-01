#ifndef _MotorSpecs_H
#define _MotorSpecs_H

class MotorSpecs {
public:
    explicit MotorSpecs(int motorCount);
    ~MotorSpecs();
    const float getNormalized_joystick_X() const;
    void setNormalized_joystick_X(float normalized_joystick_X);
    const float getNormalized_joystick_Y() const;
    void setNormalized_joystick_Y(float normalized_joystick_Y);
    const int getJoystick_button() const;
    void setJoystick_button(int joystick_button);
    const int getMotor(int motorId) const;
    void setMotor(int motorId, int motorValue);

private:
    float normalized_joystick_X;
    float normalized_joystick_Y;
    int joystick_button;
    int *motors;
};

#endif