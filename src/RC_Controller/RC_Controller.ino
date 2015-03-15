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

void setup() {
    lcdWelcome();

    //initializaion------------------
    pinMode(JOYSTICK_PUSHBUTTON, INPUT);
    digitalWrite(JOYSTICK_PUSHBUTTON, HIGH);

    Serial.begin(9600);
    Serial1.begin(9600);
    Serial2.begin(9600);

    controlReader.calibrate();
}

void loop() {
    detectKey();
    //--------------------------------------------------------
    controlReader.readControlSpecs(controlSpecs);
    coder.toSerial(controlSpecs);
    delay(200);

    serial_2_get_data_and_decode();

    serialDisplay();
    lcdDisplay(robot_battery_voltage);
    /*while (Serial2.available()) {
      int received = Serial2.read();
      Serial.write(received);
    }*/

    //Serial.print(Serial2_received_data_status);
}

void serialDisplay() {
//    Serial.print("Battery Voltage: ");
//    Serial.print(robot_battery_voltage);
//    Serial.println(" V");
}

void serial_2_get_data_and_decode() {
    if (Serial2.available() > 0) {
        Serial_2_data_recieved = Serial2.readStringUntil('\n');
        //Serial.println(Serial_2_data_recieved);
        //Serial.println(Serial_2_data_recieved.length());
        String head = Serial_2_data_recieved.substring(0, 1);  //if there is a valid start signal "#"
        if (head.equals("#") && (Serial_2_data_recieved.length() == 42)) {  //decompose the received string
            String str_normalized_joystick_X = Serial_2_data_recieved.substring(1, 6);
            String str_normalized_joystick_Y = Serial_2_data_recieved.substring(7, 12);
            String str_joystick_button = Serial_2_data_recieved.substring(13, 14);
            String str_Motor1 = Serial_2_data_recieved.substring(15, 18);
            String str_Motor2 = Serial_2_data_recieved.substring(19, 22);
            String str_Motor3 = Serial_2_data_recieved.substring(23, 26);
            String str_Motor4 = Serial_2_data_recieved.substring(27, 30);
            String str_Motor5 = Serial_2_data_recieved.substring(31, 34);
            String str_checksum = Serial_2_data_recieved.substring(35);

            //convert string to numerical value
            char buf1[str_normalized_joystick_X.length()];
            str_normalized_joystick_X.toCharArray(buf1, str_normalized_joystick_X.length() + 1);
            float temp_normalized_joystick_X = atof(buf1);
            char buf2[str_normalized_joystick_Y.length()];
            str_normalized_joystick_Y.toCharArray(buf2, str_normalized_joystick_Y.length() + 1);
            float temp_normalized_joystick_Y = atof(buf2);
            int temp_joystick_button = str_joystick_button.toInt();
            int temp_Motor1 = str_Motor1.toInt();
            int temp_Motor2 = str_Motor2.toInt();
            int temp_Motor3 = str_Motor3.toInt();
            int temp_Motor4 = str_Motor4.toInt();
            int temp_Motor5 = str_Motor5.toInt();
            char buf3[str_checksum.length()];
            str_checksum.toCharArray(buf1, str_checksum.length() + 1);
            float temp_checksum = atof(buf1);

            //calculate checksum
            float sum_of_received_data = temp_normalized_joystick_X + temp_normalized_joystick_Y + temp_joystick_button + temp_Motor1 + temp_Motor2 + temp_Motor3 + temp_Motor4 + temp_Motor5;

            //if data is valid
            if (sum_of_received_data == temp_checksum) {
                robot_battery_voltage = temp_normalized_joystick_X + 10;
                //normalized_joystick_Y= temp_normalized_joystick_Y;
                //joystick_button = temp_joystick_button;
                // Motor1=temp_Motor1;
                //Motor2=temp_Motor2;
                //Motor3=temp_Motor3;
                //Motor4=temp_Motor4;
                // Motor5=temp_Motor5;

                Serial2_received_data_status = 1;
            }
        }
    }
}