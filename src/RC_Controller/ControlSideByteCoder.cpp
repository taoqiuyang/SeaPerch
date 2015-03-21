#include <SeaPerch_BinaryUtils.h>

#include "ControlSideByteCoder.h"

ControlSideByteCoder::ControlSideByteCoder(HardwareSerial &serial) : ControlSideCoder(serial) {
}

void ControlSideByteCoder::toSerial(ControlSpecs &controlSpecs) const {
    float checksum = 0;
    char buffer[max(INT_SIZE, FLOAT_SIZE)];

    serial.print("#");

    float normalizedJoystickX = controlSpecs.getNormalized_joystick_X();
    BinaryUtils::toBytes(normalizedJoystickX, buffer);
    toSerial(buffer, FLOAT_SIZE);
    checksum += normalizedJoystickX;

    float normalizedJoystickY = controlSpecs.getNormalized_joystick_Y();
    BinaryUtils::toBytes(normalizedJoystickY, buffer);
    toSerial(buffer, FLOAT_SIZE);
    checksum += normalizedJoystickY;

    int slidePotValue = controlSpecs.getSlidePotValue();
    BinaryUtils::toBytes(slidePotValue, buffer);
    toSerial(buffer, INT_SIZE);
    checksum += slidePotValue;

    int slidePotMode = static_cast<int>(controlSpecs.getSlidePotMode());
    BinaryUtils::toBytes(slidePotMode, buffer);
    toSerial(buffer, INT_SIZE);
    checksum += slidePotMode;

    BinaryUtils::toBytes(checksum, buffer);
    toSerial(buffer, FLOAT_SIZE);

    serial.flush();
}

void ControlSideByteCoder::toSerial(char *buffer, int size) const {
    for (int i = 0; i < size; i++) {
        serial.write(buffer[i]);
    }
}