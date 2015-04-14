#ifndef SEAPERCH_ROBOTDATA_H
#define SEAPERCH_ROBOTDATA_H

#include "SeaPerch_Orientation.h"

class RobotData {
public:
    explicit RobotData();

//    float getBatteryVoltage() const;
//
//    void setBatteryVoltage(const float aBatteryVoltage);

    Orientation const &getOrientation() const;

    void setOrientation(Orientation const &orientation);

private:
//    float batteryVoltage;
    Orientation orientation;
};

#endif //SEAPERCH_ROBOTDATA_H
