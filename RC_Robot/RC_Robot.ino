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
//Motor Libs-------------------
#include <Adafruit_MotorShield.h>
//-----------------------------

//IMU Libs---------------------
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_BMP085_U.h>
#include <Adafruit_10DOF.h>
//----------------------------

#include "RobotSideByteCoder.h"
#include "utility/Adafruit_PWMServoDriver.h"

//IMU----------------------------------------------------------------------
Adafruit_10DOF                dof   = Adafruit_10DOF();
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(30301);
Adafruit_LSM303_Mag_Unified   mag   = Adafruit_LSM303_Mag_Unified(30302);
Adafruit_BMP085_Unified       bmp   = Adafruit_BMP085_Unified(18001);
float seaLevelPressure = SENSORS_PRESSURE_SEALEVELHPA;
double yaw,pitch,roll,temperature_IMU,alt_IMU;
//--------------------------------------------------------------------------

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

float normalized_joystick_X, normalized_joystick_Y, checksum;
int joystick_button;

const int BATTERY_MEASUREMENT_PIN = 15;
float battery_voltage, float_to_be_sent;
int int_to_be_sent_0, int_to_be_sent_1, int_to_be_sent_2, int_to_be_sent_3, int_to_be_sent_4;

RobotSideByteCoder byteCoder(Serial2);
MotorSpecs motorSpecs(5);

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
  for (int i = 0; i < motorSpecs.getMotorCount(); i++) {
    motorSpecs.setMotor(i, 0);
  }
  //---------------------------------

  //---initialize the IMU------------
  initSensors();
  //---------------------------------

}


void loop() {
  /* ----Xinyi---------------------------------
   Serial.println("Calling Coder!");
   if (byteCoder.fromSerial(motorSpecs)) {
   Motor1 = motorSpecs.getMotor(0);
   Motor2 = motorSpecs.getMotor(1);
   Motor3 = motorSpecs.getMotor(2);
   Motor4 = motorSpecs.getMotor(3);
   Motor5 = motorSpecs.getMotor(4);
   Serial.print("Motor1: ");
   Serial.print(Motor1);
   Serial.print("Motor2: ");
   Serial.print(Motor2);
   Serial.print("Motor3: ");
   Serial.print(Motor3);
   Serial.print("Motor4: ");
   Serial.print(Motor4);
   Serial.print("Motor5: ");
   Serial.print(Motor5);
   Serial.println();
   motor_execute();
   }-------------------------------------------*/
  //
      
  //    checksum = battery_voltage + normalized_joystick_Y + joystick_button + Motor1 + Motor2 + Motor3 + Motor4 + Motor5;
  //    serial_2_send_data();

    get_sensor_data();
    Serial.print("roll: ");
    Serial.print(roll);
    Serial.print("   pitch: ");
    Serial.print(pitch);
    Serial.print("   yaw: ");
    Serial.print(yaw);
    Serial.println();

  delay(20);
}


void get_sensor_data() {
  //Battery voltage---------------------------------------------
  battery_voltage = analogRead(BATTERY_MEASUREMENT_PIN);
  battery_voltage = battery_voltage / 1024.0 * 5.0 * 3.0 - 10;
  //------------------------------------------------------------

  //IMU---------------------------------------------------------
  sensors_event_t accel_event;
  sensors_event_t mag_event;
  sensors_event_t bmp_event;
  sensors_vec_t   orientation;

  /* Read the accelerometer and magnetometer */
  accel.getEvent(&accel_event);
  mag.getEvent(&mag_event);

  /* Use the new fusionGetOrientation function to merge accel/mag data */
  if (dof.fusionGetOrientation(&accel_event, &mag_event, &orientation))
  {
    /* 'orientation' should have valid .roll and .pitch fields */
    roll= orientation.roll;
    pitch=orientation.pitch;
    yaw=orientation.heading;
  }

  bmp.getEvent(&bmp_event);
  if (bmp_event.pressure)
  {
    /* Get ambient temperature in C */
    float temperature;
    bmp.getTemperature(&temperature);
    /* Convert atmospheric pressure, SLP and temp to altitude */
    alt_IMU=bmp.pressureToAltitude(seaLevelPressure,bmp_event.pressure,temperature); 
    temperature_IMU=temperature;
  }
  //---------------------------------------------------------------
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
    if (Motor1 <= 258) {
      motorSpd4 = 0;
    } //joystick bias
    Motor_Driver_1->setSpeed(motorSpd4);
    Motor_Driver_1->run(FORWARD);
  } 
  else {
    motorSpd4 = 255 - Motor1;
    motorSpd4 = map(motorSpd4, 0, 255, 30, 255); //eliminate motor dead end
    if (Motor1 >= 252) {
      motorSpd4 = 0;
    }
    Motor_Driver_1->setSpeed(motorSpd4);
    Motor_Driver_1->run(BACKWARD);
  }

  if (Motor2 >= 255) {
    motorSpd5 = Motor2 - 255;
    motorSpd5 = map(motorSpd5, 0, 255, 30, 255); //eliminate motor dead end
    if (Motor2 <= 258) {
      motorSpd5 = 0;
    }
    Motor_Driver_2->setSpeed(motorSpd5);
    Motor_Driver_2->run(FORWARD);
  } 
  else {
    motorSpd5 = 255 - Motor2;
    motorSpd5 = map(motorSpd5, 0, 255, 30, 255); //eliminate motor dead end
    if (Motor2 >= 252) {
      motorSpd5 = 0;
    }

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

void initSensors()
{
  if(!accel.begin())
  {
    /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println(F("Ooops, no LSM303 detected ... Check your wiring!"));
    while(1);
  }
  if(!mag.begin())
  {
    /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    while(1);
  }
  if(!bmp.begin())
  {
    /* There was a problem detecting the BMP180 ... check your connections */
    Serial.println("Ooops, no BMP180 detected ... Check your wiring!");
    while(1);
  }
}



