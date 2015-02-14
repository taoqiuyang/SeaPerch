#include "MotorSpecs.h"

MotorSpecs::MotorSpecs(unsigned int motorCount) : motorCount(motorCount) {
    motors = new int[motorCount];
}

MotorSpecs::MotorSpecs(const MotorSpecs& motorSpecs) {
    motorCount = motorSpecs.getMotorCount();
    joystick_button = motorSpecs.getJoystick_button();
    normalized_joystick_X = motorSpecs.getNormalized_joystick_X();
    normalized_joystick_Y = motorSpecs.getNormalized_joystick_Y();

    motors = new int[motorCount];
    for (int i = 0; i < motorCount; ++i) {
        motors[i] = motorSpecs.getMotor(i);
    }
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

const int MotorSpecs::getJoystick_button() const {
    return joystick_button;
}

void MotorSpecs::setJoystick_button(int joystick_button) {
    MotorSpecs::joystick_button = joystick_button;
}

const int MotorSpecs::getMotor(int motorId) const {
    return motors[motorId];
}

void MotorSpecs::setMotor(int motorId, int motorValue) {
    motors[motorId] = motorValue;
}

const unsigned int MotorSpecs::getMotorCount() const {
    return motorCount;
}