/*
SeaPerch Remote Control Test
 
 Author: Qiuyang Tao
 Electronic Team - Embeded System Group
 Virtical Integrated Project - RoboSense
 Georgia Institute of Technology
 
 =================Description================================================
 Read the data come form serial port 2, decode and drive the motor
 
 
 ================= How to use ===============================================
 
 */
//I2C lib
#include <Wire.h>
//PID lib
#include <PID_v1.h>

//Motor Driver Libs------------
#include <Servo.h>
//-----------------------------

//Depth Sensor Libs------------
#include <MS5803_I2C.h>
//-----------------------------

//IMU Libs---------------------
#include <Adafruit_Sensor.h>
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_BMP085_U.h>
#include <Adafruit_10DOF.h>
//----------------------------

#include <Arduino.h>
#include <SeaPerch_AlgoUtils.h>
#include <SeaPerch_RobotData.h>
#include <SeaPerch_Orientation.h>
#include <SeaPerch_BinaryUtils.h>
#include <SeaPerch_SerialUtils.h>
#include <SeaPerch_ControlSpecs.h>

#include "MotorExecutor.h"
#include "RobotDataReader.h"
#include "RobotSideByteCoder.h"

//IMU----------------------------------------------------------------------
float seaLevelPressure = SENSORS_PRESSURE_SEALEVELHPA;
double yaw, pitch, roll, temperature_IMU, alt_IMU;
//--------------------------------------------------------------------------

//Depth Sensor--------------------------------------------------------------
MS5803 sensor(ADDRESS_HIGH); //ADDRESS_HIGH=0x76 ADDRESS_LOW=0x77 default is HIGH  
float temperature_c, temperature_f;
double pressure_abs, pressure_relative, altitude_delta, pressure_baseline;
// Create Variable to store altitude in (m) for calculations;
double base_altitude = 1655.0; // Altitude of SparkFun's HQ in Boulder, CO. in (m)
//--------------------------------------------------------------------------

unsigned long lastSignalTimestamp;
unsigned long TIMEOUT_THRESHOLD_MS = 1000;

RobotData robotData;
ControlSpecs controlSpecs;
RobotDataReader dataReader;
MotorExecutor motorExecutor;
RobotSideByteCoder byteCoder(Serial2);

void setup() {
    Serial.begin(9600);
    Serial1.begin(9600);
    Serial2.begin(2400);
    Serial2.setTimeout(10);

    //---initialize Depth Sensor-------
    sensor.reset();
    sensor.begin();
    pressure_baseline = sensor.getPressure(ADC_4096);
    //---------------------------------

    dataReader.intialize();
    motorExecutor.initialize(pressure_baseline);
}


void loop() {
    if (byteCoder.fromSerial(controlSpecs)) {
        lastSignalTimestamp = millis();
        motorExecutor.execute(controlSpecs, sensor.getPressure(ADC_4096));
        dataReader.readRobotData(robotData);
        delay(300);
        byteCoder.toSerial(robotData);
    } else {
        unsigned long currentTime = millis();
        if (currentTime - lastSignalTimestamp >= TIMEOUT_THRESHOLD_MS) {
            motorExecutor.emergencyBrake();
        }
    }

//    get_sensor_data();
//    Serial.print("  roll: ");
//    Serial.print(roll);
//    Serial.print("  pitch: ");
//    Serial.print(pitch);
//    Serial.print("  yaw: ");
//    Serial.print(yaw);
//    Serial.print("  temp_IMU:");
//    Serial.print(temperature_IMU);
//    Serial.print("  Temp Dep: ");
//    Serial.print(temperature_c);
//    Serial.print("  Pres(mbar): ");
//    Serial.println(pressure_abs);
//    Serial.println();
}


//void get_sensor_data() {
//    //IMU---------------------------------------------------------
//    sensors_event_t accel_event;
//    sensors_event_t mag_event;
//    sensors_event_t bmp_event;
//    sensors_vec_t orientation;
//    /* Read the accelerometer and magnetometer */
//    accel.getEvent(&accel_event);
//    mag.getEvent(&mag_event);
//    /* Use the new fusionGetOrientation function to merge accel/mag data */
//    if (dof.fusionGetOrientation(&accel_event, &mag_event, &orientation)) {
//        /* 'orientation' should have valid .roll and .pitch fields */
//        roll = orientation.roll;
//        pitch = orientation.pitch;
//        yaw = orientation.heading;
//    }
//    bmp.getEvent(&bmp_event);
//    if (bmp_event.pressure) {
//        /* Get ambient temperature in C */
//        float temperature;
//        bmp.getTemperature(&temperature);
//        /* Convert atmospheric pressure, SLP and temp to altitude */
//        alt_IMU = bmp.pressureToAltitude(seaLevelPressure, bmp_event.pressure, temperature);
//        temperature_IMU = temperature;
//    }
//    //---------------------------------------------------------------
//
//    //Depth Sensor---------------------------------------------------
//    // To measure to higher degrees of precision use the following sensor settings:
//    // ADC_256
//    // ADC_512
//    // ADC_1024
//    // ADC_2048
//    // ADC_4096
//    temperature_c = sensor.getTemperature(CELSIUS, ADC_512);
//    temperature_f = sensor.getTemperature(FAHRENHEIT, ADC_512);
//    pressure_abs = sensor.getPressure(ADC_4096);
//    pressure_relative = sealevel(pressure_abs, base_altitude);
//    altitude_delta = altitude(pressure_abs, pressure_baseline);
//    //---------------------------------------------------------------
//}

double sealevel(double P, double A)
// Given a pressure P (mbar) taken at a specific altitude (meters),
// return the equivalent pressure (mbar) at sea level.
// This produces pressure readings that can be used for weather measurements.
{
    return (P / pow(1 - (A / 44330.0), 5.255));
}


double altitude(double P, double P0)
// Given a pressure measurement P (mbar) and the pressure at a baseline P0 (mbar),
// return altitude (meters) above baseline.
{
    return (44330.0 * (1 - pow(P / P0, 1 / 5.255)));
}
