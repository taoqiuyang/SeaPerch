#ifndef _LCDDisplayer_H
#define _LCDDisplayer_H

#include <Arduino.h>
#include <LiquidCrystal.h>

//LCD key shield------------------------
LiquidCrystal lcd(8, 13, 9, 4, 5, 6, 7);
const int MAX_LINE = 2;
int NUM_KEYS = 5;
int adc_key_val[5] = {50, 200, 400, 600, 800};
int key = -1;
int oldkey = -1;
char msgs[5][16] = {"Right ",
        "Up    ",
        "Down  ",
        "Left  ",
        "Select"};

// Convert ADC value from keypad to key number
int getKey(unsigned int input) {
    for (int i = 0; i < NUM_KEYS; i++) {
        if (input < adc_key_val[i]) {
            return i;
        }
    }

    return -1;
}

void lcdDisplay(String message) {
    int oldLineID = -1;

    for (int i = 0; i < MAX_LINE; i++) {
        lcd.setCursor(0, i);
        int newLineID = message.indexOf('\n', oldLineID + 1);

        if (newLineID == -1) { // no more new lines
            lcd.print(message.substring(oldLineID + 1));
            return;
        } else {
            lcd.print(message.substring(oldLineID + 1, newLineID));

            if (newLineID == message.length() - 1) { // having a '\n' at the end, terminate
                return;
            } else {
                oldLineID = newLineID;
            }
        }
    }
}

void lcdWelcome() {
    //LCD welcome screen-------------
    lcd.begin(16, 2);
    lcd.clear();
    lcdDisplay("Gatech VIP\nSeaPerch Project");
    delay(2000);
    lcd.clear();
}

void detectKey() {
    //Detect key pressed on LCD sheild----------------------
    key = getKey(analogRead(0));
    if (key != oldkey)   // if keypress is detected
    {
        delay(50);  // wait for debounce time
        key = getKey(analogRead(0));    // convert sensor value into key press
        if (key != oldkey) {
            lcd.setCursor(0, 1);
            oldkey = key;
            if (key >= 0) {
                lcd.print(msgs[key]);
            }
        }
    }
}

#endif