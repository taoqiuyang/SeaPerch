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
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); //attach the board with 3 motors
Adafruit_DCMotor *Motor_Driver_1 = AFMS.getMotor(1);
Adafruit_DCMotor *Motor_Driver_2 = AFMS.getMotor(2);
Adafruit_DCMotor *Motor_Driver_3 = AFMS.getMotor(3);
Adafruit_DCMotor *Motor_Driver_4 = AFMS.getMotor(4);
uint8_t motorSpd = 0;
int Motor1 = 255;
int Motor2 = 255;
int Motor3 = 255;
int Motor4 = 255;
int Motor5 = 255;


String Serial_1_data_recieved = "";
String Serial_2_data_recieved = "";
int Serial2_received_data_status = 0;  //0 for no valid data, 1 for valid data received

float normalized_joystick_X, normalized_joystick_Y, checksum;
int joystick_button;

const int BATTERY_MEASUREMENT_PIN = 15;
float battery_voltage, float_to_be_sent;
int int_to_be_sent_0, int_to_be_sent_1, int_to_be_sent_2, int_to_be_sent_3, int_to_be_sent_4;


void setup() {
    pinMode(BATTERY_MEASUREMENT_PIN, INPUT);
    Serial.begin(9600);
    Serial1.begin(9600);
    Serial2.begin(9600);

    //---initialize the motor controller
    AFMS.begin();  // 1.6KHz PWM

    Motor_Driver_1->setSpeed(motorSpd);
    Motor_Driver_2->setSpeed(motorSpd);
    Motor_Driver_3->setSpeed(motorSpd);
    Motor_Driver_4->setSpeed(motorSpd);
}


void loop() {



    //Serial_1_send_data();


    serial_2_get_data_and_decode();
    //Serial.print(Serial2_received_data_status);
    motor_execute();

    get_sensor_data();
    checksum = battery_voltage + normalized_joystick_Y + joystick_button + Motor1 + Motor2 + Motor3 + Motor4 + Motor5;
    serial_2_send_data();
    delay(20);

    /*while (Serial2.available()) {
    int received = Serial2.read();
    Serial.write(received); 
  }*/

}


void get_sensor_data() {
    battery_voltage = analogRead(BATTERY_MEASUREMENT_PIN);
    battery_voltage = battery_voltage / 1024.0 * 5.0 * 3.0 - 10;
}


void motor_execute() {
    uint8_t motorSpd1 = 0;
    uint8_t motorSpd2 = 0;
    uint8_t motorSpd3 = 0;
    uint8_t motorSpd4 = 0;
    uint8_t motorSpd5 = 0;

    if (Motor1 >= 255) {
        motorSpd4 = Motor1 - 255; //value [0,255]
        motorSpd4 = map(motorSpd4, 0, 255, 30, 255); //eliminate motor dead end
        if (Motor1 <= 258) {motorSpd4 = 0;} //joystick bias
        Motor_Driver_1->setSpeed(motorSpd4);
        Motor_Driver_1->run(FORWARD);
    } else {
        motorSpd4 = 255 - Motor1;
        motorSpd4 = map(motorSpd4, 0, 255, 30, 255); //eliminate motor dead end
        if (Motor1 >= 252) {motorSpd4 = 0;}
        Motor_Driver_1->setSpeed(motorSpd4);
        Motor_Driver_1->run(BACKWARD);
    }

    if (Motor2 >= 255) {
        motorSpd5 = Motor2 - 255;
        motorSpd5 = map(motorSpd5, 0, 255, 30, 255); //eliminate motor dead end
        if (Motor2 <= 258) {motorSpd5 = 0;}
        Motor_Driver_2->setSpeed(motorSpd5);
        Motor_Driver_2->run(FORWARD);
    } else {
        motorSpd5 = 255 - Motor2;
        motorSpd5 = map(motorSpd5, 0, 255, 30, 255); //eliminate motor dead end
        if (Motor2 >= 252) {motorSpd5 = 0;}

        Motor_Driver_2->setSpeed(motorSpd5);
        Motor_Driver_2->run(BACKWARD);
    }

//    Motor3 -= 255;
//    if (Motor3 <= -10) {
//        Motor_Driver_3->setSpeed(-1 * Motor3 * 0.7);
//        Motor_Driver_3->run(BACKWARD);
//    } else if (Motor3 >= 10){
//        Motor_Driver_3->setSpeed(Motor3 * 0.7);
//        Motor_Driver_3->run(FORWARD);
//    } else {
//        Motor_Driver_3->setSpeed(0);
//    }
}


void serial_2_send_data() {
    Serial2.flush();
    Serial2.print("#");
    Serial2.print(battery_voltage, 3);
    Serial2.print(",");
    Serial2.print(normalized_joystick_Y, 3);
    Serial2.print(",");
    Serial2.print(joystick_button);
    Serial2.print(",");
    Serial2.print(Motor1 / 100);
    Serial2.print((Motor1 - (Motor1 / 100) * 100) / 10);
    Serial2.print(Motor1 % 10);
    Serial2.print(",");
    Serial2.print(Motor2 / 100);
    Serial2.print((Motor2 - (Motor2 / 100) * 100) / 10);
    Serial2.print(Motor2 % 10);
    Serial2.print(",");
    Serial2.print(Motor3 / 100);
    Serial2.print((Motor3 - (Motor3 / 100) * 100) / 10);
    Serial2.print(Motor3 % 10);
    Serial2.print(",");
    Serial2.print(Motor4 / 100);
    Serial2.print((Motor4 - (Motor4 / 100) * 100) / 10);
    Serial2.print(Motor4 % 10);
    Serial2.print(",");
    Serial2.print(Motor5 / 100);
    Serial2.print((Motor5 - (Motor5 / 100) * 100) / 10);
    Serial2.print(Motor5 % 10);
    Serial2.print(",");
    Serial2.print(checksum, 3);

    Serial2.print("\n");
}


void serial_2_get_data_and_decode() {
    if (Serial2.available() > 0) {
        Serial_2_data_recieved = Serial2.readStringUntil('\n');
        Serial.println(Serial_2_data_recieved);
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
                normalized_joystick_X = temp_normalized_joystick_X;
                normalized_joystick_Y = temp_normalized_joystick_Y;
                joystick_button = temp_joystick_button;
                Motor1 = temp_Motor1;
                Motor2 = temp_Motor2;
                Motor3 = temp_Motor3;
                Motor4 = temp_Motor4;
                Motor5 = temp_Motor5;

                Serial2_received_data_status = 1;
            }
        }
    }
}



    

