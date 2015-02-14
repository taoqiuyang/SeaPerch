#ifndef _ControlSideCoder_H
#define _ControlSideCoder_H

#include <MotorSpecs.h>

class ControlSideCoder {
public:
    explicit ControlSideCoder(HardwareSerial &serial) : serial(serial) {};

    virtual void toSerial(MotorSpecs &motorSpecs) const = 0;

protected:
    HardwareSerial &serial;
};

#endif