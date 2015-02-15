#ifndef _RobotSideCoder_H
#define _RobotSideCoder_H

#include <SeaPerch_MotorSpecs.h>

class RobotSideCoder {
public:
    explicit RobotSideCoder(HardwareSerial &serial) : serial(serial) {
    };

    bool fromSerial(MotorSpecs &motorSpecs) const;

protected:
    HardwareSerial &serial;
};

#endif