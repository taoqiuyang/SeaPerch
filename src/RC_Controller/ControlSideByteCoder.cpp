#include <SeaPerch_BinaryUtils.h>

#include "ControlSideByteCoder.h"

ControlSideByteCoder::ControlSideByteCoder(HardwareSerial &serial) : ControlSideCoder(serial) {
}

void ControlSideByteCoder::toSerial(ControlSpecs &controlSpecs) const {
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

    int slidePotMode = static_cast<int>(controlSpecs.getSlidePotMode());
    intToSerial(slidePotMode);
    checksum += slidePotMode;

    floatToSerial(checksum);

    serial.flush();
}

void ControlSideByteCoder::intToSerial(int toSend) const {
    char buffer[INT_SIZE];

    BinaryUtils::toBytes(toSend, buffer);
    charBufferToSerial(buffer, INT_SIZE);
}

void ControlSideByteCoder::floatToSerial(float toSend) const {
    char buffer[FLOAT_SIZE];

    BinaryUtils::toBytes(toSend, buffer);
    charBufferToSerial(buffer, FLOAT_SIZE);
}

void ControlSideByteCoder::charBufferToSerial(char *buffer, int size) const {
    for (int i = 0; i < size; i++) {
        serial.write(buffer[i]);
    }
}