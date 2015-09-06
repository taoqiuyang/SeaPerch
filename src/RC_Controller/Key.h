#ifndef _Keys_H
#define _Keys_H

enum Key {
    NOT_DETECTED = -1, RIGHT = 0, UP = 1, DOWN = 2, LEFT = 3, SELECT =4
};

const int NUM_KEYS = 5;
const char keyNames[5][16] = {"Right ",
                              "Up    ",
                              "Down  ",
                              "Left  ",
                              "Select"};

extern int currentKey;

#endif
