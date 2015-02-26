#include <arduino.h>

#include "MotorExecutor.h"

const int I2CAddress = 0x61;
enum MotorPosition {
    LEFT = 1, RIGHT = 2, UP = 3
};

MotorExecutor::MotorExecutor() : AFMS(I2CAddress) {
    leftMotor = AFMS.getMotor(LEFT);
    rightMotor = AFMS.getMotor(RIGHT);
    upMotor = AFMS.getMotor(UP);
}

void MotorExecutor::begin() {
    AFMS.begin();  // 1.6KHz PWM
    leftMotor->setSpeed(0);
    rightMotor->setSpeed(0);
    upMotor->setSpeed(0);
}

void MotorExecutor::execute(const ControlSpecs &controlSpecs) const {
    float normalizedX = controlSpecs.getNormalized_joystick_X();
    float normalizedY = controlSpecs.getNormalized_joystick_Y();

    float normalizedLeft = max(min(normalizedY + normalizedX, 1.0), -1.0); // [-1, 1]
    float normalizedRight = max(min(normalizedY - normalizedX, 1.0), -1.0); // [-1, 1]

    uint8_t leftDirection = normalizedLeft > 0 ? FORWARD : BACKWARD;
    uint8_t rightDirection = normalizedRight > 0 ? FORWARD : BACKWARD;

    int rawLeftMagnitude = abs((int)(normalizedLeft * 255));
    int rawRightMagnitude = abs((int)(normalizedRight * 255));
    int leftMagnitude = rawLeftMagnitude == 0 ? 0 : map(rawLeftMagnitude, 1, 255, 30, 150);
    int rightMagnitude = rawRightMagnitude == 0 ? 0 : map(rawRightMagnitude, 1, 255, 30, 150);

    leftMotor->setSpeed(leftMagnitude);
    leftMotor->run(leftDirection);
    rightMotor->setSpeed(rightMagnitude);
    rightMotor->run(rightDirection);

    //    uint8_t motorSpd1 = 0;
//    uint8_t motorSpd2 = 0;
//    uint8_t motorSpd3 = 0;
//    uint8_t motorSpd4 = 0;
//    uint8_t motorSpd5 = 0;
//
//    if (Motor1 >= 255) {
//        motorSpd4 = Motor1 - 255; //value [0,255]
//        motorSpd4 = map(motorSpd4, 0, 255, 30, 255); //eliminate motor dead end
//        if (Motor1 <= 258) {
//            motorSpd4 = 0;
//        } //joystick bias
//        leftMotor->setSpeed(motorSpd4);
//        leftMotor->run(FORWARD);
//    }
//    else {
//        motorSpd4 = 255 - Motor1;
//        motorSpd4 = map(motorSpd4, 0, 255, 30, 255); //eliminate motor dead end
//        if (Motor1 >= 252) {
//            motorSpd4 = 0;
//        }
//        leftMotor->setSpeed(motorSpd4);
//        leftMotor->run(BACKWARD);
//    }
//
//    if (Motor2 >= 255) {
//        motorSpd5 = Motor2 - 255;
//        motorSpd5 = map(motorSpd5, 0, 255, 30, 255); //eliminate motor dead end
//        if (Motor2 <= 258) {
//            motorSpd5 = 0;
//        }
//        rightMotor->setSpeed(motorSpd5);
//        rightMotor->run(FORWARD);
//    }
//    else {
//        motorSpd5 = 255 - Motor2;
//        motorSpd5 = map(motorSpd5, 0, 255, 30, 255); //eliminate motor dead end
//        if (Motor2 >= 252) {
//            motorSpd5 = 0;
//        }
//
//        rightMotor->setSpeed(motorSpd5);
//        rightMotor->run(BACKWARD);
//    }

//    int Motor1 = controlSpecs.getMotor(0);
//    int Motor2 = controlSpecs.getMotor(1);
//    int Motor3 = controlSpecs.getMotor(2);
//    Motor3 -= 255;
//    if (Motor3 <= -10) {
//        upMotor->setSpeed(-1 * Motor3 * 0.7);
//        upMotor->run(BACKWARD);
//    } else if (Motor3 >= 10) {
//        upMotor->setSpeed(Motor3 * 0.7);
//        upMotor->run(FORWARD);
//    } else {
//        upMotor->setSpeed(0);
//    }
}
