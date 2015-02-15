#include <SeaPerch_BinaryUtils.h>

#include "ControlSideByteCoder.h"

ControlSideByteCoder::ControlSideByteCoder(HardwareSerial &serial) : ControlSideCoder(serial) {
}

void ControlSideByteCoder::toSerial(MotorSpecs &motorSpecs) const {
    int checksum = 0;
    int byteMask = 0xff;

    serial.print("#");

    char buffer[INT_SIZE];
    for (int i = 0; i < motorSpecs.getMotorCount(); i++) {
        int motorValue = motorSpecs.getMotor(i);

        toBytes(motorValue, buffer);
        checksum += motorValue;

        for (int j = 0; j < INT_SIZE; j++) {
            serial.write(buffer[j]);
        }
    }

    toBytes(checksum, buffer);
    for (int k = 0; k < sizeof(int); k++) {
        serial.write(buffer[k]);
    }
    serial.flush();

    delay(200);
}