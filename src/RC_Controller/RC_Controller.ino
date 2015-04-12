/*
SeaPerch Remote Control Test

Author: Qiuyang Tao
Electronic Team - Embeded System Group
Virtical Integrated Project - RoboSense
Georgia Institute of Technology

================= How to use ===============================================

*/
#include <Arduino.h>
#include <LiquidCrystal.h>
#include <SeaPerch_BinaryUtils.h>
#include <SeaPerch_ControlSpecs.h>

#include "ControlPin.h"
#include "LCDDisplayer.h"
#include "ControlReader.h"
#include "ControlSideByteCoder.h"

ControlSpecs controlSpecs;

//Serial Comm-------------------------
String Serial_1_data_recieved = "";
String Serial_2_data_recieved = "";
int Serial2_received_data_status = 0;  //0 for no valid data, 1 for valid data received

//Data feedback-----------------------
float robot_battery_voltage;

//Slide pot---------------------------
int depth_motor;

ControlSideByteCoder byteCoder = ControlSideByteCoder(Serial2);
ControlSideCoder &coder = byteCoder;
ControlReader controlReader;

LCDDisplayer lcdDisplayer;

void setup() {
    lcdDisplayer.initialize();

    pinMode(JOYSTICK_PUSHBUTTON, INPUT);
    digitalWrite(JOYSTICK_PUSHBUTTON, HIGH);

    Serial.begin(9600);
    Serial1.begin(9600);
    Serial2.begin(2400);

    controlReader.calibrate();
}

void loop() {
//    detectKey();

    controlReader.readControlSpecs(controlSpecs);
    coder.toSerial(controlSpecs);
    delay(100);

    lcdDisplayer.display(String() + "Battery Voltage:\n" + robot_battery_voltage + " V");
}
