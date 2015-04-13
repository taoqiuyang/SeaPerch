#include <Arduino.h>
#include <SeaPerch_AlgoUtils.h>

#include "RobotDataReader.h"

enum Pin {
    BATTERY_VOLTAGE = 15
};

RobotDataReader::RobotDataReader() { }

void RobotDataReader::intialize() {
    pinMode(BATTERY_VOLTAGE, INPUT);
}

void RobotDataReader::readRobotData(RobotData &robotData) const {
    robotData.setBatteryVoltage(readBatteryVoltage());
}

const float RobotDataReader::readBatteryVoltage() const {
    return AlgoUtils::map(analogRead(BATTERY_VOLTAGE), 0, 1023, 0, 15);
}