#include "SeaPerch_ControlSpecs.h"

ControlSpecs::ControlSpecs(){
}

ControlSpecs::ControlSpecs(const ControlSpecs& controlSpecs) {
    slidePotValue = controlSpecs.getSlidePotValue();
    depthControlMode = controlSpecs.getDepthControlMode();
    normalized_joystick_X = controlSpecs.getNormalized_joystick_X();
    normalized_joystick_Y = controlSpecs.getNormalized_joystick_Y();
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

const int ControlSpecs::getSlidePotValue() const {
    return slidePotValue;
}

void ControlSpecs::setSlidePotValue(const int aSlidePotValue) {
    slidePotValue = aSlidePotValue;
}

const DepthControlMode ControlSpecs::getDepthControlMode() const {
    return depthControlMode;
}

void ControlSpecs::setDepthControlMode (const DepthControlMode aDepthControlMode) {
    depthControlMode = aDepthControlMode;
}

const SpeedControlMode ControlSpecs::getSpeedControlMode() const {
    return speedControlMode;
}

void ControlSpecs::setSpeedControlMode(const SpeedControlMode aSpeedControlMode) {
    speedControlMode = aSpeedControlMode;
}