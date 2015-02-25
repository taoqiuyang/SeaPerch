#ifndef _SeaPerch_ControlSpecs_H
#define _SeaPerch_ControlSpecs_H

class ControlSpecs {
public:
    explicit ControlSpecs(unsigned int motorCount);

    ControlSpecs(const ControlSpecs& controlSpecs);

    ~ControlSpecs();

    const float getNormalized_joystick_X() const;

    void setNormalized_joystick_X(const float aNormalized_joystick_X);

    const float getNormalized_joystick_Y() const;

    void setNormalized_joystick_Y(const float aNormalized_joystick_Y);

    const int getJoystick_button() const;

    void setJoystick_button(const int aJoystick_button);

    const int getSlidePot() const;

    void setSlidePot(const int aSlidePot);

    const int getMotor(int motorId) const;

    void setMotor(int motorId, int motorValue);

    const unsigned int getMotorCount() const;

private:
    int *motors;
    int motorCount;
    int joystick_button;
    int slidePot;
    float normalized_joystick_X;
    float normalized_joystick_Y;
};

#endif