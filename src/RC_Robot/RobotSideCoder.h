#ifndef _RobotSideCoder_H
#define _RobotSideCoder_H

#include <SeaPerch_ControlSpecs.h>
#include <SeaPerch_RobotData.h>

class RobotSideCoder {
public:
    explicit RobotSideCoder(HardwareSerial &serial) : serial(serial) {
    };

    virtual bool fromSerial(ControlSpecs &controlSpecs) const = 0;

    virtual void toSerial(const RobotData &robotData) const = 0;

protected:
    HardwareSerial &serial;
};

#endif