#include "ControlSideTextCoder.h"

ControlSideTextCoder::ControlSideTextCoder(HardwareSerial &serial) : ControlSideCoder(serial) {
}

void ControlSideTextCoder::sendMotorSpec(int motorSpec) const {
    serial.print(motorSpec / 100);
    serial.print((motorSpec - (motorSpec / 100) * 100) / 10);
    serial.print(motorSpec % 10);
    serial.print(",");
}

void ControlSideTextCoder::toSerial(ControlSpecs &controlSpecs) const {
    float checksum = controlSpecs.getNormalized_joystick_X() + controlSpecs.getNormalized_joystick_Y() + controlSpecs.getJoystick_button();
    for (int i = 0; i < controlSpecs.getMotorCount(); i++) {
        checksum += controlSpecs.getMotor(i);
    }

    serial.flush();
    serial.print("#");

    serial.print(controlSpecs.getNormalized_joystick_X(), 3);
    serial.print(",");
    serial.print(controlSpecs.getNormalized_joystick_Y(), 3);
    serial.print(",");
    serial.print(controlSpecs.getJoystick_button());
    serial.print(",");
    for (int i = 0; i < controlSpecs.getMotorCount(); i++) {
        sendMotorSpec(controlSpecs.getMotor(i));
    }
    serial.print(checksum, 3);

    serial.print("\n");
}