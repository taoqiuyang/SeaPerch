#include <Arduino.h>
#include "KeyDetector.h"

KeyDetector::KeyDetector(LCDDisplayer &aLCDDisplayer) : lcdDisplayer(aLCDDisplayer), oldkey(-1) {
}

void KeyDetector::detectKey() {
    //Detect key pressed on LCD sheild----------------------
    if (getKey(analogRead(0)) != oldkey) {  // if keypress is detected
        delay(50);  // wait for debounce time
        int key = getKey(analogRead(0));    // convert sensor value into key press
        if (key != oldkey) {
            oldkey = key;
            if (key >= 0) {
                lcdDisplayer.display(keyNames[key]);
            }
        }
    }
}

// Convert ADC value from keypad to key number
int KeyDetector::getKey(unsigned int input) const {
    for (int i = 0; i < NUM_KEYS; i++) {
        if (input < adc_key_val[i]) {
            return i;
        }
    }

    return -1;
}