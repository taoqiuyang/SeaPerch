#ifndef _KeyDector_H_
#define _KeyDector_H_

//int NUM_KEYS = 5;
//int adc_key_val[5] = {50, 200, 400, 600, 800};
//int key = -1;
//int oldkey = -1;
//char msgs[5][16] = {"Right ",
//                    "Up    ",
//                    "Down  ",
//                    "Left  ",
//                    "Select"};
//
//// Convert ADC value from keypad to key number
//int getKey(unsigned int input) {
//    for (int i = 0; i < NUM_KEYS; i++) {
//        if (input < adc_key_val[i]) {
//            return i;
//        }
//    }
//
//    return -1;
//}
//
//void detectKey() {
//    //Detect key pressed on LCD sheild----------------------
//    key = getKey(analogRead(0));
//    if (key != oldkey)   // if keypress is detected
//    {
//        delay(50);  // wait for debounce time
//        key = getKey(analogRead(0));    // convert sensor value into key press
//        if (key != oldkey) {
//            lcd.setCursor(0, 1);
//            oldkey = key;
//            if (key >= 0) {
//                lcd.print(msgs[key]);
//            }
//        }
//    }
//}

#endif
