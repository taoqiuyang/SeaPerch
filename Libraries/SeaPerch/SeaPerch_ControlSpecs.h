#ifndef _SeaPerch_ControlSpecs_H
#define _SeaPerch_ControlSpecs_H

class ControlSpecs {
public:
    explicit ControlSpecs(unsigned int motorCount);

    ControlSpecs(const ControlSpecs& controlSpecs);

    ~ControlSpecs();

    const float getNormalized_joystick_X() const;

    void setNormalized_joystick_X(float normalized_joystick_X);

    const float getNormalized_joystick_Y() const;

    void setNormalized_joystick_Y(float normalized_joystick_Y);

    const int getJoystick_button() const;

    void setJoystick_button(int joystick_button);

    const int getMotor(int motorId) const;

    void setMotor(int motorId, int motorValue);

    const unsigned int getMotorCount() const;

private:
    int *motors;
    int motorCount;
    int joystick_button;
    float normalized_joystick_X;
    float normalized_joystick_Y;
};

#endif