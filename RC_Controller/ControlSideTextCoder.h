#ifndef _ControlSide_TextCoder_H
#define _ControlSide_TextCoder_H

#include <Arduino.h>
#include "MotorSpecs.h"

class ControlSideTextCoder {
public:
    explicit ControlSideTextCoder(HardwareSerial &serial);
    void toSerial(MotorSpecs *motorSpecs) const;

private:
    void sendMotorSpec(int motorSpec) const;
    HardwareSerial &serial;
};

#endif