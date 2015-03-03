#include "SeaPerch_AlgoUtils.h"

double AlgoUtils::map(int value, int fromLow, int fromHigh, double toLow, double toHigh) {
    if (value <= fromLow) {
        return toLow;
    }

    if (value >= fromHigh) {
        return toHigh;
    }

    int fromRange = fromHigh - fromLow;
    double toRange = toHigh - toLow;

    return toLow + (value / (double)fromRange) * toRange;
}