#include "SeaPerch_RobotData.h"

RobotData::RobotData() { }

const float RobotData::getBatteryVoltage() const {
    return batteryVoltage;
}

void RobotData::setBatteryVoltage(const float aBatteryVoltage) {
    batteryVoltage = aBatteryVoltage;
}