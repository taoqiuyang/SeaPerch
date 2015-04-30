#include <SeaPerch_Orientation.h>
#include <SeaPerch_SerialUtils.h>
#include <SeaPerch_BinaryUtils.h>

#include "RobotSideByteCoder.h"
#include "SeaPerch_ControlMode.h"

RobotSideByteCoder::RobotSideByteCoder(HardwareSerial & serial) : RobotSideCoder(serial) {
}

// block until serial incoming data available
bool RobotSideByteCoder::fromSerial(ControlSpecs & controlSpecs) const {
    if (serial.available() <= 0 || !serial.find("C")) {
        return false;
    }

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
    int depthControlMode = BinaryUtils::toInt(buffer);
    controlSpecs.setDepthControlMode(static_cast<DepthControlMode>(depthControlMode));
    expectedChecksum += depthControlMode;

    serial.readBytes(buffer, INT_SIZE);
    int speedControlMode = BinaryUtils::toInt(buffer);
    controlSpecs.setSpeedControlMode(static_cast<SpeedControlMode>(speedControlMode));
    expectedChecksum += speedControlMode;

    serial.readBytes(buffer, FLOAT_SIZE);
    float checksum = BinaryUtils::toFloat(buffer);

    return expectedChecksum == checksum;
}

void RobotSideByteCoder::toSerial(const RobotData &robotData) const {
    float checksum = 0;
    const Orientation &orientation = robotData.getOrientation();

    serial.print("R");

    float roll = orientation.getRoll();
    SerialUtils::floatToSerial(serial, roll);
    checksum += roll;

    float pitch = orientation.getPitch();
    SerialUtils::floatToSerial(serial, pitch);
    checksum += pitch;

    float yaw = orientation.getYaw();
    SerialUtils::floatToSerial(serial, yaw);
    checksum += yaw;

    SerialUtils::floatToSerial(serial, checksum);

    serial.flush();
    char junk[100];
    serial.readBytes(junk, 4 + FLOAT_SIZE * 4);
}
