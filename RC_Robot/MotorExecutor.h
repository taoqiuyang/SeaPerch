#ifndef _MotorExecutor_H
#define _MotorExecutor_H

#include <SeaPerch_MotorSpecs.h>

//Motors--------------------------------------------------------------------
Adafruit_MotorShield AFMS(0x61); //attach the board with 3 motors
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
//--------------------------------------------------------------------------

void setupMotor(MotorSpecs &motorSpecs) {
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

    Motor3 -= 255;
    if (Motor3 <= -10) {
        Motor_Driver_3->setSpeed(-1 * Motor3 * 0.7);
        Motor_Driver_3->run(BACKWARD);
    } else if (Motor3 >= 10) {
        Motor_Driver_3->setSpeed(Motor3 * 0.7);
        Motor_Driver_3->run(FORWARD);
    } else {
        Motor_Driver_3->setSpeed(0);
    }
}

void unpackSpecs(MotorSpecs &motorSpecs) {
    Motor1 = motorSpecs.getMotor(0);
    Motor2 = motorSpecs.getMotor(1);
    Motor3 = motorSpecs.getMotor(2);
    Motor4 = motorSpecs.getMotor(3);
    Motor5 = motorSpecs.getMotor(4);
    motor_execute();
}

#endif