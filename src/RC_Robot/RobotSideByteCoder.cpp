#include <SeaPerch_BinaryUtils.h>

#include "RobotSideByteCoder.h"
#include "SeaPerch_ControlMode.h"

RobotSideByteCoder::RobotSideByteCoder(HardwareSerial & serial) : RobotSideCoder(serial) {
}

bool RobotSideByteCoder::fromSerial(ControlSpecs & controlSpecs) const {
    if (serial.available() > 0) {
        if (serial.find("#")) {
            char buffer[max(INT_SIZE, FLOAT_SIZE)];
            float expectedChecksum = 0;

            serial.readBytes(buffer, FLOAT_SIZE);
            float normalizedJoystickX = BinaryUtils::toFloat(buffer);
            controlSpecs.setNormalized_joystick_X(normalizedJoystickX);
            expectedChecksum += normalizedJoystickX;

            serial.readBytes(buffer, FLOAT_SIZE);
            float normalizedJoystickY = BinaryUtils::toFloat(buffer);
            controlSpecs.setNormalized_joystick_Y(normalizedJoystickY);
            expectedChecksum += normalizedJoystickY;

            serial.readBytes(buffer, INT_SIZE);
            int slidePotValue = BinaryUtils::toInt(buffer);
            controlSpecs.setSlidePotValue(slidePotValue);
            expectedChecksum += slidePotValue;

            serial.readBytes(buffer, INT_SIZE);
            int slidePotMode = BinaryUtils::toInt(buffer);
            controlSpecs.setSlidePotMode(static_cast<DepthControlMode>(slidePotMode));
            expectedChecksum += slidePotMode;

            serial.readBytes(buffer, FLOAT_SIZE);
            float checksum = BinaryUtils::toFloat(buffer);

            return expectedChecksum == checksum;
        }
    } else {
        return false;
    }
}