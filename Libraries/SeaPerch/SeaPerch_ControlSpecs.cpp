#include "SeaPerch_ControlSpecs.h"

ControlSpecs::ControlSpecs(unsigned int motorCount) : motorCount(motorCount) {
    motors = new int[motorCount];
}

ControlSpecs::ControlSpecs(const ControlSpecs& controlSpecs) {
    motorCount = controlSpecs.getMotorCount();
    joystick_button = controlSpecs.getJoystick_button();
    normalized_joystick_X = controlSpecs.getNormalized_joystick_X();
    normalized_joystick_Y = controlSpecs.getNormalized_joystick_Y();

    motors = new int[motorCount];
    for (int i = 0; i < motorCount; ++i) {
        motors[i] = controlSpecs.getMotor(i);
    }
}

ControlSpecs::~ControlSpecs() {
    delete[] motors;
}

const float ControlSpecs::getNormalized_joystick_X() const {
    return normalized_joystick_X;
}

void ControlSpecs::setNormalized_joystick_X(const float aNormalized_joystick_X) {
    normalized_joystick_X = aNormalized_joystick_X;
}

const float ControlSpecs::getNormalized_joystick_Y() const {
    return normalized_joystick_Y;
}

void ControlSpecs::setNormalized_joystick_Y(const float aNormalized_joystick_Y) {
    normalized_joystick_Y = aNormalized_joystick_Y;
}

const int ControlSpecs::getJoystick_button() const {
    return joystick_button;
}

void ControlSpecs::setJoystick_button(const int aJoystick_button) {
    joystick_button = aJoystick_button;
}

const int ControlSpecs::getSlidePot() const {
    return slidePot;
}

void ControlSpecs::setSlidePot(const int aSlidePot) {
    slidePot = aSlidePot;
}

const int ControlSpecs::getMotor(int motorId) const {
    return motors[motorId];
}

void ControlSpecs::setMotor(int motorId, int motorValue) {
    motors[motorId] = motorValue;
}

const unsigned int ControlSpecs::getMotorCount() const {
    return motorCount;
}