#include <Arduino.h>
#include <SeaPerch_AlgoUtils.h>

#include "RobotDataReader.h"

enum Pin {
    BATTERY_VOLTAGE = 15
};

RobotDataReader::RobotDataReader() : bmp(18001), mag(30302), accel(30301) { }

void RobotDataReader::intialize() {
    initSensors();
    pinMode(BATTERY_VOLTAGE, INPUT);
}

void RobotDataReader::initSensors() {
    if (!accel.begin()) {
        /* There was a problem detecting the LSM303 ... check your connections */
        Serial.println(F("Ooops, no LSM303 detected ... Check your wiring!"));
        while (1);
    }
    if (!mag.begin()) {
        /* There was a problem detecting the LSM303 ... check your connections */
        Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
        while (1);
    }
    if (!bmp.begin()) {
        /* There was a problem detecting the BMP180 ... check your connections */
        Serial.println("Ooops, no BMP180 detected ... Check your wiring!");
        while (1);
    }
}

void RobotDataReader::readRobotData(RobotData &robotData) {
    robotData.setOrientation(readOrientation());
//    robotData.setBatteryVoltage(readBatteryVoltage());
}

//const float RobotDataReader::readBatteryVoltage() const {
//    return AlgoUtils::map(analogRead(BATTERY_VOLTAGE), 0, 1023, 0, 15);
//}

const Orientation RobotDataReader::readOrientation() {
    sensors_event_t mag_event;
    sensors_vec_t orientation;
    sensors_event_t accel_event;

    /* Read the accelerometer and magnetometer */
    accel.getEvent(&accel_event);
    mag.getEvent(&mag_event);

    /* Use the new fusionGetOrientation function to merge accel/mag data */
    if (dof.fusionGetOrientation(&accel_event, &mag_event, &orientation)) {
        // switched pitch and roll due to hardware setup
        return Orientation(orientation.pitch, orientation.roll, orientation.heading);
    } else {
        return Orientation();
    }
}