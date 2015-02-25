#ifndef _SeaPerch_BinaryUtils_H
#define _SeaPerch_BinaryUtils_H

const int INT_SIZE = sizeof(int);
const int FLOAT_SIZE = sizeof(float);

class BinaryUtils {
public:
    static void toBytes(const int anInt, char *buffer);
    static void toBytes(const float aFloat, char *buffer);
    static int toInt(const char *buffer);
    static float toFloat(const char *buffer);

private:
    static void bytecpy(char *dst, const char *src, int size);
};

#endif