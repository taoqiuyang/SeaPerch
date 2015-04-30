#include <SeaPerch_Orientation.h>
#include <SeaPerch_SerialUtils.h>
#include <SeaPerch_BinaryUtils.h>

#include "ControlSideByteCoder.h"

ControlSideByteCoder::ControlSideByteCoder(HardwareSerial &serial) : ControlSideCoder(serial) {
}

void ControlSideByteCoder::toSerial(const ControlSpecs &controlSpecs) const {
    float checksum = 0;

    serial.print("C");

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
    char junk[100];
    serial.readBytes(junk, 4 + FLOAT_SIZE * 3 + INT_SIZE * 3);
}

bool ControlSideByteCoder::fromSerial(RobotData &robotData) const {
    if (serial.available() <= 0 || !serial.find("R")) {
        return false;
    }

    char buffer[max(INT_SIZE, FLOAT_SIZE)];
    float expectedChecksum = 0;

    serial.readBytes(buffer, FLOAT_SIZE);
    float roll = BinaryUtils::toFloat(buffer);
    expectedChecksum += roll;

    serial.readBytes(buffer, FLOAT_SIZE);
    float pitch = BinaryUtils::toFloat(buffer);
    expectedChecksum += pitch;

    serial.readBytes(buffer, FLOAT_SIZE);
    float yaw = BinaryUtils::toFloat(buffer);
    expectedChecksum += yaw;

    serial.readBytes(buffer, FLOAT_SIZE);
    float checksum = BinaryUtils::toFloat(buffer);

    if (expectedChecksum == checksum) {
        robotData.setOrientation(Orientation(roll, pitch, yaw));
        return true;
    } else {
        return false;
    }
}
