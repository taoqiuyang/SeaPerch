#ifndef _BinaryUtils_H
#define _BinaryUtils_H

const int BYTE_MASK = 0xff;
const int INT_SIZE = sizeof(int);

void toBytes(int integer, char *buffer) {
    for (int i = 0; i < INT_SIZE; i++) {
        char currentByte = (integer >> (8 * i)) & BYTE_MASK;
        buffer[INT_SIZE - i - 1] = currentByte;
    }
}

int toInt(char *buffer) {
    int integer = 0;

    for (int i = 0; i < INT_SIZE; i++) {
        char currentByte = buffer[INT_SIZE - i - 1];
        integer |= (currentByte & BYTE_MASK) << (8 * i);
    }

    return integer;
}

#endif