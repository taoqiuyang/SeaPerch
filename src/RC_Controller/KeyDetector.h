#ifndef _KeyDector_H_
#define _KeyDector_H_

#include "Key.h"
#include "LCDDisplayer.h"

class KeyDetector {
public:
    KeyDetector(LCDDisplayer &aLCDDisplayer);

    Key detectKey();

private:
    Key oldkey;
    LCDDisplayer &lcdDisplayer;
    const int adc_key_val[5] = {50, 200, 400, 600, 800};

    Key getKey(unsigned int input) const;
};

#endif
