#include <SeaPerch_SerialUtils.h>

#include "ControlSideByteCoder.h"

ControlSideByteCoder::ControlSideByteCoder(HardwareSerial &serial) : ControlSideCoder(serial) {
}

void ControlSideByteCoder::toSerial(const ControlSpecs &controlSpecs) const {
    float checksum = 0;

    serial.print("#");

    float normalizedJoystickX = controlSpecs.getNormalized_joystick_X();
    SerialUtils::floatToSerial(serial, normalizedJoystickX);
    checksum += normalizedJoystickX;

    float normalizedJoystickY = controlSpecs.getNormalized_joystick_Y();
    SerialUtils::floatToSerial(serial, normalizedJoystickY);
    checksum += normalizedJoystickY;

    int slidePotValue = controlSpecs.getSlidePotValue();
    SerialUtils::intToSerial(serial, slidePotValue);
    checksum += slidePotValue;

    int depthControlMode = static_cast<int>(controlSpecs.getDepthControlMode());
    SerialUtils::intToSerial(serial, depthControlMode);
    checksum += depthControlMode;

    int speedControlMode = static_cast<int>(controlSpecs.getSpeedControlMode());
    SerialUtils::intToSerial(serial, speedControlMode);
    checksum += speedControlMode;

    SerialUtils::floatToSerial(serial, checksum);

    serial.flush();
}