#include "SeaPerch_RobotData.h"

RobotData::RobotData() { }

//float RobotData::getBatteryVoltage() const {
//    return batteryVoltage;
//}
//
//void RobotData::setBatteryVoltage(const float aBatteryVoltage) {
//    batteryVoltage = aBatteryVoltage;
//}

Orientation const &RobotData::getOrientation() const {
    return orientation;
}

void RobotData::setOrientation(Orientation const &orientation) {
    RobotData::orientation = orientation;
}