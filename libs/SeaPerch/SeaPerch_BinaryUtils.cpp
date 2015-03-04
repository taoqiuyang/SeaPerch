#include "SeaPerch_BinaryUtils.h"

void BinaryUtils::toBytes(const int anInt, char *buffer) {
    char const *bytes = reinterpret_cast<char const *>(&anInt);
    bytecpy(buffer, bytes, INT_SIZE);
}

void BinaryUtils::toBytes(const float aFloat, char *buffer) {
    char const *bytes = reinterpret_cast<char const *>(&aFloat);
    bytecpy(buffer, bytes, FLOAT_SIZE);
}

int BinaryUtils::toInt(const char *buffer) {
    char bytes[INT_SIZE];
    bytecpy(bytes, buffer, INT_SIZE);

    return *reinterpret_cast<int *>(bytes);
}

float BinaryUtils::toFloat(const char *buffer) {
    char bytes[FLOAT_SIZE];
    bytecpy(bytes, buffer, FLOAT_SIZE);

    return *reinterpret_cast<float *>(bytes);
}

void BinaryUtils::bytecpy(char *dst, const char *src, int size) {
    for (int i = 0; i < size; i++) {
        dst[i] = src[i];
    }
}