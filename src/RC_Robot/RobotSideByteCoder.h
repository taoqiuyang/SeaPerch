#ifndef _RobotSideByteCoder_H
#define _RobotSideByteCoder_H

#include <Arduino.h>
#include "RobotSideCoder.h"

class RobotSideByteCoder : public RobotSideCoder {
public:
    explicit RobotSideByteCoder(HardwareSerial &serial);

    bool fromSerial(ControlSpecs &controlSpecs) const;

    void toSerial(const RobotData &robotData) const;
};

#endif