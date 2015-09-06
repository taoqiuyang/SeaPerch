#include "Key.h"
#include "LCDDisplayer.h"

#include <Arduino.h>

LCDDisplayer::LCDDisplayer(RobotData &robotData) : robotData(robotData), lcd(8, 13, 9, 4, 5, 6, 7) {
}

void LCDDisplayer::initialize() {
    lcd.begin(16, 2);
    lcd.clear();
    display("Gatech VIP\nSeaPerch Project");
    delay(2000);
    lcd.clear();
}

void LCDDisplayer::refresh() {
    if (currentKey == UP) {
        displayRow--;

        if (displayRow == -1) {
            displayRow = tableSize - 1;
        }

        Serial.println(displayRow);
        currentKey = NOT_DETECTED;
    } else if (currentKey == DOWN) {
        displayRow = (displayRow + 1) % tableSize;
        currentKey = NOT_DETECTED;
    }

    messageTable[0] = "roll: " + String(robotData.getOrientation().getRoll());
    messageTable[1] = "pitch: " + String(robotData.getOrientation().getPitch());
    messageTable[2] = "yaw: " + String(robotData.getOrientation().getYaw());

    display(messageTable[displayRow] + "\n" + messageTable[(displayRow + 1) % tableSize]);
}

void LCDDisplayer::display(String message) {
    lcd.clear();
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