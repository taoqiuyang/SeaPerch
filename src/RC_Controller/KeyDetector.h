#ifndef _KeyDector_H_
#define _KeyDector_H_

#include "Key.h"

class KeyDetector {
public:
    KeyDetector();

    Key detectKey();

private:
    const int adc_key_val[5] = {50, 200, 400, 600, 800};

    Key mapKey(unsigned int input) const;
};

#endif
