#ifndef _ControlSideCoder_H
#define _ControlSideCoder_H

#include <SeaPerch_ControlSpecs.h>;

class ControlSideCoder {
public:
    explicit ControlSideCoder(HardwareSerial &serial) : serial(serial) {};

    virtual void toSerial(const ControlSpecs &controlSpecs) const = 0;

protected:
    HardwareSerial &serial;
};

#endif