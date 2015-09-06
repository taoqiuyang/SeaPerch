#include <Arduino.h>

#include "ControlPin.h"
#include "KeyDetector.h"

int currentKey = NOT_DETECTED;

KeyDetector::KeyDetector() {
}

Key KeyDetector::detectKey() {
    //Detect key pressed on LCD sheild----------------------
    if (mapKey(analogRead(KEYPAD)) != currentKey) {  // if keypress is detected
        delay(50);  // wait for debounce time
        Key key = mapKey(analogRead(KEYPAD));    // convert sensor value into key press

        if (key != currentKey) {
            currentKey = key;
        }
    }
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