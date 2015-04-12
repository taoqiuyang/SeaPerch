#ifndef _LCDDisplayer_H
#define _LCDDisplayer_H

#include <LiquidCrystal.h>

class LCDDisplayer {
public:
    LCDDisplayer();

    void initialize();

    void display(String message);

private:
    const int MAX_LINE = 2;

    LiquidCrystal lcd;
};

#endif