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
    VERTICAL_RIGHT = 5
};

MotorExecutor::MotorExecutor() : myPID(&pidInput, &pidOutput, &pidSetpoint, Kp, Ki, Kd, DIRECT) {
    horizontalLeft.attach(HORIZONTAL_LEFT);
    horizontalRight.attach(HORIZONTAL_RIGHT);
    verticalLeft.attach(VERTICAL_LEFT);
    verticalRight.attach(VERTICAL_RIGHT);
}

void MotorExecutor::initialize(const double aPressureBase) {
    pressureBase = aPressureBase;
    pressureCap = pressureBase + MAX_ALLOWED_DEPTH;

    horizontalLeft.write(STILL_MOTOR_SPEED);
    horizontalRight.write(STILL_MOTOR_SPEED);
    verticalLeft.write(STILL_MOTOR_SPEED);
    verticalRight.write(STILL_MOTOR_SPEED);

    myPID.SetOutputLimits(MIN_MOTOR_SPEED, MAX_MOTOR_SPEED);
    myPID.SetMode(AUTOMATIC);
}

void MotorExecutor::execute(const ControlSpecs &controlSpecs, const double currentDepth) {
//    executeHorizontalMotors(controlSpecs.getNormalized_joystick_X(), controlSpecs.getNormalized_joystick_Y());

//    ControlMode slidePotMode = controlSpecs.getSlidePotMode();
//    if (slidePotMode == DEPTH) {
//        executeDepthControlledVerticalMotor(controlSpecs.getSlidePotValue(), currentDepth);
//    } else if (slidePotMode == SPEED){
//        executeSpeedControlledVerticalMotor(controlSpecs.getSlidePotValue());
//    }
}

void MotorExecutor::executeHorizontalMotors(const float normalizedX, const float normalizedY) {
    float normalizedLeft = max(min(normalizedX + normalizedY, 1.0), -1.0); // [-1, 1]
    float normalizedRight = max(min(normalizedX - normalizedY, 1.0), -1.0); // [-1, 1]

    int leftSpeed = (int)map(normalizedLeft, -1, 1, MIN_ALLOWED_SPEED, MAX_ALLOWED_SPEED);
    int rightSpeed = (int)map(normalizedRight, -1, 1, MIN_ALLOWED_SPEED, MAX_ALLOWED_SPEED);

    horizontalLeft.write(leftSpeed);
    horizontalRight.write(rightSpeed);
}

void MotorExecutor::executeSpeedControlledVerticalMotor(const int speedInput) {
//    int rawVerticalPropulsion = map(speedInput, 0, 1023, -1 * MAX_MOTOR_SPEED, MAX_MOTOR_SPEED);
//    int verticalMagnitude = (rawVerticalPropulsion < MIN_MOTOR_SPEED && rawVerticalPropulsion > -1 * MIN_MOTOR_SPEED) ? 0
//            : map(abs(rawVerticalPropulsion), MIN_MOTOR_SPEED, MAX_MOTOR_SPEED, MIN_ALLOWED_SPEED, MAX_ALLOWED_SPEED);
//    uint8_t verticalDirection = rawVerticalPropulsion > 0 ? FORWARD : BACKWARD;
//
//    vertialLeft->setSpeed(verticalMagnitude);
//    vertialLeft->run(verticalDirection);
}

void MotorExecutor::executeDepthControlledVerticalMotor(const int depthInput, const double currentDepth) {
//    pidInput = currentDepth;
//    pidSetpoint = AlgoUtils::map(depthInput, 0, 1023, pressureBase, pressureCap);
//    myPID.Compute();
//
//    uint8_t verticalDirection = pidOutput > 0 ? FORWARD : BACKWARD;
//    int verticalMagnitude = abs((int)pidOutput);
//
//    vertialLeft->setSpeed(verticalMagnitude);
//    vertialLeft->run(verticalDirection);
}
