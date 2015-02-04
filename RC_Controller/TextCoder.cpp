#include "TextCoder.h"

TextCoder::TextCoder(HardwareSerial &serial) : serial(serial) {}

void TextCoder::sendMotorSpec(int motorSpec) const {
    serial.print(motorSpec / 100);
    serial.print((motorSpec - (motorSpec / 100) * 100) / 10);
    serial.print(motorSpec % 10);
    serial.print(",");
}

void TextCoder::toSerial(MotorSpecs *motorSpecs) const {
    float checksum = motorSpecs->getNormalized_joystick_X() + motorSpecs->getNormalized_joystick_Y() + motorSpecs->getJoystick_button();
    for (int i = 0; i < motorSpecs->getMotorCount(); i++) {
        checksum += motorSpecs->getMotor(i);
    }

    serial.flush();
    serial.print("#");

    serial.print(motorSpecs->getNormalized_joystick_X(), 3);
    serial.print(",");
    serial.print(motorSpecs->getNormalized_joystick_Y(), 3);
    serial.print(",");
    serial.print(motorSpecs->getJoystick_button());
    serial.print(",");
    for (int i = 0; i < motorSpecs->getMotorCount(); i++) {
        sendMotorSpec(motorSpecs->getMotor(i));
    }
    serial.print(checksum, 3);

    serial.print("\n");
}