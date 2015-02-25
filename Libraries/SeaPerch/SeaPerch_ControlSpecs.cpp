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

void ControlSpecs::setNormalized_joystick_X(float normalized_joystick_X) {
    ControlSpecs::normalized_joystick_X = normalized_joystick_X;
}

const float ControlSpecs::getNormalized_joystick_Y() const {
    return normalized_joystick_Y;
}

void ControlSpecs::setNormalized_joystick_Y(float normalized_joystick_Y) {
    ControlSpecs::normalized_joystick_Y = normalized_joystick_Y;
}

const int ControlSpecs::getJoystick_button() const {
    return joystick_button;
}

void ControlSpecs::setJoystick_button(int joystick_button) {
    ControlSpecs::joystick_button = joystick_button;
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