#include <SeaPerch_BinaryUtils.h>

#include "ControlSideByteCoder.h"

ControlSideByteCoder::ControlSideByteCoder(HardwareSerial &serial) : ControlSideCoder(serial) {
}

void ControlSideByteCoder::toSerial(ControlSpecs &controlSpecs) const {
    float checksum = 0;
    char buffer[20];

    serial.print("#");

    for (int i = 0; i < controlSpecs.getMotorCount(); i++) {
        int motorValue = controlSpecs.getMotor(i);

        BinaryUtils::toBytes(motorValue, buffer);
        checksum += motorValue;
        toSerial(buffer, INT_SIZE);
    }

    float normalizedJoystickX = controlSpecs.getNormalized_joystick_X();
    BinaryUtils::toBytes(normalizedJoystickX, buffer);
    toSerial(buffer, FLOAT_SIZE);
    checksum += normalizedJoystickX;

    float normalizedJoystickY = controlSpecs.getNormalized_joystick_Y();
    BinaryUtils::toBytes(normalizedJoystickY, buffer);
    toSerial(buffer, FLOAT_SIZE);
    checksum += normalizedJoystickY;

    float slidePot = controlSpecs.getSlidePot();
    BinaryUtils::toBytes(slidePot, buffer);
    toSerial(buffer, FLOAT_SIZE);
    checksum += slidePot;

    BinaryUtils::toBytes(checksum, buffer);
    toSerial(buffer, FLOAT_SIZE);

    serial.flush();
}

void ControlSideByteCoder::toSerial(char *buffer, int size) const {
    for (int i = 0; i < size; i++) {
        serial.write(buffer[i]);
    }
}