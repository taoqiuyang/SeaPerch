#ifndef _KeyDector_H_
#define _KeyDector_H_

#include "LCDDisplayer.h"

class KeyDetector {
public:
    KeyDetector(LCDDisplayer &aLCDDisplayer);

    void detectKey();

private:
    int oldkey;
    LCDDisplayer &lcdDisplayer;

    const int NUM_KEYS = 5;
    const int adc_key_val[5] = {50, 200, 400, 600, 800};
    const char keyNames[5][16] = {"Right ",
                                  "Up    ",
                                  "Down  ",
                                  "Left  ",
                                  "Select"};

    int getKey(unsigned int input) const;
};

#endif
