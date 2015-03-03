#ifndef _MotorExecutor_H
#define _MotorExecutor_H

#include <PID_v1.h>
#include <SeaPerch_ControlSpecs.h>
#include <Adafruit_MotorShield.h>
#include <utility/Adafruit_PWMServoDriver.h>

class MotorExecutor {
public:
    explicit MotorExecutor();

    void initialize(const double aPressureBaseline);

    void execute(const ControlSpecs &controlSpecs, const double currentDepth);

private:
    PID myPID;
    double pidInput;
    double pidOutput;
    double pidSetpoint;
    double pressureBaseline;
    Adafruit_MotorShield AFMS;
    Adafruit_DCMotor *leftMotor;
    Adafruit_DCMotor *rightMotor;
    Adafruit_DCMotor *verticalMotor;

    void executeHorizontalMotors(const float normalizedX, const float normalizedY);

    void executeSpeedControlledVerticalMotor(const int speedInput);

    void executeDepthControlledVerticalMotor(const int depthInput, const double currentDepth);
};

#endif
