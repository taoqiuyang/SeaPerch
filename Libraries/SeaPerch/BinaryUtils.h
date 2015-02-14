#ifndef _BinaryUtils_H
#define _BinaryUtils_H

const int BYTE_MASK = 0xff;
const int INT_SIZE = sizeof(int);

void toBytes(int integer, char *buffer);
int toInt(char *buffer);

#endif