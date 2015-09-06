#ifndef _LCDDisplayer_H
#define _LCDDisplayer_H

#include <LiquidCrystal.h>
#include <SeaPerch_RobotData.h>

class LCDDisplayer {
public:
    LCDDisplayer(RobotData &robotData);

    void initialize();

    void refresh();

    void display(String message);

private:
    const int MAX_LINE = 2;

    static const int tableSize = 3;

    RobotData &robotData;

    String messageTable[tableSize];

    int displayRow;

    LiquidCrystal lcd;
};

#endif