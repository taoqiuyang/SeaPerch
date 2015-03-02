#ifndef _MotorExecutor_H
#define _MotorExecutor_H

#include <PID_v1.h>
#include <SeaPerch_ControlSpecs.h>
#include <Adafruit_MotorShield.h>
#include <utility/Adafruit_PWMServoDriver.h>

class MotorExecutor {
public:
    explicit MotorExecutor();

    void begin();

    void execute(const ControlSpecs &controlSpecs, const double currentDepth);

private:
    PID myPID;
    double Input_PID;
    double Output_PID;
    double Setpoint_PID;
    Adafruit_MotorShield AFMS;
    Adafruit_DCMotor *leftMotor;
    Adafruit_DCMotor *rightMotor;
    Adafruit_DCMotor *verticalMotor;

    void executeJoystickCommand(float normalizedX, float normalizedY);

    void executeSlidePotCommand(int slidePotValue);
};

#endif
