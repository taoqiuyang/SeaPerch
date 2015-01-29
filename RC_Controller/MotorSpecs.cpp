#include "MotorSpecs.h"

MotorSpecs::MotorSpecs(int motorCount) {
    motors = new int[motorCount];
}

MotorSpecs::~MotorSpecs() {
    delete[] motors;
}

const float MotorSpecs::getNormalized_joystick_X() const {
    return normalized_joystick_X;
}

void MotorSpecs::setNormalized_joystick_X(float normalized_joystick_X) {
    MotorSpecs::normalized_joystick_X = normalized_joystick_X;
}

const float MotorSpecs::getNormalized_joystick_Y() const {
    return normalized_joystick_Y;
}

void MotorSpecs::setNormalized_joystick_Y(float normalized_joystick_Y) {
    MotorSpecs::normalized_joystick_Y = normalized_joystick_Y;
}