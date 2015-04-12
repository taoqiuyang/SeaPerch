#ifndef _SeaPerch_AlgoUtils_H
#define _SeaPerch_AlgoUtils_H

class AlgoUtils {
public:
    static constexpr double map(int value, int fromLow, int fromHigh, double toLow, double toHigh);
    static constexpr double map(float value, int fromLow, int fromHigh, int toLow, int toHigh);

private:
    static constexpr double map(double value, double fromLow, double fromHigh, double toLow, double toHigh);
};

#endif