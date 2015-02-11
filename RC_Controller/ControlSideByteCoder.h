#ifndef _ControlSideByteCoder_H
#define _ControlSideByteCoder_H

#include <Arduino.h>
#include "ControlSideCoder.h"

class ControlSideByteCoder : public ControlSideCoder {
public:
    explicit ControlSideByteCoder(HardwareSerial &serial);

    void toSerial(MotorSpecs &motorSpecs) const;
};

#endif