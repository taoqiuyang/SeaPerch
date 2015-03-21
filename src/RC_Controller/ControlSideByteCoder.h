#ifndef _ControlSideByteCoder_H
#define _ControlSideByteCoder_H

#include <Arduino.h>
#include "ControlSideCoder.h"

class ControlSideByteCoder : public ControlSideCoder {
public:
    explicit ControlSideByteCoder(HardwareSerial &serial);

    void toSerial(ControlSpecs &controlSpecs) const;

private:
    void intToSerial(const int toSend) const;
    void floatToSerial(const float toSend) const;
    void charBufferToSerial(const char *buffer, const int size) const;
};

#endif