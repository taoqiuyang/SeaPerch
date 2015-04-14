#include <SeaPerch_BinaryUtils.h>

#include "ControlSideByteCoder.h"

ControlSideByteCoder::ControlSideByteCoder(HardwareSerial &serial) : ControlSideCoder(serial) {
}

void ControlSideByteCoder::toSerial(const ControlSpecs &controlSpecs) const {
    float checksum = 0;

    serial.print("#");

    float normalizedJoystickX = controlSpecs.getNormalized_joystick_X();
    floatToSerial(normalizedJoystickX);
    checksum += normalizedJoystickX;

    float normalizedJoystickY = controlSpecs.getNormalized_joystick_Y();
    floatToSerial(normalizedJoystickY);
    checksum += normalizedJoystickY;

    int slidePotValue = controlSpecs.getSlidePotValue();
    intToSerial(slidePotValue);
    checksum += slidePotValue;

    int depthControlMode = static_cast<int>(controlSpecs.getDepthControlMode());
    intToSerial(depthControlMode);
    checksum += depthControlMode;

    int speedControlMode = static_cast<int>(controlSpecs.getSpeedControlMode());
    intToSerial(speedControlMode);
    checksum += speedControlMode;

    floatToSerial(checksum);

    serial.flush();
}

void ControlSideByteCoder::intToSerial(const int toSend) const {
    char buffer[INT_SIZE];

    BinaryUtils::toBytes(toSend, buffer);
    charBufferToSerial(buffer, INT_SIZE);
}

void ControlSideByteCoder::floatToSerial(const float toSend) const {
    char buffer[FLOAT_SIZE];

    BinaryUtils::toBytes(toSend, buffer);
    charBufferToSerial(buffer, FLOAT_SIZE);
}

void ControlSideByteCoder::charBufferToSerial(const char *buffer, const int size) const {
    for (int i = 0; i < size; i++) {
        serial.write(buffer[i]);
    }
}