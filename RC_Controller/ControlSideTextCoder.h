#ifndef _ControlSideTextCoder_H
#define _ControlSideTextCoder_H

#include <Arduino.h>
#include "ControlSideCoder.h"

class ControlSideTextCoder : public ControlSideCoder {
public:
    explicit ControlSideTextCoder(HardwareSerial &serial);

    void toSerial(ControlSpecs &controlSpecs) const;

private:
    void sendMotorSpec(int motorSpec) const;
};

#endif