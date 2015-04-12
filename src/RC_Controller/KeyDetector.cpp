#include <Arduino.h>

#include "ControlPin.h"
#include "KeyDetector.h"

KeyDetector::KeyDetector() {
}

Key KeyDetector::detectKey() {
    static Key oldkey = NOT_DETECTED;

    //Detect key pressed on LCD sheild----------------------
    if (mapKey(analogRead(KEYPAD)) != oldkey) {  // if keypress is detected
        delay(50);  // wait for debounce time
        Key key = mapKey(analogRead(KEYPAD));    // convert sensor value into key press

        if (key != oldkey) {
            oldkey = key;
            if (key != NOT_DETECTED) {
                return key;
            }
        }
    }

    return NOT_DETECTED;
}

// Convert ADC value from keypad to key number
Key KeyDetector::mapKey(unsigned int input) const {
    for (int i = 0; i < NUM_KEYS; i++) {
        if (input < adc_key_val[i]) {
            return static_cast<Key>(i);
        }
    }

    return NOT_DETECTED;
}