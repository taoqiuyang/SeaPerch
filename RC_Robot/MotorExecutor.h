#ifndef _MotorExecutor_H
#define _MotorExecutor_H

#include <SeaPerch_MotorSpecs.h>
#include <Adafruit_MotorShield.h>
#include <utility/Adafruit_PWMServoDriver.h>

class MotorExecutor {
public:
    explicit MotorExecutor();

    void begin();

    void execute(const MotorSpecs &motorSpecs) const;

private:
    Adafruit_MotorShield AFMS;
    Adafruit_DCMotor *leftMotor;
    Adafruit_DCMotor *rightMotor;
    Adafruit_DCMotor *upMotor;
};

#endif