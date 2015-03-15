#include <arduino.h>

#include "MotorExecutor.h"
#include "SeaPerch_AlgoUtils.h"

const int I2C_ADDR = 0x61;
const int MAX_MOTOR_SPEED = 255;
const int MIN_MOTOR_SPEED = 5;
const int MAX_ALLOWED_SPEED = 150;
const int MIN_ALLOWED_SPEED = 30;
const int MAX_ALLOWED_DEPTH = 1000; // mbar

//initial tuning parameters
const double Kp = 5;
const double Ki = 0.0;
const double Kd = 0.0;

enum MotorPosition {
    LEFT = 1, RIGHT = 2, VERTICAL = 3
};

MotorExecutor::MotorExecutor() : AFMS(I2C_ADDR), myPID(&pidInput, &pidOutput, &pidSetpoint, Kp, Ki, Kd, DIRECT) {
    leftMotor = AFMS.getMotor(LEFT);
    rightMotor = AFMS.getMotor(RIGHT);
    verticalMotor = AFMS.getMotor(VERTICAL);
}

void MotorExecutor::initialize(const double aPressureBase) {
    pressureBase = aPressureBase;
    pressureCap = pressureBase + MAX_ALLOWED_DEPTH;

    AFMS.begin();  // 1.6KHz PWM
    leftMotor->setSpeed(0);
    rightMotor->setSpeed(0);
    verticalMotor->setSpeed(0);

    myPID.SetOutputLimits(-1 * MAX_MOTOR_SPEED, MAX_MOTOR_SPEED);
    myPID.SetMode(AUTOMATIC);
}

void MotorExecutor::execute(const ControlSpecs &controlSpecs, const double currentDepth) {
    executeHorizontalMotors(controlSpecs.getNormalized_joystick_X(), controlSpecs.getNormalized_joystick_Y());
//    executeSpeedControlledVerticalMotor(controlSpecs.getSlidePot());
    executeDepthControlledVerticalMotor(controlSpecs.getSlidePot(), currentDepth);
}

void MotorExecutor::executeHorizontalMotors(const float normalizedX, const float normalizedY) {
    float normalizedLeft = max(min(normalizedX + normalizedY, 1.0), -1.0); // [-1, 1]
    float normalizedRight = max(min(normalizedX - normalizedY, 1.0), -1.0); // [-1, 1]

    uint8_t leftDirection = normalizedLeft > 0 ? FORWARD : BACKWARD;
    uint8_t rightDirection = normalizedRight > 0 ? FORWARD : BACKWARD;

    int rawLeftMagnitude = abs((int)(normalizedLeft * MAX_MOTOR_SPEED));
    int rawRightMagnitude = abs((int)(normalizedRight * MAX_MOTOR_SPEED));
    int leftMagnitude = rawLeftMagnitude == 0 ? 0 : map(rawLeftMagnitude, MIN_MOTOR_SPEED, MAX_MOTOR_SPEED, MIN_ALLOWED_SPEED, MAX_ALLOWED_SPEED);
    int rightMagnitude = rawRightMagnitude == 0 ? 0 : map(rawRightMagnitude, MIN_MOTOR_SPEED, MAX_MOTOR_SPEED, MIN_ALLOWED_SPEED, MAX_ALLOWED_SPEED);

    leftMotor->setSpeed(leftMagnitude);
    leftMotor->run(leftDirection);
    rightMotor->setSpeed(rightMagnitude);
    rightMotor->run(rightDirection);
}

void MotorExecutor::executeSpeedControlledVerticalMotor(const int speedInput) {
    int rawVerticalPropulsion = map(speedInput, 0, 1023, -1 * MAX_MOTOR_SPEED, MAX_MOTOR_SPEED);
    int verticalMagnitude = (rawVerticalPropulsion < MIN_MOTOR_SPEED && rawVerticalPropulsion > -1 * MIN_MOTOR_SPEED) ? 0
            : map(abs(rawVerticalPropulsion), MIN_MOTOR_SPEED, MAX_MOTOR_SPEED, MIN_ALLOWED_SPEED, MAX_ALLOWED_SPEED);
    uint8_t verticalDirection = rawVerticalPropulsion > 0 ? FORWARD : BACKWARD;

    verticalMotor->setSpeed(verticalMagnitude);
    verticalMotor->run(verticalDirection);
}

void MotorExecutor::executeDepthControlledVerticalMotor(const int depthInput, const double currentDepth) {
    pidInput = currentDepth;
    pidSetpoint = AlgoUtils::map(depthInput, 0, 1023, pressureBase, pressureCap);
    myPID.Compute();

    uint8_t verticalDirection = pidOutput > 0 ? FORWARD : BACKWARD;
    int verticalMagnitude = abs((int)pidOutput);

    verticalMotor->setSpeed(verticalMagnitude);
    verticalMotor->run(verticalDirection);
}