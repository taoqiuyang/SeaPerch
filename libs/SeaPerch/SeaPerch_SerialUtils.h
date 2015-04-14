#ifndef SEAPERCH_SEAPERCH_SERIALUTILS_H
#define SEAPERCH_SEAPERCH_SERIALUTILS_H

#include <Arduino.h>

class SerialUtils {
public:
    static void intToSerial(HardwareSerial &serial, const int toSend);
    static void floatToSerial(HardwareSerial &serial, const float toSend);

private:
    static void charBufferToSerial(HardwareSerial &serial, const char *buffer, const int size);
};

#endif //SEAPERCH_SEAPERCH_SERIALUTILS_H
