#ifndef _MotorExecutor_H
#define _MotorExecutor_H

#include <SeaPerch_MotorSpecs.h>
#include <Adafruit_MotorShield.h>
#include <utility/Adafruit_PWMServoDriver.h>

//Motors--------------------------------------------------------------------
Adafruit_MotorShield AFMS(0x61); //attach the board with 3 motors
Adafruit_DCMotor *leftMotor = AFMS.getMotor(1);
Adafruit_DCMotor *rightMotor = AFMS.getMotor(2);
Adafruit_DCMotor *upMotor = AFMS.getMotor(3);
int Motor1 = 255;
int Motor2 = 255;
int Motor3 = 255;
int Motor4 = 255;
int Motor5 = 255;
//--------------------------------------------------------------------------

void setupMotor(MotorSpecs &motorSpecs) {
    //---initialize the motor controller
    AFMS.begin();  // 1.6KHz PWM
    leftMotor->setSpeed(0);
    rightMotor->setSpeed(0);
    upMotor->setSpeed(0);
    //---------------------------------
}

void motor_execute(MotorSpecs &motorSpecs) {
    Motor1 = motorSpecs.getMotor(0);
    Motor2 = motorSpecs.getMotor(1);
    Motor3 = motorSpecs.getMotor(2);

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
        leftMotor->setSpeed(motorSpd4);
        leftMotor->run(FORWARD);
    }
    else {
        motorSpd4 = 255 - Motor1;
        motorSpd4 = map(motorSpd4, 0, 255, 30, 255); //eliminate motor dead end
        if (Motor1 >= 252) {
            motorSpd4 = 0;
        }
        leftMotor->setSpeed(motorSpd4);
        leftMotor->run(BACKWARD);
    }

    if (Motor2 >= 255) {
        motorSpd5 = Motor2 - 255;
        motorSpd5 = map(motorSpd5, 0, 255, 30, 255); //eliminate motor dead end
        if (Motor2 <= 258) {
            motorSpd5 = 0;
        }
        rightMotor->setSpeed(motorSpd5);
        rightMotor->run(FORWARD);
    }
    else {
        motorSpd5 = 255 - Motor2;
        motorSpd5 = map(motorSpd5, 0, 255, 30, 255); //eliminate motor dead end
        if (Motor2 >= 252) {
            motorSpd5 = 0;
        }

        rightMotor->setSpeed(motorSpd5);
        rightMotor->run(BACKWARD);
    }

    Motor3 -= 255;
    if (Motor3 <= -10) {
        upMotor->setSpeed(-1 * Motor3 * 0.7);
        upMotor->run(BACKWARD);
    } else if (Motor3 >= 10) {
        upMotor->setSpeed(Motor3 * 0.7);
        upMotor->run(FORWARD);
    } else {
        upMotor->setSpeed(0);
    }
}

#endif