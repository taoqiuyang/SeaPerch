#ifndef _ControlPin_H
#define _ControlPin_H

/*
=================PinValues================================================
RX2, TX2 --> Bluetooth module
A0  --> Key input from LCD button shield
A12 --> Battery Voltage
A13 --> Joystick Vertical
A14 --> Joystick Horizontal
A15 --> Slide Pot
D52 --> Joystick button
D53 --> Slide Pot LED (Active HIGH)

 */

enum ControlPin {
    KEYPAD = 0, JOYSTICK_VERTICAL = 13, JOYSTICK_HORIZONTAL = 14, SLIDE_POT = 15, JOYSTICK_PUSHBUTTON = 52
};

#endif