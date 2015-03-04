#ifndef _RobotSideCoder_H
#define _RobotSideCoder_H

#include <SeaPerch_ControlSpecs.h>

class RobotSideCoder {
public:
    explicit RobotSideCoder(HardwareSerial &serial) : serial(serial) {
    };

    bool fromSerial(ControlSpecs &controlSpecs) const;

protected:
    HardwareSerial &serial;
};

#endif