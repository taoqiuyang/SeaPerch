#include "LCDDisplayer.h"

#include <Arduino.h>

LCDDisplayer::LCDDisplayer() : lcd(8, 13, 9, 4, 5, 6, 7) {

}

void LCDDisplayer::display(String message) {
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

void LCDDisplayer::initialize() {
    lcd.begin(16, 2);
    lcd.clear();
    display("Gatech VIP\nSeaPerch Project");
    delay(2000);
    lcd.clear();
}
