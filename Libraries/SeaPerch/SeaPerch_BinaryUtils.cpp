#include "SeaPerch_BinaryUtils.h"

void toBytes(const int anInt, char *buffer) {
    char const *bytes = reinterpret_cast<char const *>(&anInt);

    for (int i = 0; i < INT_SIZE; i++) {
        buffer[i] = bytes[i];
    }
}

int toInt(const char *buffer) {
    char bytes[INT_SIZE];

    for (int i = 0; i < INT_SIZE; i++) {
        bytes[i] = buffer[i];
    }

    return *reinterpret_cast<int *>(bytes);
}