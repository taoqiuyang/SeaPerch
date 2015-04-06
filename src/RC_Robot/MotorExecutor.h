#ifndef _MotorExecutor_H
#define _MotorExecutor_H

#include <Servo.h>
#include <PID_v1.h>
#include <SeaPerch_ControlSpecs.h>

class MotorExecutor {
public:
    explicit MotorExecutor();

    void initialize(const double aPressureBase);

    void execute(const ControlSpecs &controlSpecs, const double currentDepth);

private:
    PID myPID;

    double pidInput;
    double pidOutput;
    double pidSetpoint;
    double pressureBase;
    double pressureCap;

    Servo horizontalLeft;
    Servo horizontalRight;
    Servo verticalLeft;
    Servo verticalRight;

    void executeHorizontalMotors(const float normalizedX, const float normalizedY);

    void executeSpeedControlledVerticalMotor(const int speedInput);

    void executeDepthControlledVerticalMotor(const int depthInput, const double currentDepth);
};

#endif
