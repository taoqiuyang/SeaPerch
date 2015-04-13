#ifndef _ControlMode_H
#define _ControlMode_H

enum DepthControlMode {
    AUTO_DEPTH, MANUAL_SPEED
};

enum SpeedControlMode {
    LIMIT_ON, LIMIT_OFF
};

extern const char* depthControlMsg[2];
extern const char* speedControlMsg[2];

#endif