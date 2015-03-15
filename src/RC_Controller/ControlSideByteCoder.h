#ifndef _ControlSideByteCoder_H
#define _ControlSideByteCoder_H

#include <Arduino.h>
#include "ControlSideCoder.h"

class ControlSideByteCoder : public ControlSideCoder {
public:
    explicit ControlSideByteCoder(HardwareSerial &serial);

    void toSerial(ControlSpecs &controlSpecs) const;

private:
    void toSerial(char *buffer, int size) const;
};

#endif