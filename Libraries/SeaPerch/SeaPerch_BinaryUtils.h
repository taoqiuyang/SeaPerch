#ifndef _SeaPerch_BinaryUtils_H
#define _SeaPerch_BinaryUtils_H

const int INT_SIZE = sizeof(int);
const int DOUBLE_SIZE = sizeof(short);

class BinaryUtils {
public:
    static void toBytes(const int anInt, char *buffer);
//    static void toBytes(const float aFloat, char *buffer);
    static int toInt(const char *buffer);
//    static int toFloat(const char *buffer);
};

#endif