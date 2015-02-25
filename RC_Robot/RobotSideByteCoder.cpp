#include <SeaPerch_BinaryUtils.h>

#include "RobotSideByteCoder.h"

RobotSideByteCoder::RobotSideByteCoder(HardwareSerial & serial) : RobotSideCoder(serial) {
}

bool RobotSideByteCoder::fromSerial(ControlSpecs & controlSpecs) const {
    if (serial.available() > 0) {
        if (serial.find("#")) {
            char buffer[INT_SIZE];
            int expectedChecksum = 0;

            for (int i = 0; i < controlSpecs.getMotorCount(); i++) {
                serial.readBytes(buffer, INT_SIZE);

                int motorValue = toInt(buffer);
                controlSpecs.setMotor(i, motorValue);
                expectedChecksum += motorValue;
            }

            serial.readBytes(buffer, INT_SIZE);
            int checksum = toInt(buffer);

            return expectedChecksum == checksum;
        }
    } else {
        return false;
    }
}