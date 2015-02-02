#ifndef _TextCoder_H
#define _TextCoder_H

#include <Arduino.h>
#include "MotorSpecs.h"

void sendMotorSpec(int motorSpec) {
    Serial2.print(motorSpec / 100);
    Serial2.print((motorSpec - (motorSpec / 100) * 100) / 10);
    Serial2.print(motorSpec % 10);
    Serial2.print(",");
}

void serial_2_send_data(MotorSpecs *motorSpecs) {
    float checksum = motorSpecs->getNormalized_joystick_X() + motorSpecs->getNormalized_joystick_Y() + motorSpecs->getJoystick_button();
    for (int i = 0; i < 5; i++) {
        checksum += motorSpecs->getMotor(i);
    }

    Serial2.flush();
    Serial2.print("#");

    Serial2.print(motorSpecs->getNormalized_joystick_X(), 3);
    Serial2.print(",");
    Serial2.print(motorSpecs->getNormalized_joystick_Y(), 3);
    Serial2.print(",");
    Serial2.print(motorSpecs->getJoystick_button());
    Serial2.print(",");
    for (int i = 0; i < 5; i++) {
        sendMotorSpec(motorSpecs->getMotor(i));
    }
    Serial2.print(checksum, 3);

    Serial2.print("\n");
}

#endif