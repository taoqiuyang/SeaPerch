#ifndef _RobotSideByteCoder_H
#define _RobotSideByteCoder_H

#include <Arduino.h>
#include <SeaPerch_MotorSpecs.h>

class RobotSideByteCoder {
public:
    explicit RobotSideByteCoder(HardwareSerial &serial);

    bool fromSerial(MotorSpecs &motorSpecs) const;

private:
    HardwareSerial &serial;
};

#endif