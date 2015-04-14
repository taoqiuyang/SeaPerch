#ifndef _ControlSideByteCoder_H
#define _ControlSideByteCoder_H

#include <Arduino.h>
#include <SeaPerch_SerialUtils.h>

#include "ControlSideCoder.h"

class ControlSideByteCoder : public ControlSideCoder {
public:
    explicit ControlSideByteCoder(HardwareSerial &serial);

    void toSerial(const ControlSpecs &controlSpecs) const;

    bool fromSerial(RobotData &robotData) const;
};

#endif