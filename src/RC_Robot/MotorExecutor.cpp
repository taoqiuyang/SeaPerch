#include <arduino.h>

#include "MotorExecutor.h"
#include "SeaPerch_AlgoUtils.h"
#include "SeaPerch_ControlMode.h"

const int MAX_MOTOR_SPEED = 160;
const int STILL_MOTOR_SPEED = 90;
const int MIN_MOTOR_SPEED = 20;
const int MAX_ALLOWED_SPEED = 120;
const int MIN_ALLOWED_SPEED = 60;
const int MAX_ALLOWED_DEPTH = 1000; // mbar

//initial tuning parameters
const double Kp = 5;
const double Ki = 0.0;
const double Kd = 0.0;

enum MotorID {
    HORIZONTAL_LEFT = 2,
    HORIZONTAL_RIGHT = 3,
    VERTICAL_LEFT = 4,
    VERTICAL_RIGHT = 5,
};

MotorExecutor::MotorExecutor() : myPID(&pidInput, &pidOutput, &pidSetpoint, Kp, Ki, Kd, DIRECT) {
}

void MotorExecutor::initialize(const double aPressureBase) {
    pressureBase = aPressureBase;
    pressureCap = pressureBase + MAX_ALLOWED_DEPTH;

    horizontalLeft.attach(HORIZONTAL_LEFT);
    horizontalRight.attach(HORIZONTAL_RIGHT);
    verticalLeft.attach(VERTICAL_LEFT);
    verticalRight.attach(VERTICAL_RIGHT);

    myPID.SetOutputLimits(MIN_MOTOR_SPEED, MAX_MOTOR_SPEED);
    myPID.SetMode(AUTOMATIC);
}

void MotorExecutor::execute(const ControlSpecs &controlSpecs, const double currentDepth) {
    executeHorizontalMotors(controlSpecs.getNormalized_joystick_X(), controlSpecs.getNormalized_joystick_Y());

    ControlMode slidePotMode = controlSpecs.getSlidePotMode();
    if (slidePotMode == DEPTH) {
        executeDepthControlledVerticalMotor(controlSpecs.getSlidePotValue(), currentDepth);
    } else if (slidePotMode == SPEED){
        executeSpeedControlledVerticalMotor(controlSpecs.getSlidePotValue());
    }
}

void MotorExecutor::executeHorizontalMotors(const float normalizedX, const float normalizedY) {
    float normalizedLeft = max(min(normalizedX + normalizedY, 1.0), -1.0); // [-1, 1]
    float normalizedRight = max(min(normalizedX - normalizedY, 1.0), -1.0); // [-1, 1]
    Serial.print(normalizedLeft);
    Serial.println();
    Serial.print(normalizedRight);
    Serial.println();

    int leftSpeed = (int)(AlgoUtils::map(normalizedLeft, -1, 1, MIN_ALLOWED_SPEED, MAX_ALLOWED_SPEED));
    int rightSpeed = (int)(AlgoUtils::map(normalizedRight, -1, 1, MIN_ALLOWED_SPEED, MAX_ALLOWED_SPEED));
    Serial.print(leftSpeed);
    Serial.println();
    Serial.print(rightSpeed);
    Serial.println();

    horizontalLeft.write(leftSpeed);
    horizontalRight.write(rightSpeed);
}

void MotorExecutor::executeSpeedControlledVerticalMotor(const int speedInput) {
    int verticalSpeed = map(speedInput, 0, 1023, MIN_ALLOWED_SPEED, MAX_ALLOWED_SPEED);

    verticalLeft.write(verticalSpeed);
    verticalRight.write(verticalSpeed);
}

void MotorExecutor::executeDepthControlledVerticalMotor(const int depthInput, const double currentDepth) {
    pidInput = currentDepth;
    pidSetpoint = AlgoUtils::map(depthInput, 0, 1023, pressureBase, pressureCap);
    myPID.Compute();

    int verticalSpeed = map((int)pidOutput, -255, 255, MIN_ALLOWED_SPEED, MAX_ALLOWED_SPEED);

    verticalLeft.write(verticalSpeed);
    verticalRight.write(verticalSpeed);
}
