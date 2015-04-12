#include "SeaPerch_AlgoUtils.h"

constexpr double AlgoUtils::map(int value, int fromLow, int fromHigh, double toLow, double toHigh) {
    return map((double)value, (double)fromLow, (double)fromHigh, toLow, toHigh);
}

constexpr double AlgoUtils::map(float value, int fromLow, int fromHigh, int toLow, int toHigh) {
    return map((double)value, (double)fromLow, (double)fromHigh, (double)toLow, (double)toHigh);
}

constexpr double AlgoUtils::map(double value, double fromLow, double fromHigh, double toLow, double toHigh) {
    if (value <= fromLow) {
        return toLow;
    }

    if (value >= fromHigh) {
        return toHigh;
    }

    double fromRange = fromHigh - fromLow;
    double toRange = toHigh - toLow;

    return toLow + ((value - fromLow) / fromRange) * toRange;
}