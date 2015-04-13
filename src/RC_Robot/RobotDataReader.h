#ifndef SEAPERCH_ROBOTDATAREADER_H
#define SEAPERCH_ROBOTDATAREADER_H

#include <SeaPerch_RobotData.h>

class RobotDataReader {
public:
    explicit RobotDataReader();

    void intialize();

    void readRobotData(RobotData &robotData) const;

private:
    const float readBatteryVoltage() const;
};

#endif //SEAPERCH_ROBOTDATAREADER_H
