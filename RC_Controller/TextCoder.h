#ifndef _TextCoder_H
#define _TextCoder_H

#include <Arduino.h>
#include "MotorSpecs.h"

class TextCoder {
public:
    explicit TextCoder(HardwareSerial &serial);
    void toSerial(MotorSpecs *motorSpecs) const;

private:
    void sendMotorSpec(int motorSpec) const;
    HardwareSerial &serial;
};

#endif