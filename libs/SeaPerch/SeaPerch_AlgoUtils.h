#ifndef _SeaPerch_AlgoUtils_H
#define _SeaPerch_AlgoUtils_H

class AlgoUtils {
public:
    static double map(int value, int fromLow, int fromHigh, double toLow, double toHigh);
    static double map(float value, int fromLow, int fromHigh, int toLow, int toHigh);
    static float map(int value, int fromLow, int fromHigh, int toLow, int toHigh);

private:
    static double map(double value, double fromLow, double fromHigh, double toLow, double toHigh);
};

#endif