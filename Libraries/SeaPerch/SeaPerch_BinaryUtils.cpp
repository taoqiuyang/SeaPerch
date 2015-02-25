#include "SeaPerch_BinaryUtils.h"

void BinaryUtils::toBytes(const int anInt, char *buffer) {
    char const *bytes = reinterpret_cast<char const *>(&anInt);
    bytecpy(buffer, bytes, INT_SIZE);
}

int BinaryUtils::toInt(const char *buffer) {
    char bytes[INT_SIZE];
    bytecpy(bytes, buffer, INT_SIZE);

    return *reinterpret_cast<int *>(bytes);
}

void BinaryUtils::bytecpy(char *dst, const char *src, int size) {
    for (int i = 0; i < size; i++) {
        dst[i] = src[i];
    }
}