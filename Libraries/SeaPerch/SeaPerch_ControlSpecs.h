#ifndef _SeaPerch_ControlSpecs_H
#define _SeaPerch_ControlSpecs_H

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

private:
    int slidePot;
    float normalized_joystick_X;
    float normalized_joystick_Y;
};

#endif