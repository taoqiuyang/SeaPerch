#include "SeaPerch_BinaryUtils.h"
#include "SeaPerch_SerialUtils.h"

void SerialUtils::intToSerial(HardwareSerial &serial, const int toSend) {
    char buffer[INT_SIZE];

    BinaryUtils::toBytes(toSend, buffer);
    charBufferToSerial(serial, buffer, INT_SIZE);
}

void SerialUtils::floatToSerial(HardwareSerial &serial, const float toSend) {
    char buffer[FLOAT_SIZE];

    BinaryUtils::toBytes(toSend, buffer);
    charBufferToSerial(serial, buffer, FLOAT_SIZE);
}

void SerialUtils::charBufferToSerial(HardwareSerial &serial, const char *buffer, const int size) {
    for (int i = 0; i < size; i++) {
        serial.write(buffer[i]);
    }
}