#ifndef SEAPERCH_ROBOTDATAREADER_H
#define SEAPERCH_ROBOTDATAREADER_H

#include <Adafruit_10DOF.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_BMP085_U.h>
#include <SeaPerch_RobotData.h>

class RobotDataReader {
public:
    explicit RobotDataReader();

    void intialize();

    void readRobotData(RobotData &robotData);

private:
    Adafruit_10DOF dof;
    Adafruit_BMP085_Unified bmp;
    Adafruit_LSM303_Mag_Unified mag;
    Adafruit_LSM303_Accel_Unified accel;

    sensors_event_t mag_event;
    sensors_event_t bmp_event;
    sensors_vec_t orientation;
    sensors_event_t accel_event;

    void initSensors();

    void updateOrientation();

    const float readBatteryVoltage() const;
};

#endif //SEAPERCH_ROBOTDATAREADER_H
