#ifndef _MotorExecutor_H
#define _MotorExecutor_H

#include <Servo.h>
#include <PID_v1.h>
#include <SeaPerch_ControlSpecs.h>

class MotorExecutor {
public:
    explicit MotorExecutor();

    void emergencyBrake();

    void initialize(const double aPressureBase);

    void execute(const ControlSpecs &controlSpecs, const double currentDepth);

private:
    PID myPID;

    int maxSpeed;
    int minSpeed;

    double pidInput;
    double pidOutput;
    double pidSetpoint;
    double pressureBase;
    double pressureCap;

    Servo horizontalLeft;
    Servo horizontalRight;
    Servo verticalLeft;
    Servo verticalRight;

    void setSpeedBoundaries(SpeedControlMode speedMode);

    void executeSpeedControlledVerticalMotor(const int speedInput);

    void setVerticalSpeed(const int leftSpeed, const int rightSpeed);

    void setHorizontalSpeed(const int leftSpeed, const int rightSpeed);

    void executeHorizontalMotors(const float normalizedX, const float normalizedY);

    void executeDepthControlledVerticalMotor(const int depthInput, const double currentDepth);
};

#endif