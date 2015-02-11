#include "RobotSideByteCoder.h"
#include "BinaryUtils.h"

RobotSideByteCoder::RobotSideByteCoder(HardwareSerial & serial) : serial(serial) {
}

bool RobotSideByteCoder::fromSerial(MotorSpecs &motorSpecs) const {
    Serial.println("Coder Called!");

    if (serial.available() > 0) {
        Serial.println("Byte stream available!!");
        if (serial.find("#")) {
            Serial.println("Starting Symbol Found!");

            char buffer[INT_SIZE];
            int expectedChecksum = 0;

            for (int i = 0; i < motorSpecs.getMotorCount(); i++) {
                serial.readBytes(buffer, INT_SIZE);

                int motorValue = toInt(buffer);
                motorSpecs.setMotor(i, motorValue);
                expectedChecksum += motorValue;
            }

            serial.readBytes(buffer, INT_SIZE);
            int checksum = toInt(buffer);

            Serial.print("Expected checksum: ");
            Serial.print(expectedChecksum);
            Serial.print("Checksum: ");
            Serial.print(checksum);

            return expectedChecksum == checksum;
        }
    } else {
        return false;
    }
}