#ifndef _SeaPerch_BinaryUtils_H
#define _SeaPerch_BinaryUtils_H

const int INT_SIZE = sizeof(int);
const int DOUBLE_SIZE = sizeof(short);

void toBytes(const int anInt, char *buffer);
int toInt(const char * buffer);

#endif