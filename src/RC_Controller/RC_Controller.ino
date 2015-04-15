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
#include <SeaPerch_RobotData.h>
#include <SeaPerch_ControlMode.h>
#include <SeaPerch_BinaryUtils.h>
#include <SeaPerch_SerialUtils.h>
#include <SeaPerch_ControlSpecs.h>
#include <SeaPerch_Orientation.h>

#include "Key.h"
#include "ControlPin.h"
#include "KeyDetector.h"
#include "LCDDisplayer.h"
#include "ControlReader.h"
#include "ControlSideByteCoder.h"

RobotData robotData;
ControlSpecs controlSpecs;
LCDDisplayer lcdDisplayer;
KeyDetector keyDetector;
ControlReader controlReader(keyDetector, lcdDisplayer);
ControlSideByteCoder byteCoder = ControlSideByteCoder(Serial2);
ControlSideCoder &coder = byteCoder;

void setup() {
    lcdDisplayer.initialize();

    Serial.begin(9600);
    Serial1.begin(9600);
    Serial2.begin(2400);

    controlReader.initialize();
}

void loop() {
    controlReader.readControlSpecs(controlSpecs);
    coder.toSerial(controlSpecs);
    byteCoder.fromSerial(robotData);
    const Orientation &orientation = robotData.getOrientation();
    lcdDisplayer.display("roll: " + String(orientation.getRoll()) + "\npitch: " +  String(orientation.getPitch()));
    delay(100);
}
