#include <SeaPerch_BinaryUtils.h>

#include "ControlSideByteCoder.h"

ControlSideByteCoder::ControlSideByteCoder(HardwareSerial &serial) : ControlSideCoder(serial) {
}

void ControlSideByteCoder::toSerial(ControlSpecs &controlSpecs) const {
    int checksum = 0;
    char buffer[INT_SIZE];

    serial.print("#");

    for (int i = 0; i < controlSpecs.getMotorCount(); i++) {
        int motorValue = controlSpecs.getMotor(i);

        BinaryUtils::toBytes(motorValue, buffer);
        checksum += motorValue;
        toSerial(buffer, INT_SIZE);
    }

    BinaryUtils::toBytes(checksum, buffer);
    toSerial(buffer, INT_SIZE);

    serial.flush();

    delay(200);
}

void ControlSideByteCoder::toSerial(char *buffer, int size) const {
    for (int i = 0; i < size; i++) {
        serial.write(buffer[i]);
    }
}