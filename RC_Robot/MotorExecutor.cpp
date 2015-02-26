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

void MotorExecutor::execute(const ControlSpecs &controlSpecs) {
    executeJoystickCommand(controlSpecs.getNormalized_joystick_X(), controlSpecs.getNormalized_joystick_Y());
    executeSlidePotCommand(controlSpecs.getSlidePot());
}

void MotorExecutor::executeJoystickCommand(float normalizedX, float normalizedY) {
    float normalizedLeft = max(min(normalizedX + normalizedY, 1.0), -1.0); // [-1, 1]
    float normalizedRight = max(min(normalizedX - normalizedY, 1.0), -1.0); // [-1, 1]

    uint8_t leftDirection = normalizedLeft > 0 ? FORWARD : BACKWARD;
    uint8_t rightDirection = normalizedRight > 0 ? FORWARD : BACKWARD;

    int rawLeftMagnitude = abs((int)(normalizedLeft * 255));
    int rawRightMagnitude = abs((int)(normalizedRight * 255));
    int leftMagnitude = rawLeftMagnitude == 0 ? 0 : map(rawLeftMagnitude, 5, 255, 30, 150);
    int rightMagnitude = rawRightMagnitude == 0 ? 0 : map(rawRightMagnitude, 5, 255, 30, 150);

    leftMotor->setSpeed(leftMagnitude);
    leftMotor->run(leftDirection);
    rightMotor->setSpeed(rightMagnitude);
    rightMotor->run(rightDirection);
}

void MotorExecutor::executeSlidePotCommand(int slidePotValue) {
    int rawUpPropulsion = map(slidePotValue, 0, 1023, -255, 255);
    uint8_t upDirection = rawUpPropulsion > 0 ? FORWARD : BACKWARD;
    int upMagnitude = (rawUpPropulsion < 5 && rawUpPropulsion > -5) ? 0 : map(abs(rawUpPropulsion), 5, 255, 30, 150);

    upMotor->setSpeed(upMagnitude);
    upMotor->run(upDirection);
}
