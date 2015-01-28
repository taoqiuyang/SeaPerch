#include "MotorSpecs.h"

float MotorSpecs::getNormalized_joystick_X() const {
    return normalized_joystick_X;
}

void MotorSpecs::setNormalized_joystick_X(float normalized_joystick_X) {
    MotorSpecs::normalized_joystick_X = normalized_joystick_X;
}